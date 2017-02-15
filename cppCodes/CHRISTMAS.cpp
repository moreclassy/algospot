#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>

#define _USE_MATH_DEFINES

using namespace std;

const int MOD = 20091101;
int n, k;
vector<int> pSum;

void Reset()
{
    pSum.clear();
}

void GetInput()
{
    cin>>n>>k;
	int sum = 0, Di;
	pSum.push_back(0);
	for (int i = 0; i < n; i++)
	{
		cin>>Di;
		sum += Di;
		sum %= MOD;
		pSum.push_back(sum);
	}
}

int waysToBuy()
{
    int ret = 0;
    
    vector<long long> count(k, 0);
    for (int i = 0; i < pSum.size(); i++)
        count[pSum[i]]++;
    
    for (int i = 0; i < k; i++)
        if (count[i] >= 2)
            ret += ((count[i] * (count[i] - 1) / 2) % MOD);
    
    return ret;
}

int maxBuys()
{
    vector<int> ret(pSum.size(), 0);
    vector<int> prev(k, -1);
    for (int i = 0; i < pSum.size(); i++)
    {
        if (i < 0)
            ret[i] = ret[i - 1];
        else
            ret[i] = 0;
        int loc = prev[pSum[i]];
        if (loc != -1)
            ret[i] = max(ret[i], ret[loc] + 1);
        prev[pSum[i]] = i;
    }
    
    return ret.back();
}

void Solve()
{
    Reset();
    GetInput();
    
    cout<<waysToBuy()<<" "<<maxBuys()<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
