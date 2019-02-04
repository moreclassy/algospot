#include <iostream>
#include <cmath>

using namespace std;

const int MAX_N = 10*1000*1000;

int minFactor[MAX_N+1];

int minFactorPower[MAX_N+1];
int factors[MAX_N+1];

int solve() {
    int n, lo, hi;
    cin>>n>>lo>>hi;
    
    int ret = 0;
    for (int i = lo; i <= hi; i++) {
        if (factors[i] == n) {
            ret++;
        }
    }
    
    return ret;
}

void getFactorSmart() {
    factors[1] = 1;
    
    for (int n = 2; n <= MAX_N; n++) {
        if (minFactor[n] == n) {
            minFactorPower[n] = 1;
            factors[n] = 2;
        } else {
            int p = minFactor[n];
            int m = n / p;
            
            if (p != minFactor[m]) {
                minFactorPower[n] = 1;
            } else {
                minFactorPower[n] = minFactorPower[m] + 1;
            }
            
            int a = minFactorPower[n];
            factors[n] = (factors[m] / a) * (a + 1);
        }
    }
}

void eratosthenes2() {
    minFactor[0] = minFactor[1] = -1;
    
    for (int i = 2; i <= MAX_N; i++)
        minFactor[i] = i;
    
    int sqrtn = (int)sqrt(MAX_N);
    
    for (int i = 2; i <= sqrtn; i++) {
        if (minFactor[i] == i) {
            for (int j = i*i; j <= MAX_N; j += i) {
                if (minFactor[j] == j)
                    minFactor[j] = i;
            }
        }
    }
}

int main() {
    eratosthenes2();
    getFactorSmart();
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        cout<<solve()<<endl;
    }
    
    return 0;
}
