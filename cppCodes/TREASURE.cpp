#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>
#include <cassert>

#include "geometry.h"

#define _USE_MATH_DEFINES

using namespace std;

typedef vector<vector2> polygon;

vector2 p1, p2;
polygon island;
int n;

void Reset()
{
    island.clear();
}

void GetInput()
{
    cin>>p1.x>>p1.y>>p2.x>>p2.y>>n;
	for (int i = 0; i < n; i++)
	{
		vector2 point;
		cin>>point.x>>point.y;
		island.push_back(point);
	}
}

polygon cutPoly(const polygon& p, const vector2& a, const vector2& b)
{
	int n = (int)p.size();
	vector<bool> inside(n);
	for (int i = 0; i < n; i++)
		inside[i] = ccw(a, b, p[i]) >= 0;
	polygon ret;
	
	for (int i = 0; i < n; i++)
	{
		int j = (i + 1)%n;
		if (inside[i]) ret.push_back(p[i]);
		if (inside[i] != inside[j]) {
			vector2 cross;
			assert(lineIntersection(p[i], p[j], a, b, cross));
			ret.push_back(cross);
		}
	}

	return ret;
}

polygon intersection(const polygon& p, vector2 point1, vector2 point2)
{
	vector2 a(point1.x, point1.y), b(point2.x, point1.y), c(point2.x, point2.y), d(point1.x, point2.y);
	polygon ret = cutPoly(p, a, b);
	ret = cutPoly(ret, b, c);
	ret = cutPoly(ret, c, d);
	ret = cutPoly(ret, d, a);
	return ret;
}

double area(const polygon& p)
{
	double ret = 0;
	for (int i = 0; i < p.size(); i++)
	{
		int j = (i + 1) % p.size();
		ret += p[i].x * p[j].y - p[j].x * p[i].y;
	}

	return fabs(ret) / 2.0;
}

void Solve()
{
    Reset();
    GetInput();
    
	polygon areaPolygon = intersection(island, p1, p2);

	cout<<area(areaPolygon)<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;

	cout<<fixed;
	cout.precision(10);
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
