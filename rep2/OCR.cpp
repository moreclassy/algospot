#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
int wCnt, pCnt;
double first[500], beside[500][500], wrong[500][500];
string words[500], input[100];
map<string, int> strIdx;
int inCnt;
int pre[100][500];

double getP(vector<vector<double>> &dp, int idx, int w) {
    double &ret = dp[idx][w];
    if (ret > -1.0) return ret;
    
    ret = 0.0;
    int inputIdx = strIdx[input[idx]];
    for (int i = 0; i < wCnt; i++) {
        double pi = getP(dp, idx - 1, i) * beside[i][w] * wrong[w][inputIdx];
        if (ret < pi) {
            pre[idx][w] = i;
        }
    }
    return ret;
}

void printWord(int idx, int w) {
    if (idx < 0) return;
    cout<<words[w]<<" ";
    printWord(idx - 1, pre[idx][w]);
}

void solve() {
    cin>>inCnt;
    for (int i = 0; i < inCnt; i++)
        cin>>input[i];
    
    vector<vector<double>> dp(inCnt, vector<double>(wCnt, -2.0));
    int firstIdx = strIdx[input[0]];
    for (int i = 0; i < wCnt; i++)
        dp[0][i] = first[i] * wrong[i][firstIdx];
    
    double maxP = 0.0;
    int lastW = 0;
    for (int i = 0; i < wCnt; i++) {
        int curP = getP(dp, inCnt - 1, i);
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
    for (int i = 0; i < wCnt; i++) {
        cin>>words[i];
        strIdx[words[i]] = i;
    }
    for (int i = 0; i < wCnt; i++)
        cin>>first[i];
    for (int i = 0; i < wCnt; i++)
        for (int j = 0; j < wCnt; j++)
            cin>>beside[i][j];
    for (int i = 0; i < wCnt; i++)
        for (int j = 0; j < wCnt; j++)
            cin>>wrong[i][j];
    
    for (int i = 0; i < pCnt; i++)
        solve();
    
	return 0;
}
