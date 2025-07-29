#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll num_v;


struct vertex {
    ll x;
    ll y;
    ll z;
};

vector<vertex> vertices;


struct edge {
    ll cost;
    ll src;
    ll dst;

    bool operator<(const edge &other) const {
        return cost < other.cost;
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
            ret += it.cost;
        }
    }

    return ret;
}

/// 최적화

struct IdxVertex {
    ll i;
    vertex ver;
};

inline bool cmpX(const IdxVertex &iv1, const IdxVertex &iv2) {
    return iv1.ver.x < iv2.ver.x;
}

inline bool cmpY(const IdxVertex &iv1, const IdxVertex &iv2) {
    return iv1.ver.y < iv2.ver.y;
}

inline bool cmpZ(const IdxVertex &iv1, const IdxVertex &iv2) {
    return iv1.ver.z < iv2.ver.z;
}

void add_edge() {
    /** 0-idx */
    vector<IdxVertex> ivX(num_v);
    vector<IdxVertex> ivY(num_v);
    vector<IdxVertex> ivZ(num_v);

    for (int i = 0; i < num_v; i++) {
        ivX[i] = {i+1, {vertices[i+1].x, vertices[i+1].y, vertices[i+1].z}};
    }

    copy(ivX.begin(), ivX.end(), ivY.begin());
    copy(ivX.begin(), ivX.end(), ivZ.begin());

    /*** [ 핵심 아이디어 ] ***
     * 거리가 먼 정점을 굳이 추가해야할 이유가 있냐?
     * 어차피 MST에서 사용되지도 않을텐데? */

    /// 각자 축의 좌표을 기준으로 정렬 -> 가까운 놈들끼리 붙어서 이어지게 됨
    sort(ivX.begin(), ivX.end(), cmpX);
    sort(ivY.begin(), ivY.end(), cmpY);
    sort(ivZ.begin(), ivZ.end(), cmpZ);

    ll costX, costY, costZ;

    for (ll i = 0; i < num_v - 1; i++) {
        costX = abs(ivX[i].ver.x - ivX[i + 1].ver.x);
        costY = abs(ivY[i].ver.y - ivY[i + 1].ver.y);
        costZ = abs(ivZ[i].ver.z - ivZ[i + 1].ver.z);

        edges.push_back({costX, ivX[i].i, ivX[i + 1].i});
        edges.push_back({costY, ivY[i].i, ivY[i + 1].i});
        edges.push_back({costZ, ivZ[i].i, ivZ[i + 1].i});
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> num_v;
    vertices.resize(num_v + 1);

    for (int i = 1; i <= num_v; i++) {
        cin >> vertices[i].x >> vertices[i].y >> vertices[i].z;
    }

    add_edge();

    cout << kruskal();
}
