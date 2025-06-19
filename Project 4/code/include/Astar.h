#pragma once
#pragma once
#include <vector>
class Graph;

struct ASRes { std::vector<double> g; std::vector<int> p; };
ASRes astar(const Graph& G, int s, int goal);
