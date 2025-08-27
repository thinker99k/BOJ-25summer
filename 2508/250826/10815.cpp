#include <iostream>
#include <bitset>

using namespace std;

bitset<200000001> bs;

inline int converter(int x) {
    return x + 100000000;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    register int x;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        bs.set(converter(x));
    }

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        cout << bs.test(converter(x)) << " ";
    }
}