#include "LCS.h"
#include <iostream>

int main() 
{
    string str1, str2; // DNS 문자열 저장 변수 선언
    std::cout << "첫 번째 DNA 문자열 입력 (A,C,G,T): ";
    cin >> str1;
    std::cout << "두 번째 DNA 문자열 입력 (A,C,G,T): ";
    cin >> str2;
    // 유효 문자 문자열 입력

    LCS lcs;

    if (!lcs.isValidDNA(str1) || !lcs.isValidDNA(str2)) 
    {
        std::cout << "[오류] DNA 문자는 A, C, G, T 만 사용할 수 있습니다." << endl;
        return 1;
    }
    // isValidDNA 함수로 DNA 규칙 검사, 안전성과 신뢰성 확보

    int length = lcs.LCS_Length(str1, str2);
    string lcs_result = lcs.Print_LCS(str1, str2);

    std::cout << "LCS 길이: " << length << endl;
    std::cout << "LCS 문자열: " << lcs_result << endl;

    return 0;
}
