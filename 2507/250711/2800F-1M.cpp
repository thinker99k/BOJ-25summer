#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

string str;
size_t str_len;

void input() {
    cin >> str;

    str_len = str.length();
}

struct brkt_pair {
    int open;
    int close;
};

vector<brkt_pair> brackets;
size_t brackets_size;

stack<int> stk;

// 올바른 괄호문자열이 들어옴이 보장됨
void chkBracket() {
    for (int i = 0; i < str_len; i++) {
        if (str[i] == '(') {
            // 여는 괄호의 인덱스를 스택에 push
            stk.push(i);
        }
        else if (str[i] == ')') {
            // {여는 괄호의 인덱스, 닫는 괄호의 인덱스}를 맵에 insert
            brackets.push_back({stk.top(), i});
            stk.pop();
        }
        else {
            // 괄호 외에는 전부 무시
            ;
        }
    }

    brackets_size = brackets.size();
}

// 정답 문자열 저장 할 벡터, 추후에 set화 되기에 정렬 필요없음
vector<string> ans_vec;
int depth_limit;

// 문자열에서 생략할 인덱스, count로 접근할거기에 순서는 상관없음
unordered_set<int> skip;

// 괄호 쌍들 빠진 문자열 생성
void backtrack3() {
    string tmp;

    for (int i = 0; i < str_len; i++) {
        if (skip.count(i)) {
            continue;
        }
        tmp += str[i];
    }

    ans_vec.push_back(tmp);
}

static inline void insertSkip(int &idx) {
    skip.insert(brackets[idx].open);
    skip.insert(brackets[idx].close);
}

static inline void eraseSkip(int &idx) {
    skip.erase(brackets[idx].open);
    skip.erase(brackets[idx].close);
}

// 실질적인 백트랙
void backtrack2(int curr_depth, int start) {
    if (curr_depth == depth_limit) {
        backtrack3();
    }
    else {
        for (int i = start; i < brackets_size; i++) {
            insertSkip(i);

            backtrack2(curr_depth + 1, start + 1);

            eraseSkip(i);
        }
    }
}

// 1~괄호쌍 갯수대로 백트랙 함수 실행
void backtrack() {
    for (int i = 1; i <= brackets_size; i++) {
        depth_limit = i;

        backtrack2(0, 0);
    }
}

void prn() {
    // set화로 중복 제거 && 사전 순 정렬
    set<string> ans_set(ans_vec.begin(), ans_vec.end());

    for (auto &it: ans_set) {
        cout << it << "\n";
    }
}

int main() {
    input();

    chkBracket();

    backtrack();

    prn();
}