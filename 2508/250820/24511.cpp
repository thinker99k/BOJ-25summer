#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, x;
    cin >> n;

    vector<int> isStack(n);
    vector<int> initVal(n);

    // x ? stack : queue
    for (int i = 0; i < n; i++) {
        cin >> isStack[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> initVal[i];
    }

    deque<int> qs; // 기존 큐와 다르게 -> 방향으로 작동

    // initial queuestack values
    for (int i = 0; i < n; i++) {
        /** stack인 곳의 값은 입력해봐야 튕겨내기에 무시해도 됨 */
        if (!isStack[i]) {
            // 큐일 때
            qs.push_back(initVal[i]);
        }
    }

    cin >> n;
    vector<int> ans;

    for (int i = 0; i < n; i++) {
        cin >> x;


        if (qs.empty()) {
            // 스택으로 작동
            ans.push_back(x);
        }
        else {
            // 큐로 작동
            qs.push_front(x);
            ans.push_back(qs.back());
            qs.pop_back();
        }
    }

    for (auto it: ans) {
        cout << it << " ";
    }
}