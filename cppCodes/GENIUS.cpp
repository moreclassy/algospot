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
    
    SquareMatrix& operator=(SquareMatrix& other)
    {
        matrix = other.matrix;
        
        return *this;
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
        if ((int)matrix.size() != other.size()) throw "행렬 크기 안맞음";
        
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
    
    SquareMatrix pow(int exponent)
    {
        if (exponent == 1) {
            SquareMatrix tmpMatrix = (*this);
            return tmpMatrix;
        }
        
        if (exponent % 2 == 1) {
            SquareMatrix tmpMatrix = (*this);
            SquareMatrix tmp2 = this->pow(exponent - 1);
            return tmpMatrix * tmp2;
        }
        
        SquareMatrix tmpMatrix = this->pow(exponent/2);
        return tmpMatrix * tmpMatrix;
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
    
    SquareMatrix Wk = W.pow(k);
    
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
    freopen("input.txt","r",stdin);	freopen("output.txt","w",stdout);
    
    cout.precision(8); cout.setf(ios::showpoint);
    
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
