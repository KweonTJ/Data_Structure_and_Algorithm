#pragma once
#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <vector>

class AdjacencyList 
{
private:
    int V;                                   // number of vertices
    std::vector< std::vector<int> > list;    // list[u] = { v1, v2, ... }

public:
    explicit AdjacencyList(int vertexCount = 0);
    void setVertexCount(int vertexCount);
    void addEdge(int u, int v);
    const std::vector<int>& neighbors(int u) const;
    int vertexCount() const { return V; }
};

#endif