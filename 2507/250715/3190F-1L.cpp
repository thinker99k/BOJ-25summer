#include <iostream>
#include <queue>

#define DEBUG 0

using namespace std;

struct Pos {
    int row;
    int col;
};

struct Turn {
    int time;
    char dir;
};


bool apple[101][101];
int LIM;

queue<Turn> q;

queue<Pos> snake;
bool snake_chk[101][101];
unsigned int snake_dir;
/**
 *   2
 * 3   1
 *   4
 */

Pos nextP;

inline void turn(const char& ch) {
    if (ch == 'L') {
        ++snake_dir;

        if (snake_dir == 5) {
            snake_dir = 1;
        }
    }
    else if (ch == 'D') {
        --snake_dir;

        if (snake_dir == 0) {
            snake_dir = 4;
        }
    }
}

inline void updateNextP() {
    switch (snake_dir) {
        case 1: {
            nextP = {snake.back().row, snake.back().col + 1};
            break;
        }
        case 2: {
            nextP = {snake.back().row - 1, snake.back().col};
            break;
        }
        case 3: {
            nextP = {snake.back().row, snake.back().col - 1};
            break;
        }
        case 4: {
            nextP = {snake.back().row + 1, snake.back().col};
            break;
        }
        default: { ; }
    }
}

inline bool isRange() {
    return nextP.row >= 1 && nextP.row <= LIM && nextP.col >= 1 && nextP.col <= LIM;
}

inline bool isAlive() {
    return snake_chk[nextP.row][nextP.col] != true;
}

inline void move() {
    snake.push({nextP.row, nextP.col}); // 큐에 새로운 머리 삽입
    snake_chk[nextP.row][nextP.col] = true; // 새로운 머리 체크

    // 사과 없음
    if (!apple[nextP.row][nextP.col]) {
        snake_chk[snake.front().row][snake.front().col] = false; // 꼬리 체크 해제
        snake.pop(); // 꼬리 자르기
    }
}


int solve() {
    // 뱀은 가장 먼저 (1,1)에
    snake.push({1, 1});
    snake_chk[1][1] = true;

    // 오른쪽을 바라보는 방향으로 있음
    snake_dir = 1;

    int t;
    for (t = 1; ; t++) {
        // 1. nextPos 갱신
        updateNextP();

#if DEBUG
        cout << t << " - (" << nextP.row << "," << nextP.col << ")\n";
#endif

        // 2. 이동가능 여부 확인
        if (!isRange() || !isAlive()) {
            break;
        }

        // 3. 이동 && 몸 길이 조정
        move();

        // 4. turn (t초가 끝나고 진행)
        if (q.front().time == t) {
            turn(q.front().dir);
            q.pop();
        }
    }

    return t;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, a, b;
    char c;

    cin >> LIM;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        apple[a][b] = true;
    }

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> c;
        q.push({a, c});
    }

    cout << solve();
}
