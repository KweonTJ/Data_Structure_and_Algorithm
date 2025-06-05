#include "BFS.h"
#include <iostream>
#include <climits>

BFS::BFS(const AdjacencyList& g)
    : graph(g), source(0)
{
    int n = graph.vertexCount();
    color.assign(n + 1, 0);
    dist.assign(n + 1, INT_MAX);
    parent.assign(n + 1, 0);
}

// s를 시작점으로 BFS 실행
void BFS::execute(int s) 
{
    source = s;
    int n = graph.vertexCount();

    // 초기화
    for (int u = 1; u <= n; ++u) 
    {
        color[u] = 0;           // WHITE
        dist[u] = INT_MAX;
        parent[u] = 0;           // NIL
    }
    color[s] = 1;               // GRAY
    dist[s] = 0;
    parent[s] = 0;

    Queue Q(n);
    Q.enqueue(s);

    while (!Q.isEmpty()) 
    {
        int u = Q.dequeue();
        for (int v : graph.neighbors(u)) 
        {
            if (color[v] == 0)    // WHIET
            {
                color[v] = 1;     // GRAY
                dist[v] = dist[u] + 1;
                parent[v] = u;
                Q.enqueue(v);
            }
        }
        color[u] = 2;             // BLACK
    }

    // 결과 출력
    std::cout << "\n[BFS 결과]\n";
    for (int v = 1; v <= n; ++v) 
    {
        printPath(v);
        std::cout << " : ";
        if (dist[v] == INT_MAX) std::cout << "∞\n";
        else                    
            std::cout << dist[v] << "\n";
        std::cout;
    }
}

// 경로 재귀 출력 (PRINT-PATH 의사코드 대응)
void BFS::printPath(int v) const 
{
    if (v == source) 
    {
        std::cout << source;
    }
    else if (parent[v] == 0) 
    {
        std::cout << "no path from " << source << " to " << v << " exists";
    }
    else 
    {
        printPath(parent[v]);
        std::cout << " -> " << v;
    }
}