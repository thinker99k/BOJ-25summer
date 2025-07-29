#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct edge {
    ll weight;
    ll src;
    ll dst;

    bool operator<(const edge &other) const {
        return weight < other.weight;
    }
};

vector<edge> edges;

vector<ll> parent(100001, 0);

ll Find(ll v) {
    if (parent[v] == v) {
        return v;
    }
    else {
        parent[v] = Find(parent[v]);
        return parent[v];
    }
}

bool Union(ll u, ll v) {
    ll rootu = Find(u);
    ll rootv = Find(v);

    if (rootu != rootv) {
        if (rootu < rootv) {
            parent[rootv] = rootu;
        }
        else {
            parent[rootu] = rootv;
        }
        // 루트가 같지 않으면 -> union 성공 -> true 반환
        return true;
    }
    // 루트가 같으면 -> union 실패 -> false 반환
    return false;
}

ll kruskal() {
    // union-find 준비
    for (int i = 0; i <= 100000; i++) {
        parent[i] = i;
    }

    // kruskal 준비
    sort(edges.begin(), edges.end());

    ll ret = 0;
    ll last = 0;

    for (auto it: edges) {
        if (Union(it.src, it.dst)) {
            ret += it.weight;
            last = it.weight;
        }
    }

    return ret - last;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll numv, nume;
    cin >> numv;
    cin >> nume;

    ll weight, src, dst;
    for (int i = 0; i < nume; i++) {
        cin >> src >> dst >> weight;
        edges.push_back({weight, src, dst});
    }

    cout << kruskal();
}
