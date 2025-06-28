#include <iostream>
#include <vector>
#include <tgmath.h>
#include <algorithm>
#include <iomanip>

using namespace std;

vector<int> parent(100);

int Find(int v) {
    if (parent[v] == v) {
        return v;
    }
    else {
        parent[v] = Find(parent[v]); // 경로압축
        return parent[v];
    }
}

bool Union(int u, int v) {
    int rootu = Find(u);
    int rootv = Find(v);
    
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
    else {
        // 루트가 같으면 -> union 실패 -> false 반환
        return false;
    }
}

struct Pos {
    double x;
    double y;
};

vector<Pos> v;

struct Edge {
    double w;
    int idx1;
    int idx2;
    
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

vector<Edge> e;

static inline double distance(Pos p1, Pos p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double kruskal(){
    for (int i = 0; i < 100; i++) {
        parent[i] = i;
    }
    
    sort(e.begin(), e.end());
    
    double ret = 0;
    
    for (auto it: e) {
        if (Union(it.idx1, it.idx2)) {
            ret += it.w;
        }
    }
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
    cin >> n;
    
    Pos tmp;
    for (int i = 0; i < n; i++) {
        cin >> tmp.x >> tmp.y;
        v.push_back(tmp);
    }
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            e.push_back({distance(v[i], v[j]), i, j});
        }
    }
    
    cout << fixed << setprecision(2) << kruskal();
}