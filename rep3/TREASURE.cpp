#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

const double PI = 2.0 * acos(0.0);

struct vector2 {
    double x, y;
    
    explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    
    bool operator == (const vector2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    
    bool operator < (const vector2& rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }
    
    vector2 operator + (const vector2& rhs) const {
        return vector2(x + rhs.x, y + rhs.y);
    }
    
    vector2 operator - (const vector2& rhs) const {
        return vector2(x - rhs.x, y - rhs.y);
    }
    
    vector2 operator * (double rhs) const {
        return vector2(x * rhs, y * rhs);
    }
    
    double norm() const {
        return hypot(x, y);
    }
    
    vector2 normalize() const {
        return vector2(x / norm(), y / norm());
    }
    
    double polar() const {
        return fmod(atan2(y, x) + 2*PI, 2*PI);
    }
    
    double dot(const vector2& rhs) const {
        return x * rhs.x + y * rhs.y;
    }
    
    double cross(const vector2& rhs) const {
        return x * rhs.y - y * rhs.x;
    }
    
    vector2 project(const vector2& rhs) const {
        vector2 r = rhs.normalize();
        return r * r.dot(*this);
    }
};

double ccw(vector2 a, vector2 b) {
    return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b) {
    return ccw(a-p, b-p);
}

const double EPSILON = 1e-9;

bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
    double det = (b - a).cross(d - c);
    
    if (fabs(det) < EPSILON) return false;
    
    x = a + (b - a) * ((c - a).cross(d - c) / det);
    
    return true;
}

typedef vector<vector2> polygon;

polygon cutPoly(const polygon& p, const vector2& a, const vector2& b) {
    int n = (int)p.size();
    
    vector<bool> inside(n);
    for (int i = 0; i < n; i++)
        inside[i] = ccw(a, b, p[i]) >= 0;
    
    polygon ret;
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (inside[i]) ret.push_back(p[i]);
        if (inside[i] != inside[j]) {
            vector2 cross;
            assert(lineIntersection(p[i], p[j], a, b, cross));
            ret.push_back(cross);
        }
    }
    
    return ret;
}

polygon intersection(const polygon& p, double x1, double y1, double x2, double y2) {
    vector2 a(x1, y1), b(x2, y1), c(x2, y2), d(x1, y2);
    
    polygon ret = cutPoly(p, a, b);
    ret = cutPoly(ret, b, c);
    ret = cutPoly(ret, c, d);
    ret = cutPoly(ret, d, a);
    
    return ret;
}

double area(const polygon& p) {
    double ret = 0;
    int n = (int)p.size();
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        ret += p[i].cross(p[j]) / 2.0;
    }
    
    return fabs(ret);
}

void solve() {
    double x1, y1, x2, y2;
    cin>>x1>>y1>>x2>>y2;
    int n; cin>>n;
    
    polygon p(n);
    for (int i = 0; i < n; i++)
        cin>>p[i].x>>p[i].y;
    
    p = intersection(p, x1, y1, x2, y2);
    
    cout<<area(p)<<endl;
}

int main() {
    cout<<fixed;
    cout.precision(10);
    int c; cin>>c;
    for (int i = 0; i < c; i++) {
        solve();
    }
    
    return 0;
}
