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

    int ans = 0;

    for (const auto &it1: metro) { // it1(역)에 대해
        ++ans;
        for (const auto &it2: featureBuffer) { // 모든 it2(특징)을
            if (!it1.second.count(it2)) { // 갖고있지 않으면
                --ans;
                break;
            }
        }
    }

    cout << ans << '\n';
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