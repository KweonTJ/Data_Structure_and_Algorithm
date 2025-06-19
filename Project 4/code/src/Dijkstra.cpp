#include "../include/Graph.h"
#include "../include/Dijkstra.h"
#include "../include/PriorityQueue.h"

static void relax(int u, int v, double w,
    std::vector<double>& d, std::vector<int>& p, PriorityQueue& Q)     
    // �� ������ �ּ� ��� & ��� �籸���� ���� ��� �ε���
{
    if (d[u] + w < d[v]) 
    {
        d[v] = d[u] + w;
        p[v] = u;
        Q.contains(v) ? Q.decrease(v, d[v]) : Q.push(v, d[v]);
    }
}

SPRes dijkstra(const Graph& G, int s)       // ���� ������ ��� ������ �ִ� ��κ��� prev �迭 ���
{
    int n = G.V();
    std::vector<double> d(n, 1e100);
    std::vector<int>    p(n, -1);
    PriorityQueue Q(n);

    d[s] = 0; Q.push(s, 0);

    while (!Q.empty()) 
    {
        int u = Q.pop();
        for (auto& e : G.adj()[u])
            relax(u, e.to, e.w, d, p, Q);
    }
    return { d, p };
}
