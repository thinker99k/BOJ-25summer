#include <iostream>
#include <vector>

#define LIM 250000

using namespace std;

typedef unsigned long long ll;

// [0] ~ [250000] -> 250001개
vector<bool> prime(LIM + 1, true);
vector<ll> sum(LIM + 1, 0);

void init() {
    prime[0] = false;
    prime[1] = false;

    for (ll i = 2; i * i <= LIM; i++) {
        if (prime[i]) {
            for (ll j = i * i; j <= LIM; j += i) {
                prime[j] = false;
            }
        }
    }

    sum[0] = 0;
    sum[1] = 0;

    for (ll i = 2; i <= LIM; i++) {
        if (prime[i]) {
            sum[i] = sum[i - 1] + 1;
        }
        else {
            sum[i] = sum[i - 1];
        }
    }
}

// start < x <= end
static inline ll find(ll start, ll end) {
    // prefix sum
    return sum[end] - sum[start];
}

vector<ll> ans;

int main() {
    init();

    ll n;
    while (true) {
        cin >> n;

        if (n == 0) {
            break;
        }

        ans.push_back(find(n, 2 * n));
    }

    for (auto it: ans) {
        cout << it << "\n";
    }
}