#pragma once
#ifndef BFS_H
#define BFS_H

#include "AdjacencyList.h"
#include "Queue.h"
#include <vector>

class BFS
{
private:
    const AdjacencyList& graph; // 그래프 참조
    std::vector<int> color;     // white = 0, gray = 1, black = 2
    std::vector<int> dist;      // 시작점에서의 거리
    std::vector<int> parent;    // 경로 복원
    int source;                 // 시작 지점
    void printPath(int v) const;    // 재귀 경로 출력

public:
    explicit BFS(const AdjacencyList& g);
    void execute(int s);           // 시작점 s에서 BFS 수행 후 결과 출력
};
#endif