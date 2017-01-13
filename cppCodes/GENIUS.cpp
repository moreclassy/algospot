//#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>
#include <stack>

#define _USE_MATH_DEFINES

using namespace std;

int n, k, m, length[50], favorite[10];
double T[50][50];
vector<bool> exponents;
ifstream cin("input.txt"); ofstream cout("output.txt");

class SquareMatrix
{
    public :
    double** matrix;
	int _size;
    
    SquareMatrix() {
		matrix = new double*[50];
		for (int i = 0; i < 50; i++)
			matrix[i] = new double[50];
	}
    SquareMatrix(int size)
    {
        setMatrix(size);
    }

	void setMatrix(int size)
	{
		_size = size;
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				matrix[i][j] = 0;
	}
    
	SquareMatrix& operator=(SquareMatrix& other)
    {
		this->copy(other);

		return *this;
    }

	void copy(SquareMatrix& other)
	{
		this->_size = other._size;
		for (int i = 0; i < other.size(); i++)
			for (int j = 0; j < other.size(); j++)
				matrix[i][j] = other.matrix[i][j];
	}
    
    int size()
    {
        return _size;
    }
    
    double* operator[](int idx)
    {
        return this->matrix[idx];
    }
    
    SquareMatrix operator*(SquareMatrix& other)
    {
        if (this->size() != other.size()) throw "행렬 크기 안맞음\n";
        
        SquareMatrix tmpMatrix(other.size());
        
        for (int i = 0; i < other.size(); i++) {
            for (int j = 0; j < other.size(); j++) {
                double tmp = 0;
                for (int k = 0; k < other.size(); k++)
                    tmp += matrix[i][k] * other.matrix[k][j];
                tmpMatrix.matrix[i][j] = tmp;
            }
        }
        
        return tmpMatrix;
    }

	void multiply(SquareMatrix& other, SquareMatrix& other2)
	{
		if (this->size() != other.size()) throw "행렬 크기 안맞음\n";

		for (int i = 0; i < other.size(); i++) {
			for (int j = 0; j < other.size(); j++) {
				double tmp = 0;
				for (int k = 0; k < other.size(); k++)
					tmp += other.matrix[i][k] * other2.matrix[k][j];
				matrix[i][j] = tmp;
			}
		}
	}
    
    void print()
    {
        for (int i = 0; i < this->size(); i++) {
            for (int j = 0; j < this->size(); j++)
                cout<<matrix[i][j]<<" ";
            cout<<endl;
        }
    }
};

SquareMatrix Identity(int n)
{
	SquareMatrix tmpMatrix(n);
	for (int i = 0; i < n; i++)
		tmpMatrix.matrix[i][i] = 1;
	return tmpMatrix;
}

SquareMatrix Pow(SquareMatrix& A, int exponent)
{
	if (exponent == 0 ) return Identity(A.size());	// 1
	if (exponent%2 > 0) return Pow(A, exponent -1) * A;	// 2
	SquareMatrix half = Pow(A, exponent/2);
	return half * half;	// 3
}

SquareMatrix W; SquareMatrix tmpMatrix; SquareMatrix Wk; SquareMatrix tmpMatrix2;

void GetExponents(int exponent)
{
	if (exponent == 0 || exponent == 1) return;

	if (exponent%2 == 0) {
		exponents.push_back(false);
		GetExponents(exponent / 2);
	} else if (exponent % 2 == 1) {
		exponents.push_back(true);
		GetExponents(exponent - 1);
	};
}

void Reset()
{
    memset(T, 0, sizeof(T));
	exponents.clear();
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

void PowMatrix()
{
	tmpMatrix = W; tmpMatrix2 = W; Wk = W;

	GetExponents(n);

	for (int i = (int)exponents.size() - 1; i >=0; i--)
	{
		if (exponents[i])
		{
			tmpMatrix = Wk;
			Wk.multiply(W, tmpMatrix);
		} else {
			tmpMatrix = Wk;
			tmpMatrix2 = Wk;
			Wk.multiply(tmpMatrix, tmpMatrix2);
		}
	}
}

vector<double> getProb()
{
    W.setMatrix(4*n);
    
    for (int i = 0; i < 3*n; i++)
        W.matrix[i][i+n] = 1.0;
    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; j++)
            W.matrix[3*n + i][(4 - length[j])*n + j] = T[j][i];
    
	PowMatrix();
    
    vector<double> ret(n, 0);
    
    for (int song = 0; song < n; ++song)
        for (int start = 0; start < length[song]; start++)
            ret[song] += Wk.matrix[(3-start)*n + song][3*n];
    
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

int main(void) {
    //freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout); // xcode용
	
	cout.precision(8); cout.setf(ios::showpoint);

    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }

	return 0;
}
