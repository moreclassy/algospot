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
    vector<string> ret;
    for (int i = 0; i < in.size(); i = i+2)
    {
        ret.push_back(in.substr(i, 2));
    }
    sort(ret.begin(), ret.end());
    for (int i = 0; i < ret.size(); i++)
    {
        cout<<ret[i];
    }
    cout<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
