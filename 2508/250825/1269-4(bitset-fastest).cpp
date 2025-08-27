#include <iostream>
#include <bitset>

using namespace std;

bitset<100000001> bs;
int numa, numb, ans;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    register int x;

    cin >> numa >> numb;
    ans = numa;

    for (int i = 0; i < numa; i++) {
        cin >> x;
        bs.set(x);
    }

    for (int i = 0; i < numb; i++) {
        cin >> x;
        ans += (bs.test(x) ? -1 : 1);
    }

    cout << ans;
}