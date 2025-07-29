#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll num_v, num_e;


struct vertex {
    ll x;
    ll y;
    ll z;
};

vector<vertex> vertices;


struct edge {
    ll weight;
    ll src;
    ll dst;

    bool operator<(const edge &other) const {
        return weight < other.weight;
    }
};

vector<edge> edges;


ll parent[100001];

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
    for (int i = 0; i <= num_v; i++) {
        parent[i] = i;
    }
    sort(edges.begin(), edges.end());


    ll ret = 0;

    for (auto it: edges) {
        if (Union(it.src, it.dst)) {
            ret += it.weight;
        }
    }

    return ret;
}

void add_edge() {
    int cnt = 0;

    for (ll i = 1; i <= num_v - 1; i++) {
        for (ll j = 1; j <= num_v; j++) {
            if (i == j) {
                continue;
            }

            edges[cnt].weight = min({abs(vertices[i].x - vertices[j].x),
                                     abs(vertices[i].y - vertices[j].y),
                                     abs(vertices[i].z - vertices[j].z)});
            edges[cnt].src = i;
            edges[cnt].dst = j;

            cnt++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> num_v;
    vertices.resize(num_v + 1);

    // ex. 정점이 5개면, 모든 경로는 (5 * 4) = 20개
    num_e = num_v * (num_v - 1);
    edges.resize(num_e);

    for (int i = 1; i <= num_v; i++) {
        cin >> vertices[i].x >> vertices[i].y >> vertices[i].z;
    }

    add_edge();

    cout << kruskal();
}
