#include "../include/Graph.h"
#include "../include/MapParser.h"
#include <cmath>

bool Graph::obs(int y, int x) const { return _mp.isObs(y, x); }
// 상하좌우는 1, 대각선 이동은 root2 이동
double Graph::cost(int y1, int x1, int y2, int x2) const
{
    int dy = std::abs(y1 - y2);     // 단일 노드 ID 변환
    int dx = std::abs(x1 - x2); 
    if (dy + dx ==1) 
    {
        return 1.0;     // 상하좌우
    } 
    else if (dy == 1 && dx == 1) 
    {
        return std::sqrt(2.0);      //  = 1.4142, 대각선
    }
    else 
    {
        return std::hypot(double(dy), double(dx)); // 일반화

    }
}

Graph::Graph(const MapParser& mp) : _mp(mp), _adj(400)
{
    static const int dy[8] = { -1, 1,  0, 0, -1, -1, 1, 1 };
    static const int dx[8] = { 0, 0, -1, 1, -1,  1,-1, 1 };

    // 모든 격자 셀 순환
    for (int y = 1; y <= 20; ++y)
        for (int x = 1; x <= 20; ++x) 
        {
            if (obs(y, x)) continue;        // 장애물 셀 건너뛰기
            int u = id(y, x);
            for (int k = 0; k < 8; ++k) 
            {
                int ny = y + dy[k], nx = x + dx[k];
                if (ny < 1 || ny > 20 || nx < 1 || nx > 20 || obs(ny, nx)) continue;
                _adj[u].push_back({ id(ny, nx), cost(y, x, ny, nx) });
            }
        }
}       // 생성자, 맵 크기 기반으로 node 수 결정
        // 장애물 블록을 노드로부터 제거
        // 참색을 위한 adj 생성
