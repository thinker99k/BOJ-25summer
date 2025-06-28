#include <iostream>
#include <vector>

using namespace std;

struct plane {
    int x;
    int y;
    
    plane operator-(const plane &other) {
        return {x - other.x, y - other.y};
    }
};

struct space {
    int x;
    int y;
    int z;
    
    space operator-(const space &other) {
        return {x - other.x, y - other.y, z - other.z};
    }
};

vector<plane> v(3);

space crossproduct(plane p1, plane p2) {
    // p1, p2는 xyz-plane의 부분공간 xy-plane에 있기에, z좌표는 0;
    
    // 순서대로 x, y, z좌표
    int arr[2][3]{
            {p1.x, p1.y, 0},
            {p2.x, p2.y, 0}
    };
    
    space ret;
    
    enum point {
        first, second
    };
    enum coord {
        x_pos, y_pos, z_pos
    };
    
    // 외적 x좌표 : p1.y * p2.z - p1.z * p2.y
    ret.x = arr[first][y_pos] * arr[second][z_pos] -
            arr[first][z_pos] * arr[second][y_pos];
    // 외적 y좌표 : p1.x * p2.z - p1.z * p2.x
    ret.y = arr[first][x_pos] * arr[second][z_pos] -
            arr[first][z_pos] * arr[second][x_pos];
    // 외적 z좌표 : p1.x * p2.y - p1.y * p2.x
    ret.z = arr[first][x_pos] * arr[second][y_pos] -
            arr[first][y_pos] * arr[second][x_pos];
    
    return ret;
}

int ccw() {
    // 어차피 점 세 개만 비교하기에, 원점은 그냥 v[0]으로 잡음
    space cpresult = crossproduct(v[0] - v[1], v[0] - v[2]);
    
    /** cp.result.z가
     * 0 -> 일직선
     * + -> 반시계방향
     * - -> 시계방향
     */
    
    return cpresult.z == 0 ? 0 : (cpresult.z > 0 ? 1 : -1);
}

int main() {
    int x, y;
    
    for (int i = 0; i < 3; i++) {
        cin >> x >> y;
        v[i] = {x, y};
    }
    
    cout << ccw();
}