#pragma once
#include <vector>
#include <string>

struct Rect { int l, t, r, b; };        // left, top, right, bottom (1-index)

class MapParser         // map.txt 파일 파싱, 장애물 목록과 맵 크기 읽기
{
public:
    explicit MapParser(const std::string& file);  
    bool isObs(int y, int x) const;   // (y,x)가 장애물 & 범위 밖이면 true   
    const std::vector<Rect>& rects() const { return _obs; }

private:
    std::vector<Rect> _obs;     // 장애물 사각형 목록
    bool _grid[21][21]{};       // 장애물 표시용 격자
};
#pragma once
