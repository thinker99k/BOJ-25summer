#include <iostream>
#include <algorithm>

using namespace std;

void string_add(string &s1, string &s2) {
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

    string ans;
    int sum, carry = 0;
    for (int i = 0; i < new_len; i++) {
        sum = (tmp_longer[i] - '0') + (tmp_shorter[i] - '0') + carry;

        carry = sum / 10;
        sum %= 10;

        ans += to_string(sum);
    }

    if(carry){
        ans += "1";
    }

    reverse(ans.begin(), ans.end());

    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s1, s2;
    cin >> s1 >> s2;

    string_add(s1, s2);
}