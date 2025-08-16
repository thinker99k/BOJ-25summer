#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // ascending 정렬
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> ans;

    int n, x;
    cin >> n;

    while(n--){
        cin >> x;

        if(x){
            // priority queue에 push
            pq.push(x);
        }
        else{
            // priority queue의 최소값을 출력 + pop
            if(pq.empty()){
                ans.push_back(0);
            }
            else{
                ans.push_back(pq.top());
                pq.pop();
            }
        }
    }

    for(auto &it : ans){
        cout << it << "\n";
    }
}