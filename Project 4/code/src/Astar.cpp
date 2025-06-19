#include "../include/Graph.h"
#include "../include/Astar.h"
#include "../include/PriorityQueue.h"
#include <cmath>

static double h(const Graph& G, int v, int goal)        
// ��Ŭ���� �Ÿ��� �̿��� ��ǥ������ �ִ� ��� Ž��
{
    int y1, x1, y2, x2;
    G.coord(v, y1, x1);
    G.coord(goal, y2, x2);
    return std::hypot(double(y1 - y2), double(x1 - x2));
}

static void relaxA(int u, int v, double w, const Graph& G, int goal,
    std::vector<double>& g, std::vector<int>& p, PriorityQueue& Q)
    // doubel : ���ۺ��� �ش� ������ ���� ���, int : ���� ��� �ε����� (��� ����)
{
    if (g[u] + w < g[v]) 
    {
        g[v] = g[u] + w;
        p[v] = u;
        double f = g[v] + h(G, v, goal);
        Q.contains(v) ? Q.decrease(v, f) : Q.push(v, f);
    }
}

ASRes astar(const Graph& G, int s, int goal)
{
    int n = G.V();
    std::vector<double> g(n, 1e100);
    std::vector<int>    p(n, -1);
    PriorityQueue Q(n);

    g[s] = 0; Q.push(s, h(G, s, goal));

    while (!Q.empty()) {
        int u = Q.pop();
        if (u == goal) break;
        for (auto& e : G.adj()[u])
            relaxA(u, e.to, e.w, G, goal, g, p, Q);
    }
    return { g, p };
}
