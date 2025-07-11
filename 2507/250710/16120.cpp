#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

#define DEBUG 0

using namespace std;

string IN;
int IN_len;

string const PPAP = "PPAP";
int const PPAP_len = 4;
int const PPA_len = 3;

stack<char> stk;

bool solve() {
    int const IDX_LIM = IN_len - 1; // 접근 가능한 인덱스의 끝

    for (int i = 0; i <= IDX_LIM; i++) {
        stk.push(IN[i]); // ? ? x y -> ? ? x y A

        if (stk.size() >= PPA_len) { // "PPA"의 길이 = 3
            if (stk.top() == 'A' && // 트리거
                i + 1 <= IDX_LIM && // 문자열 다음 인덱스에 접근 가능
                IN[i + 1] == 'P') { // 그 다음 접근한게 'P'

                stk.push(IN[i + 1]); // ? ? x y A -> ? ? x y A P

                string tmp;

                tmp += stk.top(); // P
                stk.pop(); // ? ? x y A P -> ? ? x y A

                tmp += stk.top(); // P A
                stk.pop(); // ? ? x y A -> ? ? x y

                tmp += stk.top(); // P A y
                stk.pop(); // ? ? x y -> ? ? x

                tmp += stk.top(); // P A y x
                stk.pop(); // ? ? x -> ? ?

                reverse(tmp.begin(), tmp.end()); // x y A P
#if DEBUG
                cout << "tmp : " << tmp << "\n";
#endif
                if (tmp != PPAP) { // x y 둘중 하나는 P가 아님
                    // 복원
                    for (int j = 0; j < PPAP_len; j++) {
                        stk.push(tmp[j]);
                    }
                }
                else { // x, y 둘 다 P
                    /** 문자열 폭발 문제와 다른 점
                     * : 사라지는게 아닌 PPAP -> P로 대체됨 */
                    stk.push('P');

                    ++i;
                }
            }
        }
    }

    /** 모든 문자열이 PPAP -> P로 치환되면
     * 최종적으로 스택에 P 하나 남아있음
     */

    return (stk.size() == 1 && stk.top() == 'P');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> IN;
    IN_len = (int) IN.length();

    if (solve()) {
        cout << PPAP << "\n";
    }
    else {
        cout << "NP\n";
    }
}