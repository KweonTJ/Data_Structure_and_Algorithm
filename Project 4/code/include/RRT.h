#pragma once
#pragma once
#include <vector>
class MapParser;

struct RNode { double x, y; int parent; };
struct RRes { bool ok; std::vector<RNode> nodes; int goalIdx; };

class RRT   // ������, �� ����, ���ø� ���� ũ��, �ִ� �ݺ� Ƚ�� ����
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
//  RRT* �˰����� �̿��� �������� ��� ��ȹ
