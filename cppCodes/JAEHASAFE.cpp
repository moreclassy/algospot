#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>

#define _USE_MATH_DEFINES

using namespace std;

int n;

int shifts(const string& original, const string& target)
{
    return (int)(original + original).find(target);
}

void Reset()
{
    
}

void GetInput()
{
    cin>>n;
}

void Solve()
{
    Reset();
    GetInput();
    
    string a, b;
    cin>>a;
    
    int result = 0;
    
    for (int i = 0; i < n; i++)
    {
        cin>>b;
        if (i%2)
            result += shifts(a, b);
        else
            result += shifts(b, a);
        swap(a, b);
    }
    cout<<result<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
