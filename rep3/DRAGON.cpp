#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX = 1000000000 + 1;
int n, p, l;
int length[51];

void preCalc() {
    length[0] = 1;
    for (int i = 1; i <= 50; i++)
        length[i] = min(MAX, 2*length[i-1] + 2);
}

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";

char expand(const string& dragonCurve, int generation, int skip) {
    if (generation == 0) {
        assert(skip < dragonCurve.size());
        return dragonCurve[skip];
    }
    
    for (int i = 0; i < dragonCurve.size(); i++) {
        if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
            if (skip >= length[generation]) {
                skip -= length[generation];
            } else if (dragonCurve[i] == 'X') {
                return expand(EXPAND_X, generation-1, skip);
            } else {
                return expand(EXPAND_Y, generation-1, skip);
            }
        } else if (skip > 0) {
            --skip;
        } else {
            return dragonCurve[i];
        }
    }
    return '#';
}

void solve() {
    cin>>n>>p>>l;
    
    for (int i = -1; i < l-1; i++) {
        cout<<expand("FX", n, p+i);
    }
    
    cout<<endl;
}

int main() {
    preCalc();
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
