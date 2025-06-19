#pragma once
#include <fstream>
#include "PathUtils.h"

// GridPath  : std::vector<std::pair<int,int>>
// part_*.txt ���Ϸ� ��ǥ���� ����
inline void saveGridPath(const std::string& fn, const GridPath& P)
{
    std::ofstream f(fn);
    for (const auto& cell : P)               // cell.first = y, cell.second = x
    {
        int y = cell.first;
        int x = cell.second;
        f << y << ' ' << x << '\n';
    }
}

// ���� ��ǥ ����Ʈ (x, y) ���� (RRT* ��¿�)
inline void saveContPath(const std::string& fn, const ContPath& P)
{
    std::ofstream f(fn);
    for (const auto& pt : P)                 // pt.first = y, pt.second = x
    {
        double y = pt.first;
        double x = pt.second;
        f << y << ' ' << x << '\n';
    }
}
