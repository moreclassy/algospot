#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>

#define _USE_MATH_DEFINES

using namespace std;

int n, k, m, length[50], favorite[10];
double T[50][50];

void Reset()
{
    memset(T, 0, sizeof(T));
}

void GetInput()
{
    cin>>n>>k>>m;
    
    for (int i = 0; i < n; i++)
        cin>>length[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin>>T[i][j];
    for (int i = 0; i < m; i++)
        cin>>favorite[i];
}

void Solve()
{
    Reset();
    GetInput();
    
}

int main(int argc, const char * argv[]) {
    freopen("input.txt","r",stdin);	freopen("output.txt","w",stdout);
    
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    fclose(stdin);	fclose(stdout);
    
    return 0;
}
