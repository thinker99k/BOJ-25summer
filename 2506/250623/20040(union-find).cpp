#include <iostream>
#include <vector>

using namespace std;

vector<int> parent(500000, 0);

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    for (int i = 0; i < 500000; i++) {
        parent[i] = i;
    }
    
    int numv, nume;
    
    cin >> numv >> nume;
    
    int s, e, ans = -1;
    bool finish = false;
    
    for (int i = 1; i <= nume; i++) {
        cin >> s >> e;
        
        // Union 실패 (사이클 있다는 뜻) -> false 반환
        if (!Union(s, e)) {
            if(!finish){
                ans = i;
                finish = true;
            }
        }
    }
    
    if (ans == -1) {
        cout << 0;
    }
    else {
        cout << ans;
    }
}