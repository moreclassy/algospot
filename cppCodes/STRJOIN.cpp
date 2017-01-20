#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>

#define _USE_MATH_DEFINES

using namespace std;

int n;
multiset<int> strs;

void Reset()
{
}

void GetInput()
{
	cin >> n;
	int tmp;
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		strs.insert(tmp);
	}
}

void Solve()
{
	Reset();
	GetInput();

	int ret = 0, tmp = 0;

	while (!strs.empty())
	{
		tmp = *(strs.begin()); strs.erase(strs.begin());
		if (!strs.empty())
		{
			tmp += *(strs.begin()); strs.erase(strs.begin());
			strs.insert(tmp);
			ret += tmp;
		}
		else {
			break;
		}
	}

	cout << ret << endl;
}

int main(int argc, const char * argv[]) {
	int caseCnt = 0;
	cin >> caseCnt;

	for (int i = 0; i < caseCnt; i++) {
		Solve();
	}

	return 0;
}
