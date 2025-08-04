#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#define DEBUG 0

using namespace std;

using is = pair<int, string>;

unordered_map<string, unordered_set<string>> graph;
unordered_map<string, int> in_degree;

vector<string> ans;

int n;

bool kahn() {
    priority_queue<is, vector<is>, greater<is>> q;
    int cnt = 0;

    // in degree 0인 node 전부 push
    for (auto it: in_degree) {
        if (it.second == 0) {
            q.push({0, it.first});
#if DEBUG
            cout << it.first << " pushed\n";
#endif
        }
    }

    is curr;

    // queue가 비면 탈출
    while (!q.empty()) {
        curr = q.top();
        q.pop();

#if DEBUG
        cout << "** " << curr.second << " visited\n";
#endif

        ans.push_back(curr.second);
        cnt++;

        for (auto it: graph[curr.second]) {
            in_degree[it]--;

            if (in_degree[it] == 0) {
                q.push({curr.first + 1, it});
#if DEBUG
                cout << it << " pushed\n";
#endif
            }
        }
    }

    return cnt == n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int m;
    cin >> m;

    string src, dst;

    for (int i = 0; i < m; i++) {
        src.clear();
        dst.clear();

        cin >> src >> dst;

        /// src가 아직 알려지지 않은 아이템일 경우
        if (!in_degree.count(src)) {
            graph.insert({src, {}});
            in_degree.insert({src, 0});
            n++;
        }
        /// 이 이후로 src는 존재하는 노드임이 보장됨
        graph[src].insert(dst);


        /// dst가 아직 알려지지 않은 아이템일 경우
        if (!in_degree.count(dst)) {
            graph.insert({dst, {}});
            in_degree.insert({dst, 0});
            n++;
        }
        /// 이 이후로 dst는 존재하는 노드임이 보장됨

        in_degree[dst]++; // dst in degree 무조건 증가
    }

    if (kahn()) {
        for (auto it: ans) {
            cout << it << "\n";
        }
    }
    else {
        cout << -1;
    }
}