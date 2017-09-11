#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>

#include "VECTOR2.h"


#define _USE_MATH_DEFINES

using namespace std;

const double EPSILON = 1e-9;
const double INFTY = 1e200;

int n, radius[50];
vector2 center[50], startPoint, startDir;

void GetInput()
{
    cin>>startPoint.x>>startPoint.y>>startDir.x>>startDir.y>>n;
    for (int i = 0; i < n; i++) {
        cin>>center[i].x>>center[i].y>>radius[i];
    }
}

vector<double> solve2(double a, double b, double c) {
    double d = b*b - 4*a*c;
    if (d < -EPSILON) return vector<double>();
    if (d < EPSILON) return vector<double>(1, -b / (2*a));
    vector<double> ret;
    ret.push_back((-b - sqrt(d)) / (2*a));
    ret.push_back((-b + sqrt(d)) / (2*a));
    return ret;
}

double hitCircle(vector2 here, vector2 dir, vector2 center, int radius) {
    double a = dir.dot(dir);
    double b = 2 * dir.dot(here - center);
    double c = center.dot(center) + here.dot(here) - 2*here.dot(center) - radius*radius;
    vector<double> sols = solve2(a, b, c);
    if (sols.empty() || sols[0] < EPSILON) return INFTY;
    return sols[0];
}

vector2 reflect(vector2 here, vector2 dir, vector2 center, vector2 contact) {
    return (dir - dir.project(contact - center)*2).normalize();
}

void simulate(vector2 here, vector2 dir) {
    dir = dir.normalize();
    int hitCount = 0;
    
    while (hitCount < 10) {
        int circle = -1;
        double time = INFTY * 0.5;
        
        for (int i = 0; i < n; i++) {
            double cand = hitCircle(here, dir, center[i], radius[i] + 1);
            if (cand < time) {
                time = cand;
                circle = i;
            }
        }
        
        if (circle == -1) break;
        if (hitCount++) cout<<" ";
        cout<<circle;
        vector2 contact = here + dir*time;
        dir = reflect(here, dir, center[circle], contact);
        here = contact;
    }
    cout<<endl;
}

void Solve()
{
    GetInput();
    
    simulate(startPoint, startDir);
}

int main(int argc, const char * argv[]) {
    int caseCnt = 0;
    cin>>caseCnt;
    
    for (int i = 0; i < caseCnt; i++) {
        Solve();
    }
    
    return 0;
}
