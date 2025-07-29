#include <iostream>
#include <algorithm>

#define DEBUG 0

using namespace std;

string arr[101][101];

int n, m;

void init() {
    arr[0][0] = "0";

    arr[1][0] = "1";
    arr[1][1] = "1";

    arr[2][0] = "1";
    arr[2][1] = "2";
    arr[2][2] = "1";

    arr[3][0] = "1";
    arr[3][1] = "3";
    arr[3][2] = "3";
    arr[3][3] = "1";

    arr[4][0] = "1";
    arr[4][1] = "4";
    arr[4][2] = "6";
    arr[4][3] = "4";
    arr[4][4] = "1";
}

string string_add(string &s1, string &s2) {
    string &longer = s1.length() > s2.length() ? s1 : s2;
    string& shorter = s1.length() > s2.length() ? s2 : s1;

    int new_len = (int) longer.length();
    int len_gap = new_len - (int) shorter.length();
    string tmp_longer, tmp_shorter;

    tmp_longer = longer;
    reverse(tmp_longer.begin(), tmp_longer.end());

    tmp_shorter = shorter;
    reverse(tmp_shorter.begin(), tmp_shorter.end());
    tmp_shorter.append(len_gap, '0'); // 길이 맞춤

    string ret;
    int sum, carry = 0;
    for (int i = 0; i < new_len; i++) {
        sum = (tmp_longer[i] - '0') + (tmp_shorter[i] - '0') + carry;

        carry = sum / 10;
        sum %= 10;

        ret += to_string(sum);
    }

    if(carry){
        ret += "1";
    }

    reverse(ret.begin(), ret.end());

    return ret;
}

void solve(){
    for(int i=5; i<=n; i++){
        arr[i][0] = "1";

        for(int j=1; j<i; j++){
            arr[i][j] = string_add(arr[i-1][j-1], arr[i-1][j]);
        }

        arr[i][i] = "1";
    }
}

int main() {
    cin >> n >> m;

    init();

    solve();

#if DEBUG
    for(int i=0; i<=n; i++){
        for(int j=0; j<=i; j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
#endif

    cout << arr[n][m];
}