#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<string, unordered_set<string>> metro;

unordered_set<string> featureBuffer;

void parse(const string &s) {
    featureBuffer.clear();

    string tok;
    for (char ch: s) {
        if (ch == ',') {
            featureBuffer.insert(tok);
            tok.clear();
        }
        else {
            tok += ch;
        }
    }

    if (!tok.empty()) {
        featureBuffer.insert(tok);
    }
}

void updateStation(const string &n, const string &f) {
    metro[n].clear();

    parse(f);

    for (const auto &it: featureBuffer) {
        metro[n].insert(it);
    }
}

void showStation(const string &f) {
    parse(f);

    unordered_set<string> tmp_odd;  // F
    unordered_set<string> tmp_even; // T
    bool isEven = false;

    for (const auto &it: metro) {
        tmp_odd.insert(it.first);
    }

    /** 탐색범위 줄여가기 */
    for (const auto &feat: featureBuffer) {
        if (!isEven) { // odd -> even
            tmp_even.clear();

            for (const auto &name: tmp_odd) {
                if (metro[name].count(feat)) {
                    tmp_even.insert(name);
                }
            }
        }
        else { // even -> odd
            tmp_odd.clear();

            for (const auto &name: tmp_even) {
                if (metro[name].count(feat)) {
                    tmp_odd.insert(name);
                }
            }
        }

        isEven = !isEven;
    }

    size_t result = isEven ? tmp_even.size() : tmp_odd.size();
    cout << result << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int x;
    string op, n, f;

    cin >> x;
    for (int i = 0; i < x; i++) {
        cin >> n;
        metro[n] = {}; // 이름 지정, 특징 비어있음
    }

    cin >> x;
    for (int i = 0; i < x; i++) {
        cin >> op;

        if (op == "U") {
            cin >> n >> f;
            updateStation(n, f);
        }
        else { // op == "G"
            cin >> f;
            showStation(f);
        }
    }

    return 0;
}