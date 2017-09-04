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
    int target, tmp;
    cin>>target;
    for (int i = 0; i < 9; i++)
    {
        cin>>tmp;
        target -= tmp;
    }
    if (target >= 0)
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
