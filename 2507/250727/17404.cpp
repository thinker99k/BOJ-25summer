#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum {
    RED, GREEN, BLUE
};

struct house {
    int cost[3];
};

int num_v;
vector<house> v;

#define INF 1000000000

int solve2(int COLOR) {
    // 0으로 초기화
    int dp[3][1001];
    fill(&dp[0][0], &dp[2][1000], INF);

    dp[COLOR][0] = v[0].cost[COLOR];

    // 두번째부터 마지막번째 집까지 색칠
    for (int i = 1; i < num_v; i++) {
        // i번째는 i-1번째와 다른 색이어야 함
        dp[RED][i] = min(dp[GREEN][i - 1], dp[BLUE][i - 1]) + v[i].cost[RED];
        dp[GREEN][i] = min(dp[RED][i - 1], dp[BLUE][i - 1]) + v[i].cost[GREEN];
        dp[BLUE][i] = min(dp[RED][i - 1], dp[GREEN][i - 1]) + v[i].cost[BLUE];
    }

    // 한바퀴 순회 -> 첫 번째로 다시 돌아옴
    vector<int> ret(3);

    for (int c = 0; c < 3; c++) {
        ret[c] = c == COLOR ? INF : dp[c][num_v - 1];
    }

    return *min_element(ret.begin(), ret.end());
}

int solve() {
    return min({solve2(RED), solve2(GREEN), solve2(BLUE)});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> num_v;
    v.resize(num_v);

    for (int i = 0; i < num_v; i++) {
        cin >> v[i].cost[RED] >> v[i].cost[GREEN] >> v[i].cost[BLUE];
    }

    cout << solve();
}