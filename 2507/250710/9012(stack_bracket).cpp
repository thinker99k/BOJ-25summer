#include <iostream>
#include <stack>

using namespace std;

bool chkBracket(string &s) {
    stack<char> stk;
    int len = (int) s.length();

    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            stk.push(s[i]);
        }
        else {
            if (stk.empty()) {
                return false;
            }
            stk.pop();
        }
    }

    return stk.empty();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    string s;
    for(int i=0; i<n; i++){
        cin >> s;
        if(chkBracket(s)){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }
}