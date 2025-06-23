#include <iostream>

#define DEBUG 0

using namespace std;

int n, m; // n = 길이, m = 질문

// 수열
int seq[2001];

// row = start, col = end;
int dp[2001][2001];

struct question {
    int s;
    int e;
};

question questions[1000000];

void solve() {
    int start, end, idx, gap;
#if DEBUG
    cout << "== odd ==\n";
#endif
    // 길이 홀수
    for (idx = 1; idx <= n; idx++) {
        for (gap = 0;; gap++) {
            start = idx - gap;
            end = idx + gap;
            
            if (start <= 0 || end > n) {
                break;
            }

            if (seq[start] == seq[end]) {
                dp[start][end] = 1;
#if DEBUG
                cout << "(" << start << "," << end << ") - yes\n";
#endif
            } else {
                break;
            }
        }
    }

#if DEBUG
    cout << "== even ==\n";
#endif
    // 길이 짝수
    for (idx = 1; idx <= n; idx++) {
        for (gap = 0;; gap++) {
            start = idx - gap;
            end = (idx + 1) + gap;
            
            if (start <= 0 || end > n) {
                break;
            }

            if (seq[start] == seq[end]) {
                dp[start][end] = 1;
#if DEBUG
                cout << "(" << start << "," << end << ") - yes\n";
#endif
            }
            else {
                break;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        cin >> seq[i];
    }
    
    cin >> m;
    int s, e;
    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        questions[i] = {s, e};
    }
    
    solve();
    
    for (int i = 0; i < m; i++) {
        cout << dp[questions[i].s][questions[i].e] << "\n";
    }
}