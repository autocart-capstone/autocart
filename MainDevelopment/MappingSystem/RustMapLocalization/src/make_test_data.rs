use parry2d::{
    na::{Point2, Vector2},
    query::RayCast,
    shape::Polyline,
};

#[derive(serde::Serialize, serde::Deserialize)]
pub struct Structures {
    s1: Polyline,
    s2: Polyline,
    max_x: f32,
    max_y: f32,
}

impl Structures {
    pub fn generate() -> Self {
        let max_x = STRUCT1_POINTS
            .iter()
            .chain(STRUCT2_POINTS.iter())
            .map(|p| p[0])
            .max_by(|p1, p2| p1.total_cmp(p2))
            .unwrap();
        let max_y = STRUCT1_POINTS
            .iter()
            .chain(STRUCT2_POINTS.iter())
            .map(|p| p[1])
            .max_by(|p1, p2| p1.total_cmp(p2))
            .unwrap();

        Self {
            s1: parry2d::shape::Polyline::new(
                STRUCT1_POINTS
                    .iter()
                    .copied()
                    .rev() // make CCW
                    .map(|p| p.into())
                    .collect(),
                None,
            ),
            s2: parry2d::shape::Polyline::new(
                STRUCT2_POINTS
                    .iter()
                    .copied()
                    .rev() // make CCW
                    .map(|p| p.into())
                    .collect(),
                None,
            ),
            max_x,
            max_y,
        }
    }
}

use rand::seq::SliceRandom;
use serde_big_array::BigArray;

use crate::{Point, PolarPoint, Vector};

#[derive(serde::Serialize, serde::Deserialize, Clone)]
pub struct TestPoint {
    pub pos: Point,
    #[serde(with = "BigArray")]
    pub measurements: [f32; 36],
}

#[derive(serde::Serialize, serde::Deserialize)]
pub struct TestData {
    pub structs: Structures,
    pub test_points: Vec<TestPoint>,
}

impl TestData {
    pub fn generate() -> Self {
        let structs = Structures::generate();

        let space = 0.1;

        let mut out = Vec::new();
        let max_x = STRUCT1_POINTS
            .iter()
            .chain(STRUCT2_POINTS.iter())
            .map(|p| p[0])
            .max_by(|p1, p2| p1.total_cmp(p2))
            .unwrap();
        let max_y = STRUCT1_POINTS
            .iter()
            .chain(STRUCT2_POINTS.iter())
            .map(|p| p[1])
            .max_by(|p1, p2| p1.total_cmp(p2))
            .unwrap();
        let max_x_int = (max_x / space).ceil() as i32;
        let max_y_int = (max_y / space).ceil() as i32;
        for x in (0..=max_x_int).map(|i| i as f32 * space) {
            for y in (0..=max_y_int).map(|i| i as f32 * space) {
                let pt = Point2::new(x, y);

                let in_s1 = structs
                    .s1
                    .project_local_point_assuming_solid_interior_ccw(pt)
                    .0
                    .is_inside;
                let in_s2 = structs
                    .s2
                    .project_local_point_assuming_solid_interior_ccw(pt)
                    .0
                    .is_inside;
                if in_s1 && !in_s2 {
                    out.push(TestPoint {
                        pos: pt,
                        measurements: get_lidar_measures_at_pos(pt, &structs.s1, &structs.s2),
                    });
                }
            }
        }

        Self {
            structs,
            test_points: out,
        }
    }

    pub fn plot(
        &self,
        plot_structs: bool,
        plot_tests_positions: bool,
        plot_1_random_test_pos_with_rays: bool,
        plot_point: Option<(Point, Vec<PolarPoint>)>,
    ) {
        use plotters::prelude::*;
        let root = BitMapBackend::new("img.png", (640, 480)).into_drawing_area();
        root.fill(&WHITE).unwrap();

        let mut chart = ChartBuilder::on(&root)
            .caption("Map", ("sans-serif", 50).into_font())
            .margin(5)
            .x_label_area_size(30)
            .y_label_area_size(30)
            .build_cartesian_2d(0f32..self.structs.max_x, 0f32..self.structs.max_y)
            .unwrap();
        if plot_structs {
            chart
                .draw_series(LineSeries::new(
                    self.structs
                        .s1
                        .segments()
                        .flat_map(|s| [s.a, s.b])
                        .map(|p| (p.x, p.y)),
                    &RED,
                ))
                .unwrap();
            chart
                .draw_series(LineSeries::new(
                    self.structs
                        .s2
                        .segments()
                        .flat_map(|s| [s.a, s.b])
                        .map(|p| (p.x, p.y)),
                    &BLUE,
                ))
                .unwrap();
        }

        if plot_tests_positions {
            chart
                .draw_series(
                    self.test_points
                        .iter()
                        .map(|p| Pixel::new((p.pos.x, p.pos.y), GREEN)),
                )
                .unwrap();
        }

        if plot_1_random_test_pos_with_rays {
            let mut rng = rand::thread_rng();
            let pos = self
                .test_points
                .as_slice()
                .choose(&mut rng)
                .unwrap()
                .clone();
            for (i, measure) in pos.measurements.into_iter().enumerate() {
                let p1 = pos.pos;

                let angle = (i as f32 * 10.0).to_radians();
                let dir = Vector::new(angle.cos(), angle.sin());

                let p2 = p1 + dir * measure;
                chart
                    .draw_series(LineSeries::new([(p1.x, p1.y), (p2.x, p2.y)], &GREEN))
                    .unwrap();
            }
        }

        if let Some((pos, polar_points)) = plot_point {
            for point in polar_points.into_iter() {
                let angle = point.angle_deg.to_radians();
                let dir = Vector::new(angle.cos(), angle.sin());

                let p1 = pos;
                let p2 = pos + dir * point.distance;
                chart
                    .draw_series(LineSeries::new([(p1.x, p1.y), (p2.x, p2.y)], &GREEN))
                    .unwrap();
            }
        }

        root.present().unwrap();
    }
}

