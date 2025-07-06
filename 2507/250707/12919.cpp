#include <iostream>
#include <algorithm>
#include <string>
#include <queue>

#define DEBUG 0

using namespace std;

string src, dst;
int src_len, dst_len;

struct word {
    string s;
    int len;
};

/** 역방향 */
bool bfs() {
    queue<word> q;
    q.push({dst, dst_len});

    string curr_s;
    int curr_len, new_len;

    while (!q.empty()) {
        curr_s = q.front().s;
        curr_len = q.front().len;
        q.pop();

#if DEBUG
        cout << curr_s << "(" << curr_len << ")\n";
#endif

        if (curr_s == src) {
            return true;
        }

        // 길이기 src_len 초과하는 것만 넣어 무의미한 탐색분기 방지
        if (curr_len > src_len) {
            new_len = curr_len - 1;

            if (curr_s.back() == 'A') {
                // 가장 뒤 A 제외한 substring
                q.push({curr_s.substr(0, new_len), new_len});
            }

            if (curr_s.front() == 'B') {
                // 가장 앞 B 제외한 substring
                string rev = curr_s.substr(1, new_len);
                reverse(rev.begin(), rev.end());

                q.push({rev, new_len});
            }
        }
    }

    return false;
}

int main() {
    cin >> src;
    cin >> dst;
    src_len = src.length();
    dst_len = dst.length();

    cout << bfs();
}