#include <iostream>
#include <vector>

using namespace std;

enum pal {
    PALINDROME,
    PSEUDO,
    NOTHING
};

bool isPseudoPalindrome(const string &str, int src, int dst) {
    while (src < dst) {
        if (str[src] == str[dst]) {
            ++src;
            --dst;
        }
        else {
            return false;
        }
    }

    return true;
}

int isPalindrome(const string &str, int src, int dst) {
    while (src < dst) {
        if (str[src] == str[dst]) { // 아직까지 팰린드롬이면 인덱스 확장
            ++src;
            --dst;
        }
        else { // 팰린드롬 깨짐, 유사 팰린드롬 가능성 있음
            if (isPseudoPalindrome(str, src + 1, dst) ||
                isPseudoPalindrome(str, src, dst - 1)) {
                return PSEUDO;
            }
            else {
                return NOTHING;
            }
        }
    }

    return PALINDROME;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    vector<string> v;

    cin >> n;
    v.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    for (const auto &it: v) {
        cout << isPalindrome(it, 0, (int) it.length() - 1) << "\n";
    }
}