#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll n, s;
vector<ll> v(100001); // 누적합 저장됨

ll ans;

static inline ll getSum(ll start, ll end) {
    return v[end] - v[start - 1];
}

static inline ll getLen(ll start, ll end) {
    return end - start + 1;
}

void search(ll start, ll end) {
    ll sum = getSum(start, end);

    if (sum > s) {
        ans = getLen(start, end);

        search(start + 1, end);
        search(start, end - 1);
    }
    else if (sum == s) {
        ans = getLen(start, end);
    }
    else { ;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    v[0] = 0;

    cin >> n >> s;

    ll tmp;

    for (ll i = 1; i <= n; i++) {
        cin >> tmp;
        v[i] = v[i - 1] + tmp;
    }

    search(1, n);

    cout << ans;
}