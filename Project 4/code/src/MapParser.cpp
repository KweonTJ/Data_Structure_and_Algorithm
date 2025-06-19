#include "../include/MapParser.h"
#include <fstream>
#include <stdexcept>

MapParser::MapParser(const std::string& file)
{
    std::ifstream fin(file);
    if (!fin) throw std::runtime_error("map.txt open failed");

    int N; fin >> N;                 // 장애물 개수
    _obs.reserve(N);
    for (int i = 0; i < N; ++i) 
    {
        Rect r; fin >> r.l >> r.t >> r.r >> r.b;
        _obs.push_back(r);
        for (int y = r.t; y <= r.b; ++y)
            for (int x = r.l; x <= r.r; ++x)
                _grid[y][x] = true;     // 장애물 표시
    }
}       // 파일 열기, 첫 줄에서 맵의 행/열 정보 읽기

bool MapParser::isObs(int y, int x) const
{
    if (y < 1 || y > 20 || x < 1 || x > 20) return true;
    return _grid[y][x];
}
