#ifndef vetor2_h
#define vetor2_h

#include <cmath>
#include <vector>

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

bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
    double ab = ccw(a, b, c) * ccw(a, b, d);
    double cd = ccw(c, d, a) * ccw(c, d, b);
    
    if (ab == 0 && cd == 0) {
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        return !(b < c || d < a);
    }
    
    return ab <= 0 && cd <= 0;
}

const double EPSILON = 1e-9;

bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
    double det = (b - a).cross(d - c);
    
    if (fabs(det) < EPSILON) return false;
    
    x = a + (b - a) * ((c - a).cross(d - c) / det);
    
    return true;
}

typedef vector<vector2> polygon;

bool isInside(vector2 q, const polygon& p) {
    int crosses = 0;
    int n = (int)p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if ((p[i].y > q.y) != (p[j].y > q.y)) {
            double atX = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
            if (q.x < atX)
                crosses++;
        }
    }
    
    return crosses % 2 > 0;
}

polygon giftWrap(const vector<vector2>& points) {
    int n = (int)points.size();
    
    polygon hull;
    vector2 pivot = *min_element(points.begin(), points.end());
    hull.push_back(pivot);
    
    while (true) {
        vector2 ph = hull.back(), next = points[0];
        for (int i = 1; i < n; i++) {
            double cross = ccw(ph, next, points[i]);
            if (cross > 0 || (cross == 0 && (next - ph).norm() < (points[i] - ph).norm()))
                next = points[i];
        }
        
        if (next == pivot) break;
        hull.push_back(next);
    }
    
    return hull;
}

bool polygonIntersects(const polygon& p, const polygon& q) {
    int n = (int)p.size(), m = (int)q.size();
    
    if (isInside(p[0], q) || isInside(q[0], p)) return true;
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (segmentIntersects(p[i], p[(i+1)%n], q[j], q[(j+1)%m]))
                return true;
    
    return false;
}

#endif /* vetor2_h */
