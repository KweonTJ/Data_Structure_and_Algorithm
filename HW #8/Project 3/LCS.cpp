#include "LCS.h"
#include <iostream>
#include <vector>

using namespace std;

// ������
LCS::LCS() : cost(nullptr), pointer(nullptr), row(0), column(0) {}

// �Ҹ���
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

// DNA ��ȿ�� �˻�
bool LCS::isValidDNA(const string& s) 
{
    for (char c : s) 
    {
        if (c != 'A' && c != 'C' && c != 'G' && c != 'T')
            return false;
    }
    return true;
}

// LCS ���̺� ���� �� ���� ���
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

// ���⿡ ���� ���ڿ� ����
string LCS::Print_LCS(const string& X, const string& Y) 
{
    // ������ �����ؼ� LCS ����
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
