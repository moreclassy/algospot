#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
	int len;
	cin>>len;

	int tmp;
	cin>>tmp;
	vector<int> lis;
	lis.push_back(tmp);

	for (int i = 1; i < len; i++) {
		cin>>tmp;
		if (tmp < lis[0]) {
			lis[0] = tmp;
			continue;
		}
		if (tmp > lis.back()) {
			lis.push_back(tmp);
			continue;
		}
		auto iter = lower_bound(lis.begin(), lis.end(), tmp);
		if (*iter == tmp) continue;
		*iter = tmp;
	}
	
	cout<<lis.size()<<endl;
}

int main()
{
    int c;
    cin>>c;
    
    for (int i = 0; i < c; i++) {
        solve();
    }
	
	return 0;
}
