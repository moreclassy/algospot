#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

class point {
public:
    double x, y;
};

vector<point> hull1, hull2;

vector<pair<point, point>> upper, lower;

void decompose(const vector<point>& hull) {
    int n = (int)hull.size();
    for (int i = 0; i < n; i++) {
        if (hull[i].x < hull[(i+1)%n].x)
            lower.push_back(make_pair(hull[i], hull[(i+1)%n]));
        else if (hull[i].x > hull[(i+1)%n].x)
            upper.push_back(make_pair(hull[i], hull[(i+1)%n]));
    }
}

bool between(const point& a, const point& b, double x) {
    return (a.x <= x && x <= b.x) || (b.x <= x && x <= a.x);
}

double at(const point& a, const point& b, double x) {
    double dy = b.y - a.y, dx = b.x - a.x;
    return a.y + dy * (x - a.x) / dx;
}

double vertical(double x) {
    double minUp = 100, maxLow = -1;
    
    for (int i = 0; i < upper.size(); i++)
        if (between(upper[i].first, upper[i].second, x))
            minUp = min(minUp, at(upper[i].first, upper[i].second, x));
    
    for (int i = 0; i < lower.size(); i++)
        if (between(lower[i].first, lower[i].second, x))
            maxLow = max(maxLow, at(lower[i].first, lower[i].second, x));
    
    return minUp - maxLow;
}

double solve() {
    int n, m;
    cin>>n>>m;
    hull1 = vector<point>(n);
    hull2 = vector<point>(m);
    
    double minX1 = 101.0, maxX1 = -1.0;
    for (int i = 0; i < n; i++) {
        cin>>hull1[i].x>>hull1[i].y;
        minX1 = min(minX1, hull1[i].x);
        maxX1 = max(maxX1, hull1[i].x);
    }
    
    double minX2 = 101.0, maxX2 = -1.0;
    for (int i = 0; i < m; i++) {
        cin>>hull2[i].x>>hull2[i].y;
        minX2 = min(minX2, hull2[i].x);
        maxX2 = max(maxX2, hull2[i].x);
    }
    
    upper = vector<pair<point, point>>();
    lower = vector<pair<point, point>>();
    
    decompose(hull1);
    decompose(hull2);
    
    double lo = max(minX1, minX2);
    double hi = min(maxX1, maxX2);
    
    if (hi < lo) return 0;
    
    for (int iter = 0; iter < 100; iter++) {
        double aab = (lo*2 + hi) / 3.0;
        double abb = (lo + 2*hi) / 3.0;
        
        if (vertical(aab) < vertical(abb))
            lo = aab;
        else
            hi = abb;
    }
    
    return max(0.0, vertical(hi));
}

int main() {
    cout<<fixed;
    cout.precision(10);
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        cout<<solve()<<endl;
    }
    
    return 0;
}
