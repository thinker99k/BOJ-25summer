#include <iostream>
#include <vector>
#include <set>
#include <queue>

#define DEBUG 0

using namespace std;

int bdnumber; // 건물 수

set<int> graph[501];
vector<int> in_degree(501, 0);
vector<int> cost(501, 0);
vector<int> dp(501, 0);

void kahn() {
    queue<int> q;

    // in degree 0인 node 전부 push
    for (int i = 1; i <= bdnumber; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
            dp[i] = cost[i];
        }
    }

    int curr;

    // queue가 비면 종료
    while (!q.empty()) {
        // curr은 in degree가 0이였기에 이번 while 루프에 탈출
        curr = q.front();
        q.pop();

        for (auto it: graph[curr]) {
            dp[it] = max(dp[it],
                         dp[curr] + cost[it]);
            /** 왜 MAX냐?
             * 다음(it)의 알려진 누적 비용
             * : 이번(curr) 방문은 의미가 없음
             *      = 시간이 덜 걸려서 계산에 포함 X
             * vs
             * 이번(curr) 누적 비용(curr) + 다음(it)"만" 비용
             * : 이번(curr)의 방문이 의미가 있음
             *      = 시간이 더 걸려서 계산에 포함 O
             */

            in_degree[it]--;
            if (in_degree[it] == 0) {
                q.push(it);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> bdnumber;

    int x;
    vector<int> order;
    for (int idx = 1; idx <= bdnumber; idx++) {
        order.clear();

        while (true) {
            cin >> x;

            if (x == -1) {
                break;
            }

            order.push_back(x);
        }

        cost[idx] = order[0];
        /**
         * order[0] : 소요시간
         * order[1] .. order[n-1] : 선행 그래프
         * (-1을 입력받지 않았기 때문에..)
         *
         * 선행 그래프가 없을수도 있음 -> order.size() = 1
         * -> 아래 for loop 들어가지 않음
         */

        for (int i = 1; i < (int) order.size(); i++) {
            // idx를 지으려면 order[x]의 건물이 선행 되어야 함
            // => edge (order[x] -> idx)
            graph[order[i]].insert(idx);
            in_degree[idx]++;
        }
    }

    kahn();

    for(int i=1; i<=bdnumber; i++){
        cout << dp[i] << "\n";
    }
}