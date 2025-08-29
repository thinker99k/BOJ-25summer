#include <iostream>
#include <vector>

using namespace std;
using ll = long long;


vector<ll> arr;

ll n, m;

inline ll getMid(ll start, ll end) {
    return (start + end) / 2;
}

namespace two {
    vector<ll> tree;

    void tInit(ll node,
               ll start, ll end) {
        if (start == end) {
            tree[node] = arr[start];
        }
        else {
            ll mid = getMid(start, end);
            tInit(2 * node,
                  start, mid);
            tInit(2 * node + 1,
                  mid + 1, end);

            tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
        }
    }

    void tUpdate(ll node, ll start, ll end,
                 ll idx, ll val) {
        if (idx < start || idx > end) {
            return;
        }

        if (start == end) {
            arr[idx] = val;
            tree[node] = val;
            return;
        }

        ll mid = getMid(start, end);
        tUpdate(node * 2, start, mid,
                idx, val);
        tUpdate(node * 2 + 1, mid + 1, end,
                idx, val);

        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    ll tMax(ll node, ll start, ll end,
            ll left, ll right) {
        if (left > end || right < start) {
            return 0;
        }

        if (left <= start && end <= right) {
            return tree[node];
        }

        ll mid = getMid(start, end);
        ll left_max = tMax(node * 2, start, mid,
                           left, right);
        ll right_max = tMax(node * 2 + 1, mid + 1, end,
                            left, right);

        if (!left_max) {
            return right_max;
        }
        else if (!right_max) {
            return left_max;
        }
        else {
            return max(left_max, right_max);
        }
    }
}

#define ROOT 1

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    two::tree.resize(4 * n);
    arr.resize(n + 1);

    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    two::tInit(ROOT, 1, n);

    vector<ll> ans;

    ll x, y, a, b;
    for (ll i = 0; i < m; i++) {
        cin >> x >> y >> a >> b;

        ans.push_back(two::tMax(ROOT, 1, n, x, y));
        two::tUpdate(ROOT, 1, n, a, b);
    }

    for (auto it: ans) {
        cout << it << "\n";
    }
}

