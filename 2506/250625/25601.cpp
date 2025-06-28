#include <unordered_map>
#include <iostream>

using namespace std;

unordered_map<string, string> graph;

bool dfs(string start, string target){
    string query = start;
    
    while (graph.count(query)){
        if(graph[query] == target){
            return true;
        }
        query = graph[query];
    }
    
    return false;
}

int main(){
    int n;
    cin >> n;
    
    string child, parent, q1, q2;
    for(int i=1; i<=n-1; i++){
        cin >> child >> parent;
        graph[child] = parent;
    }
    
    cin >> q1 >> q2;
    if(dfs(q1, q2) || dfs(q2, q1)){
        cout << 1;
    }
    else {
        cout << 0;
    }
}