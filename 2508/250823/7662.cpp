#include <iostream>
#include <sstream>
#include <set>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k, x;
    char op;

    cin >> n;

    vector<string> ans;

    for (int i = 0; i < n; i++) {
        multiset<int> ms;

        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> op >> x;

            switch (op) {
                case 'I': {
                    // 삽입
                    ms.insert(x);
                    break;
                }
                case 'D': {
                    switch (x) {
                        case 1: {
                            // 최대값 삭제
                            if(!ms.empty()){
                                ms.erase(prev(ms.end()));
                            }
                            break;
                        }
                        case -1: {
                            // 최소값 삭제
                            if(!ms.empty()){
                                ms.erase(ms.begin());
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }

        stringstream ss;

        if (!ms.empty()) {
            ss << *ms.rbegin() << " " << *ms.begin();
        }
        else {
            ss << "EMPTY";
        }

        ans.push_back(ss.str());
    }

    for (auto it : ans){
        cout << it << "\n";
    }
}