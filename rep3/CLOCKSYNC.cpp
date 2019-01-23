#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 987654321;

const int button[10][5] = {
    {0, 1, 2, -1, -1},
    {3, 7, 9, 11, -1},
    {4, 10, 14, 15, -1},
    {0, 4, 5, 6, 7},
    {6, 7, 8, 10, 12},
    {0, 2, 14, 15, -1},
    {3, 14, 15, -1, -1},
    {4, 5, 7, 14, 15},
    {1, 2, 3, 4, 5},
    {3, 4, 5, 9, 13}
};

int clocks[16];

bool isDone() {
    for (int i = 0; i < 16; i++)
        if (clocks[i] != 12 && clocks[i] != 0)
            return false;
    return true;
}

void clickButton(int bi) {
    for (int j = 0; j < 5; j++) {
        if (button[bi][j] < 0) continue;
        clocks[button[bi][j]] += 3;
        clocks[button[bi][j]] %= 12;
    }
}

int minButton(int bi) {
    if (isDone()) return 0;
    if (bi >= 10) return INF;
    
    int ret = INF;
    for (int i = 0; i <= 3; i++) {
        ret = min(ret, minButton(bi+1) + i);
        clickButton(bi);
    }
    
    return ret;
}

void solve() {
    for (int i = 0; i < 16; i++)
        cin>>clocks[i];
    
    int ret = minButton(0);
    cout<<(ret >= INF ? -1 : ret)<<endl;
}

int main() {
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
