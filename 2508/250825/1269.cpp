#include <iostream>
#include <unordered_set>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int numa, numb, x;
    cin >> numa >> numb;

    unordered_set<int> a, b;

    for(int i=0; i<numa; i++){
        cin >> x;

        a.insert(x);
    }

    for(int i=0; i<numb; i++){
        cin >> x;

        if(a.count(x)){
            // 교집합 속하면

            // 1. a에서 빼줌
            a.erase(x);

            // 2. b에 넣지 않음
        }
        else{
            // 교집합 속하지 않으면
            b.insert(x);
        }
    }

    cout << a.size() + b.size();
    
}