#include <iostream>
#include <queue>

#define DEBUG 0

using namespace std;

int n;
bool arr[17][17];

struct pos {
    int row;
    int col;

    bool operator==(const pos &other) const {
        return (row == other.row) &&
               (col == other.col);
    }

    pos operator+(const pos &other) const {
        return {row + other.row, col + other.col};
    }
};

/// 0도, -45도, -90도 방향
const pos dpos[3] = {
        {0, 1},
        {1, 1},
        {1, 0}
};

// 0, -45, -90
enum {
    hor, diag, ver
};

struct pipe {
    pos p;
    uint dir;
};

/// 다음 pos에 대한 검사
inline bool isRange(pipe &pi) {
    return (pi.p.row <= n && pi.p.col <= n);
}

inline bool isSpacePos(pos &p) {
    return !arr[p.row][p.col];
}

inline bool isSpace(pipe &pi) {
    if (pi.dir == diag) {
        pos alsocheck[2] = {
                {pi.p.row - 1, pi.p.col},
                {pi.p.row,     pi.p.col - 1}
        };

        return (isSpacePos(pi.p) &&
                isSpacePos(alsocheck[0]) &&
                isSpacePos(alsocheck[1]));
    }
    else {
        return (isSpacePos(pi.p));
    }
}

int bfs() {
    int ret = 0;

    queue<pipe> q;
    q.push({{1, 2}, hor});
    pipe curr, next[3];

    const pos dst = {n, n};

    int pushstart, pushend;

    while (!q.empty()) {
        curr = q.front();
        q.pop();

        if (curr.p == dst) {
            ret++;
        }

        next[0] = {curr.p + dpos[0], hor};
        next[1] = {curr.p + dpos[1], diag};
        next[2] = {curr.p + dpos[2], ver};

        switch (curr.dir) {
            case hor: {
                pushstart = 0;
                pushend = 1;
                break;
            }
            case diag: {
                pushstart = 0;
                pushend = 2;
                break;
            }
            case ver: {
                pushstart = 1;
                pushend = 2;
                break;
            }
        }

        for (int idx = pushstart; idx <= pushend; idx++) {
            if (isRange(next[idx]) && isSpace(next[idx])) {
                q.push(next[idx]);
#if DEBUG
                cout << "(" << next[idx].p.row << "," << next[idx].p.col << ") ";
#endif
            }
        }

#if DEBUG
        cout << "pushed\n";
#endif
    }

    return ret;
}

int main() {
    cin >> n;

    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) {
            cin >> arr[r][c]; // 1이면 벽
        }
    }

    cout << bfs();
}