<<<<<<< HEAD
#include <iostream>
=======
//#include <iostream>
>>>>>>> 694b43ea09a4753fa63473750465f8d1479bb285
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>

#define _USE_MATH_DEFINES

using namespace std;

<<<<<<< HEAD
void Reset()
{
    
=======
ifstream cin("input.txt"); ofstream cout("output.txt");

const int EMPTY = -987654321;
int n, board[50], cache[50][50];

void Reset()
{
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++)
			cache[i][j] = EMPTY;
>>>>>>> 694b43ea09a4753fa63473750465f8d1479bb285
}

void GetInput()
{
<<<<<<< HEAD
    
=======
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
>>>>>>> 694b43ea09a4753fa63473750465f8d1479bb285
}

void Solve()
{
    Reset();
    GetInput();
    
<<<<<<< HEAD
}

int main(int argc, const char * argv[]) {
    freopen("input.txt","r",stdin);	freopen("output.txt","w",stdout);
    
=======
	cout<<play(0, n-1)<<endl;
}

int main(int argc, const char * argv[]) {
>>>>>>> 694b43ea09a4753fa63473750465f8d1479bb285
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
