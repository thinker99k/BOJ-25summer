#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    queue<int> q;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;

        if (str == "push") {
            int x;
            cin >> x;
            q.push(x);
        }
        else if (str == "pop") {
            if (!q.empty()) {
                cout << q.front() << "\n";
                q.pop();
            }
            else {
                cout << -1 << "\n";
            }
        }
        else if (str == "size") {
            cout << q.size() << "\n";
        }
        else if (str == "empty") {
            cout << q.empty() << "\n";
        }
        else if (str == "front") {
            if (!q.empty()) {
                cout << q.front() << "\n";
            }
            else {
                cout << -1 << "\n";
            }
        }
        else if (str == "back") {
            if (!q.empty()) {
                cout << q.back() << "\n";
            }
            else {
                cout << -1 << "\n";
            }
        }
    }
}

