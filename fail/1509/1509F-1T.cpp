#include <iostream>
#include <cstring>
#include <stdint.h>

#define DEBUG 0

using namespace std;

int sz;
char str[2501];
int dp[2501][2501];

void solve1() {
    int start, end, idx, gap;
    
    // 길이 홀수
    for (idx = 1; idx <= sz; idx++) {
        for (gap = 0;; gap++) {
            start = idx - gap;
            end = idx + gap;
            
            if (start <= 0 || end > sz) {
                break;
            }
            
            if (str[start] == str[end]) {
                dp[start][end] = 1;
            }
            else {
                break;
            }
        }
    }
    
    // 길이 짝수
    for (idx = 1; idx <= sz; idx++) {
        for (gap = 0;; gap++) {
            start = idx - gap;
            end = (idx + 1) + gap;
            
            if (start <= 0 || end > sz) {
                break;
            }
            
            if (str[start] == str[end]) {
                dp[start][end] = 1;
            }
            else {
                break;
            }
        }
    }
}

int ans;

void solve2(int idx, int cnt) {
    if (idx == 0) { // 도착
        if (cnt < ans) {
            ans = cnt;
        }
    }
    else { // 중간
        cnt++;
        
        for (int i = 1; i <= idx; i++) {
            if (dp[i][idx]) {
                solve2(i - 1, cnt);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> (str + 1);
    sz = strlen(str + 1);
    
    solve1();

#if DEBUG
    for (int i = 1; i <= sz; i++) {
        for (int j = 1; j <= sz; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }
#endif
    
    ans = INT32_MAX;
    solve2(sz, 0);
    
    cout << ans;
    
}