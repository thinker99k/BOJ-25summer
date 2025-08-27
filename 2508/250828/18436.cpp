#include <iostream>
#include <vector>

using namespace std;
using ll = long long;


vector<ll> arr;

ll n, opcnt;

inline ll getMid(ll start, ll end) {
    return (start + end) / 2;
}

// ODD
namespace one {
    vector<ll> tree;

    inline ll isOdd(ll &x) {
        return x & 1 ? 1 : 0;
    }

    void tInit(ll node,
               ll start, ll end) {
        if (start == end) {
            tree[node] = isOdd(arr[start]);
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
            tree[node] = isOdd(val);
            return;
        }

        ll mid = getMid(start, end);
        tUpdate(node * 2, start, mid,
                idx, val);
        tUpdate(node * 2 + 1, mid + 1, end,
                idx, val);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    ll tOdd(ll node, ll start, ll end,
            ll left, ll right) {
        if (left > end || right < start) {
            return 0;
        }

        if (left <= start && end <= right) {
            return tree[node];
        }

        ll mid = getMid(start, end);
        ll left_odd = tOdd(node * 2, start, mid,
                           left, right);
        ll right_odd = tOdd(node * 2 + 1, mid + 1, end,
                            left, right);

        if (!left_odd) {
            return right_odd;
        }
        else if (!right_odd) {
            return left_odd;
        }
        else {
            return left_odd + right_odd;
        }
    }
}

// EVEN
namespace two {
    vector<ll> tree;

    inline ll isEven(ll &x) {
        return x & 1 ? 0 : 1;
    }

    void tInit(ll node,
               ll start, ll end) {
        if (start == end) {
            tree[node] = isEven(arr[start]);
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
            tree[node] = isEven(val);
            return;
        }

        ll mid = getMid(start, end);
        tUpdate(node * 2, start, mid,
                idx, val);
        tUpdate(node * 2 + 1, mid + 1, end,
                idx, val);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    ll tEven(ll node, ll start, ll end,
             ll left, ll right) {
        if (left > end || right < start) {
            return 0;
        }

        if (left <= start && end <= right) {
            return tree[node];
        }

        ll mid = getMid(start, end);
        ll left_even = tEven(node * 2, start, mid,
                             left, right);
        ll right_even = tEven(node * 2 + 1, mid + 1, end,
                              left, right);

        if (!left_even) {
            return right_even;
        }
        else if (!right_even) {
            return left_even;
        }
        else {
            return left_even + right_even;
        }
    }
}


#define ROOT 1

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    one::tree.resize(4 * n);
    two::tree.resize(4 * n);
    arr.resize(n + 1);

    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    one::tInit(ROOT, 1, n);
    two::tInit(ROOT, 1, n);

    vector<ll> ans;

    cin >> opcnt;

    ll o, a, b;
    for (ll i = 0; i < opcnt; i++) {
        cin >> o >> a >> b;

        switch (o) {
            case 1: {
                one::tUpdate(ROOT, 1, n,
                             a, b);
                two::tUpdate(ROOT, 1, n,
                             a, b);
                break;
            }
            case 2: {
                ans.push_back(
                        two::tEven(ROOT, 1, n,
                                   a, b));
                break;
            }
            case 3: {
                ans.push_back(
                        one::tOdd(ROOT, 1, n,
                                  a, b));

                break;
            }
            default: { ;
            }
        }
    }

    for (auto it: ans) {
        cout << it << "\n";
    }
}

