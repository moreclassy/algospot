#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool checkWild(string& wild, string& str, vector<vector<int>> &dp, int w, int s) {
	if (wild.size() == w) {
		return str.size() == s;
	}
	
	if (wild.size() == w + 1 && wild[w] == '*') {
		return true;
	}
	
	if (str.size() == s) {
		return wild.size() == w || (wild[w] == '*' && checkWild(wild, str, dp, w + 1, s)); 
	}
	
	int &ret = dp[w][s];
	if (ret != -1) return ret;
	
	if (wild[w] == '?') {
		ret = checkWild(wild, str, dp, w + 1, s + 1);
	} else if (wild[w] == '*') {
		ret = checkWild(wild, str, dp, w + 1, s) || checkWild(wild, str, dp, w, s + 1) || checkWild(wild, str, dp, w + 1, s + 1);
	} else {
		ret = wild[w] == str[s] && checkWild(wild, str, dp, w + 1, s + 1);
	}
	
	return ret;
}

void solve() {
	string wild;
	cin>>wild;
	int n;
	cin>>n;
	
	vector<string> ret;
	string str;
	for (int i = 0; i < n; i++) {
		cin>>str;
		vector<vector<int>> dp(wild.size(), vector<int>(str.size(), -1));
		if (checkWild(wild, str, dp, 0, 0))
			ret.push_back(str);
	}
	
	sort(ret.begin(), ret.end());
	
	for (auto s : ret)
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