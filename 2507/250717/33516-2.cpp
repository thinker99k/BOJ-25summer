#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <unordered_set>

#define DEBUG 0

using namespace std;

string IN;
int IDX_LIM;

string const skeep = "skeep";
int const skeep_len = 5;

/**
 * 문자열에서 skeep이라는 연속한 부분 문자열을 찾아 s를 제외한 소문자 알파벳 하나로 바꾼다.
 */
unordered_set<string> skeep_variant = {
        // ? 0개 -> 5c0 = 1
        "skeep",

        // (? 1개 -> 5c1 = 5) - (s 대체 = 1) = 4
        "s?eep", "sk?ep", "ske?p", "skee?",

        // (? 2개 -> 5c2 = 10) - (s 대체 = 4) = 6
        "s??ep", "s?e?p", "s?ee?", "sk??p", "sk?e?", "ske??",

        // (? 3개 -> 5c3 = 10) - (s 대체 = 6) = 4
        "s???p", "s??e?", "s?e??", "sk???",

        // (? 4개 -> 5c4 = 5) - (s 대체 = 4) = 1
        "s????",

        // (? 5개 -> 5c5 = 1) - (s 대체 = 1) = 0
};

stack<char> stk;
int ans = 0;
bool trans;

static inline bool solve2() {
    if (trans) { // "skeep"의 길이 = 5
        if (stk.top() == 'p' || stk.top() == '?') { // 트리거

            string tmp;

            tmp += stk.top(); // p
            stk.pop(); // * * 1 2 3 4 p -> * * 1 2 3 4

            tmp += stk.top(); // p 4
            stk.pop(); // * * 1 2 3 4   -> * * 1 2 3

            tmp += stk.top(); // p 4 3
            stk.pop(); // * * 1 2 3     -> * * 1 2

            tmp += stk.top(); // p 4 3 2
            stk.pop(); // * * 1 2       -> * * 1

            tmp += stk.top(); // p 4 3 2 1
            stk.pop(); // * * 1         -> * *

            reverse(tmp.begin(), tmp.end()); // 1 2 3 4 p
#if DEBUG
            cout << "tmp : " << tmp << "\n";
#endif
            if (skeep_variant.count(tmp)) { // skeep 혹은 파생에 해당할 경우
                /** ? 는 만능문자 */
                stk.push('?');
                ++ans; // 치환 갯수 늘려줌

                trans = true;
                return true;
            }
            else {
                // 복원
                for (int j = 0; j < skeep_len; j++) {
                    stk.push(tmp[j]);
                }

                trans = false; // 더이상 치환 진행 불가
                return false;
            }
        }
    }

    return false;
}

static inline void solve1(){
    trans = stk.size() >= skeep_len;
    while (trans) {
        trans = stk.size() >= skeep_len;

        if (!solve2()) {
            break;
        }
    }
}
static inline void solve() {
    for (int i = 0; i <= IDX_LIM; i++) {
        stk.push(IN[i]); // * * 1 2 3 4 -> * * 1 2 3 4 p

        solve1();
    }

    // 스택에 남은것들
    solve1();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> IDX_LIM;
    cin >> IN;

    --IDX_LIM; // 접근 가능한 인덱스의 끝
    solve();

    cout << ans;
}