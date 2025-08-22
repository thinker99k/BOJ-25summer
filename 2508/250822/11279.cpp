#include <iostream>
#include <queue>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, x;
    cin >> n;

    priority_queue<int> pq;
    vector<int> ans;

    for(int i=0; i<n; i++){
        cin >> x;

        if(x){
            pq.push(x);
        }
        else{
            if(!pq.empty()){
                ans.push_back(pq.top());
                pq.pop();
            }
            else{
                ans.push_back(0);
            }
        }
    }

    for(auto it : ans){
        cout << it << "\n";
    }
}