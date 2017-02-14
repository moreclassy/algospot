#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>

#define _USE_MATH_DEFINES

using namespace std;

int start;
int cache[1<<25];
vector<int> moves;
inline int cell(int y, int x) { return 1 << (y*5 + x); }

void PreCalc()
{
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++) {
			vector<int> cells;
			for (int dy = 0; dy < 2; dy++)
				for (int dx = 0; dx < 2; dx++)
					cells.push_back(cell(y + dy, x + dx));
			int square = cells[0] + cells[1] + cells[2] + cells[3];
			for (int i = 0; i < 4; i++)
				moves.push_back(square - cells[i]);
		}

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 4; j++) {
			moves.push_back(cell(i, j) + cell(i, j+1));
			moves.push_back(cell(j, i) + cell(j+1, i));
		}
}

void Reset()
{
    memset(cache, -1, sizeof(cache));
}

void GetInput()
{
	start = 0;
	for (int i = 0; i < 25; i++) {
		char input;
		cin>>input;
		if (input == '#') start |= (1<<i);
	}
}

bool CanWin(int board)
{
	int& ret = cache[board];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < moves.size(); i++)
		if ((moves[i] & board) == 0 && !CanWin(board | moves[i])) {
			ret = 1;
			break;
		}

	return ret;
}

void Solve()
{
    Reset();
    GetInput();
    
	cout<<(CanWin(start) ? "WINNING" : "LOSING")<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
	PreCalc();
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
