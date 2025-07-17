#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    stack<int> stk;

    int n;
    cin >> n;

    string s;
    int x;
    for (int i = 0; i < n; i++) {
        s.clear();
        cin >> s;

        if (s == "push") {
            cin >> x;

            stk.push(x);
        }
        else if (s == "pop") {
            if (!stk.empty()) {
                cout << stk.top() << "\n";
                stk.pop();
            }
            else {
                cout << "-1" << "\n";
            }
        }
        else if (s == "size") {
            cout << stk.size() << "\n";
        }
        else if (s == "empty") {
            cout << stk.empty() << "\n";
        }
        else if (s == "top") {
            if (!stk.empty()) {
                cout << stk.top() << "\n";
            }
            else {
                cout << "-1" << "\n";
            }
        }
        else {
            return -1;
        }
    }
}