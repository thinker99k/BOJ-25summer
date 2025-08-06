#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int src;
    int dst;
    int cost;
};

const int INF = 2147483647;

const string STR[2] = {"NO\n", "YES\n"};
vector<bool> ans;

vector<Edge> graph;
vector<int> sum;

int n;

int src, dst, cost;

bool bellman_ford() {
    /** 원래 1(실제 idx)부터지만, 가상의 정점 0을 위해 0부터 시작 */
    for (int i = 0; i < n; i++) {
        for (auto it: graph) {
            // idx
            src = it.src;
            dst = it.dst;

            // src -> dst 비용
            cost = it.cost;

            // 이미 방문한 노드(src)에서 (비용 != INF)
            // 이웃 노드로 가는 비용이 현재 알려진 비용보다 적을 경우
            if (sum[src] != INF &&
                sum[src] + cost < sum[dst]) {
                sum[dst] = sum[src] + cost;
            }
        }
    }

    // 음수 사이클 검사
    for (auto it: graph) {
        // idx
        src = it.src;
        dst = it.dst;

        // src -> dst 비용
        cost = it.cost;

        // 이미 방문한 노드(src)에서
        // 다른 노드로 가는 비용이
        // 현재 알려진 비용보다 적을 경우
        if (sum[src] != INF &&
            sum[src] + cost < sum[dst]) {
            /** 음수 사이클 발생 */
            return false;
        }
    }

    // 음수 사이클이 없는 성공적인 최단경로 탐색
    return true;
}

void solve() {
    sum.clear();
    sum.resize(n + 1);
    fill(sum.begin(), sum.end(), INF);

    /** 가상의 출발점 0은 모든 정점과 비용 0으로 연결되어있다 생각 */
    for(int i=1; i<=n; i++){
        graph.push_back({0, i, 0});
    }
    sum[0] = 0;

    if (!bellman_ford()) {
        ans.push_back(true);
        return;
    }

    ans.push_back(false);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t, m, w, s, d, c;

    cin >> t;

    for (int i = 0; i < t; i++) {
        graph.clear();

        cin >> n >> m >> w;

        // 도로 : 방향성 X
        for (int j = 0; j < m; j++) {
            cin >> s >> d >> c;
            graph.push_back({s, d, c});
            graph.push_back({d, s, c});
        }

        // 웜홀 : 방향성 O
        for (int j = 0; j < w; j++) {
            cin >> s >> d >> c;
            graph.push_back({s, d, (c * -1)});
        }

        solve();
    }

    for (auto it: ans) {
        cout << STR[it];
    }
}