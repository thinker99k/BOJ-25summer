#include <iostream>
#include <queue>

#define DEBUG 0

using namespace std;

int r, c, k;
char graph[1001][1001];
bool chk[1001][1001][11];

const int rpp[] = {-1, 1, 0, 0};
const int cpp[] = {0, 0, -1, 1};

struct pos {
    int row;
    int col;
};

struct search {
    pos coord;
    int crack;
    int cost;
};

static inline bool isRange(int nr, int nc) {
    return (nr >= 1 && nr <= r && nc >= 1 && nc <= c);
}

int bfs() {
    search start = {{1, 1}, 0, 1};
    
    queue<search> q;
    
    chk[start.coord.row][start.coord.col][0] = true;
    q.push(start);
    
    search curr;
    
    while (!q.empty()) {
        curr = q.front();
        q.pop();

#if DEBUG
        cout << curr.coord.row << " "
             << curr.coord.col << " "
             << curr.cost << " "
             << curr.crack << " -> ";
#endif
        
        if (curr.coord.row == r && curr.coord.col == c) {
            return curr.cost;
        }
        
        for (int i = 0; i < 4; i++) {
            int nr = curr.coord.row + rpp[i];
            int nc = curr.coord.col + cpp[i];
            
            if (isRange(nr, nc)) { // 범위 내일 때
                if (graph[nr][nc] == '0') { // 이동 가능 ('0')
                    if (curr.crack <= k) { // 벽 깨는 리밋 이하 (이번에 벽 안깰거기에 <=)
                        if (!chk[nr][nc][curr.crack]) {
                            chk[nr][nc][curr.crack] = true;
                            q.push({{nr, nc}, curr.crack, curr.cost + 1}); // 벽 안깸
#if DEBUG
                            cout << "(" << nr << "," << nc << ") ";
#endif
                        }
                    }
                }
                else { // 이동 불가능 ('1')
                    if (curr.crack < k) { // 벽 깨는 리밋 미만 (이번에 벽 깰거기에 <)
                        if (!chk[nr][nc][curr.crack + 1]) {
                            chk[nr][nc][curr.crack + 1] = true;
                            q.push({{nr, nc}, curr.crack + 1, curr.cost + 1}); // 벽 깸
#if DEBUG
                            cout << "(" << nr << "," << nc << ") ";
#endif
                        }
                    }
                }
            }
        }
#if DEBUG
        cout << "pushed\n";
#endif
    }
    
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> r >> c >> k;
    
    for (int i = 1; i <= r; i++) {
        cin >> (graph[i] + 1);
    }
    
    cout << bfs() << "\n";
    
    return 0;
}