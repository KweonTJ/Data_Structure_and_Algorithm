#ifndef __POLYLIST_H__
#define __POLYLIST_H__

#include <iostream>
using namespace std;

struct NODE
{
	int coef;
	int expo;
	NODE* link;
};

class CPolyList
{
protected:
	NODE* head;
	NODE* last;
public:
	CPolyList(); // head, last �ʱ�ȭ (NULL)
	~CPolyList(); // new�� ������ ��� NODE delete
	void Clear(); // ��� ���׽� R �ʱ�ȭ
	void AppendTerm(int coef, int expo); // �� �߰�
	void Print(); // ���׽� ���
	void Simplify(); // �����Լ�
	void AddPoly(CPolyList& Q, CPolyList& R); // ���׽� Q�� ���� ���׽� R ����
	void MultiPoly(CPolyList& Q, CPolyList& R); // ���׽� Q�� ���� ���׽� R ����
};

#endif
