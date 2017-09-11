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
    unsigned int in;
    cin>>in;
    unsigned int ret = 0;
    for (unsigned int i = 0; i < 4; i++)
    {
        ret <<= 8;
        ret |= in%(1<<8);
        in >>= 8;
    }
    
    cout<<ret<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
