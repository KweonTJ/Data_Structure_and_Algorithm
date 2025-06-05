#pragma once
#include <string>
using namespace std;

class LCS
{
protected:
	int** cost;			// 2차원 배열 c[i][j] 동적 할당
	int** pointer;		// 2차원 b[i][j] 동적 할당
	int row;			// 2차원 배열 c[i][j], b[i],[j]의 행의 수
	int column;			// 2차원 배열 c[i][j], b[i],[j]의 열의 수

public:
	LCS();		// 생성자, 초기화
	~LCS();		// 소멸자, 메모리 해제
	bool isValidDNA(const string& s);		// A,C,G,T 외 검사, 입력 유효성 검사
	int	LCS_Length(const string& X, const string& Y);		// 방향 저장, LCS 길이 및 테이블 생성
	string	Print_LCS(const string& X, const string& Y);		// 내부 재귀함수 호출, LCS 문자열 출력
};

