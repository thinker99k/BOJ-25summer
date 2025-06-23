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

vector<ll> parent(1001, 0);

ll tmp[1001][1001];

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
    sort(edges.begin(), edges.end());
    
    ll ret = 0;
    
    for (auto it: edges) {
        if (Union(it.src, it.dst)) {
            ret += it.weight;
        }
    }
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // union-find 준비
    for (ll i = 0; i <= 1000; i++) {
        parent[i] = i;
    }
    
    ll numv;
    cin >> numv;
    
    for(ll i=1; i<=numv; i++){
        for(ll j=1; j<=numv; j++){
            cin >> tmp[i][j];
        }
    }
    
    for(ll i=1; i<=numv; i++){
        for(ll j=i; j<=numv; j++){
            edges.push_back({tmp[i][j], i, j});
        }
    }
    
    cout << kruskal();
}
