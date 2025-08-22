#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct queuestack{
    bool kind;
    queue<int> q; // kind = false
    stack<int> s; // kind = true

    void push(int x){
        if(kind){
            s.push(x);
        }
        else{
            q.push(x);
        }
    }

    void pop(){
        if(kind){
            s.pop();
        }
        else{
            q.pop();
        }
    }

    // queue.front(), stack.top()
    int firstElement(){
        if(kind){
            return s.top();
        }
        else{
            return q.front();
        }
    }

    bool empty(){
        if(kind){
            return s.empty();
        }
        else{
            return q.empty();
        }
    }

    u_int32_t size(){
        if(kind){
            return s.size();
        }
        else{
            return q.size();
        }
    }
};

struct chain{
    vector<queuestack> qs;

    chain(int sz){
        qs.resize(sz);
    }

    int operate(int x){
        int tmp = x;

        for(int i=0; i<qs.size(); i++){
            qs[i].push(tmp);
            tmp = qs[i].firstElement();
            qs[i].pop();
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

    chain c(n);

    for(int i=0; i<n; i++){
        cin >> x;
        if(x){
            // stack
            c.qs[i].kind = true;
        }
        else{
            // queue
            c.qs[i].kind = false;
        }
    }

    // initial queuestack values
    for(int i=0; i<n; i++){
        cin >> x;
        c.qs[i].push(x);
    }

    // chain operate
    vector<int> ans;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> x;
        ans.push_back(c.operate(x));
    }

    for(auto it : ans){
        cout << it << " ";
    }
};

