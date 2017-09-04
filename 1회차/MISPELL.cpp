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
    int i;
    cin>>i;
    string in;
    cin>>in;
    if (i > 1){
        cout<<in.substr(0, i-1);
    }
    cout<<in.substr(i, in.size() - i)<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        cout<<i+1<<" ";
        Solve();
    }
    
    return 0;
}
