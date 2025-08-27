#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int, int> um;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    register int x;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        um[x]++;
    }

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (!um.count(x)) {
            cout << 0 << " ";
        }
        else {
            cout << um[x] << " ";
        }
    }
}