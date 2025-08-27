#include <iostream>
#include <set>

using namespace std;

int n;
set<string, greater<string>> s;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        string name, io;
        cin >> name >> io;

        if (io[0] == 'e') {
            s.insert(name);
        }
        else {
            s.erase(name);
        }
    }

    for (auto it: s) {
        cout << it << "\n";
    }
}