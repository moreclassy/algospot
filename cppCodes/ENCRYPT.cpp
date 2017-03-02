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
    string in;
    cin>>in;
    string buf = "";
    for (int i = 0; i < in.size(); i++)
    {
        if (i % 2)
            buf += in[i];
        else
            cout<<in[i];
    }
    cout<<buf<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
