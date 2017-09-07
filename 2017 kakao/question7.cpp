#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> dp;

int helper(vector<string>& strs, string& t, int i) {
    if (i < 0) return 0;
    int& ret = dp[i];
    if (ret != -1) return ret;
    ret = 987654321;
    for (string str : strs) {
        if (i + 1 < str.size()) continue;
        bool match = true;
        for (int j = 0; j < str.size(); j++) {
            if (i - j >= 0 && t[i - j] != str[str.size() - 1 - j]) {
                match = false;
                break;
            }
        }
        if (match)
            ret = min(ret, helper(strs, t, i - str.size()) + 1);
    }
    return ret;
}

int solution(vector<string> strs, string t)
{
    dp = vector<int>(t.size(), -1);
    
    int answer = helper(strs, t, t.size() - 1);
    return answer > 20001 ? -1 : answer;
}
