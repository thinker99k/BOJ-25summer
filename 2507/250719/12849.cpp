#include <iostream>
#include <vector>

typedef long long ll;

ll const prime = 1e9 + 7;
ll ans;

using namespace std;

int LIM;

vector<int> ssu[8];

// row = time, col = bd
ll dp[1000001][8];

enum {
    it,
    cs,
    faith,
    truth,
    student,
    hyungnam,
    chapel,
    future
};

inline void link(int x, int y) {
    ssu[x].push_back(y);
    ssu[y].push_back(x);
}

void init() {
    link(it, cs);
    link(cs, faith);
    link(faith, truth);
    link(truth, student);
    link(student, hyungnam);
    link(hyungnam, chapel);
    link(chapel, future);
    link(future, it);
    link(cs, future);
    link(future, faith);
    link(faith, chapel);
    link(chapel, truth);

    dp[0][0] = 1;
}

inline void modulo(ll *ptr) {
    *ptr %= prime;

    if (*ptr < 0) {
        *ptr += prime;
    }
}

void solve() {
    int TIME, BD;
    for (TIME = 0; TIME < LIM; TIME++) {
        // 1. 이번 TIME -> MODULO
        for (BD = 0; BD <= 7; BD++) {
            modulo(&dp[TIME][BD]);
        }

        // 2. 다음 TIME -> 배열 연산
        for (BD = 0; BD <= 7; BD++) {
            if (dp[TIME][BD]) {
                for (auto &iter: ssu[BD]) { // 인접한 건물에 대해
                    dp[TIME + 1][iter] += dp[TIME][BD]; // 경우의 수 증가
                }
            }
        }
    }

    // 마지막 TIME = LIM -> MODULO
    for (BD = 0; BD <= 7; BD++) {
        modulo(&dp[LIM][BD]);
    }

    ans = dp[LIM][it];
}

int main() {
    init();

    cin >> LIM;

    solve();

    cout << (int) ans;
}