#include <fstream>
#include <iostream>
#include "AdjacencyList.h"
#include "BFS.h"

using namespace std;

int main() 
{
    std::string filename;
    std::cout << "그래프 파일 이름 입력 ( ex) graph1.txt ): ";
    std::cin >> filename;
    std::ifstream fin(filename);
    if (!fin) 
    {
        std::cerr << "[오류] 파일을 열 수 없습니다: " << filename << "\n";
        return 1;
    }

    int V;
    if (!(fin >> V)) 
    {
        cerr << "Error: vertex count missing or invalid in file header\n";
        return 1;
    }
    if (V <= 0) 
    {
        cerr << "Error: vertex count must be positive, got " << V << "\n";
        return 1;
    };

    AdjacencyList G(V);
    
    // adj matrix → list 변환
    for (int i = 1; i <= V; ++i) 
    {
        for (int j = 1, x; j <= V; ++j) 
        {
            if (!(fin >> x)) 
            {
                std::cout << "Error: expected " << V * V << " adjacency values, but file ended early\n";
                return 1;
                
            }
                       // 값 검증: 0 또는 1 이 아니면 에러
                if (x != 0 && x != 1) 
                {
                std::cout << "Error: invalid adjacency value " << x
                     << " at (" << i << "," << j << "). Only 0 or 1 allowed.\n";
                return 1;
                
            }
                       // 1인 경우에만 간선 추가
                if (x == 1)
                    G.addEdge(i, j);
        }
    }

    // BFS 수행
    BFS bfs(G);
    bfs.execute(1);

    return 0;
}
