#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

int cache[19684];

int state2int(char s) {
    if (s == '.') return 0;
    if (s == 'x') return 1;
    if (s == 'o') return 2;
    return -1000000;
}

int getBlock(int state, int r, int c) {
    return state / (int)pow(3, r*3 + c) % 3;
}

int countBlock(int state, int block) {
    int ret = 0;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (block == getBlock(state, r, c))
                ret++;
        }
    }
    return ret;
}

int putBlock(int state, int r, int c, int block) {
    return state + block * (int)pow(3, r*3 + c);
}

int checkWinner(int state) {
    int board[3][3];
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            board[r][c] = getBlock(state, r, c);
        }
    }
    
    bool is1win = true;
    bool is2win = true;
    
    for (int r = 0; r < 3; r++) {
        is1win = true;
        is2win = true;
        for (int c = 0; c < 3; c++) {
            if (board[r][c] != 1) is1win = false;
            if (board[r][c] != 2) is2win = false;
        }
        if (is1win) return 1;
        if (is2win) return 2;
    }
    
    for (int c = 0; c < 3; c++) {
        is1win = true;
        is2win = true;
        for (int r = 0; r < 3; r++) {
            if (board[r][c] != 1) is1win = false;
            if (board[r][c] != 2) is2win = false;
        }
        if (is1win) return 1;
        if (is2win) return 2;
    }
    
    is1win = true;
    is2win = true;
    for (int i = 0; i < 3; i++) {
        if (board[i][i] != 1) is1win = false;
        if (board[i][i] != 2) is2win = false;
    }
    if (is1win) return 1;
    if (is2win) return 2;
    
    is1win = true;
    is2win = true;
    for (int i = 0; i < 3; i++) {
        if (board[i][2-i] != 1) is1win = false;
        if (board[i][2-i] != 2) is2win = false;
    }
    if (is1win) return 1;
    if (is2win) return 2;
    
    return -1;
}

int winner(int state) {
    int& ret = cache[state];
    if (ret != -1) return ret;
    
    int isOver = checkWinner(state);
    if (isOver != -1) return isOver;
    
    int count0 = countBlock(state, 0);
    int count1 = countBlock(state, 1);
    int count2 = countBlock(state, 2);
    
    if (count0 == 0) {
        return 0;
    }
    
    bool isTie = false;
    int curBlock = count1 <= count2 ? 1 : 2;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (getBlock(state, r, c) == 0) {
                int nextWinner = winner(putBlock(state, r, c, curBlock));
                if (nextWinner == curBlock) return ret = curBlock;
                if (nextWinner == 0) isTie = true;
            }
        }
    }
    
    return ret = isTie ? 0 : 3 - curBlock;
}

string solve() {
    int state = 0;
    for (int i = 0; i < 9; i++) {
        char input; cin>>input;
        int cur = state2int(input);
        state += cur * (int)pow(3, i);
    }
    
    int ret = winner(state);
    if (ret == 1) return "x";
    if (ret == 2) return "o";
    return "TIE";
}

int main() {
    memset(cache, -1, sizeof(cache));
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        cout<<solve()<<endl;
    }
    
    return 0;
}
