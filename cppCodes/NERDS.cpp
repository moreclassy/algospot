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

int n;
vector<vector2> nerd, notNerd;

void reset()
{
	nerd.clear();
	notNerd.clear();
}

void GetInput()
{
	cin>>n;
	int isNerd;
	vector2 p;
	for (int i = 0; i < n; i++)
	{
		cin>>isNerd>>p.x>>p.y;
		if (isNerd)
			nerd.push_back(p);
		else
			notNerd.push_back(p);
	}
}

polygon giftWrap(const vector<vector2>& points)
{
	int n = points.size();
	polygon hull;

	vector2 pivot = *min_element(points.begin(), points.end());
	hull.push_back(pivot);

	while (true)
	{
		vector2 ph = hull.back(), next = points[0];
		for (int i = 1; i < n; i++)
		{
			double cross = ccw(ph, next, points[i]);
			double dist = (next - ph).norm() - (points[i] - ph).norm();
			if (cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}
		if (next == pivot) break;
		hull.push_back(next);
	}
	return hull;
}

bool polygonIntersects(const polygon& p, const polygon& q)
{
	int n = p.size(), m = q.size();

	if (isInside(p[0], q) || isInside(q[0], p)) return true;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (segmentIntersects(p[i], p[(i+1)%n], q[j], q[(j+1)%m]))
				return true;

	return false;
}

void Solve()
{
	reset();
    GetInput();
    
	if (segmentIntersects(giftWrap(nerd), giftWrap(notNerd)))
		cout<<"THEORY IS INVALID";
	else
		cout<<"THEORY HOLDS";
	cout<<endl;
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;

	cout<<fixed;
	cout.precision(8);
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
