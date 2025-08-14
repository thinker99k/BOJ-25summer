#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

ll V;

struct Edge {
    ll dest;
    ll cost;
};

struct Search {
    ll idx;
    ll sum;
};

vector<Edge> graph[100001];
vector<bool> chk(100001, false);

pair<ll, ll> bfs(ll start) {
    fill(chk.begin(), chk.end(), 0);

    // <가장 먼 노드, 누적 비용> return
    pair<ll, ll> ret = {start, 0};

    queue<Search> q;

    q.push({start, 0});
    chk[start] = true;

    Search curr;
    while (!q.empty()) {
        curr = q.front();
        q.pop();

        if (curr.sum > ret.second) {
            ret.first = curr.idx;
            ret.second = curr.sum;
        }

        for (auto it: graph[curr.idx]) {
            if (!chk[it.dest]) {
                q.push({it.dest, curr.sum + it.cost});
                chk[it.dest] = true;
            }
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll a, b, c;

    while(cin >> a >> b >> c){
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }

    pair<ll, ll> tmpans = bfs(1);
    pair<ll, ll> ans = bfs(tmpans.first);

    cout << ans.second;
}