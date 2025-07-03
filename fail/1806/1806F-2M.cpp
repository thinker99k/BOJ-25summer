#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>

using namespace std;

typedef long long ll;

ll n, s;
vector<ll> v(100001); // 누적합 저장됨

struct range {
    ll start;
    ll end;
};

static inline ll getSum2(range &r) {
    return v[r.end] - v[r.start - 1];
}

static inline ll getLen2(range &r) {
    return r.end - r.start + 1;
}

ll search2(ll start, ll end) {
    ll ret = INT64_MAX;

    queue<range> q;
    q.push({start, end});

    range curr;
    ll sum;

    while (!q.empty()) {
        curr = q.front();
        q.pop();

        sum = getSum2(curr);

        if(sum > s){
            ret = getLen2(curr);

            q.push({curr.start+1, curr.end});
            q.push({curr.start, curr.end-1});
        }
        else if(sum == s){
            ret = getLen2(curr);
        }
    }

    return ret;
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

    cout << search2(1, n);

}