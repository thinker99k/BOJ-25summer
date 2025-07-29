#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

void stkflush(stack<char> &stk, string &ans){
    while (!stk.empty()) {
        ans += stk.top();
        stk.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    int s_len, idx_lim;
    getline(cin, s);
    s_len = (int) s.length();
    idx_lim = s_len - 1;

    string ans;

    stack<char> stk;
    string tmpTag;
    for (int i = 0; i <= idx_lim; i++) {
        if (s[i] == '<') {
            stkflush(stk, ans);

            while (s[i] != '>') {
                ans += s[i];
                i++;
            }

            ans += '>';
        }
        else if (s[i] == ' ') {
            stkflush(stk, ans);

            ans += ' ';
        }
        else {
            stk.push(s[i]);
        }
    }

    stkflush(stk, ans);

    cout << ans;
}