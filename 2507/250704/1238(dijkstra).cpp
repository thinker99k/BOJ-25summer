#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

#define DEBUG 1

#define INF 1e9

using namespace std;

struct Edge {
    int weight;
    int destination;

    const bool operator<(const Edge &other) const {
        if(weight == other.weight){
            return destination < other.destination;
        }
        /** priority를 최소값으로 잡기 위해 */
        return weight > other.weight;
    }
};

int n, m, x;

set<Edge> graph[1001]; // map으로 바꾸면 시간 개선 가능

int dijkstra(int src, int dst) {
    vector<int> dist(n+1, INF);
    // 시작정점 -> 시작정점 거리 0
    dist[src] = 0;

    // 지금까지 진행된 거리, 탐색할 노드가 저장될 우선순위 큐
    priority_queue<Edge> pq;

    pq.push({0, src});

    int currv, currdist, nextv, nextdist;

    while (!pq.empty()) {
        currv = pq.top().destination;
        currdist = pq.top().weight;

        /** 거리를 기준으로 가장 짧은 원소가 pop되기에, 한 간선에 여러 거리가 있어도 가장 낮은 거리가 pop됨이 보장됨 */
        pq.pop();

        for (auto it: graph[currv]) {
            // 다음 정점 후보는 현 정점에서 간선으로 이어진 정점
            nextv = it.destination;

            // 다음 정점까지 최소거리 후보는 현재까지 진행된 거리(시작점으로부터의 거리) + 다음 정점까지 거리
            nextdist = currdist + it.weight;

            // 알려진 거리보다 짧을 경우
            if (nextdist < dist[nextv]) {
                dist[nextv] = nextdist;
                pq.push({dist[nextv], nextv});
            }
        }
    }

    return dist[dst];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int src, dst, cost;
    vector<int> ans;

    cin >> n >> m >> x;
    ans.resize(n+1);
    ans[0] = 0;

    for (int i = 0; i < m; i++) {
        cin >> src >> dst >> cost;
        graph[src].insert({cost, dst});
    }

    for(int i=1; i<=n; i++){
        ans[i] = dijkstra(i, x) + dijkstra(x, i);
    }

    cout << *max_element(ans.begin()+1, ans.end());
}