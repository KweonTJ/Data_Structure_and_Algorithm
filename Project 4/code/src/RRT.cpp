#include "../include/RRT.h"
#include "../include/MapParser.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

static double urand(double a, double b)
{
    return a + (b - a) * (double(rand()) / RAND_MAX);
}

RRT::RRT(const MapParser& mp, double step, int maxN)
    : _mp(mp), _step(step), _max(maxN)
{
    srand((unsigned)time(nullptr));
    _nodes.push_back({ 1.0, 1.0, -1 });            // 
}

double RRT::dist(double x1, double y1, double x2, double y2) const
{
    return std::hypot(x1 - x2, y1 - y2);
}

bool RRT::collision(double x1, double y1, double x2, double y2) const
{
    const int K = 10;
    for (int i = 0; i <= K; ++i) 
    {
        double t = double(i) / K;
        double x = x1 + t * (x2 - x1);
        double y = y1 + t * (y2 - y1);
        int gx = int(std::round(x)), gy = int(std::round(y));
        if (_mp.isObs(gy, gx)) return true;
    }
    return false;
}

int RRT::nearest(double x, double y) const
{
    int idx = 0; double best = 1e9;
    for (int i = 0; i < (int)_nodes.size(); ++i) 
    {
        double d = dist(x, y, _nodes[i].x, _nodes[i].y);
        if (d < best) { best = d; idx = i; }
    }
    return idx;
}

RRes RRT::run()         // RRT* 알고리즘 실행
{
    const double gx = 20.0, gy = 20.0;

    for (int it = 0; it < _max; ++it) 
    {
        double xs = urand(1.0, 20.0);
        double ys = urand(1.0, 20.0);

        int near = nearest(xs, ys);
        double th = std::atan2(ys - _nodes[near].y, xs - _nodes[near].x);
        double nx = _nodes[near].x + _step * std::cos(th);
        double ny = _nodes[near].y + _step * std::sin(th);

        if (nx < 1 || nx > 20 || ny < 1 || ny > 20) continue;
        if (collision(_nodes[near].x, _nodes[near].y, nx, ny)) continue;

        _nodes.push_back({ nx, ny, near });

        if (dist(nx, ny, gx, gy) <= _step &&
            !collision(nx, ny, gx, gy)) 
            {
            _nodes.push_back({ gx, gy, (int)_nodes.size() - 1 });
            return { true, _nodes, (int)_nodes.size() - 1 };
        }
    }
    return { false, _nodes, -1 };
}
