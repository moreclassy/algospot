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

const double kgToPd = 2.2046, pdToKg = 0.4536, liToGa = 0.2642, gaToLi = 3.7854;

void Solve()
{
    double in;
    string type;
    cin>>in>>type;
    if (type == "kg")
        cout<<in*kgToPd<<" lb";
    else if (type == "lb")
        cout<<in*pdToKg<<" kg";
    else if (type == "l")
        cout<<in*liToGa<<" g";
    else if (type == "g")
        cout<<in*gaToLi<<" l";
    cout<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    cout<<fixed; cout.precision(4); cout.setf(ios::showpoint);
    for (int i = 0; i < caseCnt; i++) {
        cout<<i+1<<" ";
        Solve();
    }
    
    return 0;
}
