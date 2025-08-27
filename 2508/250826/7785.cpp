#include <iostream>
#include <unordered_set>
#include <set>

using namespace std;

int n;
unordered_set<string> us;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    for(int i=0; i<n; i++){
        string name, io;
        cin >> name >> io;

        if(io[0] == 'e'){
            us.insert(name);
        }
        else{
            us.erase(name);
        }
    }

    set<string, greater<string>> s(us.begin(), us.end());

    for(auto it : s){
        cout << it << "\n";
    }
}