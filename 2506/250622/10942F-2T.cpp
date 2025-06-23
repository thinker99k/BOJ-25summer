#include <iostream>
#include <cstring>

using namespace std;

int n, m; // n = 길이, m = 질문

// 수열
int seq[2001];

int ans[1000000];

int solve(int start, int end) {
    int i, j, mid = (start + end) / 2;
    
    for (i = start; i < mid; i++) {
        for (j = end; j > mid; j--) {
            if(seq[i] != seq[j]){
                return false;
            }
        }
    }
    
    return true;
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
        ans[i] = solve(s, e);
    }
    
    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
}