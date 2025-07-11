#include <iostream>
#include <vector>
#include <deque>

using namespace std;

typedef unsigned int Data;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; // 명령 갯수
    cin >> n;

    deque<int> DQ;
    vector<int> ans;

    int sel, tmp;
    for (int i = 0; i < n; i++) {
        cin >> sel;

        switch (sel) {
            case 1: {
                cin >> tmp;
                DQ.push_front(tmp);
                break;
            }
            case 2: {
                cin >> tmp;
                DQ.push_back(tmp);
                break;
            }
            case 3: {
                if (!DQ.empty()) {
                    ans.push_back(DQ.front());
                    DQ.pop_front();
                }
                else {
                    ans.push_back(-1);
                }
                break;
            }
            case 4: {
                if (!DQ.empty()) {
                    ans.push_back(DQ.back());
                    DQ.pop_back();
                }
                else {
                    ans.push_back(-1);
                }
                break;
            }
            case 5: {
                ans.push_back((int)DQ.size());
                break;
            }
            case 6: {
                ans.push_back(DQ.empty());
                break;
            }
            case 7: {
                if (!DQ.empty()) {
                    ans.push_back(DQ.front());
                }
                else {
                    ans.push_back(-1);
                }
                break;
            }
            case 8: {
                if (!DQ.empty()) {
                    ans.push_back(DQ.back());
                }
                else {
                    ans.push_back(-1);
                }
                break;
            }
            default: { // 그럴 일 없음
                break;
            }
        }
    }

    for (const auto it : ans) {
        cout << it << "\n";
    }
}
