#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

vector<ll> arr;

ll n, m;

inline ll getMid(ll start, ll end) {
    return (start + end) / 2;
}

struct vi {
    ll val;
    ll idx;

    bool operator<(const vi &other) const {
        return (val == other.val) ? idx < other.idx : val < other.val;
    }

    bool operator>(const vi &other) const {
        return (val == other.val) ? idx > other.idx : val > other.val;
    }
};

namespace one {
    vector<vi> tree;

    void tInit(ll node,
               ll start, ll end) {
        if (start == end) {
            tree[node] = {arr[start], start};
        }
        else {
            ll mid = getMid(start, end);
            tInit(2 * node,
                  start, mid);
            tInit(2 * node + 1,
                  mid + 1, end);

            tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
        }
    }

    void tUpdate(ll node, ll start, ll end,
                 ll idx, ll val) {
        if (idx < start || idx > end) {
            return;
        }

        if (start == end) {
            arr[idx] = val;
            tree[node] = {val, idx};
            return;
        }

        ll mid = getMid(start, end);
        tUpdate(node * 2, start, mid,
                idx, val);
        tUpdate(node * 2 + 1, mid + 1, end,
                idx, val);

        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    vi tMin(ll node, ll start, ll end,
            ll left, ll right) {
        // 유효하지 않은 구간
        if (left > end || right < start) {
            return {0, 0};
        }

        if (left <= start && end <= right) {
            return tree[node];
        }

        ll mid = getMid(start, end);
        vi left_min = tMin(node * 2, start, mid,
                           left, right);
        vi right_min = tMin(node * 2 + 1, mid + 1, end,
                            left, right);

        if (!left_min.val) {
            return right_min;
        }
        else if (!right_min.val) {
            return left_min;
        }
        else {
            return min(left_min, right_min);
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
    arr.resize(n + 1);

    for (ll i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    one::tInit(ROOT, 1, n);

    cin >> m;

    vector<ll> ans;

    ll op, a, b;
    for (ll i = 0; i < m; i++) {
        cin >> op;

        if (op == 1) {
            cin >> a >> b;
            one::tUpdate(ROOT, 1, n,
                         a, b);
        }
        else {
            ans.push_back(
                    one::tMin(ROOT, 1, n,
                              1, n).idx);
        }
    }

    for (auto it: ans) {
        cout << it << "\n";
    }
}

