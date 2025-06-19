#pragma once
#include <vector>
class Graph;

struct SPRes { std::vector<double> d; std::vector<int> p; };
SPRes dijkstra(const Graph& G, int s);
#pragma once