fn get_lidar_measures_at_pos(pos: Point, struct1: &Polyline, struct2: &Polyline) -> [f32; 36] {
    std::array::from_fn(|i| {
        let angle = (i as f32 * 10.0).to_radians();
        let dir = Vector::new(angle.cos(), angle.sin());
        let ray = parry2d::query::Ray::new(pos, dir);
        let p1 = struct1
            .cast_local_ray(&ray, f32::MAX, false)
            .unwrap_or(f32::MAX);
        let p2 = struct2
            .cast_local_ray(&ray, f32::MAX, false)
            .unwrap_or(f32::MAX);

        f32::min(p1, p2)
    })
}

pub const STRUCT1_POINTS: [[f32; 2]; 180] = [
    [00.00, 00.11],
    [-0.13, 00.11],
    [-0.13, 00.28],
    [-0.24, 00.28],
    [-0.24, 02.06],
    [-0.11, 02.06],
    [-0.11, 02.24],
    [00.00, 02.24],
    [02.56, 02.24],
    [02.56, 02.37],
    [03.44, 02.37],
    [03.44, 02.24],
    [03.96, 02.24],
    [03.96, 06.69],
    [03.84, 06.69],
    [03.84, 07.57],
    [03.96, 07.57],
    [03.96, 12.02],
    [03.84, 12.02],
    [03.84, 12.90],
    [03.96, 12.90],
    [03.96, 14.34],
    [03.84, 14.34],
    [03.84, 15.22],
    [03.96, 15.22],
    [03.96, 16.75],
    [03.84, 16.75],
    [03.84, 17.63],
    [03.96, 17.63],
    [03.96, 17.73],
    [03.88, 17.73],
    [03.88, 17.89],
    [03.96, 17.89],
    [03.96, 20.19],
    [05.07, 20.19],
    [05.07, 20.27],
    [05.23, 20.27],
    [05.23, 20.19],
    [05.79, 20.19],
    [05.79, 19.25],
    [16.31, 19.25],
    [16.31, 20.00],
    [17.42, 20.00],
    [17.42, 20.08],
    [17.58, 20.08],
    [17.58, 20.00],
    [17.63, 20.00],
    [17.63, 19.25],
    [24.52, 19.25],
    [24.52, 20.78],
    [24.02, 20.78],
    [24.02, 23.45],
    [18.96, 23.45],
    [18.96, 23.34],
    [18.08, 23.34],
    [18.08, 23.45],
    [17.63, 23.45],
    [17.63, 20.38],
    [17.55, 20.38],
    [17.55, 20.11],
    [17.38, 20.11],
    [17.38, 20.38],
    [17.33, 20.38],
    [17.33, 20.11],
    [16.35, 20.11],
    [16.35, 20.38],
    [16.31, 20.38],
    [16.31, 23.45],
    [16.01, 23.45],
    [16.01, 23.34],
    [15.13, 23.34],
    [15.13, 23.45],
    [12.53, 23.45],
    [12.53, 23.34],
    [11.65, 23.34],
    [11.65, 23.45],
    [08.65, 23.45],
    [08.65, 23.67],
    [08.54, 23.67],
    [08.54, 24.65],
    [08.65, 24.65],
    [08.65, 25.51],
    [08.73, 25.51],
    [08.73, 25.62],
    [09.61, 25.62],
    [09.61, 25.51],
    [11.72, 25.51],
    [11.72, 25.62],
    [12.60, 25.62],
    [12.60, 25.51],
    [13.24, 25.51],
    [13.24, 24.90],
    [14.45, 24.90],
    [14.45, 25.51],
    [14.65, 25.51],
    [14.65, 25.62],
    [15.53, 25.62],
    [15.53, 25.51],
    [17.51, 25.51],
    [17.51, 25.62],
    [18.39, 25.62],
    [18.39, 25.51],
    [18.89, 25.51],
    [18.89, 25.62],
    [19.77, 25.62],
    [19.77, 25.51],
    [23.22, 25.51],
    [23.22, 25.62],
    [24.10, 25.62],
    [24.10, 25.51],
    [24.60, 25.51],
    [24.60, 25.62],
    [25.48, 25.62],
    [25.48, 25.51],
    [28.93, 25.51],
    [28.93, 25.62],
    [29.81, 25.62],
    [29.81, 25.51],
    [30.01, 25.51],
    [30.01, 23.51],
    [25.86, 23.51],
    [25.86, 19.25],
    [26.66, 19.25],
    [26.66, 19.36],
    [27.54, 19.36],
    [27.54, 19.25],
    [27.77, 19.25],
    [27.77, 19.61],
    [28.39, 19.61],
    [28.38, 19.25],
    [33.59, 19.25],
    [33.59, 16.82],
    [25.97, 16.82],
    [25.97, 06.00],
    [26.08, 06.00],
    [26.08, 05.80],
    [25.97, 05.80],
    [25.97, 05.72],
    [26.08, 05.72],
    [26.08, 04.84],
    [25.97, 04.84],
    [25.97, 00.11],
    [25.97, 00.11],
    [25.87, 00.11],
    [25.87, 00.00],
    [24.99, 00.00],
    [24.99, 00.11],
    [24.89, 00.11],
    [24.89, 00.00],
    [24.31, 00.00],
    [24.31, 00.11],
    [21.26, 00.11],
    [21.26, 00.00],
    [20.38, 00.00],
    [20.38, 00.11],
    [17.50, 00.11],
    [17.50, 00.00],
    [16.62, 00.00],
    [16.62, 00.11],
    [13.78, 00.11],
    [13.78, 00.00],
    [12.90, 00.00],
    [12.90, 00.11],
    [10.24, 00.11],
    [10.24, 00.00],
    [09.36, 00.00],
    [09.36, 00.11],
    [07.15, 00.11],
    [07.15, 00.00],
    [06.27, 00.00],
    [06.27, 00.11],
    [04.04, 00.11],
    [04.04, 00.00],
    [03.16, 00.00],
    [03.16, 00.11],
    [01.00, 00.11],
    [01.00, 00.00],
    [00.12, 00.00],
    [00.12, 00.11],
    [00.00, 00.11],
];

