#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

unordered_set<int> graph[100001];

void makeTree(int parent){
    for(auto child : graph[parent]){
        graph[child].erase(parent);
    }
    
    for(auto child : graph[parent]){
        makeTree(child);
    }
}

int bfs(int node){
    queue<int> q;
    q.push(node);
    
    int curr;
    int ret = 1; // 자기 자신
    
    while(!q.empty()){
        curr = q.front();
        q.pop();
        ret += graph[curr].size();
        
        // tree이기에 사이클 발생하지 않음, 따라서 checked 불필요
        for(auto it : graph[curr]){
            q.push(it);
        }
    }
    
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int N, R, Q;
    cin >> N >> R >> Q;
    
    int a, b;
    for(int i=1; i<=N-1; i++){
        cin >> a >> b;
        graph[a].insert(b);
        graph[b].insert(a);
    }
    
    makeTree(R);
    
    vector<int> ans;
    
    for(int i=0; i<Q; i++){
        cin >> a;
        ans.push_back(bfs(a));
    }
    
    for(auto it : ans){
        cout << it << "\n";
    }
}