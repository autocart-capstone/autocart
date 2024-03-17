use parry2d::na::{Point2, Vector2};

use crate::{get_points_from_file::get_points_from_file, make_test_data::TestData};

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

#[derive(Clone)]
pub struct AvgPolarPoint {
    count: u32,
    distance: f32,
}

pub fn find_position(points: &[PolarPoint], data: &TestData) -> (Point, f32, f32) {
    let avg_points: [AvgPolarPoint; 36] = std::array::from_fn(|i| {
        let center_angle_deg = (i * 10) as f32;
        let mut count = 0;
        let distance_acc = points
            .iter()
            .filter(|p| f32::abs(p.angle_deg - center_angle_deg) < 10.0)
            .fold(0.0, |acc, e| {
                count += 1;
                acc + e.distance
            });
        AvgPolarPoint {
            count,
            distance: distance_acc / count as f32,
        }
    });

    let (min_point_position, metric, shift) = (0..36)
        .flat_map(|shift| {
            let mut points_shifted = avg_points.clone();
            points_shifted.rotate_right(shift);
            data.test_points.iter().map(move |test_point| {
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
        .min_by(|a, b| a.1.total_cmp(&b.1))
        .unwrap();
    let angle = shift as f32 * 10.0;
    (min_point_position, metric, angle)
}

fn main() {
    let b = std::fs::read(TEST_DATA_PATH).unwrap();
    let data = bincode::deserialize::<TestData>(&b).unwrap();

    //data.plot(true, false, true, None);

    let points = get_points_from_file("../Matlab + txt files/test475.txt");
    //dbg!(&points);

    let (min_point_position, metric, angle) = find_position(&points, &data);

    dbg!(min_point_position, metric, angle);

    let mut polar_points_rotated = points.clone();
    for p in polar_points_rotated.iter_mut() {
        p.angle_deg += angle;
    }

    data.plot(
        true,
        false,
        false,
        Some((min_point_position, polar_points_rotated)),
    );

    //let bytes = bincode::serialize(&data).unwrap();
    //let mut file = File::create("foo.txt")?;
    //file.write_all(b"Hello, world!")?;
}

#[cfg(test)]
mod tests {
    use crate::{find_position, get_points_from_file, make_test_data::TestData, TEST_DATA_PATH};

    #[test]
    fn test475() {
        let b = std::fs::read(TEST_DATA_PATH).unwrap();
        let data = bincode::deserialize::<TestData>(&b).unwrap();

        //data.plot(true, false, true, None);

        let points = get_points_from_file("../Matlab + txt files/test475.txt");
        //dbg!(&points);

        let (min_point_position, metric, angle) = find_position(&points, &data);

        dbg!(min_point_position, metric, angle);

        let mut polar_points_rotated = points.clone();
        for p in polar_points_rotated.iter_mut() {
            p.angle_deg += angle;
        }

        data.plot(
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
