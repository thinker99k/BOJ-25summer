#include <iostream>
#include <algorithm>

using namespace std;

string target;
int target_len;

bool func(string s, int l){
    //cout << s << "(" << l << ")\n";
    
    if(l > target_len){
        return false;
    }
    
    if(s == target){
        return true;
    }
    else {
        string rev = s;
        reverse(rev.begin(), rev.end());
        
        return func((s + "A"), l+1) || func(rev + "B", l+1);
    }
}

int main(){
    string start;
    cin >> start;
    cin >> target;
    target_len = target.length();
    
    cout << func(start, start.length());
}