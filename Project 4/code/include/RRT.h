#pragma once
#pragma once
#include <vector>
class MapParser;

struct RNode { double x, y; int parent; };
struct RRes { bool ok; std::vector<RNode> nodes; int goalIdx; };

class RRT   // 생성자, 맵 정보, 샘플링 스텝 크기, 최대 반복 횟수 설정
{
public:
    RRT(const MapParser& mp, double step, int maxN);
    RRes run();

private:
    const MapParser& _mp;
    double _step;
    int    _max;
    std::vector<RNode> _nodes;

    double dist(double, double, double, double) const;
    bool   collision(double, double, double, double) const;
    int    nearest(double, double) const;
};
//  RRT* 알고리즘을 이용한 자유공간 경로 계획
