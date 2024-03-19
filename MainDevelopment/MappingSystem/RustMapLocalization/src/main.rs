use std::{
    io::{Read, Write},
    net::TcpStream,
};

use itertools::Itertools;
use parry2d::na::{Point2, Vector2};
use plotters::coord::ranged1d::IntoSegmentedCoord;

use crate::make_test_data::TestData;

pub mod get_points_from_file;
pub mod make_test_data;

type Point = Point2<f32>;
type Vector = Vector2<f32>;

const TEST_DATA_PATH: &str = "test_data.bin";

#[derive(Debug, Clone)]
pub struct PolarPoint {
    angle_deg: f32,
    /// In meters
    distance: f32,
}

#[derive(Clone, Debug)]
pub struct AvgPolarPoint {
    count: u32,
    distance: f32,
}

impl AvgPolarPoint {
    pub fn from_points(points: &[PolarPoint]) -> [Self; 36] {
        const ANGLE_AVG_RANGE: f32 = 10.0;
        std::array::from_fn(|i| {
            let center_angle_deg = i as f32 * ANGLE_AVG_RANGE;
            let (count, distance_acc) = points
                .iter()
                .filter(|p| {
                    [
                        f32::abs(p.angle_deg - center_angle_deg),
                        f32::abs(p.angle_deg - center_angle_deg - 360.0),
                        f32::abs(p.angle_deg - center_angle_deg + 360.0),
                    ]
                    .into_iter()
                    .min_by(f32::total_cmp)
                    .unwrap()
                        <= ANGLE_AVG_RANGE / 2.0
                })
                .fold((0, 0.0), |(count_acc, distance_acc), e| {
                    (count_acc + 1, distance_acc + e.distance)
                });
            let avg_distance = if count == 0 {
                0.0
            } else {
                distance_acc / count as f32
            };
            AvgPolarPoint {
                count,
                distance: avg_distance,
            }
        })
    }
}

pub fn find_position(
    points: &[PolarPoint],
    data: &TestData,
    last_pos: Option<(Point, f32)>,
) -> (Point, f32, f32) {
    let start_instant = std::time::Instant::now();
    let avg_points: [AvgPolarPoint; 36] = AvgPolarPoint::from_points(points);

    let (min_point_position, metric, shift) = last_pos
        .map(|(_, angle)| {
            let ind = (angle / 10.0) as i32;
            ind - 9..ind + 9
        })
        .unwrap_or_else(|| 0..36)
        .flat_map(|shift| {
            let mut points_shifted = avg_points.clone();
            if shift < 0 {
                points_shifted.rotate_right(shift.unsigned_abs() as usize);
            } else {
                points_shifted.rotate_left(shift as usize);
            }
            //dbg!(&points_shifted);
            data.test_points
                .iter()
                .filter(|test_point| match last_pos {
                    Some((p, _)) => (test_point.pos - p).magnitude() < 0.5, // only points close to last pos go through
                    None => true,                                           // all points go through
                })
                .map(move |test_point| {
                    let metric = test_point
                        .measurements
                        .iter()
                        .zip(points_shifted.iter())
                        .fold(0.0, |acc, (test_distance, measurement)| {
                            acc + f32::abs(test_distance - measurement.distance)
                                * measurement.count as f32
                        });
                    (test_point.pos, metric, shift)
                })
        })
        .min_by(|a, b| {
            //dbg!(a, b);
            a.1.partial_cmp(&b.1).unwrap()
        })
        .unwrap();
    let angle = shift as f32 * 10.0; // in degrees
    dbg!(start_instant.elapsed().as_secs_f64());
    (min_point_position, metric, angle)
}

fn main() {
    let b = std::fs::read(TEST_DATA_PATH).unwrap();
    let data = bincode::deserialize::<TestData>(&b).unwrap();

    let args = std::env::args().collect_vec();
    let addr = &args[1];
    let mut stream = TcpStream::connect(addr).unwrap();

    let mut last_pos = None;

    loop {
        let mut size_buf: [u8; 4] = Default::default();
        stream.read_exact(&mut size_buf).unwrap();
        let size = u32::from_le_bytes(size_buf);
        //dbg!(size);
        let mut data_buf = vec![0_u8; size as usize * 4];
        stream.read_exact(&mut data_buf).unwrap();
        let points = (0..data_buf.len())
            .step_by(8)
            .map(|i| PolarPoint {
                angle_deg: f32::from_le_bytes(data_buf[i..i + 4].try_into().unwrap()),
                distance: f32::from_le_bytes(data_buf[i + 4..i + 8].try_into().unwrap()) / 1000.0,
            })
            .collect_vec();
        //dbg!(&points);
        let (min_point_position, metric, angle) = find_position(&points, &data, last_pos);
        dbg!(min_point_position, metric, angle);
        stream
            .write_all(format!("{} {}", min_point_position.x, min_point_position.y).as_bytes())
            .unwrap();
        last_pos = Some((min_point_position, angle));

        let mut polar_points_rotated = points.clone();
        for p in polar_points_rotated.iter_mut() {
            p.angle_deg += angle;
        }
        data.plot(
            "img",
            true,
            false,
            false,
            Some((min_point_position, polar_points_rotated)),
        );
    }
}

#[cfg(test)]
mod tests {
    use std::{path::PathBuf, str::FromStr};

    use crate::{
        find_position, get_points_from_file::get_points_from_file, make_test_data::TestData,
        TEST_DATA_PATH,
    };

    #[test]
    fn plot_random_testpoint() {
        let b = std::fs::read(TEST_DATA_PATH).unwrap();
        let data = bincode::deserialize::<TestData>(&b).unwrap();
        data.plot("random_testpoint", true, false, true, None);
    }

    #[test]
    fn plot_all_testpoint() {
        let b = std::fs::read(TEST_DATA_PATH).unwrap();
        let data = bincode::deserialize::<TestData>(&b).unwrap();
        data.plot("testpoints", true, true, false, None);
    }

    #[test]
    fn test475() {
        let b = std::fs::read(TEST_DATA_PATH).unwrap();
        let data = bincode::deserialize::<TestData>(&b).unwrap();

        //data.plot(true, false, true, None);
        let path = "../Matlab + txt files/test475.txt";

        let points = get_points_from_file(path);

        //for p in points.iter_mut() {
        //    p.angle_deg = (p.angle_deg + 20.0) % 360.0;
        //}

        let less_points = &points; //[0..1200];
                                   //dbg!(&points);

        let (min_point_position, metric, angle) = find_position(less_points, &data, None);

        dbg!(min_point_position, metric, angle);

        let mut polar_points_rotated = less_points.to_owned();
        for p in polar_points_rotated.iter_mut() {
            p.angle_deg -= angle;
        }
        dbg!(polar_points_rotated.len());

        let path = PathBuf::from_str(path).unwrap();

        data.plot(
            path.file_name().unwrap().to_str().unwrap(),
            true,
            false,
            false,
            Some((min_point_position, polar_points_rotated)),
        );

        //let bytes = bincode::serialize(&data).unwrap();
        //let mut file = File::create("foo.txt")?;
        //file.write_all(b"Hello, world!")?;
    }

    #[test]
    fn write_data_to_file() {
        let data = TestData::generate();
        let bytes = bincode::serialize(&data).unwrap();
        let mut file = std::fs::File::create(crate::TEST_DATA_PATH).unwrap();
        std::io::Write::write_all(&mut file, &bytes).unwrap();
    }
}
