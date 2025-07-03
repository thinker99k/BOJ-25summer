#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int val;
    vector<Node *> neighbor;
    
    Node(int v) : val(v) {
        neighbor.clear();
    };
};

Node * makeNode (int v){
    return new Node(v);
}

vector<Node*> graph(100001);
vector<int> sz(100001, 1);

void cnt(Node* curr, int parent_val){
    // it : Node*
    for(auto it : curr->neighbor){
        // 단방향 탐색
        if(it->val != parent_val){
            cnt(it, curr->val);
            sz[curr->val] += sz[it->val];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int N, R, Q;
    cin >> N >> R >> Q;
    
    graph.resize(N+1);
    sz.resize(N+1);
    
    for(int i=1; i<=N; i++){
        graph[i] = makeNode(i);
    }
    
    int a, b;
    for (int i = 1; i <= N - 1; i++) {
        cin >> a >> b;
        graph[a]->neighbor.push_back(graph[b]);
        graph[b]->neighbor.push_back(graph[a]);
    }
    
    cnt(graph[R], -1);
    
    for(int i=1; i<=Q; i++){
        cin >> a;
        cout << sz[a] << "\n";
    }
}