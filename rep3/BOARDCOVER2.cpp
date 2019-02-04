#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <algorithm>

using namespace std;

vector<vector<pair<int, int>>> rotations;
int blockSize;
int boardH, boardW;
int covered[10][10];
int best;

vector<string> rotate(const vector<string>& arr) {
    vector<string> ret(arr[0].size(), string(arr.size(), '.'));
    for (int i = 0; i < arr.size(); i++)
        for (int j = 0; j < arr[0].size(); j++)
            ret[j][arr.size()-i-1] = arr[i][j];
    return ret;
}

void generateRotation(vector<string> block) {
    rotations.clear();
    rotations.resize(4);
    for (int rot = 0; rot < 4; rot++) {
        int originY = -1, originX = -1;
        for (int i = 0; i < block.size(); i++)
            for (int j = 0; j < block[i].size(); j++)
                if (block[i][j] == '#') {
                    if (originY == -1) {
                        originY = i;
                        originX = j;
                    }
                    rotations[rot].push_back(make_pair(i - originY, j - originX));
                }
        block = rotate(block);
    }
    sort(rotations.begin(), rotations.end());
    rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
    blockSize = (int)rotations[0].size();
}

bool outRange(int ny, int nx) {
    return ny < 0 || ny >= boardH || nx < 0 || nx >= boardW;
}

bool set(int y, int x, const vector<pair<int, int>>& block, int delta) {
    bool ret = true;
    
    for (auto blk : block) {
        int ny = y + blk.first, nx = x + blk.second;
        if (outRange(ny, nx)) {
            ret = false;
            continue;
        }
        if (covered[ny][nx]) ret = false;
        covered[ny][nx] += delta;
    }
    
    return ret;
}

void printCover() {
    for (int h = 0; h < boardH; h++) {
        for (int w = 0; w < boardW; w++)
            cout<<covered[h][w]<<" ";
        cout<<endl;
    }
}

int countZero() {
    int ret = 0;
    for (int h = 0; h < boardH; h++)
        for (int w = 0; w < boardW; w++)
            if (covered[h][w] == 0)
                ret++;
    return ret;
}

void search(int placed) {
    if (best >= placed + countZero()/blockSize)
        return;
    int y = -1, x = -1;
    
    for (int i = 0; i < boardH; i++) {
        for (int j = 0; j < boardW; j++)
            if (covered[i][j] == 0) {
                y = i;
                x = j;
                break;
            }
        if (y != -1) break;
    }
    
    if (y == -1) {
        best = max(best, placed);
        return;
    }
    
    for (int i = 0; i < rotations.size(); i++) {
        if (set(y, x, rotations[i], 1))
            search(placed + 1);
        set(y, x, rotations[i], -1);
    }
    
    covered[y][x] = 1;
    search(placed);
    covered[y][x] = 0;
}

int solve() {
    best = 0;
    
    int blockR, blockC;
    cin>>boardH>>boardW>>blockR>>blockC;
    
    memset(covered, 0, sizeof(covered));
    for (int h = 0; h < boardH; h++)
        for (int w = 0; w < boardW; w++) {
            char in; cin>>in;
            if (in == '#') {
                covered[h][w] = 1;
            }
        }
    
    vector<string> block(blockR);
    for (int r = 0; r < blockR; r++)
        cin>>block[r];
    
    generateRotation(block);
    
    search(0);
    
    return best;
}

int main() {
    int t; cin>>t;
    for (int i = 0; i < t; i++) {
        cout<<solve()<<endl;
    }
    return 0;
}
