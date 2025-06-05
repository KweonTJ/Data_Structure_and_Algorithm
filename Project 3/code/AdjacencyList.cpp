#include "AdjacencyList.h"

AdjacencyList::AdjacencyList(int vertexCount)
    : V(0)
{
    setVertexCount(vertexCount);
}

void AdjacencyList::setVertexCount(int vertexCount)
{
    V = vertexCount;
    list.clear();
    list.resize(V + 1);      // 1-based indexing (vertices labeled 1..V)
}

void AdjacencyList::addEdge(int u, int v)
{
    if (u < 1 || v < 1 || u > V || v > V) return; // simple guard
    list[u].push_back(v);
}

const std::vector<int>& AdjacencyList::neighbors(int u) const
{
    return list[u];
}