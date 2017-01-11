#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>

#define _USE_MATH_DEFINES

using namespace std;

int n, k, m, length[50], favorite[10];
double T[50][50];

class SquareMatrix
{
    public :
    vector<vector<double>> matrix;
    
    SquareMatrix() { }
    SquareMatrix(int size)
    {
        matrix = *new vector<vector<double>>(size);
        for (int i = 0; i < size; i++)
            matrix[i] = *new vector<double>(size, 0);
    }
    
    void operator=(SquareMatrix& other)
    {
        matrix = other.matrix;
    }
    
    int size()
    {
        return (int)matrix.size();
    }
    
    vector<double>& operator[](int idx)
    {
        return matrix[idx];
    }
    
    SquareMatrix operator*(SquareMatrix& other)
    {
        if ((int)matrix.size() != other.size()) throw "행렬 크기 안맞음\n";
        
        SquareMatrix tmpMatrix(other.size());
        
        for (int i = 0; i < other.size(); i++) {
            for (int j = 0; j < other.size(); j++) {
                double tmp = 0;
                for (int k = 0; k < other.size(); k++)
                    tmp += matrix[i][k] * other[k][j];
                tmpMatrix[i][j] = tmp;
            }
        }
        
        return tmpMatrix;
    }
    
    void print()
    {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++)
                cout<<matrix[i][j]<<" ";
            cout<<endl;
        }
    }
};

SquareMatrix Identity(int n)
{
	SquareMatrix tmpMatrix(n);
	for (int i = 0; i < n; i++)
		tmpMatrix[i][i] = 1;
	return tmpMatrix;
}

SquareMatrix Pow(SquareMatrix& A, int exponent)
{
	if (exponent == 0 ) return Identity(A.size());
	if (exponent%2 > 0) return Pow(A, exponent -1) * A;
	SquareMatrix half = Pow(A, exponent/2);
	return half * half;
}

void Reset()
{
    memset(T, 0, sizeof(T));
}

void GetInput()
{
    cin>>n>>k>>m;
    
    for (int i = 0; i < n; i++)
        cin>>length[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin>>T[i][j];
    for (int i = 0; i < m; i++)
        cin>>favorite[i];
}

vector<double> getProb()
{
    SquareMatrix W(4*n);
    
    for (int i = 0; i < 3*n; i++)
        W[i][i+n] = 1.0;
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; j++)
            W[3*n + i][(4 - length[j])*n + j] = T[j][i];
    
    SquareMatrix Wk = Pow(W, k);
    
    vector<double> ret(n, 0);
    
    for (int song = 0; song < n; ++song)
        for (int start = 0; start < length[song]; start++)
            ret[song] += Wk[(3-start)*n + song][3*n];
    
    return ret;
}

void Solve()
{
    Reset();
    GetInput();
    
    vector<double> prob = getProb();
    
    for (int i = 0; i < m; i++)
        cout<<prob[favorite[i]]<<" ";
    cout<<endl;
}

int main(int argc, const char * argv[]) {
    //freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout); // xcode용
	//ifstream cin("input.txt"); ofstream cout("output.txt");

	cout.precision(8); cout.setf(ios::showpoint);

    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
