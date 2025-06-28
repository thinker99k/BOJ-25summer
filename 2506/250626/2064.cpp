#include <algorithm>
#include <cstdio>
#include <vector>
#include <bitset>

using namespace std;

int n;

struct bs84 {
    bitset<8> bs1;
    bitset<8> bs2;
    bitset<8> bs3;
    bitset<8> bs4;
};

typedef bitset<32> bs32;

bs32 bs84_bs32(const bs84& bb) {
    bs32 ret;
    for (int i = 0; i < 8; ++i) {
        ret[31 - i] = bb.bs1[7 - i];
        ret[23 - i] = bb.bs2[7 - i];
        ret[15 - i] = bb.bs3[7 - i];
        ret[7 - i] = bb.bs4[7 - i];
    }
    return ret;
}

bs84 bs32_bs84(const bs32& bb) {
    bs84 ret;
    for (int i = 0; i < 8; ++i) {
        ret.bs1[7 - i] = bb[31 - i];
        ret.bs2[7 - i] = bb[23 - i];
        ret.bs3[7 - i] = bb[15 - i];
        ret.bs4[7 - i] = bb[7 - i];
    }
    return ret;
}

vector<bs32> v;

void print_bs84_ip(const bs84& bb) {
    printf("%lu.%lu.%lu.%lu\n",
           bb.bs1.to_ulong(),
           bb.bs2.to_ulong(),
           bb.bs3.to_ulong(),
           bb.bs4.to_ulong()
    );
}

void solve() {
    const bs32 base = v[0];
    int prefix = 32;
    
    for (int i = 1; i < n; ++i) {
        bs32 cmp = v[i];
        
        for (int j = 0; j < prefix; ++j) {
            // MSB부터 비교
            if (base[31 - j] != cmp[31 - j]) {
                prefix = j; // 안맞으면 prefix_len 줄임
                break;
            }
        }
    }
    
    bs32 mask;
    for (int i = 0; i < prefix; ++i) {
        mask[31 - i] = true;
    }
    
    bs32 network = v[0] & mask;
    
    print_bs84_ip(bs32_bs84(network));
    print_bs84_ip(bs32_bs84(mask));
}

int main() {
    scanf("%d", &n);
    getchar();
    
    int partial_i[4];
    bs84 partial_b;
    
    for (int i = 0; i < n; i++) {
        scanf("%d.%d.%d.%d", &partial_i[0], &partial_i[1], &partial_i[2], &partial_i[3]);
        getchar();
        
        v.push_back(bs84_bs32({partial_i[0], partial_i[1], partial_i[2], partial_i[3]}));
    }
    
    solve();
}
