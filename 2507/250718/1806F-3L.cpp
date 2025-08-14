#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll n, s;
vector<ll> v1(100001); // 수열
vector<ll> v2(100001); // 누적합

struct range {
    ll start;
    ll end;
};

static inline ll getSum(ll start, ll end) {
    return v2[end] - v2[start - 1];
}

static inline ll getLen(ll start, ll end) {
    return end - start + 1;
}


ll search(ll start, ll end) {
    ll sum0 = getSum(start, end);
    if (sum0 < s) {
        return 0;
    }
    else if (sum0 == s) {
        return getLen(start, end);
    }
    else { // 초기 상태가 s 초과일 때
        ll ret;

        while (true) {
            ret = getLen(start, end);

            if (getSum(start + 1, end) >= s) { // 길이 좌 하나 줄어듦 (-1)
                start += 1;
            }
            else if (getSum(start, end - 1) >= s) { // 길이 우 하나 줄어듦 (-1)
                end -= 1;
            }
            else { // 앞이든 뒤든 줄이면 s보다 작아짐
                break;
            }
        }

        return ret;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    v1[0] = 0;
    v2[0] = 0;

    cin >> n >> s;

    for (ll i = 1; i <= n; i++) {
        cin >> v1[i];
        v2[i] = v2[i - 1] + v1[i];
    }

    for(int i=1; i<=n; i++){
        cout << v1[i] << " " << v2[i] << "\n";
    }

    cout << search(1, n);
}