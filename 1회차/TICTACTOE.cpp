#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>

#define _USE_MATH_DEFINES

using namespace std;

vector<string> board(3);
char _turn;
int cache[20000];

void Reset()
{
    for (int i = 0; i < 20000; i++)
        cache[i] = -2;
}

void GetInput()
{
    int t = 0;
    for (int i = 0; i < 3; i++) {
        cin>>board[i];
        for (int j = 0; j < (int)board[i].length(); j++) {
            if (board[i][j] == 'x') t++;
            else if (board[i][j] == 'o') t--;
        }
    }
    if (t > 0) _turn = 'o';
    else _turn = 'x';
}

bool IsFinished(const vector<string>& _board, char turn)
{
    bool isDiaFin = true;
    bool isDiaFin2 = true;
    for (int i = 0; i < 3; i++) {
        bool isColFin = true, isRowFin = true;
        for (int j = 0; j < 3; j++) {
            if (_board[i][j] != turn) isColFin = false;
            if (_board[j][i] != turn) isRowFin = false;
        }
        if (isColFin) return true;
        if (isRowFin) return true;
        
        if (_board[i][i] != turn) isDiaFin = false;
        if (_board[i][2-i] != turn) isDiaFin2 = false;
    }
    
    if (isDiaFin) return true;
    if (isDiaFin2) return true;
    
    return false;
}

int Bijection(const vector<string>& _board)
{
    int ret = 0;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++) {
            ret = ret*3;
            if (_board[y][x] == 'o') ret++;
            else if (board[y][x] == 'x') ret += 2;
        }
    return ret;
}

int CanWin(vector<string>& _board, char turn)
{
    if (IsFinished(_board, 'o'+'x'-turn)) return -1;
    int& ret = cache[Bijection(_board)];
    if (ret != -2) return ret;
    
    int minValue = 2;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
            if (_board[y][x] == '.') {
                _board[y][x] = turn;
                minValue = min(minValue, CanWin(_board, 'o'+'x'-turn));
                _board[y][x] = '.';
            }
    
    if (minValue == 2 || minValue == 0) return ret = 0;
    
    return ret = -minValue;
}

void Solve()
{
    Reset();
    GetInput();
    
    int result = CanWin(board, _turn);
    if (result == 0)
        cout<<"TIE"<<endl;
    else if (result != -1)
        cout<<(char)_turn<<endl;
    else
        cout<<(char)('o'+'x'-_turn)<<endl;
}

int main(int argc, const char * argv[]) {
    freopen("input.txt","r",stdin);	freopen("output.txt","w",stdout);
    
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
