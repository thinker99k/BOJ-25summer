#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, c;

const char b36char[36]{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'
};

struct base36 {
    string num;

    base36() : num("") {
    };

    base36(string s) : num(s) {
    };

    inline int my_atoi(char &c) {
        // '0'보다 작은 비정상적인 입력은 없다 가정
        if (c <= '9') {
            return int(c - '0');
        }
        else {
            return int((c - 'A') + 10);
        }
    }

    inline char my_itoa(int i) {
        // 0보다 작은 비정상적인 입력은 없다 가정
        if (i <= 9) {
            return char('0' + i);
        }
        else {
            return char('A' + (i - 10));
        }
    }

    base36 operator+(base36 &other) {
        base36 ret;

        base36 &longer = num.length() > other.num.length()
                         ? *this : other;
        base36 &shorter = num.length() > other.num.length()
                          ? other : *this;

        int new_len = (int) longer.num.length();
        int len_gap = new_len - (int) shorter.num.length();

        base36 tmp_longer = longer;
        reverse(tmp_longer.num.begin(), tmp_longer.num.end());

        base36 tmp_shorter = shorter;
        reverse(tmp_shorter.num.begin(), tmp_shorter.num.end());
        tmp_shorter.num.append(len_gap, '0');

        int sum, carry = 0;
        for (int i = 0; i < new_len; i++) {
            sum = my_atoi(tmp_longer.num[i]) +
                  my_atoi(tmp_shorter.num[i]) +
                  carry;

            carry = sum / 36;
            sum %= 36;

            ret.num += my_itoa(sum);
        }

        if (carry) {
            ret.num += my_itoa(carry);
        }

        reverse(ret.num.begin(), ret.num.end());

        return ret;
    };

    // 자기 자신의 num의 문자를 바꿈 -> 주의해서 사용
    void changech(char from){
        for(auto &it : num){
            if(it == from){
                it = 'Z';
            }
        }
    }
};

vector<base36> v;

vector<int> comb;

void solve2(){
    vector<base36> tmpv = v;

    for(auto &it_w : tmpv){
        for(auto &it_c : comb){
            it_w.changech(b36char[it_c]);
        }
    }

    base36 ret;
}

void backtrack(int start){
    if(comb.size() == c){
        solve2();
    }
    else{
        for(int i = start; i < 36; i++){
            comb.push_back(i);
            backtrack(i+1);
            comb.pop_back();
        }
    }
}

void solve(){
    backtrack(0);
}

int main() {
    cin >> n;

    for(int i=0; i<n; i++){
        string str;
        cin >> str;
        v.push_back(base36(str));
    }

    cin >> c;

    solve();
}