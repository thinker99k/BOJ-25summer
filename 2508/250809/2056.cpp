#include <iostream>
#include <sstream>

#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

int n; // num of vertex


int kahn(vector<int> &cost,
         vector<int> &in_degree,
         vector<vector<int>> &graph,
         int fin) {

    vector<int> cost_sum(n + 1, 0);

    priority_queue<int> pq;

    // in degree 0인 node 전부 push
    for (int i = 1; i <= n; i++) {
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

    return *max_element(cost_sum.begin()+1, cost_sum.end());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // 1-idx
    vector<int> cost(n + 1, 0);
    vector<int> in_degree(n + 1, 0);
    vector<vector<int>> graph(n + 1);

    int pre;
    int presz;

    for (int idx = 1; idx <= n; idx++) {
        string line;
        getline(cin, line);

        stringstream ss(line);
        ss >> cost[idx] >> presz;

        for (int i = 0; i < presz; i++) {
            /// idx를 하기 위해서는 pre가 필요함
            ss >> pre;
            graph[pre].push_back(idx);
            in_degree[idx]++;
        }
    }

    cout << kahn(cost, in_degree, graph, n);
}