#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// all number is same
bool same(string& str) {
    for (int i = 1; i < str.size(); i++)
        if (str[i] != str[i-1]) return false;
    return true;
}

// increase or decrease by one
bool one(string& str) {
    for (int i = 2; i < str.size(); i++)
        if (str[i-1] - str[i-2] != str[i] - str[i-1] || abs(str[i] - str[i-1]) != 1) return false;
    return true;
}

// two numbers appear by turns
bool cross(string& str) {
    for (int i = 2; i < str.size(); i++)
        if (str[i] != str[i-2]) return false;
    return true;
}

// arithmatic series
bool mono(string& str) {
    for (int i = 2; i < str.size(); i++)
        if (str[i-1] - str[i-2] != str[i] - str[i-1]) return false;
    return true;
}

int difficulty(string str) {
    if (str.size() <= 2) return 10;
    if (same(str)) return 1;
    if (one(str)) return 2;
    if (cross(str)) return 4;
    if (mono(str)) return 5;
    return 10;
}

int minDifficulty(string &str, vector<int> &dp, int i) {
    int &ret = dp[i];
    if (ret != -1) return ret;
    ret = min(minDifficulty(str, dp, i - 1) + 10, minDifficulty(str, dp, i - 2) + 10);
    if (i >= 3) ret = min(ret, minDifficulty(str, dp, i - 3) + difficulty(str.substr(i - 3, 3)));
    if (i >= 4) ret = min(ret, minDifficulty(str, dp, i - 4) + difficulty(str.substr(i - 4, 4)));
    if (i >= 5) ret = min(ret, minDifficulty(str, dp, i - 5) + difficulty(str.substr(i - 5, 5)));
    return ret;
}

void solve() {
    string str;
    cin>>str;
    
    vector<int> dp(str.size() + 1, -1);
    dp[0] = 0; dp[1] = 10; dp[2] = 10;
    
    cout<<minDifficulty(str, dp, str.size())<<endl;
}

int main() {
	int c;
	cin>>c;
	for (int i = 0; i < c; i++) {
		solve();
	}

	return 0;
}
