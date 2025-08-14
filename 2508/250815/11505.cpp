#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

vector<ll> tree;
vector<ll> arr;

ll n, op1sz, op2sz, opsz;

inline ll getMid(ll start, ll end) {
    return (start + end) / 2;
}

inline ll mod(ll x) {
    return x % 1000000007;
}

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

        tree[node] = mod(mod(tree[node * 2]) * mod(tree[node * 2 + 1]));
    }
}

// op1
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

    tree[node] = mod(mod(tree[node * 2]) * mod(tree[node * 2 + 1]));
}

// op2
ll tMul(ll node, ll start, ll end,
        ll left, ll right) {
    if (left > end || right < start) {
        return 1;
    }

    if (left <= start && end <= right) {
        return tree[node];
    }

    ll mid = getMid(start, end);
    ll left_mul = tMul(node * 2, start, mid,
                       left, right);
    ll right_mul = tMul(node * 2 + 1, mid + 1, end,
                        left, right);

    return mod(mod(left_mul) * mod(right_mul));
}

#define ROOT 1

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> op1sz >> op2sz;
    tree.resize(4 * n);
    arr.resize(n + 1);
    opsz = op1sz + op2sz;

    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    tInit(ROOT, 1, n);

    vector<ll> ans;

    ll o, a, b;
    for (ll i = 0; i < opsz; i++) {
        cin >> o >> a >> b;

        if (o == 1) {
            tUpdate(ROOT, 1, n,
                    a, b);
        }
        else {
            ans.push_back(
                    tMul(ROOT, 1, n,
                         a, b));
        }
    }

    for (auto it: ans) {
        cout << it << "\n";
    }
}

