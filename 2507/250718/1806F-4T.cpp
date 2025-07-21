#include <iostream>

#define DEBUG 0

using namespace std;

int END;
int tosearch;

int v1[100001]; // sequence
int v2[100001]; // prefix sum

inline int getSum(int start, int end) {
    return v2[end] - v2[start - 1];
}

#define idx_len (idx_e - idx_s + 1);

#define idx_e (idx_s + len - 1)

int search(int len) {
    for (int idx_s = 1; idx_e <= END; idx_s++) {
        // 이번 길이에서 찾음 -> 길이 반환
        if (getSum(idx_s, idx_e) >= tosearch) {
            return idx_len;
        }
    }

    // 이번 길이에서 못찾음 -> 0 반환
    return 0;
}

int solve() {
    int ret;

    // 짧은 길이부터 탐색 확장해나감
    for (int len = 1; len <= END; len++) {
        ret = search(len);

        // 이번 길이에서 찾음 -> 길이 반환
        if (ret) {
            return ret;
        }
    }

    // 결국 못찾음 ->  0 반환
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> END >> tosearch;

    for (int i = 1; i <= END; i++) {
        cin >> v1[i];
        v2[i] = v2[i - 1] + v1[i];
    }


    cout << solve();
}