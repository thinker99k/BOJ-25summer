#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> llll;
typedef pair<ll, llll> edge;

vector<edge> edges;
vector<ll> parent(10001, 0);

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
        if (Union(it.second.first, it.second.second)) {
            ret += it.first;
        }
    }
    
    return ret;
}

int main() {
    // union-find 준비
    for (int i = 0; i <= 10000; i++) {
        parent[i] = i;
    }
    
    ll numv, nume;
    cin >> numv >> nume;
    
    ll weight, src, dst;
    for (int i = 0; i < nume; i++) {
        cin >> src >> dst >> weight;
        edges.push_back(make_pair(weight, make_pair(src, dst)));
    }
    
    cout << kruskal();
}
