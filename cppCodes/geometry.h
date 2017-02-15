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

double ccw(vector2 a, vector2 b)
{
	return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b)
{
	return ccw(a - p, b - p);
}

const double EPSILON = 1e-9;

bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x)
{
	double det = (b - a).cross(d - c);

	if (fabs(det) < EPSILON) return false;

	x = a + (b - a) * ((c - a).cross(d - c) / det);

	return true;
}

bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d)
{
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);

	if (ab == 0 && cd == 0)
	{
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

bool isInside(vector2 q, const vector<vector2>& p)
{
	int crosses = 0;
	for (int i = 0; i < p.size(); i++)
	{
		int j = (i + 1) % p.size();
		if ((p[i].y > q.y) != (p[j].y > q.y))
		{
			double atX = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			if (q.x < atX)
				++crosses;
		}
	}
	return crosses % 2 > 0;
}