#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct lencmp {
    inline bool operator()(const string &s1, const string &s2) {
        return s1.size() < s2.size();
    }
};

int main() {
    int t, n;
    string s;
    vector<bool> ans;

    cin >> t;

    lencmp lc;

    for (int tc = 1; tc <= t; tc++) {
        vector<string> phonebook_vec;
        bool collision = false;

        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> s;
            phonebook_vec.push_back(s);
        }

        // 길이 순 정렬
        sort(phonebook_vec.begin(), phonebook_vec.end(), lc);

        // 속도를 위해 set 사용.. 의미가 있을까??;;
        set<string> phonebook_set(phonebook_vec.begin(), phonebook_vec.end());

        for(auto it : phonebook_set){
            // 충돌 확인되었으면 의미없는 충돌 확인 건너뛰기
            if (collision) {
                break;
            }

            // 충돌 확인
            for (int j = 1; j <= it.length(); j++) {
                string tmp = it.substr(0, j-1);

                if (phonebook_set.count(tmp)) {
                    collision = true;
                    break;
                }
            }
        }

        ans.push_back(!collision);
    }

    for (auto it: ans) {
        if (it) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
}
