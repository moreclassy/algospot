#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int height = 0, width = 0;

const int blockType[4][3][2] = {
	{{0,0}, {1,0}, {0,1}},
	{{0,0}, {0,1}, {1,1}},
	{{0,0}, {1,0}, {1,1}},
	{{0,0}, {1,0}, {1,-1}}
};

int matrix[21][21];

void SetMatrix()
{
	for (int i = 0; i < 21; i++) {
		fill_n(matrix[i], 21, 0);
	}
    char tmp = '#';
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            cin>>tmp;
            if (tmp == '#') {   // filled
                matrix[h][w] = 1;
            } else if (tmp == '.') {    // empty
                matrix[h][w] = 0;
            }
        }
    }
}

void PrintMatrix()
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (matrix[i][j] == 0) {
				cout<<'.';
			} else {
				cout<<'#';
			}
		}
		cout<<endl;
	}
}

bool Set(int x, int y, int type, int delta)
{
	bool covered = true;
	for (int i = 0; i < 3; i++) {
		const int ny = y + blockType[type][i][0];
		const int nx = x + blockType[type][i][1];
		if (ny < 0 || ny >= height || nx < 0 || nx >= width) {
			covered = false;
		} else if ((matrix[ny][nx] += delta) > 1) {
			covered = false;
		}
	}
	return covered;
}

int CoverMatrix()
{
	int x = -1, y = -1;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (matrix[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1) {
			break;
		}
	}
	
	if (y == -1) {
		return 1;
	}
	
	int ret = 0;
	for (int type = 0; type < 4; type++) {
		if (Set(x, y, type, 1)) {
			ret += CoverMatrix();
		}
		Set(x, y, type, -1);
	}
	
	return ret;
}

void Solve()
{
    cin>>height>>width;
    SetMatrix();
    cout<<CoverMatrix()<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}