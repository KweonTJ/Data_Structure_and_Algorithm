#include <fstream>
#include <iostream>
#include "AdjacencyList.h"
#include "BFS.h"

using namespace std;

int main() 
{
    std::string filename;
    std::cout << "�׷��� ���� �̸� �Է� ( ex) graph1.txt ): ";
    std::cin >> filename;
    std::ifstream fin(filename);
    if (!fin) 
    {
        std::cerr << "[����] ������ �� �� �����ϴ�: " << filename << "\n";
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
    
    // adj matrix �� list ��ȯ
    for (int i = 1; i <= V; ++i) 
    {
        for (int j = 1, x; j <= V; ++j) 
        {
            if (!(fin >> x)) 
            {
                std::cout << "Error: expected " << V * V << " adjacency values, but file ended early\n";
                return 1;
                
            }
                       // �� ����: 0 �Ǵ� 1 �� �ƴϸ� ����
                if (x != 0 && x != 1) 
                {
                std::cout << "Error: invalid adjacency value " << x
                     << " at (" << i << "," << j << "). Only 0 or 1 allowed.\n";
                return 1;
                
            }
                       // 1�� ��쿡�� ���� �߰�
                if (x == 1)
                    G.addEdge(i, j);
        }
    }

    // BFS ����
    BFS bfs(G);
    bfs.execute(1);

    return 0;
}
