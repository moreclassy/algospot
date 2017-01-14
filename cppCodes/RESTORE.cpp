#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>

#define _USE_MATH_DEFINES

using namespace std;

vector<string> words;
const int MAX_N = 15;
int cache[MAX_N][1<<MAX_N], overlap[MAX_N][MAX_N];

void Reset()
{
    memset(cache, -1, sizeof(cache));
    memset(overlap, 0, sizeof(overlap));
    words.clear();
}

void InsertNewWord(string newStr)
{
    for (vector<string>::iterator it = words.begin(); it != words.end(); it++)
    {
        if (strstr((*it).c_str(), newStr.c_str()) != nullptr) return;
        if (strstr(newStr.c_str(), (*it).c_str()) != nullptr) words.erase(it);
    }
    words.push_back(newStr);
}

void CalcOverlap()
{
    for (int i = 0; i < (int)words.size(); i++)
    {
        for (int j = 0; j < (int)words.size(); j++)
        {
            if (i == j) continue;
            int minLen = min((int)words[i].length(), (int)words[j].length());
            int tmpOverlap = 0;
            for (int k = 1; k < minLen; k++)
                if (words[i].substr((int)words[i].length() - k, k) == words[j].substr(0, k))
                    tmpOverlap = k;
            overlap[i][j] = tmpOverlap;
        }
    }
}

int Restore(int last, int used)
{
    if (used == (1<<words.size()) - 1) return 0;
    
    int& ret = cache[last][used];
    if (ret != -1) return ret;
    
    ret = 0;
    for (int next = 0; next < (int)words.size(); next++)
        if ((used & (1<<next)) == 0)
        {
            int cand = overlap[last][next] + Restore(next, used + (1<<next));
            ret = max(ret, cand);
        }
    
    return ret;
}

string Reconstruction(int last, int used)
{
    if (used == ((1<<words.size()) - 1)) return "";
    
    for (int next = 0; next < (int)words.size(); next++)
    {
        if (used & (1<<next)) continue;
        int ifUsed = Restore(next, used + (1<<next)) + overlap[last][next];
        if (Restore(last, used) == ifUsed)
            return (words[next].substr(overlap[last][next]) + Reconstruction(next, used + (1<<next)));
    }
    
    return "**********fail***********";
}

void Solve()
{
    Reset();
    int k;
    cin>>k;
    string tmpWord;
    for (int i = 0; i < k; i++)
    {
        cin>>tmpWord;
        InsertNewWord(tmpWord);
    }
    
    CalcOverlap();
    
    int minLen = 1234567890;
    string result = "";
    for (int i = 0; i < (int)words.size(); i++)
    {
        string tmpStr = words[i] + Reconstruction(i, (1<<i));
        if (minLen > (int)tmpStr.length())
        {
            minLen = (int)tmpStr.length();
            result = tmpStr;
        }
    }
    
    cout<<result<<endl;
}

int main(int argc, const char * argv[]) {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
