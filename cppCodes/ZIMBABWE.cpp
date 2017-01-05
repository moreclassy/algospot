#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>
#include <string>

using namespace std;

string e, digits;
int n, m;
int cache[1<<14][20][2];

void Reset()
{
	memset(cache, 0, sizeof(cache));
}

int price(int index, int taken, int mod, int less)
{
	if (index == n)
		return (mod == 0 && less == 1) ? 1 : 0;
	int& ret = cache[taken][mod][less];
}

void Solve()
{
	Reset();
	cin>>e>>m;
	n = e.length();
	digits = e;
	sort(digits.begin(), digits.end());
	cout<<price(0, 0, 0, 1)<<endl;
}

int main(int argc, const char * argv[]) {
	int caseCnt = 0;
	cin >> caseCnt;
	
	cout.precision(10);
	for (int i = 0; i < caseCnt; i++) {
		Solve();
	}
	
	return 0;
}