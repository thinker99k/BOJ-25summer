#include <iostream>
#include <vector>
#include <queue>

using ui = u_int32_t;

using namespace std;

vector<vector<int>> ans;

void solve() {
    vector<int> tcans;

    // top()이 중간에 가까워야 함
    priority_queue<int>
            descending; // (*50, 49, 48, ...)
    priority_queue<int, vector<int>, greater<int>>
            ascending; // (*51, 52, 53, ...)

    /**
    * for 로직이 des, asc가 적어도 원소 하나씩은 가지고 있어야 작동 가능하기에
    * 처음 두 번은 그냥 예외적으로 처리해야 할듯..
    */

    int n, x;
    cin >> n;

    // 첫 번째 입력
    cin >> x;
    ascending.push(x);
    tcans.push_back(ascending.top());

    if (n == 1) {
        ans.push_back(tcans);
        return;
    }

    // 두 번째 입력
    cin >> x;
    if (x > ascending.top()) {
        descending.push(ascending.top());
        ascending.pop();
        ascending.push(x);
    }
    else {
        descending.push(x);
    }
    /** 짝수번째 입력 정답 투입 x */
    // tcans.push_back(descending.top());

    if (n == 2) {
        ans.push_back(tcans);
        return;
    }

    // 세 번째 입력부터
    for (int i = 3; i <= n; i++) {
        cin >> x;

        /**
         * 0. 경우 나눠서 push
         */
        if (x < descending.top()) {
            descending.push(x);
        }
        else {
            ascending.push(x);
        }

        if ((ascending.size() + descending.size()) % 2) {
            /**
             * des.size + asc.size = 홀수
             * (des, asc는 이어져서 정렬되어 있음이 보장)
             * 1. des.size = asc.size - 1가 되도록 맞춰줌 (asc가 하나 많음)
             * 2. asc.top 가져옴 (딱 중앙 값)
             */

            if (ascending.size() - 1u > descending.size()) {
                // asc -> des
                while (ascending.size() - 1u > descending.size()) {
                    descending.push(ascending.top());
                    ascending.pop();
                }
            }
            else if (descending.size() > ascending.size() - 1u) {
                // des -> asc
                while (descending.size() > ascending.size() - 1u) {
                    ascending.push(descending.top());
                    descending.pop();
                }
            }

            tcans.push_back(ascending.top());
        }
        else {
            /**
             * des.size + asc.size = 짝수
             * (des, asc는 이어져서 정렬되어 있음이 보장)
             * 1. des.size = asc.size가 되도록 맞춰줌
             * 2. des.top 가져옴 (중앙에서 왼쪽 값)
             */

            if (ascending.size() > descending.size()) {
                // asc -> des
                while (ascending.size() > descending.size()) {
                    descending.push(ascending.top());
                    ascending.pop();
                }
            }
            else if (descending.size() > ascending.size()) {
                // des -> asc
                while (descending.size() > ascending.size()) {
                    ascending.push(descending.top());
                    descending.pop();
                }
            }

            /** 짝수번째 입력 정답 투입 x */
            // tcans.push_back(descending.top());
        }
    }

    ans.push_back(tcans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc;
    cin >> tc;

    for (int i = 0; i < tc; i++) {
        solve();
    }

    ui cnt;
    for (auto &it: ans) {
        cnt = it.size();
        cout << cnt << "\n";

        for (int i = 1; i <= cnt; i++) {
            cout << it[i - 1] << " ";

            if (i % 10 == 0) {
                cout << "\n";
            }
        }

        cout << "\n";
    }
}