#include <iostream>
#include <cstring>

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
    memset(dp, 0, 2001 * 2001);
    
    /** 길이 : e - s + 1 */
    
    int i, j;
    
    // 길이 1
    for (i = 1; i <= 2000; i++) {
        dp[i][i] = 1;
    }
    
    // 길이 2
    for (i = 1; i <= n - 1; i++) {
        for (j = i + 1; j <= n; j++) {
            dp[i][j] = seq[i] == seq[j];
        }
    }
    
    // 길이 3
    for (i = 1; i <= n - 2; i++) {
        for (j = i + 2; j <= n; j++) {
            dp[i][j] = seq[i] == seq[j];
        }
    }
    
    // 길이 4~n
    for (int dist = 4; dist <= n; dist++) {
        // i = start
        for (i = 1; i <= n - (dist - 1); i++) {
            // j = end
            for (j = i + (dist - 1); j <= n; j++) {
                dp[i][j] = (seq[i] == seq[j]) // 지금 비교
                           && dp[i + 1][j - 1]; // dist-2 때 이미 계산됨
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