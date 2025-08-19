#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    priority_queue<int, vector<int>, greater<int>> pq;

    int n, x;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        pq.push(x);
    }

    if (n == 1) {
        cout << 0;
    }
    else {
        int ans = 0;

        while (true){
            x = 0;

            x += pq.top();
            pq.pop();
            x += pq.top();
            pq.pop();

            ans += x;

            if(pq.empty()){
                break;
            }
            else{
                pq.push(x);
            }
        }

        cout << ans;
    }
}