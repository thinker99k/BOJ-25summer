#include <iostream>
#include <cstring>

using namespace std;

int n, m; // n = 길이, m = 질문

// 수열
int seq[2001];

// row = start, col = end;
int dp[2001][2001];

int ans[1000000];

int solve(int start, int end) {
    if (start == end) { // 길이 1
        return true;
    }
    else if (end - start == 1) { // 길이 2
        return seq[start] == seq[end];
    }
    else { // 길이 3++
        return (seq[start] == seq[end])
               && solve(start + 1, end - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    memset(dp, 0, 2001 * 2001);
    for (int i = 1; i <= 2000; i++) {
        dp[i][i] = 1;
    }
    
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        cin >> seq[i];
    }
    
    cin >> m;
    int s, e;
    for (int i = 0; i < m; i++) {
        cin >> s >> e;
        ans[i] = solve(s, e);
    }
    
    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
}