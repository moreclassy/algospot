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
    
    SquareMatrix& operator*(SquareMatrix& other)
    {
        if ((int)matrix.size() != other.size())
        {
            throw "행렬 크기 안맞음";
        }
        
        SquareMatrix tmpMatrix = *this;
        
        for (int i = 0; i < other.size(); i++) {
            for (int j = 0; j < other.size(); j++) {
                double tmp = 0;
                for (int k = 0; k < other.size(); k++)
                    tmp += tmpMatrix[i][k] * other[k][j];
                matrix[i][j] = tmp;
            }
        }
        
        return *this;
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

void Solve()
{
    Reset();
    GetInput();
    
}

int main(int argc, const char * argv[]) {
    freopen("input.txt","r",stdin);	freopen("output.txt","w",stdout);
    
    SquareMatrix W(3);
    W[0][0] = 1; W[0][1] = 2; W[0][2] = 0;
    W[1][0] = 2; W[1][1] = 0; W[1][2] = 3;
    W[2][0] = 2; W[2][1] = 0; W[2][2] = 1;
    
    SquareMatrix Z = W;
    Z[0][0] = 5;
    
    Z = (Z * W);
    Z.print();
    
    /*int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }*/
     
    fclose(stdin);	fclose(stdout);
    
    return 0;
}
