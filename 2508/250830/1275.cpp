#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

vector<ll> arr;

ll n, m;

inline ll getMid(ll start, ll end) {
    return (start + end) / 2;
}


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

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
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

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll tSum(ll node, ll start, ll end,
        ll left, ll right) {
    if (left > end || right < start) {
        return 0;
    }

    if (left <= start && end <= right) {
        return tree[node];
    }

    ll mid = getMid(start, end);
    ll left_sum = tSum(node * 2, start, mid,
                       left, right);
    ll right_sum = tSum(node * 2 + 1, mid + 1, end,
                        left, right);

    return left_sum + right_sum;
}


#define ROOT 1

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    tree.resize(4 * n);
    arr.resize(n + 1);

    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    tInit(ROOT, 1, n);

    vector<ll> ans;

    ll x, y, a, b;
    for (ll i = 0; i < m; i++) {
        cin >> x >> y >> a >> b;
        if (x > y) {
            swap(x, y);
        }
        ans.push_back(tSum(ROOT, 1, n, x, y));
        tUpdate(ROOT, 1, n, a, b);
    }

    for (auto it: ans) {
        cout << it << "\n";
    }
}

