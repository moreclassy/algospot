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

vector<char> map{' ', '!', '$', '%', '(', ')', '*'};

void Solve()
{
    string in;
    cin>>in;
    for (int i = 0; i < in.size(); i++)
    {
        if (in[i] == '%') {
            int idx = i+2;
            if (in[idx] == '0')
                cout<<map[0];
            else if (in[idx] == '1')
                cout<<map[1];
            else if (in[idx] == '4')
                cout<<map[2];
            else if (in[idx] == '5')
                cout<<map[3];
            else if (in[idx] == '8')
                cout<<map[4];
            else if (in[idx] == '9')
                cout<<map[5];
            else if (in[idx] == 'a')
                cout<<map[6];
            i += 2;
        } else {
            cout<<in[i];
        }
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
