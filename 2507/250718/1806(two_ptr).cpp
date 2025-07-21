#include <iostream>

using namespace std;

int END;
int tosearch;

int arr[100001];

/** 투포인터 조건 : 구간합 >= 검색값 */
static inline bool condition(int s) {
    return s >= tosearch;
}

int solve() {
    int len = 1e9 + 7, new_len;

    int L = 1, R = 1; // 구간
    int sum = 0; // 구간합

    while (R <= END) {
        // 1. R 탐색 -> 길이 늘림
        sum += arr[R];

        // 2. 투 포인터 탐색
        // 조건에 맞으면 맞지 않을 때까지
        while (condition(sum)) {
            // 2-1. L 탐색 -> 길이 줄임
            sum -= arr[L];

            // 2-2. new_len 갱신
            new_len = R - L + 1;
            len = min(len, new_len); // 짧은거 유지

            // 2-3. 이번 L 탐색 완료
            L++;
        }

        // 3. 이번 R 탐색 완료
        R++;
    }

    return (len == 1e9 + 7) ? 0 : len;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> END >> tosearch;

    for (int i = 1; i <= END; i++) {
        cin >> arr[i];
    }

    cout << solve();
}