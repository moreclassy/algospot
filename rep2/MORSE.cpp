#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int dp[201][101];
const int MAX = 1000000000;
const int INF = 1000000001;

int combination(int n, int m) {
	int &ret = dp[n][m];
	if (ret != -1) return ret;
	
	if (n < m) return ret = 0;
	if (n == m) return ret = 1;
	if (m == 1) return ret = n;
	
	long long tc = (long long)combination(n - 1, m) + (long long)combination(n - 1, m - 1);
	if (tc > MAX) return ret = INF;
	return ret = tc;
}

void getStr(int l, int s, int k, string& str) {
	if (k <= 1) {
		str += string(l, '-') + string(s, 'o');
		return;
	}
	if (l == 0) {
		str += string(s, 'o');
		return;
	}
	if (s == 0) {
		str += string(l, '-');
		return;
	}
	
	int comb = combination(l - 1 + s, s);
	
	if (comb > k) {
		str += '-';
		l--;
	} else {
		str += 'o';
		k -= comb;
		s--;
	}
	getStr(l, s, k, str);
}

void solve() {
	int l, s, k;
	cin>>l>>s>>k;
	
	string str;
	getStr(l, s, k, str);
	cout<<str<<endl;
}

int main() {
	int c;
	cin>>c;
	
	memset(dp, -1, sizeof(dp));
	
	for (int i = 0; i < c; i++) solve();
	
	return 0;
}