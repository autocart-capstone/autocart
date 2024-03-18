use itertools::Itertools;

use crate::PolarPoint;

pub fn get_points_from_file(path: &str) -> Vec<PolarPoint> {
    let string = std::fs::read_to_string(path).unwrap();
    let mut out = string
        .lines()
        .skip(6)
        .flat_map(|line| {
            let mut it = line.trim_start_matches('S').split_ascii_whitespace();
            it.next();
            let theta = it.next().unwrap().parse::<f32>().unwrap();
            let theta = 360.0 - theta;
            it.next();
            let distance = it.next().unwrap().parse::<f32>().unwrap();
            let distance = distance / 1000.0;
            it.next();
            let quality = it.next().unwrap().parse::<u32>().unwrap();
            if quality > 0 {
                Some(PolarPoint {
                    angle_deg: theta,
                    distance,
                })
            } else {
                None
            }
        })
        .collect_vec();
    out
}
