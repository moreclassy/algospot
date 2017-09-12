#include <iostream>
#include <vector>

using namespace std;

const int mod = 1000000007;

int count(vector<int>& dp, int i) {
	if (i < 0) return 0;
	int& ret = dp[i];
	if (ret != -1) return ret;
	ret = (count(dp, i-1) + count(dp, i-2)) % mod;
	return ret;
}

void solve() {
	int n;
	cin>>n;
	vector<int> dp(n+1, -1);
	dp[0] = 1; dp[1] = 1;
	
	int ret = (count(dp, n) + mod - count(dp, n/2)) % mod;
	if (n%2 == 0) ret += mod - count(dp, n/2 -1);
	ret %= mod;
	
	cout<<ret<<endl;
}

int main() {
	int c;
	cin>>c;

	for (int i = 0; i < c; i++) {
		solve();
	}
	return 0;
}