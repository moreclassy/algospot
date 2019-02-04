#include <iostream>

using namespace std;

double n;
int m;
double p;

double balance(double amount, int duration, double rates, double monthlyPayment) {
    double balance = amount;
    
    for (int i = 0; i < duration; i++) {
        balance *= (1.0 + (rates / 12.0) / 100.0);
        balance -= monthlyPayment;
    }
    
    return balance;
}

double payment(double amount, int duration, double rates) {
    double lo = 0, hi = amount * (1.0 + (rates / 12.0) / 100.0);
    
    for (int iter = 0; iter < 100; iter++) {
        double mid = (hi + lo) / 2.0;
        if (balance(amount, duration, rates, mid) <= 0)
            hi = mid;
        else
            lo = mid;
    }
    
    return hi;
}

void solve() {
    cin>>n>>m>>p;
    
    cout<<payment(n, m, p)<<endl;
}

int main() {
    cout<<fixed;
    cout.precision(10);
    int t; cin>>t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    
    return 0;
}
