#include <iostream>
#include <vector>
#include <queue>

#define DEBUG 0

using ui = u_int32_t;

using namespace std;

vector<int> ans;

// top()이 중간에 가까워야 함
priority_queue<int>
        descending; // (*50, 49, 48, ...)
priority_queue<int, vector<int>, greater<int>>
        ascending; // (*51, 52, 53, ...)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#if DEBUG
    vector<int> tmp;
    ui sz;
#endif

    int n, x;
    cin >> n;

    /**
     * for 로직이 des, asc가 적어도 원소 하나씩은 가지고 있어야 작동 가능하기에
     * 처음 두 번은 그냥 예외적으로 처리해야 할듯..
     */

    // 첫 번째 입력
    cin >> x;
    ascending.push(x);
    ans.push_back(ascending.top());

#if DEBUG
    sz = descending.size();
    for (int j = 0; j < sz; j++) {
        tmp.push_back(descending.top());
        descending.pop();
    }

    cout << "des : *";
    for (auto it: tmp) {
        cout << it << " ";
        descending.push(it);
    }
    cout << "\n";
    tmp.clear();

    sz = ascending.size();
    for (int j = 0; j < sz; j++) {
        tmp.push_back(ascending.top());
        ascending.pop();
    }

    cout << "asc : *";
    for (auto it: tmp) {
        cout << it << " ";
        ascending.push(it);
    }
    cout << "\n";
    tmp.clear();

    cout << ans.back() << " pushed\n\n";
#endif


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
    ans.push_back(descending.top());

#if DEBUG
    sz = descending.size();
    for (int j = 0; j < sz; j++) {
        tmp.push_back(descending.top());
        descending.pop();
    }

    cout << "des : *";
    for (auto it: tmp) {
        cout << it << " ";
        descending.push(it);
    }
    cout << "\n";
    tmp.clear();

    sz = ascending.size();
    for (int j = 0; j < sz; j++) {
        tmp.push_back(ascending.top());
        ascending.pop();
    }

    cout << "asc : *";
    for (auto it: tmp) {
        cout << it << " ";
        ascending.push(it);
    }
    cout << "\n";
    tmp.clear();

    cout << ans.back() << " pushed\n\n";
#endif


    // 세 번째 입력부터
    for (int i = 3; i <= n; i++) {
        cin >> x;
        ascending.push(x); // 일단 ascending에 push

        /// 0. des.top < asc.top이 되도록 맞춰줌
        while (descending.top() > ascending.top()) {
            /// des.top <= asc.top이 되면 탈출
            // asc -> des
            descending.push(ascending.top());
            ascending.pop();
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

            ans.push_back(ascending.top());
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

            ans.push_back(descending.top());
        }

#if DEBUG
        sz = descending.size();
        for (int j = 0; j < sz; j++) {
            tmp.push_back(descending.top());
            descending.pop();
        }

        cout << "des : *";
        for (auto it: tmp) {
            cout << it << " ";
            descending.push(it);
        }
        cout << "\n";
        tmp.clear();

        sz = ascending.size();
        for (int j = 0; j < sz; j++) {
            tmp.push_back(ascending.top());
            ascending.pop();
        }

        cout << "asc : *";
        for (auto it: tmp) {
            cout << it << " ";
            ascending.push(it);
        }
        cout << "\n";
        tmp.clear();

        cout << ans.back() << " pushed\n\n";
#endif

    }

    for (auto it: ans) {
        cout << it << "\n";
    }
}