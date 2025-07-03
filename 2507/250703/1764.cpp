#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int i1, i2;

    cin >> i1 >> i2;

    set<string> str_set;
    for(int i=1; i<=i1; i++){
        string s;
        cin >> s;
        str_set.insert(s);
    }

    vector<string> str_vec;
    for(int i=1; i<=i2; i++){
        string s;
        cin >> s;
        if(str_set.count(s)){
            str_vec.push_back(s);
        }
    }

    sort(str_vec.begin(), str_vec.end());

    cout << str_vec.size() << "\n";
    for(auto it : str_vec){
        cout << it << "\n";
    }
}
