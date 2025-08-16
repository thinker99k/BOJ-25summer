#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
using ll = long long;
using Edge = pair<ll, ll>; // 비용, dst

#define INF LLONG_MAX

ll v, e;
ll via1, via2;

vector<vector<Edge>> graph;

ll dijkstra(ll src, ll dst) {
    if (src == dst) {
        return 0LL;
    }

    vector<ll> ret(v + 1, INF);

    // 시작정점 거리 0
    ret[src] = 0LL;

    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    pq.push({0LL, src});

    Edge curr;

    ll nextidx, nextdist;

    while (!pq.empty()) {
        curr = pq.top();
        pq.pop();

        if (curr.second == dst) {
            break;
        }

        if (ret[curr.second] < curr.first) {
            continue;
        }

        for (auto it: graph[curr.second]) {
            nextidx = it.second;
            nextdist = curr.first + it.first;

            if (nextdist < ret[nextidx]) {
                ret[nextidx] = nextdist;
                pq.push({nextdist, nextidx});
            }
        }
    }

    return ret[dst];
}


int main() {
    cin >> v >> e;
    graph.resize(v + 1);

    ll src, dst, cost;
    for (int i = 0; i < e; i++) {
        cin >> src >> dst >> cost;

        graph[src].push_back({cost, dst});
        graph[dst].push_back({cost, src});
    }

    cin >> via1 >> via2;

    ll dist[3][2] = {
            {dijkstra(1, via1),    dijkstra(1, via2)},
            {dijkstra(via1, via2), dijkstra(via2, via1)}, // 같은거 알고있으나 보기좋으라고..
            {dijkstra(via2, v),    dijkstra(via1, v)}
    };

    bool valid[3][2];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            valid[i][j] = dist[i][j] != INF;
        }
    }

    ll pdist[2] = {
            dist[0][0] + dist[1][0] + dist[2][0],
            dist[0][1] + dist[1][1] + dist[2][1]
    };

    bool pvalid[2] = {
            valid[0][0] && valid[1][0] && valid[2][0],
            valid[0][1] && valid[1][1] && valid[2][1]
    };

    if (pvalid[0] && pvalid[1]) {
        // 둘 다 가능
        cout << min(pdist[0], pdist[1]);
    }
    else if (!pvalid[0] && !pvalid[1]) {
        // 둘 다 불가능
        cout << -1 << "\n";
    }
    else {
        // 둘 중 하나만 가능
        if (pvalid[0]) {
            cout << pdist[0] << "\n";
        }
        else {
            cout << pdist[1] << "\n";
        }
    }
}