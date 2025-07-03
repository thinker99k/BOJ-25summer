#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string src;
int src_len;
string dst;
int dst_len;

bool func(string s, int l){
    // cout << s << "(" << l << ")\n";
    
    if(s == src){
        return true;
    }
    
    if(s.back() == 'A'){
        return func(s.substr(0, l-1), l-1);
    }
    else if (s.back() == 'B'){
        string rev = s.substr(0, l-1);
        reverse(rev.begin(), rev.end());
        
        return func(rev, l-1);
    }
    else {
        return false;
    }
}

int main(){
    cin >> src;
    cin >> dst;
    src_len = src.length();
    dst_len = dst.length();
    
    cout << func(dst, dst_len);
}