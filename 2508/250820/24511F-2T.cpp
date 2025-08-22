#include <iostream>
#include <vector>

using namespace std;

struct QueueStack{
    int isStack;
    int num;

    int operateStack(int x){
        return x;
    }

    int operateQueue(int x){
        int ret = num;
        num = x;
        return ret; // 기존 값 반환
    }

    inline int operate(int x){
        if(isStack){
            return operateStack(x);
        }
        else{
            return operateQueue(x);
        }
    }
};

struct Chain{
    vector<QueueStack> v;

    // constructor
    Chain(int sz){
        v.resize(sz);
    }

    int operate(int x){
        int tmp = x;

        for(auto & it : v){
            tmp = it.operate(tmp);
        }

        return tmp;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, x;
    cin >> n;

    Chain ch(n);

    for(int i=0; i<n; i++){
        cin >> ch.v[i].isStack;
    }

    // initial queuestack values
    for(int i=0; i<n; i++){
        cin >> ch.v[i].num;
    }

    // chain operate
    vector<int> ans;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> x;
        ans.push_back(ch.operate(x));
    }

    for(auto it : ans){
        cout << it << " ";
    }
}