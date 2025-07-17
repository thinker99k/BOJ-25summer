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
int const skee_len = 4;

stack<char> stk;

/**
 * 문자열에서 skeep이라는 연속한 부분 문자열을 찾아 s를 제외한 소문자 알파벳 하나로 바꾼다.
 */
unordered_set<string> skeep_variant = {
        // ? 0개 -> 5c0 = 1
        "skeep",

        // (? 1개 -> 5c1 = 5)
        // - (s 대체 = 1)
        // = 4

        "s?eep", "sk?ep", "ske?p", "skee?",

        // (? 2개 -> 5c2 = 10)
        // - (s 대체 = 4)
        // = 6
        "s??ep",
        "s?e?p", "s?ee?", "sk??p", "sk?e?", "ske??",

        // (? 3개 -> 5c3 = 10)
        // - (s 대체 = 6)
        // = 4
        "s???p", "s??e?", "s?e??", "sk???",

        // (? 4개 -> 5c4 = 5)
        // - (s 대체 = 4)
        // = 1
        "s????",

        // (? 5개 -> 5c5 = 1)
        // - (s 대체 = 1)
        // = 0
};

int solve() {
    int ret = 0;

    IDX_LIM--; // 접근 가능한 인덱스의 끝

    for (int i = 0; i <= IDX_LIM; i++) {
        stk.push(IN[i]); // ? ? 1 2 3 -> ? ? 1 2 3 e

        if (stk.size() >= skee_len) { // "skee"의 길이 = 4
            if ((stk.top() == 'e' || stk.top() == '?') && // 트리거
                i + 1 <= IDX_LIM && // 문자열 다음 인덱스에 접근 가능
                IN[i + 1] == 'p') { // 그 다음 접근한게 'P'

                stk.push(IN[i + 1]); // ? ? 1 2 3 e -> ? ? 1 2 3 e p

                string tmp;

                tmp += stk.top(); // p
                stk.pop(); // ? ? 1 2 3 e p -> ? ? 1 2 3 e

                tmp += stk.top(); // p e
                stk.pop(); // ? ? 1 2 3 e   -> ? ? 1 2 3

                tmp += stk.top(); // p e 3
                stk.pop(); // ? ? 1 2 3     -> ? ? 1 2

                tmp += stk.top(); // p e 3 2
                stk.pop(); // ? ? 1 2       -> ? ? 1

                tmp += stk.top(); // p e 3 2 1
                stk.pop(); // ? ? 1         -> ? ?

                reverse(tmp.begin(), tmp.end()); // 1 2 3 e p
#if DEBUG
                cout << "tmp : " << tmp << "\n";
#endif
                if(skeep_variant.count(tmp)){ // skeep 혹은 파생에 해당할 경우
                    /** ? 는 만능문자 */
                    stk.push('?');

                    ++ret; // 치환 갯수 늘려줌
                    ++i; // 다음 인덱스 여기서 탐색 완료함
                }
                else {
                    // 복원
                    for (int j = 0; j < skeep_len; j++) {
                        stk.push(tmp[j]);
                    }
                }
            }
        }
    }

    string tmp;

    // 원래 문자열 끝까지 탐색하고 스택 남은 것들
    if(stk.size() >= 5){
        tmp += stk.top(); // p
        stk.pop(); // ? ? 1 2 3 e p -> ? ? 1 2 3 e

        tmp += stk.top(); // p e
        stk.pop(); // ? ? 1 2 3 e   -> ? ? 1 2 3

        tmp += stk.top(); // p e 3
        stk.pop(); // ? ? 1 2 3     -> ? ? 1 2

        tmp += stk.top(); // p e 3 2
        stk.pop(); // ? ? 1 2       -> ? ? 1

        tmp += stk.top(); // p e 3 2 1
        stk.pop(); // ? ? 1         -> ? ?

        reverse(tmp.begin(), tmp.end()); // 1 2 3 e p
#if DEBUG
        cout << "tmp : " << tmp << "\n";
#endif
        if(skeep_variant.count(tmp)){ // skeep 혹은 파생에 해당할 경우
            /** ? 는 만능문자 */
            stk.push('?');

            ++ret; // 치환 갯수 늘려줌
        }
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> IDX_LIM;
    cin >> IN;

    cout << solve();
}