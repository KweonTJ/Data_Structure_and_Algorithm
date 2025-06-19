#pragma once
#include <fstream>
#include "PathUtils.h"

// GridPath  : std::vector<std::pair<int,int>>
// part_*.txt 파일로 좌표리스 저장
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

// 연속 좌표 리스트 (x, y) 저장 (RRT* 출력용)
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