pub const STRUCT2_POINTS: [[f32; 2]; 69] = [
    [05.81, 01.94],
    [05.81, 03.54],
    [05.94, 03.54],
    [05.94, 04.50],
    [05.81, 04.50],
    [05.81, 04.63],
    [05.94, 04.63],
    [05.94, 05.59],
    [05.81, 05.59],
    [05.81, 05.72],
    [05.94, 05.72],
    [05.94, 06.68],
    [05.81, 06.68],
    [05.81, 07.40],
    [05.94, 07.40],
    [05.94, 08.36],
    [05.81, 08.36],
    [05.81, 08.49],
    [05.94, 08.49],
    [05.94, 09.45],
    [05.81, 09.45],
    [05.81, 10.18],
    [05.94, 10.18],
    [05.94, 11.14],
    [05.81, 11.14],
    [05.81, 11.27],
    [05.94, 11.27],
    [05.94, 12.23],
    [05.81, 12.23],
    [05.81, 12.36],
    [05.94, 12.36],
    [05.94, 13.32],
    [05.81, 13.32],
    [05.81, 14.29],
    [06.55, 14.29],
    [06.55, 15.31],
    [05.81, 15.31],
    [05.81, 17.51],
    [13.86, 17.51],
    [13.86, 16.74],
    [14.86, 16.74],
    [14.86, 17.51],
    [24.14, 17.51],
    [24.14, 15.95],
    [23.39, 15.95],
    [23.39, 15.90],
    [23.31, 15.90],
    [23.31, 15.74],
    [23.39, 15.74],
    [23.39, 14.64],
    [24.14, 14.64],
    [24.14, 01.94],
    [22.64, 01.94],
    [22.64, 02.69],
    [21.62, 02.69],
    [21.62, 01.94],
    [17.79, 01.94],
    [17.79, 02.05],
    [16.09, 02.05],
    [16.09, 01.94],
    [15.02, 01.94],
    [15.02, 02.07],
    [14.14, 02.07],
    [14.14, 01.94],
    [14.04, 01.94],
    [14.04, 02.07],
    [13.91, 02.07],
    [13.91, 01.94],
    [05.81, 01.94],
];
