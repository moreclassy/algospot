#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const long long NEGINF = numeric_limits<long long>::min();

int jlis(vector<int> &a, vector<int> &b, vector<vector<int>> &dp, int ia, int ib) {
	int& ret = dp[ia + 1][ib + 1];
	if (ret != -1) return ret;

	ret = 2;
	long long ca = ia < 0 ? NEGINF : a[ia];
	long long cb = ib < 0 ? NEGINF : b[ib];
	long long cmax = max(ca, cb);
	for (int na = ia + 1; na < a.size(); na++)
		if (cmax < a[na])
			ret = max(ret, jlis(a, b, dp, na, ib) + 1);

	for (int nb = ib + 1; nb < b.size(); nb++)
		if (cmax < b[nb])
			ret = max(ret, jlis(a, b, dp, ia, nb) + 1);
	
	return ret;
}

void solve() {
	int lena, lenb;
	cin>>lena>>lenb;
	vector<int> a(lena);
	for (int i = 0; i < lena; i++) cin>>a[i];
	vector<int> b(lenb);
	for (int i = 0; i < lenb; i++) cin>>b[i];

	vector<vector<int>> dp(lena + 1, vector<int>(lenb + 1, -1));

	cout<<jlis(a, b, dp, -1, -1) - 2<<endl;
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
