#pragma once
#include <vector>
#include <utility>
#include "RRT.h"
class Graph; struct RNode;

using GridPath = std::vector<std::pair<int, int>>;       // (y,x)
using ContPath = std::vector<std::pair<double, double>>; // (y,x)

GridPath backtrack(const std::vector<int>& p, int s, int g, const Graph& G);
ContPath backtrack(const std::vector<RNode>& N, int idx);

double length(const GridPath& P);     // ��� ���� ���
double length(const ContPath& P);     // ��� ���� ���
