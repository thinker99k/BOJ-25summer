#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

vector<int> parent(1000001);
vector<int> count(1000001);

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
            count[rootu] += count[rootv];
        }
        else {
            parent[rootu] = rootv;
            count[rootv] += count[rootu];
        }
        // 루트가 같지 않으면 -> union 성공 -> true 반환
        return true;
    }
    else {
        // 루트가 같으면 -> union 실패 -> false 반환
        return false;
    }
}

vector<int> ans;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    iota(parent.begin(), parent.end(), 0);
    fill(count.begin(), count.end(), 1);
    
    int n;
    cin >> n;
    
    char op;
    int i1, i2;
    
    for (int i = 0; i < n; i++) {
        cin >> op;
        
        if (op == 'I') {
            cin >> i1 >> i2;
            Union(i1, i2);
        }
        else {
            cin >> i1;
            cout << count[Find(i1)] << "\n";
        }
    }
}
