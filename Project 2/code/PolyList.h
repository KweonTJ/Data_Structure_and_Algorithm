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
	CPolyList(); // head, last 초기화 (NULL)
	~CPolyList(); // new로 생성된 모둔 NODE delete
	void Clear(); // 결과 다항식 R 초기화
	void AppendTerm(int coef, int expo); // 항 추가
	void Print(); // 다항식 출력
	void Simplify(); // 정렬함수
	void AddPoly(CPolyList& Q, CPolyList& R); // 다항식 Q를 더해 다항식 R 생성
	void MultiPoly(CPolyList& Q, CPolyList& R); // 다항식 Q를 곱해 다항식 R 생성
};

#endif
