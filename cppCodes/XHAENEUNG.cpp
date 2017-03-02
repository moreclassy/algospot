#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <queue>
#include <map>

#define _USE_MATH_DEFINES

using namespace std;

string nums[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

bool isAnigram(string _s1, string _s2)
{
    string s1 = _s1, s2 = _s2;
    if (s1.size() != s2.size())
        return false;
    for (int i = 0; i < s1.size(); i++) {
        for (int j = 0; j < s2.size(); j++) {
            if (s1[i] == s2[j]) {
                s2[j] = '*';
                break;
            }
        }
    }
    for (int i = 0; i < s2.size(); i++)
        if (s2[i] != '*')
            return false;
    return true;
}

int convertToInt(string s)
{
    for (int i = 0; i < 11; i++)
        if (s.compare(nums[i]) == 0)
            return i;
    return -1234567890;
}

int calculate(string a, string op, string b)
{
    int ret = convertToInt(a);
    if (op == "+")
        ret += convertToInt(b);
    else if (op == "-")
        ret -= convertToInt(b);
    else if (op == "*")
        ret *= convertToInt(b);
    return ret;
}

void Solve()
{
    string a, op, b, eq, c;
    cin>>a>>op>>b>>eq>>c;
    int retInt = calculate(a, op, b);
    if (retInt < 0 || retInt > 10) {
        cout<<"no"<<endl;
        return;
    }
    if (isAnigram(c, nums[retInt]))
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
