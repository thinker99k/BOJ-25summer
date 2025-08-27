#include <iostream>
#include <vector>

using namespace std;

char chess[8][9];

vector<pair<int, int>> white;

void init() {
    for (int i = 0; i < 8; i++) {
        for (int j = i % 2; j < 8; j += 2) {
            white.push_back({i, j});
        }
    }
}

int solve() {
    for (int i = 0; i <= 7; i++) {
        cin >> chess[i];
    }

    int ret = 0;
    for (auto it: white) {
        if (chess[it.first][it.second] == 'F') {
            ret++;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    init();
    cout << solve();
}

