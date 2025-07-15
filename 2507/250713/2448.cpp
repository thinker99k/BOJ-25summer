#include <iostream>
#include <cstring>
#include <queue>

#define DEBUG 0

using namespace std;

int n;
char const ch[2] = {' ', '*'}; // false, true
bool arr[3333][6666]; // 1-idx

void prn() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n-i; j++) {
            cout << ' ';
        }
        for (int j = 1; j <= 2 * i - 1; j++) {
            cout << ch[arr[i][j]];
        }
        for (int j = 1; j <= n-i; j++) {
            cout << ' ';
        }

        cout << " \n";
    }
}

struct triangle {
    int row;
    int col;
    int ver;
    int hor;
};

void unmark(triangle t) {
    int ver_lim = t.row + t.ver;
    int hor_lim = t.col - t.hor + 1;

    // 아래로 탐색
    for (int i = t.row; i < ver_lim; i++) {
        // 왼쪽으로 탐색
        for (int j = t.col; j > hor_lim; j--) {
            arr[i][j] = false;
        }

        hor_lim += 2;
    }
}

void unmark2(triangle t) {
#if DEBUG
    cout << "unmark (" << t.row << "," << t.col << ")\n";
#endif
    arr[t.row][t.col] = false;
}

void bfs() {
    memset(&arr[0][0], true, 3333 * 6666);
    triangle start = {
            n / 2 + 1,  // row
            n,          // col
            n / 2,      // ver
            n           // hor
    };

    queue<triangle> q;
    q.push(start);
#if DEBUG
    cout << "(" << start.row <<
            "," << start.col <<
            ") - " << start.ver << "*" << start.hor << "\n";
#endif


    triangle curr;
    int next_hor, next_ver;

    while (!q.empty()) {
        curr = q.front();
        q.pop();

#if DEBUG
        cout << "\nremoving (" << curr.row << "," << curr.col << ")\n";
#endif

        unmark(curr);

#if DEBUG
        prn();
#endif

        if (curr.ver >= 2) {
            next_ver = curr.ver / 2;
            next_hor = curr.hor / 2;

            if (next_ver > 1) {
#if DEBUG
                cout << "== PUSH ==\n";
#endif

                // 상좌
                q.push({curr.row - next_ver, curr.col - next_hor,
                        next_ver, next_hor});

#if DEBUG
                cout << "(" << curr.row - next_ver <<
                        "," << curr.col - next_hor <<
                        ") - " << next_ver << "*" << next_hor << "\n";
#endif

                // 하좌
                q.push({curr.row + next_ver, curr.col - next_hor,
                        next_ver, next_hor});

#if DEBUG
                cout << "(" << curr.row + next_ver <<
                        "," << curr.col - next_hor <<
                        ") - " << next_ver << "*" << next_hor << "\n";
#endif

                // 하우
                q.push({curr.row + next_ver, curr.col + next_hor,
                        next_ver, next_hor});

#if DEBUG
                cout << "(" << curr.row + next_ver <<
                        "," << curr.col + next_hor <<
                        ") - " << next_ver << "*" << next_hor << "\n";
#endif
            }
            else {
                // 푸시 안하고 바로 지움
                triangle tmp[3] = {
                        {curr.row - 2, curr.col - 4, 0, 0},
                        {curr.row + 1, curr.col - 4, 0, 0},
                        {curr.row + 1, curr.col + 2, 0, 0}
                };

                for (auto &it: tmp) {
                    unmark2(it);
                }
            }
        }
    }
}

void prn3(){
    cout << "  *   \n";
    cout << " * *  \n";
    cout << "***** \n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;

    if(n == 3){
        prn3();
    }
    else{
        bfs();

        prn();
    }
}
