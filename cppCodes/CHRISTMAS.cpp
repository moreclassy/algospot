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

int SolveFirst()
{
	vector<int> tmpList = pSum;
	sort(tmpList.begin(), tmpList.end());
	int before = tmpList[0], cnt = 0, result = 0;
	for (int i = 1; i < tmpList.size(); i++)
	{
		if (tmpList[i] == before) {
			cnt++;
			continue;
		}
		if (cnt > 1) {
			result += cnt * (cnt - 1) / 2;
			cnt = 1;
			before = tmpList[i];
		}
	}

	return result;
}

void Solve()
{
    Reset();
    GetInput();
    cout<<SolveFirst()<<" "<<endl;;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
