#pragma once
#include <vector>
class MapParser;

struct Edge { int to; double w; };      // 목적지 ID, 가중치

class Graph 
{
public:
    explicit Graph(const MapParser& mp);

    int V() const { return 400; }                  // 20*20 격자
    const std::vector<std::vector<Edge>>& adj() const { return _adj; }

    int  id(int y, int x) const { return (y - 1) * 20 + (x - 1); }
    void coord(int id, int& y, int& x) const { y = id / 20 + 1; x = id % 20 + 1; }

private:
    const MapParser& _mp;
    std::vector<std::vector<Edge>> _adj;        // 인접 리스트

    bool   obs(int y, int x) const;
    double cost(int y1, int x1, int y2, int x2) const;   // 이동 비용
};      // Grid 기반 그래플를 내부적 표현, Node ID, 좌표를 상호 변화
#pragma once
