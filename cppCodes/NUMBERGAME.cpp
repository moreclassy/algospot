//#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>

#define _USE_MATH_DEFINES

using namespace std;

ifstream cin("input.txt"); ofstream cout("output.txt");

const int EMPTY = -987654321;
int n, board[50], cache[50][50];

void Reset()
{
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++)
			cache[i][j] = EMPTY;
}

void GetInput()
{
    cin>>n;
	for (int i = 0; i < n; i++)
		cin>>board[i];
}

int play(int left, int right)
{
	if (left > right) return 0;

	int& ret = cache[left][right];
	if (ret != EMPTY) return ret;

	ret = max(ret, -play(left+1, right) + board[left]);
	ret = max(ret, -play(left, right-1) + board[right]);

	if(right - left >= 1) {
		ret = max(ret, -play(left+2, right));
		ret = max(ret, -play(left, right-2));
	}

	return ret;
}

void Solve()
{
    Reset();
    GetInput();
    
	cout<<play(0, n-1)<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
