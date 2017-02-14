const double PI = 2.0 * acos(0.0);

struct vector2 {
    double x, y;
    
    explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_)
    {}
    
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
    
    double norm() const { return hypot(x, y); }
    
    vector2 normalize() const {
        return vector2(x / norm(), y / norm());
    }
    
    // x축의 양의 방향으로부터 이 벡터까지 반시계 방향으로 잰 각도
    double polar() const { return fmod(atan2(y, x) + 2*PI, 2*PI); }
    
    double dot(const vector2& rhs) const {
        return x*rhs.x + y*rhs.y;
    }
    
    double cross(const vector2& rhs) const {
        return x*rhs.y - y*rhs.x;
    }
    
    // 이 벡터를 rhs에 사영한 결과
    vector2 project(const vector2& rhs) const {
        vector2 r = rhs.normalize();
        return r * r.dot(rhs);
    }
};