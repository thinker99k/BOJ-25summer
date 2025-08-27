#include <iostream>
#include <unordered_set>

using namespace std;

string s;
int slen;
unordered_set<string> part;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> s;
    slen = (int) s.length();

    for (int length = 1; length <= slen; length++) {
        for(int start = 0; start + length <= slen; start++){
            part.insert(s.substr(start, length));
        }
    }

    cout << part.size();
}