#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MIN = -987654321;

vector<string> name(100);
vector<int> volume(100);
vector<int> need(100);
int n, w;

int maxNeed(vector<vector<int>>& dp, int i, int c) {
    if (c < 0) return MIN;
    if (i < 0) return 0;
    if (i == 0) return c < volume[0] ? 0 : need[0];
    int &ret = dp[i][c];
    if (ret != -1) return ret;
    
    ret = max(maxNeed(dp, i - 1, c), maxNeed(dp, i - 1, c - volume[i]) + need[i]);
    return ret;
}

void print(vector<vector<int>>& dp, int i, int c, vector<string> &check) {
    if (i < 0 || c < 0) return;
    if (maxNeed(dp, i, c) == maxNeed(dp, i - 1, c)) {
        print(dp, i - 1, c, check);
    } else {
        check.push_back(name[i]);
        print(dp, i - 1, c - volume[i], check);
    }
}

void solve() {
    cin>>n>>w;
    
    for (int i = 0; i < n; i++) {
        cin>>name[i]>>volume[i]>>need[i];
    }
    
    vector<vector<int>> dp(n, vector<int>(w + 1, -1));
    
    int lc = w, mn = MIN;
    for (int i = 0; i < volume[n-1]; i++) {
        int cur = maxNeed(dp, n - 1, w - i);
        if (cur > mn) {
            mn = cur; lc = w - i;
        }
    }
    
    vector<string> check;
    print(dp, n - 1, lc, check);
    cout<<mn<<" "<<check.size()<<endl;
    for (auto s : check)
        cout<<s<<endl;
}

int main() {
	int c;
	cin>>c;
	
	for (int i = 0; i < c; i++) {
		solve();
	}
	
	return 0;
}
