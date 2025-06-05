#pragma once
#include <string>
using namespace std;

class LCS
{
protected:
	int** cost;			// 2���� �迭 c[i][j] ���� �Ҵ�
	int** pointer;		// 2���� b[i][j] ���� �Ҵ�
	int row;			// 2���� �迭 c[i][j], b[i],[j]�� ���� ��
	int column;			// 2���� �迭 c[i][j], b[i],[j]�� ���� ��

public:
	LCS();		// ������, �ʱ�ȭ
	~LCS();		// �Ҹ���, �޸� ����
	bool isValidDNA(const string& s);		// A,C,G,T �� �˻�, �Է� ��ȿ�� �˻�
	int	LCS_Length(const string& X, const string& Y);		// ���� ����, LCS ���� �� ���̺� ����
	string	Print_LCS(const string& X, const string& Y);		// ���� ����Լ� ȣ��, LCS ���ڿ� ���
};

