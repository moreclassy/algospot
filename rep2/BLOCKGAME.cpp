#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bitset>
#include <cstring>

using namespace std;

char dp[1<<25];
vector<int> moves;

inline int cell(int r, int c) { return 1 << (5 * r + c); }

int getInputState() {
    int ret = 0;
    for (int i = 0; i < 25; i++) {
        char in;
        cin>>in;
        if (in == '#')
            ret += (1<<i);
    }
    
    return ret;
}

int flipLeft(int state) {
    int nextState = 0;
    
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if ((state & cell(r, c)) != 0) {
                nextState += cell(r, 4 - c);
            }
        }
    }
    
    return nextState;
}

int flipUp(int state) {
    int nextState = 0;
    
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if ((state & cell(r, c)) != 0) {
                nextState += cell(4 - r, c);
            }
        }
    }
    
    return nextState;
}

int rotate(int state) {
    int nextState = 0;
    
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if ((state & cell(r, c)) != 0) {
                nextState += cell(c, 4 - r);
            }
        }
    }
    
    return nextState;
}

int diag1(int state) {
    int nextState = 0;
    
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if ((state & cell(r, c)) != 0) {
                nextState += cell(c, r);
            }
        }
    }
    
    return nextState;
}

int diag2(int state) {
    int nextState = 0;
    
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if ((state & cell(r, c)) != 0) {
                nextState += cell(4 - r, 4 - c);
            }
        }
    }
    
    return nextState;
}

void setVal(int state, char val) {
    int rot = state;
    for (int i = 0; i < 3; i++) {
        rot = rotate(rot);
        dp[rot] = val;
    }
    dp[flipLeft(state)] = val;
    dp[flipUp(state)] = val;
    dp[diag1(state)] = val;
    dp[diag2(state)] = val;
}

char canWin(int state) {
    char &ret = dp[state];
    if (ret != -1) return ret;
    
    for (int i = 0; i < moves.size(); i++) {
        if ((moves[i] & state) == 0 && canWin(state | moves[i]) == 0) {
            setVal(state, 1);
            return ret = 1;
        }
    }
    
    setVal(state, 0);
    return ret = 0;
}

void solve() {
    memset(dp, -1, 1<<25);
    dp[0] = 0;
    
    int state = getInputState();
    
    if (canWin(state) == 1)
        cout<<"WINNING"<<endl;
    else
        cout<<"LOSING"<<endl;
}

void preCalc() {
    for (int r = 0; r < 4; r++)  {
        for (int c = 0; c < 4; c++) {
            vector<int> cells;
            for (int dr = 0; dr < 2; dr++) {
                for (int dc = 0; dc < 2; dc++) {
                    cells.push_back(cell(r + dr, c + dc));
                }
            }
            int square = cells[0] + cells[1] + cells[2] + cells[3];
            for (int i = 0; i < 4; i++) {
                moves.push_back(square - cells[i]);
            }
        }
    }
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            moves.push_back(cell(i, j) + cell(i, j+1));
            moves.push_back(cell(j, i) + cell(j+1, i));
        }
    }
}

int main() {
    preCalc();
    
    int c;
    cin>>c;
    
    for (int i = 0; i < c; i++) {
        solve();
    }

	return 0;
}
