#include <iostream>
#include <vector>
#include <hash_map>

using namespace std;

struct vec{
    long long x;
    long long y;
};

vector<vec> vecs(200001);

static inline long long dotProduct(vec u, vec v){
    return u.x * v.x + u.y * v.y;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int n;
    cin >> n;
    
    for(int i=1; i<=n; i++){
        cin >> vecs[i].x >> vecs[i].y;
    }
    
    int ans = 0;
    
    for(int i=1; i<=n-1; i++){
        for(int j=i+1; j<=n; j++){
            if(dotProduct(vecs[i], vecs[j]) == 0){
                ans++;
            }
        }
    }
    
    cout << ans;
}