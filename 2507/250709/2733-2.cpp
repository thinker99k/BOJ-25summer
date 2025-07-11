#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <cstring>

#define DEBUG 0

using namespace std;

vector<string> ans;

typedef u_int8_t BYTE;

/** 메모리, 버퍼 */
BYTE mem[32768];
BYTE *ptr;
unordered_map<int, int> br_pair;
string IN;
int IN_IDX;
string OUT;

/** 상수 */
BYTE *const mem_start = &mem[0];
BYTE *const mem_end = &mem[32767];
string const ERR = "COMPILE ERROR";

void init() {
    memset(mem_start, 0, sizeof(mem));
    ptr = mem_start;
    br_pair.clear();
    IN.clear();
    IN_IDX = 0;
    OUT.clear();
}

/** 명령어 */
// > : 포인터 증가
static inline void GTR() {
    if (ptr == mem_end) {
        ptr = mem_start;
    }
    else {
        ++ptr;
    }
}

// < : 포인터 감소
static inline void LES() {
    if (ptr == mem_start) {
        ptr = mem_end;
    }
    else {
        --ptr;
    }
}

// + : 포인터가 가리키는 값 증가
static inline void PLUS() {
    ++(*ptr);
}

// - : 포인터가 가리키는 값 감소
static inline void MINUS() {
    --(*ptr);
};

// . : 포인터가 가리키는 값 출력
static inline void DOT() {
    OUT += (char) *ptr;
#if DEBUG
    cout << (char) *ptr;
#endif
}

// [ : 포인터가 가리키는 값이 0이면, 짝이 되는 뒤쪽의 ]로 이동
static inline void LR() {
    if ((*ptr) == 0) {
        IN_IDX = br_pair[IN_IDX];
    }
}

// ] : 포인터가 가리키는 값이 0이 아니면, 짝이 되는 앞쪽의 [로 이동
static inline void RR() {
    if ((*ptr) != 0) {
        IN_IDX = br_pair[IN_IDX];
    }
}

/* yacc에서는
 * ( ) : LP, RP (Parenthesis)
 * { } : LB, RB (Bracket)
 * [ ] : LR, RR (bRacket)
 * 으로 토큰화
 */

static inline void OP2(char &ch) {
    switch (ch) {
        case '>': {
            GTR();
            break;
        }
        case '<': {
            LES();
            break;
        }
        case '+': {
            PLUS();
            break;
        }
        case '-': {
            MINUS();
            break;
        }
        case '.': {
            DOT();
            break;
        }
        case '[': {
            LR();
            break;
        }
        case ']': {
            RR();
            break;
        }
        default: {
            // 상기 7개 operator 외에는 아무 것도 하면 안됨
            break;
        }
    }
}

// 컴파일 에러가 없는 코드가 들어옴이 보장
string compiler2() {
    int len = (int) IN.length();
    while (IN_IDX < len) {
        OP2(IN[IN_IDX]);
        IN_IDX++;
    }

    return OUT;
}

// 컴파일 에러 미리 점검
bool chkBracket() {
    stack<int> stk;
    int open;

    int len = (int) IN.length();
    for (int i = 0; i < len; i++) {
        if (IN[i] == '[') { // 여는 괄호
            stk.push(i);
        }
        else if (IN[i] == ']') { // 닫는 괄호
            if (stk.empty()) { // 스택에서 뽑아야 하는데 여는 괄호가 남아있지 않음
                return false;
            }
            open = stk.top();
            stk.pop();

            // 메모리(mem)에서 이동이 아닌 코드(IN)에서 이동
            br_pair[open] = i;
            br_pair[i] = open;
        }
        else { // 그외
            ; // 무시
        }
    }

    /* 뽑을거 다 뽑았는데
     * 스택에 여는 괄호가 남아있음 (덜 뽑아냄) -> false
     * 스택이 비어있음 -> true */
    return stk.empty();
}

void solve() {
    string line;

    while (true) {
        getline(cin, line); // c++ 스트림

        // 프로그램 끝 -> 입력 종료
        if (line == "end") {
            break;
        }

        size_t percent = line.find('%');
        if (percent == string::npos) { // 주석 없을 때
            IN += line; // 전체 이어붙히기
        }
        else { // 주석 있을 때
            IN += line.substr(0, percent); // 주석 전까지 이어붙히기
        }
    }
#if DEBUG
    cout << IN << "\n";
#endif

    if (chkBracket()) { // 괄호가 짝이 맞으면
#if DEBUG
        for(auto it : br_pair){
            cout << it.first << " " << it.second << "\n";
        }
#endif
        ans.push_back(compiler2());
    }
    else { // 괄호가 짝이 안 맞으면
        ans.push_back(ERR);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        init();
        solve();
    }

    for (int i = 1; i <= n; i++) {
        cout << "PROGRAM #" << i << ":\n";
        cout << ans[i - 1] << "\n";
    }
}