#include <iostream>
#include <vector>
#include <numeric>
#include <set>

using namespace std;

namespace CCW {
    struct pos {
        int x;
        int y;

        pos operator-(const pos &other) const {
            return {x - other.x, y - other.y};
        }

        bool operator<(const pos &other) const {
            if (x == other.x) {
                return y < other.y;
            }

            return x < other.x;
        }

        bool operator>(const pos &other) const {
            if (x == other.x) {
                return y > other.y;
            }

            return x > other.x;
        }
    };

    struct line {
        pos src;
        pos dst;
    };

    vector<line> lines;

    void init(int sz) {
        lines.resize(sz + 1); // 1-idx
    }

    void inputLines(int sz) {
        for (int i = 1; i <= sz; i++) {
            cin >> CCW::lines[i].src.x >> CCW::lines[i].src.y
                    >> CCW::lines[i].dst.x >> CCW::lines[i].dst.y;
        }
    }

    struct space {
        int x;
        int y;
        int z;

        // 외적
        space operator*(const space &other) const {
            return {y * other.z - z * other.y,
                    x * other.z - z * other.x,
                    x * other.y - y * other.x};
        }
    };

    int ccw(pos p1, pos p2, pos p3) {
        // 들어오는 점 : 선분a, 선분a, 선분b

        space cp = (space) {p1.x - p3.x, p1.y - p3.y, 0} *
                   (space) {p2.x - p3.x, p2.y - p3.y, 0};

        /** cp.z가
         * 0 -> 일직선
         * + -> 반시계방향
         * - -> 시계방향
         */

        return cp.z == 0 ? 0 : (cp.z > 0 ? 1 : -1);
    }

    /** 외워서 써라 */
    bool isCross(line l1, line l2) {
        int ab = ccw(l1.src, l1.dst, l2.src) * ccw(l1.src, l1.dst, l2.dst);
        int cd = ccw(l2.src, l2.dst, l1.src) * ccw(l2.src, l2.dst, l1.dst);

        if (ab == 0 && cd == 0) {
            if (l1.src > l1.dst) {
                swap(l1.src, l1.dst);
            }
            if (l2.src > l2.dst) {
                swap(l2.src, l2.dst);
            }
            return !(l1.dst < l2.src || l2.dst < l1.src);
        }
        return ab <= 0 && cd <= 0;
    }
}


namespace UF {
    vector<int> parent; // 0~n으로 초기화됨
    vector<int> groupsz; // 1...1로 초기화됨
    int maxszidx;

    void init(int sz) {
        UF::parent.resize(sz + 1);
        iota(UF::parent.begin(), UF::parent.end(), 0);

        UF::groupsz.resize(sz + 1);
        fill(UF::groupsz.begin(), UF::groupsz.end(), 1);
    }

    int Find(int v) {
        if (parent[v] == v) {
            return v;
        }
        else {
            parent[v] = Find(parent[v]); // 경로압축
            return parent[v];
        }
    }

    int rootu, rootv, loidx, hiidx;

    bool Union(int u, int v) {
        rootu = Find(u);
        rootv = Find(v);

        if (rootu != rootv) {
            loidx = rootu < rootv ? rootu : rootv;
            hiidx = rootu > rootv ? rootu : rootv;

            parent[hiidx] = loidx;
            groupsz[loidx] += groupsz[hiidx];

            // 가장 큰 그룹사이즈 idx 갱신
            if (groupsz[loidx] > groupsz[maxszidx]) {
                maxszidx = loidx;
            }

            // 루트가 같지 않으면 -> union 성공 -> true 반환
            return true;
        }
        else {
            // 루트가 같으면 -> union 실패 -> false 반환
            return false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    CCW::init(n);
    UF::init(n);
    CCW::inputLines(n);

    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (CCW::isCross(CCW::lines[i], CCW::lines[j])) {
                UF::Union(i, j);
            }
        }
    }

    set<int> realParent;

    for (int i = 1; i <= n; i++) {
        // 각 노드의 부모를 찾아서 set에 넣기(중복제거)
        realParent.insert(UF::Find(i));
    }

    cout << realParent.size() << "\n" << UF::groupsz[UF::maxszidx];
}
