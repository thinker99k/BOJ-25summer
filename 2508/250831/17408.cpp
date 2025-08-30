#include <iostream>
#include <vector>
#include <array>

#define DEBUG 0

using namespace std;

using ii = pair<int, int>;

vector<int> arr;

// first : 가장 큰 수, second : 두 번째로 큰 수
vector<ii> tree;

inline int getMid(int start, int end) {
    return (start + end) / 2;
}

int tmp[4];

ii getFirstSecond() {
    int max1 = tmp[0], max2 = 0, x;

    for(int i=1; i<4; i++){
        x = tmp[i];
        if (x > max1) {
            max2 = max1;
            max1 = x;
        }
        else if (x > max2) {
            max2 = x;
        }
    }

    return {max1, max2};
}

void tInit(int node,
           int start, int end) {
    if (start == end) {
        tree[node] = {arr[start], 0};
    }
    else {
        int mid = getMid(start, end);
        tInit(2 * node,
              start, mid);
        tInit(2 * node + 1,
              mid + 1, end);

        tmp[0] = tree[node * 2].first,
        tmp[1] = tree[node * 2].second,
        tmp[2] = tree[node * 2 + 1].first,
        tmp[3] = tree[node * 2 + 1].second;

        tree[node] = getFirstSecond();
    }
}

void tUpdate(int node, int start, int end,
             int idx, int val) {
    if (idx < start || idx > end) {
        return;
    }

    if (start == end) {
        arr[idx] = val;
        tree[node].first = val;
        return;
    }

    int mid = getMid(start, end);
    tUpdate(node * 2, start, mid,
            idx, val);
    tUpdate(node * 2 + 1, mid + 1, end,
            idx, val);

    tmp[0] = tree[node * 2].first,
    tmp[1] = tree[node * 2].second,
    tmp[2] = tree[node * 2 + 1].first,
    tmp[3] = tree[node * 2 + 1].second;

    tree[node] = getFirstSecond();
}

ii tSumMax(int node, int start, int end,
           int left, int right) {
    if (left > end || right < start) {
        return {0, 0};
    }

    if (left <= start && end <= right) {
        return tree[node];
    }

    int mid = getMid(start, end);
    ii leftSumMax = tSumMax(node * 2, start, mid,
                            left, right);
    ii rightSumMax = tSumMax(node * 2 + 1, mid + 1, end,
                             left, right);

    tmp[0] = leftSumMax.first,
    tmp[1] = leftSumMax.second,
    tmp[2] = rightSumMax.first,
    tmp[3] = rightSumMax.second;

    return getFirstSecond();
}

#define ROOT 1

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, op, a, b;
    cin >> n;
    tree.resize(4 * n);
    arr.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    tInit(ROOT, 1, n);

    vector<int> ans;

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> op >> a >> b;

        switch (op) {
            case 1: {
                tUpdate(ROOT, 1, n,
                        a, b);
                break;
            }
            case 2: {
                ii ret = tSumMax(ROOT, 1, n, a, b);
#if DEBUG
                cout << ret.first << " " << ret.second << "\n";
#endif
                ans.push_back(ret.first + ret.second);
            }
        }
    }

    for (auto it: ans) {
        cout << it << "\n";
    }
}