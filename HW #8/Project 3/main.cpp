#include "LCS.h"
#include <iostream>

int main() 
{
    string str1, str2; // DNS ���ڿ� ���� ���� ����
    std::cout << "ù ��° DNA ���ڿ� �Է� (A,C,G,T): ";
    cin >> str1;
    std::cout << "�� ��° DNA ���ڿ� �Է� (A,C,G,T): ";
    cin >> str2;
    // ��ȿ ���� ���ڿ� �Է�

    LCS lcs;

    if (!lcs.isValidDNA(str1) || !lcs.isValidDNA(str2)) 
    {
        std::cout << "[����] DNA ���ڴ� A, C, G, T �� ����� �� �ֽ��ϴ�." << endl;
        return 1;
    }
    // isValidDNA �Լ��� DNA ��Ģ �˻�, �������� �ŷڼ� Ȯ��

    int length = lcs.LCS_Length(str1, str2);
    string lcs_result = lcs.Print_LCS(str1, str2);

    std::cout << "LCS ����: " << length << endl;
    std::cout << "LCS ���ڿ�: " << lcs_result << endl;

    return 0;
}
