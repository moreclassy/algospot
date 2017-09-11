#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <queue>

#define _USE_MATH_DEFINES

using namespace std;

void Solve()
{
    int retX = 0, retY = 0;
    int inX, inY;
    for (int i = 0; i < 3; i++)
    {
        cin>>inX>>inY;
        retX ^= inX;
        retY ^= inY;
    }
    cout<<retX<<" "<<retY<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
