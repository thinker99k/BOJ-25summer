#include <iostream>
#include <vector>
#include <set>
#include <numeric>

using namespace std;

vector<int> parent(300001, 0);

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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    iota(parent.begin(), parent.end(), 0);
    
    int n, u, v;
    
    // 섬이 n개 -> 기존에 다리는 n-1개 -> 다리 하나 부숴서 n-2개
    cin >> n;
    
    for(int i=1; i<=n-2; i++){
        cin >> u >> v;
        Union(u, v);
    }
    
    set<int> s(parent.begin()+1, parent.begin()+1+n);
    set<int> ans;
    
    for (auto it : s){
        ans.insert(Find(it));
    }
    
    for (auto it : ans){
        cout << it << " ";
    }
}