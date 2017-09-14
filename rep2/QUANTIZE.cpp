#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int limit = 987654321;

int minError(vector<int> &pSum, vector<int> &pSum2, int from, int to) {
	if (from == to) return 0;
	int sum = pSum[to] - (from == 0 ? 0 : pSum[from - 1]);
	int cnt = to - from + 1;
	int mean = (int)floor((double)sum / (double)cnt + 0.5);
	int sum2 = pSum2[to] - (from == 0 ? 0 : pSum2[from - 1]);
	return sum2 - 2*mean*sum + mean*mean*cnt;
}

int quantize(vector<int> &nums, vector<vector<int>> &dp, vector<int> &pSum, vector<int> &pSum2, int from, int parts) {
	if (from == nums.size()) return 0;
	if (parts == 0) return limit;

	int &ret = dp[from][parts];
	if (ret != -1) return ret;

	ret = limit;

	for (int to = from; to < nums.size(); to++) {
		ret = min(ret, quantize(nums, dp, pSum, pSum2, to +1, parts -1) + minError(pSum, pSum2, from, to));
	}

	return ret;
}

void solve() {
    int len, parts;
	cin>>len>>parts;
	vector<int> nums(len);
	for (int i = 0; i < len; i++) cin>>nums[i];
	
	sort(nums.begin(), nums.end());

	vector<int> pSum(len);
	vector<int> pSum2(len);
	int psum = 0, psum2 = 0;
	for (int i = 0; i < len; i++) {
		psum += nums[i];
		pSum[i] = psum;
		psum2 += nums[i]*nums[i];
		pSum2[i] = psum2;
	}

	vector<vector<int>> dp(len + 1, vector<int>(parts + 1, -1));

	cout<<quantize(nums, dp, pSum, pSum2, 0, parts)<<endl;
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
