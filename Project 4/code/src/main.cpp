#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib> // systme() python 연결
#include <filesystem>
#include "../include/Graph.h"
#include "../include/MapParser.h"
#include "../include/RRT.h"
#include "../include/Astar.h"
#include "../include/Dijkstra.h"
#include "../include/PathUtils.h"
#include "../include/FileIO.h"

int main()
{
    std::cout << " 사용할 맵 파일 이름을 입력하세요 (예: map.txt): ";
    std::string mapFile;
    std::getline(std::cin, mapFile);
    if (mapFile.empty()) {
        std::cerr << " 오류: 맵 파일이 입력되지 않았습니다.\n";
        return 1;
    }

    try 
    {
        MapParser mp(mapFile);
        Graph     G(mp);

        int S = G.id(1, 1);
        int Goal = G.id(20, 20);

        /*---------------- Dijkstra ----------------*/
        auto t0 = std::chrono::high_resolution_clock::now();
        auto dRes = dijkstra(G, S);
        auto t1 = std::chrono::high_resolution_clock::now();
        GridPath Pd = backtrack(dRes.p, S, Goal, G);
        double tDij = std::chrono::duration<double>(t1 - t0).count();
        saveGridPath("path_D.txt", Pd);

        /*---------------- A* ----------------------*/
        t0 = std::chrono::high_resolution_clock::now();
        auto aRes = astar(G, S, Goal);
        t1 = std::chrono::high_resolution_clock::now();
        GridPath Pa = backtrack(aRes.p, S, Goal, G);
        double tA = std::chrono::duration<double>(t1 - t0).count();
        saveGridPath("path_A.txt", Pa);

        /*---------------- RRT* --------------------*/
        RRT rrt(mp, 1.0, 5000);            // 
        t0 = std::chrono::high_resolution_clock::now();
        auto rRes = rrt.run();
        t1 = std::chrono::high_resolution_clock::now();
        double tR = std::chrono::duration<double>(t1 - t0).count();

        if (rRes.ok) 
        {
            ContPath Pr = backtrack(rRes.nodes, rRes.goalIdx);
            saveContPath("path_R.txt", Pr);
            std::cout << "[RRT*]   length = " << length(Pr)
                << ", time = " << tR << " s\n";
        }
        else 
        {
            std::cout << "[RRT*]   FAIL (no path)\n";
        }

        std::cout << "[A*]     length = " << length(Pa)
            << ", time = " << tA << " s\n"
            << "[Dijkstra] length = " << length(Pd)
            << ", time = " << tDij << " s\n";

        // python 코드로 연결, path_*.txt 시각화
        {
            std::string cmd =
                "python \"visualize.py\" "
                "\"map.txt\" "
                "\"path_A.txt\" "
                "\"path_D.txt\" "
                "\"path_R.txt\"";
            int ret = std::system(cmd.c_str());
        }
    }
    catch (const std::exception& ex) 
    {
        std::cerr << "Error: " << ex.what() << '\n';
    }
    return 0;
}
