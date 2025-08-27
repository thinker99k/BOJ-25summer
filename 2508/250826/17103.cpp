#include <iostream>
#include <vector>

#define MILLION 1000000

using namespace std;

vector<bool> isPrime(MILLION + 1, true);

void init() {
    isPrime[0] = isPrime[1] = false;
    for (int p = 2; p * p <= MILLION; ++p) {
        if (isPrime[p]) {
            for (int j = p * p; j <= MILLION; j += p) {
                isPrime[j] = false;
            }
        }
    }
}

inline int solve(int x) {
    int half = x / 2, remain, ret = 0;

    for (int i = 2; i <= half; i++) {
        remain = x - i;

        if (isPrime[i] && isPrime[remain]) {
            ret++;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    init();

    int T, x;
    cin >> T;

    for (int i = 0; i < T; i++) {
        cin >> x;
        cout << solve(x) << "\n";
    }
}