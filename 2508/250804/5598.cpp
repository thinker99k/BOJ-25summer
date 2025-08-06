#include <iostream>
#include <string>

using namespace std;

void solve1(string &str) {
    string ans;
    char tmp;

    for (auto it: str) {
        tmp = it - 3;

        if (tmp < 'A') {
            tmp += 26;
        }

        ans += tmp;
    }

    cout << ans;
}

void solve2(string &str) {
    string ans;
    char tmp;

    for (auto it: str) {
        if ('A' <= it && it <= 'C') {
            tmp = 'Z' - ('C' - it);
        }
        else {
            tmp = it - 3;
        }

        ans += tmp;
    }

    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string str;
    cin >> str;

    //solve1(str);
    solve2(str);

    return 0;
}