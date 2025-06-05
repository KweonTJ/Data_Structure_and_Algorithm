#include "LCS.h"
#include <iostream>
#include <vector>

using namespace std;

// 생성자
LCS::LCS() : cost(nullptr), pointer(nullptr), row(0), column(0) {}

// 소멸자
LCS::~LCS() 
{
    for (int i = 0; i < row; ++i) 
    {
        delete[] cost[i];
        delete[] pointer[i];
    }
    delete[] cost;
    delete[] pointer;
}

// DNA 유효성 검사
bool LCS::isValidDNA(const string& s) 
{
    for (char c : s) 
    {
        if (c != 'A' && c != 'C' && c != 'G' && c != 'T')
            return false;
    }
    return true;
}

// LCS 테이블 구성 및 길이 계산
int LCS::LCS_Length(const string& X, const string& Y) 
{
    row = X.length() + 1;
    column = Y.length() + 1;

    cost = new int* [row];
    pointer = new int* [row];

    for (int i = 0; i < row; ++i) 
    {
        cost[i] = new int[column] {};
        pointer[i] = new int[column] {};
    }

    for (int i = 1; i < row; ++i) 
    {
        for (int j = 1; j < column; ++j) 
        {
            if (X[i - 1] == Y[j - 1]) {
                cost[i][j] = cost[i - 1][j - 1] + 1;
                pointer[i][j] = 1; // diagonal
            }
            else if (cost[i - 1][j] >= cost[i][j - 1]) 
            {
                cost[i][j] = cost[i - 1][j];
                pointer[i][j] = 2; // up
            }
            else 
            {
                cost[i][j] = cost[i][j - 1];
                pointer[i][j] = 3; // left
            }
        }
    }

    return cost[row - 1][column - 1];
}

// 방향에 따른 문자열 추적
string LCS::Print_LCS(const string& X, const string& Y) 
{
    // 역으로 주적해서 LCS 구성
    string lcs;
    int i = row - 1;
    int j = column - 1;

    while (i > 0 && j > 0) 
    {
        if (pointer[i][j] == 1) 
        {
            lcs = X[i - 1] + lcs;
            i--; j--; 
        }
        else if (pointer[i][j] == 2) 
        {
            i--;
        }
        else 
        {
            j--;
        }
    }
    return lcs;
}
