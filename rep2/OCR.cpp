#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
int wCnt, pCnt;
vector<double> first;
vector<vector<double>> beside, wrong;
vector<string> words;
int input[100];
map<string, int> strIdx;
int inCnt;
int pre[100][500];

void printPre() {
    for (int i = 0; i < inCnt; i++) {
        for (int j = 0; j < wCnt; j++)
            cout<<pre[i][j]<<" ";
        cout<<endl;
    }
}

double getP(vector<vector<double>> &dp, int idx, int w) {
    double &ret = dp[idx][w];
    if (ret > -1.0) return ret;
    
    for (int i = 0; i < wCnt; i++) {
        double pi = getP(dp, idx - 1, i) * beside[i][w] * wrong[w][input[idx]];
        if (ret < pi) {
            pre[idx][w] = i;
            ret = pi;
        }
    }
    
    return ret;
}

void printWord(int idx, int w) {
    if (idx < 0) return;
    printWord(idx - 1, pre[idx][w]);
    cout<<words[w]<<" ";
}

void printTable(vector<vector<double>> &dp) {
    for (int i = 0; i < dp.size(); i++) {
        for (int j = 0; j < dp[i].size(); j++)
            cout<<dp[i][j]<<" ";
        cout<<endl;
    }
}

void solve() {
    cin>>inCnt;
    for (int i = 0; i < inCnt; i++) {
        string inStr;
        cin>>inStr;
        input[i] = strIdx[inStr];
    }
    
    vector<vector<double>> dp(inCnt, vector<double>(wCnt, -2.0));
    
    for (int i = 0; i < wCnt; i++)
        dp[0][i] = first[i] * wrong[i][input[0]];
    
    double maxP = -2.0;
    int lastW = 0;
    for (int i = 0; i < wCnt; i++) {
        double curP = getP(dp, inCnt - 1, i);
        
        if (curP > maxP) {
            maxP = curP;
            lastW = i;
        }
    }
    
    printWord(inCnt - 1, lastW);
    cout<<endl;
}

int main() {
    cin>>wCnt>>pCnt;
    
    words = vector<string>(wCnt);
    for (int i = 0; i < wCnt; i++) {
        cin>>words[i];
        strIdx[words[i]] = i;
    }
    
    first = vector<double>(wCnt);
    for (int i = 0; i < wCnt; i++)
        cin>>first[i];
    
    beside = vector<vector<double>>(wCnt, vector<double>(wCnt));
    for (int i = 0; i < wCnt; i++)
        for (int j = 0; j < wCnt; j++)
            cin>>beside[i][j];
    
    wrong = vector<vector<double>>(wCnt, vector<double>(wCnt));
    for (int i = 0; i < wCnt; i++)
        for (int j = 0; j < wCnt; j++)
            cin>>wrong[i][j];
    
    for (int i = 0; i < pCnt; i++)
        solve();
    
	return 0;
}
