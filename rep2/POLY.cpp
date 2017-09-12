#include <iostream>
#include <vector>

using namespace std;

const int mod = 10000000;

int count(vector<vector<int>> &dp, int n, int b) {
	int &ret = dp[n][b];
	if (ret != -1) return ret;

	int prevN = n - b;
	ret = 0;
	for (int i = 1; i <= prevN; i++) {
		ret += count(dp, prevN, i) * (i + b - 1);
		ret %= mod;
	}

	return ret;
}

void solve() {
	int n;
	cin>>n;

	vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
	for (int i = 1; i <= n; i++) dp[i][i] = 1;

	int ret = 0;
	for (int i = 1; i <= n; i++) {
		ret += count(dp, n, i);
		ret %= mod;
	}

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