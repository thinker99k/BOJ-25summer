#include <iostream>

using namespace std;

using ll = long long;

ll arr[100001];
int END;

inline ll getSum(int idx1, int idx2) {
    return arr[idx1] + arr[idx2];
}

void solve() {
    ll gap = 9999999999, sum, abssum;

    pair<int, int> ans;

    int L = 1, R = END;

    while (L < R) {
        sum = getSum(L, R);
        abssum = abs(sum);

        if (abssum < gap) {
            gap = abssum;
            ans = {L, R};
        }

        if (sum < 0) {
            L++;
        }
        else {
            R--;
        }
    }

    cout << arr[ans.first] << " " << arr[ans.second];
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> END;

    for (int i = 1; i <= END; i++) {
        cin >> arr[i];
    }

    solve();
}