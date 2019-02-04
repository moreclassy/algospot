#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

int n;
const double L = 25;

vector<double> differentiate(const vector<double>& poly) {
    vector<double> ret(poly.size() - 1);
    for (int i = 0; i < ret.size(); i++)
        ret[i] = (i+1) * poly[i+1];
    return ret;
}

vector<double> solveNaive(const vector<double>& poly) {
    if (poly.size() == 3) {
        double a2 = pow(poly[1], 2) - 4*poly[2]*poly[0];
        
        if (a2 < 0)
            return vector<double>();
        
        if (a2 < 1e-9)
            return vector<double>(1, a2);
        
        a2 = sqrt(a2) / (2*poly[2]);
        
        vector<double> ret;
        
        double a1 = -poly[1] / (2*poly[2]);
        ret.push_back(a1 - a2);
        ret.push_back(a1 + a2);
        
        sort(ret.begin(), ret.end());
        
        return ret;
    }
    
    if (poly.size() == 2) {
        return vector<double>(1, -poly[0] / poly[1]);
    }
    
    return vector<double>();
}

double evaluate(const vector<double>& poly, double x0) {
    double ret = poly[0];
    for (int i = 1; i < poly.size(); i++) {
        ret += poly[i]*pow(x0, i);
    }
    return ret;
}

vector<double> solve(const vector<double>& poly) {
    if ((int)poly.size() - 1 <= 2) return solveNaive(poly);
    
    vector<double> derivative = differentiate(poly);
    vector<double> sols = solve(derivative);
    
    sols.insert(sols.begin(), -L-1);
    sols.insert(sols.end(), L+1);
    
    vector<double> ret;
    for (int i = 0; i+1 < sols.size(); i++) {
        double x1 = sols[i], x2 = sols[i+1];
        double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);
        
        if (y1*y2 > 0) continue;
        
        if (y1 > y2) {
            swap(y1, y2);
            swap(x1, x2);
        }
        
        for (int iter = 0; iter < 100; iter++) {
            double mx = (x1 + x2) / 2;
            double my = evaluate(poly, mx);
            if (y1*my > 0) {
                y1 = my;
                x1 = mx;
            } else {
                y2 = my;
                x2 = mx;
            }
        }
        ret.push_back((x1 + x2) / 2);
    }
    
    sort(ret.begin(), ret.end());
    
    return ret;
}

void solve() {
    cin>>n;
    vector<double> poly(n+1);
    for (int i = n; i >= 0; i--)
        cin>>poly[i];
    
    auto ret = solve(poly);
    for (auto r : ret)
        cout<<r<<" ";
    cout<<endl;
}

int main() {
    cout<<fixed;
    cout.precision(12);
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
