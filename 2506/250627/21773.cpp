#include <iostream>
#include <queue>

using namespace std;

struct process {
    int priority; // 정렬 1순위
    int pid; // 정렬 2순위
    int ttl; // 정렬 3순위
    
    bool operator <(const process& other) const {
        // 정렬 1순위
        if (priority != other.priority) {
            return priority < other.priority; // 높은 priority부터
        }
        // 정렬 2순위
        return pid > other.pid; // 낮은 pid부터
    }
};

int t; // time

vector<process> v;
priority_queue<process> pq;

void solve() {
    for (int i = 1; i <= t; i++) {
        cout << pq.top().pid << "\n";
        
        if (pq.top().ttl - 1) {
            pq.push({pq.top().priority - 1, pq.top().pid, pq.top().ttl - 1});
        }
        
        pq.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n; // number of process
    
    cin >> t >> n;
    
    int tmp[3];
    
    for (int i = 0; i < n; i++) {
        // <pid> <ttl> <init priority>
        cin >> tmp[0] >> tmp[1] >> tmp[2];
        pq.push({tmp[2], tmp[0], tmp[1]});
    }
    
    solve();
}
