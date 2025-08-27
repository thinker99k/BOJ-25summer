#include <iostream>
#include <unordered_set>

using namespace std;

int n, m;
unordered_set<string> us;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        us.insert(s);
    }

    int ans = 0;

    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;

        if (us.count(s)) {
            ans++;
        }
    }

    cout << ans;
}

