#include <iostream>

using namespace std;

typedef long long ll;

struct plane {
    ll x;
    ll y;
    
    plane operator-(const plane &other) {
        return {x - other.x, y - other.y};
    }
};

struct space {
    ll x;
    ll y;
    ll z;
    
    space operator-(const space &other) {
        return {x - other.x, y - other.y, z - other.z};
    }
};

struct line {
    plane src;
    plane dst;
};

space crossproduct(plane p1, plane p2) {
    // p1, p2는 xyz-plane의 부분공간 xy-plane에 있기에, z좌표는 0;
    
    // 순서대로 x, y, z좌표
    ll arr[2][3]{
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

ll ccw(plane p1, plane p2, plane p3) {
    // 들어오는 점 : 선분a, 선분a, 선분b
    space cp = crossproduct(p1 - p3, p2 - p3);
    
    /** cp.z가
     * 0 -> 일직선
     * + -> 반시계방향
     * - -> 시계방향
     */
    
    return cp.z == 0 ? 0 : (cp.z > 0 ? 1 : -1);
}

bool isCross(line l1, line l2) {
    /** ccw()가
     * 0 -> 일직선
     * 1 -> 반시계방향
     * -1 -> 시계방향
     */
    // l1 기준
    ll l1_1 = ccw(l1.src, l1.dst, l2.src);
    ll l1_2 = ccw(l1.src, l1.dst, l2.dst);
    
    // l2 기준
    ll l2_1 = ccw(l2.src, l2.dst, l1.src);
    ll l2_2 = ccw(l2.src, l2.dst, l1.dst);
    
    ll r1 = l1_1 * l1_2;
    ll r2 = l2_1 * l2_2;
    
    ll r1r2 = r1 * r2;
    
    if (r1r2 == 0) {
        return true;
    }
    else {
        if (r1r2 > 0) {
            if (r1 < 0) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
}

int main() {
    line l1, l2;
    
    cin >> l1.src.x >> l1.src.y >> l1.dst.x >> l1.dst.y;
    cin >> l2.src.x >> l2.src.y >> l2.dst.x >> l2.dst.y;
    
    cout << isCross(l1, l2);
}