#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;

vector<int> graph[32001];
vector<int> in_degree(32001);
vector<bool> visited(32001);

vector<int> ans;

void dfs(int node){
    visited[node] = true;
    cout << node << "\n";

    for(auto &it : graph[node]){
        if(!visited[it]){
            dfs(it);
        }
    }
}

void kahn(){
    priority_queue<int, vector<int>, greater<int>> pq;

    // in degree 0인 node 전부 push
    for(int i=1; i<=n; i++){
        if(in_degree[i] == 0){
            pq.push(i);
        }
    }

    int curr;

    // queue가 비면 탈출
    while(!pq.empty()){
        curr = pq.top();
        pq.pop();

        ans.push_back(curr);

        for(auto it : graph[curr]){
            in_degree[it]--;

            if(in_degree[it] == 0){
                pq.push(it);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int m, x, y;
    cin >> n >> m;

    for(int i=0; i<m; i++){
        cin >> x >> y;
        graph[x].push_back(y);
        in_degree[y]++;
    }

    kahn();

    for (auto it : ans){
        cout << it << " ";
    }
}