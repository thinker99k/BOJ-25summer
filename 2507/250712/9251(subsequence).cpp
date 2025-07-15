#include <iostream>

#define DEBUG 0

// 1-idx 메크로
#define IDX(x) (x-1)

using namespace std;

int dp[4001][4001]; // row0, col0 알아서 0으로 초기화됨
string s1, s2;
int len1, len2;

void solve(){
    int prev1, prev2;

    // row = s1
    for(int i=1; i<=len1; i++){
        // col = s2
        for(int j=1; j<=len2; j++){
            // s1[i]와 s2[j]가
            if(s1[IDX(i)] == s2[IDX(j)]){ // 같으면
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else{ // 다르면
                prev1 = dp[i-1][j];
                prev2 = dp[i][j-1];
                dp[i][j] = max(prev1, prev2);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> s1 >> s2;
    len1 = (int) s1.length();
    len2 = (int) s2.length();

    solve();

#if DEBUG
    for(int i=1; i<=len1; i++){
        for(int j=1; j<=len2; j++){
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
#endif

    cout << dp[len1][len2];
}
