#include <iostream>
#include <cstring>
#include <stdint.h>
#include <stack>

#define DEBUG 1

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

struct s_element {
    int i;
    int c;
};

void solve2(int start) {
    stack<s_element> s;
    s.push({start, 0});
    
    s_element cur;
    while (!s.empty()) {
        cur = s.top();
        s.pop();
        
        if (cur.i == 0) {
            if (cur.c < ans) {
                ans = cur.c;
            }
        }
        
        for (int i = 1; i <= cur.i; i++) {
            if (dp[i][cur.i]) {
                s.push({i - 1, cur.c + 1});
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
    solve2(sz);
    
    cout << ans;
    
}