#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, ssz;
    string s;

    cin >> n >> m;
    cin >> s;
    ssz = (int) s.size();

    string sample = "IOI";
    int slen = 3;

    for (int i = 1; i < n; i++) {
        sample += "OI";
        slen += 2;
    }

    string window;
    int ans = 0;

    for (int i = 0; i <= ssz - slen; i++) {
        window.clear();

        window = s.substr(i, slen);

        if(window == sample){
            ans++;
        }
    }

    cout << ans;
}