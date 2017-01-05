#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>

using namespace std;

bool isFriend[10][10], isMatched[10];
int numOfstudent = 0, numOfCouple = 0;

void Reset()
{
	for(int i = 0; i < 10; i++)
	{
		isMatched[i] = false;
		for (int j = 0; j < 10; j++)
			isFriend[i][j] = false;
	}
}

bool IsComplete()
{
	for (int i = 0; i < numOfstudent; i++)
		if (!isMatched[i]) return false;
	return true;
}

int MatchCount(int begin)
{
	if (IsComplete()) return 1;
	if (begin >= numOfstudent) return 0;
	if (isMatched[begin]) return MatchCount(begin + 1);

	int result = 0;
	for (int j = begin + 1; j < numOfstudent; j++) if (!isMatched[j] && isFriend[begin][j])
	{
		isMatched[begin] = isMatched[j] = true;
		result += MatchCount(begin + 1);
		isMatched[begin] = isMatched[j] = false;
	}

	return result;
}

void Solve()
{
	Reset();
	cin>>numOfstudent>>numOfCouple;

	int i = 0, j = 0;
	for (int x = 0; x < numOfCouple; x++)
	{
		cin>>i>>j;
		isFriend[i][j] = isFriend[j][i] = true;
	}

	cout<<MatchCount(0)<<endl;
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