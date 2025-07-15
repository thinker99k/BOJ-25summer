#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	vector<int> v;

	int n;
	cin >> n;
	v.resize(n);

	for(int i=0; i<n; i++){
		cin >> v[i];
	}

	sort(v.begin(), v.end());

	for(auto &it : v){
		cout << it << "\n";
	}

	return 0;
}
