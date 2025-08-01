#include <iostream>

#define DEBUG 0

using namespace std;
using ll = long long;

ll matrix[8][8];
ll ans[8][8];

void init() {
    enum {
        it,
        cs,
        faith,
        truth,
        student,
        hyungnam,
        chapel,
        future
    };

    matrix[it][cs] = 1;
    matrix[cs][it] = 1;

    matrix[cs][faith] = 1;
    matrix[faith][cs] = 1;

    matrix[faith][truth] = 1;
    matrix[truth][faith] = 1;

    matrix[truth][student] = 1;
    matrix[student][truth] = 1;

    matrix[student][hyungnam] = 1;
    matrix[hyungnam][student] = 1;

    matrix[hyungnam][chapel] = 1;
    matrix[chapel][hyungnam] = 1;

    matrix[chapel][future] = 1;
    matrix[future][chapel] = 1;

    matrix[future][it] = 1;
    matrix[it][future] = 1;

    matrix[cs][future] = 1;
    matrix[future][cs] = 1;

    matrix[future][faith] = 1;
    matrix[faith][future] = 1;

    matrix[faith][chapel] = 1;
    matrix[chapel][faith] = 1;

    matrix[chapel][truth] = 1;
    matrix[truth][chapel] = 1;

    for (int i = 0; i < 8; i++) {
        ans[i][i] = 1LL;
    }
}

ll tmp[8][8];
ll tll;

ll const prime = 1000000007;

inline ll modulo(const ll n) {
    return (n % prime + prime) % prime;
}

// ans, matrix 곱하여 ans에 저장
void domulti1() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tll = 0;

            for (int k = 0; k < 8; k++) {
                tll += modulo(ans[i][k] * matrix[k][j]);
            }

            tmp[i][j] = modulo(tll);
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ans[i][j] = tmp[i][j];
        }
    }
}

// matrix, matrix 곱하여 matrix에 저장
void domulti2() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tll = 0;

            for (int k = 0; k < 8; k++) {
                tll += modulo(matrix[i][k] * matrix[k][j]);
            }

            tmp[i][j] = modulo(tll);
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            matrix[i][j] = tmp[i][j];
        }
    }
}

void multi(ll k) {
    while (k) {
        // k가 홀수일 경우 matrix, ans 곱
        if (k % 2) {
            domulti1();
        }

        // matrix 거듭제곱
        domulti2();

        k /= 2;
    }
}

int main() {
    init();

    int d;
    cin >> d;

    multi(d);

#if DEBUG
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
#endif

    cout << ans[0][0];
}