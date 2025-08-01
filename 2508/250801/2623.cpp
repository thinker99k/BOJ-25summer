#include <iostream>
#include <vector>
#include <set>
#include <queue>

#define DEBUG 0

using namespace std;

int singer; // 가수 수

set<int> graph[1001];
vector<int> in_degree(1001);

vector<int> ans;

bool kahn() {
    queue<int> q;
    int cnt = 0;

    // in degree 0인 node 전부 push
    for (int i = 1; i <= singer; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    int curr;

    // queue가 비면 탈출
    while (!q.empty()) {
        curr = q.front();
        q.pop();
        cnt++;

        ans.push_back(curr);

        for (auto it: graph[curr]) {
            in_degree[it]--;

            if (in_degree[it] == 0) {
                q.push(it);
            }
        }
    }

#if DEBUG
    for (auto it: ans) {
        cout << it << " ";
    }
    cout << "\n";
#endif

    return cnt == singer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int pd, t, x;
    int src, dst;
    cin >> singer >> pd;

    vector<int> order;
    for (int i = 0; i < pd; i++) {
        order.clear();

        cin >> t; // 한 pd가 주장하는 순서의 길이

        for (int j = 0; j < t; j++) {
            cin >> x;
            order.push_back(x);
        }

        for (int j = 0; j < t - 1; j++) {
            src = order[j];
            dst = order[j + 1];

            // 중복 간선 제거, 차수도 거기에 맞춤
            if(!graph[src].count(dst)){
                graph[src].insert(dst);
                in_degree[dst]++;
            }
        }
    }

    if (kahn()) {
        for (auto it: ans) {
            cout << it << "\n";
        }
    }
    else {
        cout << 0;
    }
}