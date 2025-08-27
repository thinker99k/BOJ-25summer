#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int numa, numb;
    register int x;
    unordered_set<int> us;

    cin >> numa >> numb;
    int ans = numa;

    for (int i = 0; i < numa; i++) {
        cin >> x;
        us.insert(x);
    }

    for (int i = 0; i < numb; i++) {
        cin >> x;
        ans += (us.count(x) ? -1 : 1);
    }

    cout << ans;
}