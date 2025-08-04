#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

using Edge = pair<string, string>;

map<string, set<string>> graph;
map<string, int> in_degree;

vector<string> ans;

bool kahn() {
    queue<string> q;
    int cnt = 0;

    // in degree 0인 node 전부 push
    for (auto &it: in_degree) {
        if (it.second == 0) {
            q.push(it.first);
        }
    }

    string curr;

    // queue가 비면 탈출
    while (!q.empty()) {
        curr.clear();

        curr = q.front();
        q.pop();

        ans.push_back(curr);
        cnt++;

        for (auto &it: graph[curr]) {
            in_degree[it]--;

            if (in_degree[it] == 0) {
                q.push(it);
            }
        }
    }

    return cnt == graph.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int m;
    cin >> m;

    string src, dst;
    vector<Edge> Edges;

    for (int i = 0; i < m; i++) {
        src.clear();
        dst.clear();

        cin >> src >> dst;
        Edges.push_back({src, dst});
    }

    for (auto it: Edges) {
        graph.insert({it.first, {}});
        graph.insert({it.second, {}});

        in_degree.insert({it.first, 0});
        in_degree.insert({it.second, 0});
    }

    for (auto it: Edges) {
        graph[it.first].insert(it.second);
        in_degree[it.second]++;
    }

    if (kahn()) {
        for (auto &it: ans) {
            cout << it << "\n";
        }
    }
    else {
        cout << -1;
    }
}