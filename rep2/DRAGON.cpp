#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX = 1000000001;
const string EXPEND_X = "X+YF";
const string EXPEND_Y = "FX-Y";
const string FIRST = "FX";

int length[51];

void precalc() {
    length[0] = 1;
    for (int i = 1; i <= 50; i++) {
        length[i] = min(MAX, 2*length[i-1] + 2);
    }
}

char getDragon(const string &seed, int epoch, int skip) {
    if (epoch == 0) {
        assert(skip < seed.size());
        return seed[skip];
    }
    
    for (int i = 0; i < seed.size(); i++) {
        if (seed[i] == 'X' || seed[i] == 'Y') {
            if (skip >= length[epoch])
                skip -= length[epoch];
            else if (seed[i] == 'X')
                return getDragon(EXPEND_X, epoch - 1, skip);
            else
                return getDragon(EXPEND_Y, epoch - 1, skip);
        } else if (skip > 0)
            skip--;
        else
            return seed[i];
    }
    return '#';
}

void solve() {
    int epoch, start, len;
    cin>>epoch>>start>>len;
    
    for (int i = 0; i < len; i++) {
        cout<<getDragon(FIRST, epoch, start + i - 1);
    }
    cout<<endl;
}

int main() {
    int c;
    cin>>c;
    
    precalc();
    
    for (int i = 0; i < c; i++)
        solve();
    
    return 0;
}
