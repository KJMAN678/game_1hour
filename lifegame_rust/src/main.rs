use std::{thread, time::Duration};

const FIELD_WIDTH: usize = 100;
const FIELD_HEIGHT: usize = 50;
const PATTERN_WIDTH: usize = 10;
const PATTERN_HEIGHT: usize = 8;

// 画面の描画を実行
fn draw_field(field: Vec<Vec<bool>>) {

    print!("{}[2J", 27 as char); // コンソール画面をクリア

    for _y in 0..FIELD_HEIGHT {
        for _x in 0..FIELD_WIDTH {
            if field[_y][_x] {
                print!("■");
            } else {
                print!(" ");
            }
        }
        println!();
    }
}

// 対象のセルと隣接する生きたセルの数を取得する
fn get_living_cells_count(_x: usize, _y: usize, field: Vec<Vec<bool>>) -> usize {

    let mut count: usize = 0;

    for y in 0.._y {

        for x in 0.._x {
            if field[y][x] {
                count += 1;
            }
        }

    }

    return count;
}

// 1ステップ分のシミュレーションを実行する関数を宣言
fn step_simulation(field: Vec<Vec<bool>>) -> Vec<Vec<bool>> {

    // 次の世代のフィールドを宣言
    let mut next_field: Vec<Vec<bool>> = vec![vec![Default::default(); FIELD_WIDTH]; FIELD_HEIGHT];

    for y in 0..FIELD_HEIGHT {

        for x in 0..FIELD_WIDTH {

            let living_cell_count: usize = get_living_cells_count(x, y, field.to_vec());

            if living_cell_count <= 1 {
                // 対象のセルを死滅させる
                next_field[y][x] = false;
            } else if living_cell_count == 2 {
                // 現状維持
                next_field[y][x] = field[y][x]
            } else if living_cell_count == 3 {
                // 対象のセルを誕生/生存させる
                next_field[y][x] = true;
            } else {
                // 対象のセルを死滅させる
                next_field[y][x] = false;
            }
        }
    }

    return next_field;

}


fn pattern_transfer(_dest_x: usize, _dest_y: usize, 
                    _src_width: usize, _src_height: usize, 
                    pattern: Vec<Vec<bool>>,
                    mut field: Vec<Vec<bool>>,
                ) -> Vec<Vec<bool>> {

    for y in 0.._src_height {
        for x in 0.._src_width {
            field[_dest_y + y][_dest_x + x] = pattern[y][x];
        }
    }

    return field;
}

fn main() {

    let mut field: Vec<Vec<bool>> = vec![vec![Default::default(); FIELD_WIDTH]; FIELD_HEIGHT];

    let pattern: Vec<Vec<bool>> = vec![
        vec![false, false, false, false, false, false, false, false, false, false],
        vec![false, false, false, false, false, false, false, true,  false, false],
        vec![false, false, false, false, false, true,  false, true,  true,  false],
        vec![false, false, false, false, false, true,  false, true,  false, false],
        vec![false, false, false, false, false, true,  false, false, false, false],
        vec![false, false, false, true,  false, false, false, false, false, false],
        vec![false, true,  false, true,  false, false, false, false, false, false],
        vec![false, false, false, false, false, false, false, false, false, false]
    ];

    field = pattern_transfer(
        FIELD_WIDTH / 2 - PATTERN_WIDTH / 2,
        FIELD_HEIGHT / 2 - PATTERN_HEIGHT / 2,
        PATTERN_WIDTH,
        PATTERN_HEIGHT,
        pattern,
        field
    ).to_vec();

    loop {
        draw_field(field.to_vec());
        field = step_simulation(field.to_vec());
        thread::sleep(Duration::from_millis(1000));
    }

}
