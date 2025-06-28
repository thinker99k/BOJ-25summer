const fs = require('fs');

function crossproduct(p1, p2) {
    // p1, p2는 xyz-plane의 부분공간 xy-plane에 있기에, z좌표는 0;

    // 순서대로 x, y, z좌표
    const arr = [
        [p1[0], p1[1], 0],
        [p2[0], p2[1], 0]
    ]

    let ret = [];

    const first = 0;
    const second = 1;

    const x_pos = 0;
    const y_pos = 1;
    const z_pos = 2;

    // 외적 x좌표 : p1.y * p2.z - p1.z * p2.y
    ret.push(
        arr[first][y_pos] * arr[second][z_pos] -
        arr[first][z_pos] * arr[second][y_pos]);
    // 외적 y좌표 : p1.x * p2.z - p1.z * p2.x
    ret.push(
        arr[first][x_pos] * arr[second][z_pos] -
        arr[first][z_pos] * arr[second][x_pos]);
    // 외적 z좌표 : p1.x * p2.y - p1.y * p2.x
    ret.push(
        arr[first][x_pos] * arr[second][y_pos] -
        arr[first][y_pos] * arr[second][x_pos]);

    return ret;
}

function ccw(p1, p2, p3) {
    // 들어오는 점 : 선분a, 선분a, 선분b
    const vector1 = [p1[0] - p3[0], p1[1] - p3[1]];
    const vector2 = [p2[0] - p3[0], p2[1] - p3[1]];
    const cp = crossproduct(vector1, vector2);

    /** cp.z가
     * 0 -> 일직선
     * + -> 반시계방향
     * - -> 시계방향
     */

    return cp[2] === 0 ? 0 : (cp[2] > 0 ? 1 : -1);
}

function isCross(line1, line2) {
    /** ccw()가
     * 0 -> 일직선
     * 1 -> 반시계방향
     * -1 -> 시계방향
     */

    const r1 =
        ccw(line1[0], line1[1], line2[0]) *
        ccw(line1[0], line1[1], line2[1]);
    const r2 =
        ccw(line2[0], line2[1], line1[0]) *
        ccw(line2[0], line2[1], line1[1])

    const r1r2 = r1 * r2;

    if (r1r2 === 0) {
        return 1;
    } else {
        if (r1r2 > 0) {
            if (r1 < 0) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
}

function main() {
    let input = fs.readFileSync('/dev/stdin').toString().split('\n');

    const i1 = input[0].split(' ').map(Number);
    const i2 = input[1].split(' ').map(Number);

    const line1
        = [[i1[0], i1[1]], [i1[2], i1[3]]]
    const line2
        = [[i2[0], i2[1]], [i2[2], i2[3]]]

    console.log(isCross(line1, line2));
}

main();