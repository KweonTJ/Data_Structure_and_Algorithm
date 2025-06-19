#include "../include/Graph.h"
#include "../include/RRT.h"
#include "../include/PathUtils.h"
#include <algorithm>
#include <cmath>

GridPath backtrack(const std::vector<int>& p, int s, int g, const Graph& G)
{
    GridPath P;
    for (int v = g; v != -1; v = p[v]) 
    {
        int y, x; G.coord(v, y, x);
        P.push_back({ y, x });
        if (v == s) break;
    }
    std::reverse(P.begin(), P.end());
    return P;
}

ContPath backtrack(const std::vector<RNode>& N, int idx)
{
    ContPath P;
    for (int v = idx; v != -1; v = N[v].parent)
        P.push_back({ N[v].y, N[v].x });
    std::reverse(P.begin(), P.end());
    return P;
}

// prev 배열이나 RRT Node list로부터 경로 (node ID & 좌표 리스트) 복원

double length(const GridPath& P)
{
    double sum = 0;
    for (size_t i = 1; i < P.size(); ++i) 
    {
        int dy = std::abs(P[i].first - P[i - 1].first);
        int dx = std::abs(P[i].second - P[i - 1].second);
        sum += (dy + dx == 1) ? 1 : 2;
    }
    return sum;
}

double length(const ContPath& P)
{
    double sum = 0;
    for (size_t i = 1; i < P.size(); ++i)
        sum += std::hypot(P[i].first - P[i - 1].first,
            P[i].second - P[i - 1].second);
    return sum;
}
// 경로의 총 길이 계산