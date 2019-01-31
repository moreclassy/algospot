#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

char cache[1<<25];
vector<int> moves;
inline int cell(int y, int x) { return 1 << (y*5 + x); }

void precalc() {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            vector<int> cells;
            for (int dy = 0; dy < 2; dy++) {
                for (int dx = 0; dx < 2; dx++) {
                    cells.push_back(cell(y + dy, x + dx));
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

char play(int board) {
    char& ret = cache[board];
    if (ret != -1) return ret;
    
    ret = 0;
    for (int i = 0; i < moves.size(); i++) {
        if ((moves[i] & board) != 0) continue;
        if (!play(board | moves[i])) {
            ret = 1;
            break;
        }
    }
    
    return ret;
}

void solve() {
    int board = 0;
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            char input; cin>>input;
            if (input == '#') board += cell(r, c);
        }
    }
    
    cout<<(play(board) ? "WINNING" : "LOSING")<<endl;
}

int main() {
    memset(cache, -1, sizeof(cache));
    precalc();
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
