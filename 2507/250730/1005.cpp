#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> ans;

void kahn(vector<int> &cost,
          vector<int> &in_degree,
          vector<vector<int>> &graph,
          int &fin) {
    int num_v = (int) cost.size() - 1;
    vector<int> cost_sum(num_v + 1, 0);

    priority_queue<int, vector<int>, greater<int>> pq;

    // in degree 0인 node 전부 push
    for (int i = 1; i <= num_v; i++) {
        if (in_degree[i] == 0) {
            cost_sum[i] = cost[i];
            pq.push(i);
        }
    }

    // queue가 비면 탈출
    while (!pq.empty()) {
        int curr = pq.top();
        pq.pop();

        for (auto it: graph[curr]) {
            // curr의 이웃 노드 in degree 감소
            in_degree[it]--;


            /** 왜 MAX냐?
             * 다음(it)의 알려진 누적 비용
             * : 이번 노드의 방문은 의미가 없음
             *      = 시간이 덜 걸려서 계산에 포함 X
             * vs
             * 현재(curr) 누적 비용(curr) + 다음(it)"만" 비용
             * : 이번 노드의 방문이 의미가 있음
             *      = 시간이 더 걸려서 계산에 포함 O
             */
            cost_sum[it] = max(cost_sum[it],
                               cost_sum[curr] + cost[it]);

            // in degree 0이면 push
            if (in_degree[it] == 0) {
                pq.push(it);
            }
        }
    }

    ans.push_back(cost_sum[fin]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        // 1-idx
        vector<int> cost;
        vector<int> in_degree;
        vector<vector<int>> graph;

        // num of vertex, num of edge
        int n, k;
        cin >> n >> k;

        cost.resize(n + 1);
        in_degree.resize(n + 1);
        graph.resize(n + 1);

        for (int j = 1; j <= n; j++) {
            cin >> cost[j];
        }

        int src, dst;
        for (int j = 0; j < k; j++) {
            cin >> src >> dst;
            graph[src].push_back(dst);
            in_degree[dst]++;
        }

        int fin;
        cin >> fin;

        kahn(cost, in_degree, graph, fin);
    }

    for (auto it: ans) {
        cout << it << "\n";
    }
}