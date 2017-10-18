#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bitset>
#include <cstring>

using namespace std;

string board[5];
vector<char> dp;
int lblock[4][3][2] = {
    { {0, 0}, {1, 0}, {1, 1} },
    { {0, 0}, {1, 0}, {0, 1} },
    { {0, 0}, {1, 1}, {0, 1} },
    { {1, 0}, {0, 1}, {1, 1} },
};

int convert() {
    int ret = 0;
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == '#')
                ret += 1;
            ret <<= 1;
        }
    }
    ret >>= 1;
    return ret;
}

vector<string> convert(int state) {
    vector<string> ret(5, string(5, '.'));
    
    for (int i = 24; i >= 0; i--) {
        if (state & (1<<i)) {
            ret[(25-i-1)/5][(25-i-1)%5] = '#';
        }
    }
    
    return ret;
}

void print(vector<string>& state) {
    cout<<endl;
    for (auto s : state) {
        cout<<s<<endl;
    }
    cout<<endl;
}

void print(int state) {
    auto origin = convert(state);
    print(origin);
}

void getInput() {
    for (int i = 0; i < 5; i++)
        cin>>board[i];
    
    dp = vector<char>(1<<26, 'n');
}

int putBlock(int state, int r, int c) {
    state |= (1<<(5*(4 - r) + 4 - c));
    return state;
}

int removeBlock(int state, int r, int c) {
    state &= ~(1<<(5*(4 - r) + 4 - c));
    return state;
}

bool isEmpty(int state, int r, int c) {
    return (state & (1<<(5*(4 - r) + 4 - c))) == 0;
}

bool isPossible(int state, int r, int c, int blck) {
    for (int i = 0; i < 3; i++) {
        int nr = r + lblock[blck][i][0];
        int nc = c + lblock[blck][i][1];
        if (!isEmpty(state, nr, nc))
            return false;
    }
    
    return true;
}

int putLBlock(int state, int r, int c, int blck) {
    for (int i = 0; i < 3; i++) {
        int nr = r + lblock[blck][i][0];
        int nc = c + lblock[blck][i][1];
        state = putBlock(state, nr, nc);
    }
    
    return state;
}

int flipLeft(int state) {
    int nextState = 0;
    
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (!isEmpty(state, r, c)) {
                nextState = putBlock(nextState, r, 4 - c);
            }
        }
    }
    
    return nextState;
}

int flipUp(int state) {
    int nextState = 0;
    
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (!isEmpty(state, r, c)) {
                nextState = putBlock(nextState, 4 - r, c);
            }
        }
    }
    
    return nextState;
}

void setVal(int state, char val) {
    int flip = flipLeft(state);
    dp[flip] = val;
    flip = flipUp(flip);
    dp[flip] = val;
    flip = flipLeft(flip);
    dp[flip] = val;
}

char canWin(int state) {
    char &ret = dp[state];
    if (ret != 'n') return ret;
    
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (c < 4 && isEmpty(state, r, c) && isEmpty(state, r, c+1)) {
                int nextState = putBlock(state, r, c);
                nextState = putBlock(nextState, r, c+1);
                if (canWin(nextState) == 'l') {
                    setVal(state, 'w');
                    return ret = 'w';
                }
            }
            
            if (r < 4 && isEmpty(state, r, c) && isEmpty(state, r+1, c)) {
                int nextState = putBlock(state, r, c);
                nextState = putBlock(nextState, r+1, c);
                if (canWin(nextState) == 'l') {
                    setVal(state, 'w');
                    return ret = 'w';
                }
            }
            
            if (c < 4 && r < 4) {
                for (int blck = 0; blck < 4; blck++) {
                    if (isPossible(state, r, c, blck)) {
                        int nextState = putLBlock(state, r, c, blck);
                        if (canWin(nextState) == 'l') {
                            setVal(state, 'w');
                            return ret = 'w';
                        }
                    }
                }
            }
        }
    }
    
    setVal(state, 'l');
    return ret = 'l';
}

void solve() {
    getInput();
    
    if (canWin(convert()) == 'w')
        cout<<"WINNING"<<endl;
    else
        cout<<"LOSING"<<endl;
}

int main() {
    int c;
    cin>>c;
    
    for (int i = 0; i < c; i++) {
        solve();
    }

	return 0;
}
