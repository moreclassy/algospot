#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>

#define _USE_MATH_DEFINES

using namespace std;

int n, m[10001], e[10001];

void Reset()
{
    
}

void GetInput()
{
    cin>>n;
	for (int i = 0; i < n; i++)
		cin>>m[i];
	for (int i = 0; i < n; i++)
		cin>>e[i];
}

void Solve()
{
    Reset();
    GetInput();
    
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
