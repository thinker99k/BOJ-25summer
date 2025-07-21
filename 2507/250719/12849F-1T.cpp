#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int LIM;

vector<int> ssu[8];

enum {
    it,
    cs,
    faith,
    truth,
    sibalsure, /** 2025년 역대급 병신 총학! */
    hyungnam,
    chapel,
    future
};

inline void link(int x, int y) {
    ssu[x].push_back(y);
    ssu[y].push_back(x);
}

void init() {
    link(it, cs);
    link(cs, faith);
    link(faith, truth);
    link(truth, sibalsure);
    link(sibalsure, hyungnam);
    link(hyungnam, chapel);
    link(chapel, future);
    link(future, it);
    link(cs, future);
    link(future, faith);
    link(faith, chapel);
    link(chapel, truth);
}

struct walk {
    int idx;
    int cost_sum;
};

typedef long long ll;

ll const prime = 1e9 + 7;
ll ans;

inline void modulo() {
    ans %= prime;

    if (ans < 0) {
        ans += prime;
    }
}

void bfs() {
    queue<walk> q;
    q.push({0, 0});

    walk curr;

    while (!q.empty()) {
        curr = q.front();
        q.pop();

        if (curr.cost_sum == LIM && curr.idx == it) {
            ans++;
            modulo();
        }
        else {
            if (curr.cost_sum < LIM) {
                for (auto it: ssu[curr.idx]) {
                    q.push({it, curr.cost_sum + 1});
                }
            }
        }
    }
}

int main() {
    init();

    cin >> LIM;

    bfs();

    cout << (int) ans;
}