#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include "PolyList.h"

using namespace std;

string RemoveSpace(const string& input)
{
    string output;
    for (char c : input)
    {
        if (c != ' ') output += c;
    }
    return output;
}

// 문자열을 파싱하여 다항식을 CPolyList로 변환
bool ParsePolynomial(const string& raw_input, CPolyList& poly) 
{   
    // 1. 공백 제거
    string input = RemoveSpace(raw_input);

    // 2. 허용 항목만 매칭
    regex term_regex(R"(([+-]?\d*)x(?:\^(\d+))?|([+-]?\d+))"); 
    auto terms_begin = sregex_iterator(input.begin(), input.end(), term_regex);
    auto terms_end = sregex_iterator();

    if (terms_begin == terms_end) return false;

    // 3. 정규식 매칭된 항 연결, 전체 입력과 일치하는지 검사
    string matched_combined;
    for (auto it = terms_begin; it != terms_end; ++it) {
        matched_combined += it->str();
    }

    if (matched_combined != input) {
        std::cout << "[오류] 입력 형식이 잘못된 항이 포함되어 있습니다.\n";
        return false;
    }

    // 4. 각 항 파싱
    for (auto i = terms_begin; i != terms_end; ++i) 
    {
        smatch match = *i;
        int coef = 0, expo = 0;

        // 일반 항 (계수X^차수)
        if (match[1].matched) 
        {
            string coef_str = match[1].str();
            if (coef_str == "" || coef_str == "+") coef = 1;
            else if (coef_str == "-") coef = -1;
            else coef = stoi(coef_str);

            // 일차항 처리 (x^1 -> x) 
            expo = match[2].matched ? stoi(match[2].str()) : 1;
        }

        // 상수항 (지수가 없는 항)
        else if (match[3].matched)
        {
            coef = stoi(match[3].str());
            expo = 0;
        }
        poly.AppendTerm(coef, expo);
    }
    return true;
}

bool HasInvalidSpaces(const string& input) 
{
    // 항 사이에 연산자 없이 붙은 공백이 있는지 검사
    regex bad_space(R"(\dx\s+\d|x\^\d\s+\d|x\s+\d|x\s+x|\^\d\s+\d)");
    return regex_search(input, bad_space);
}

int main() 
{
    string input1, input2;
    std::cout << "다항식 1 입력 : ";
    getline(cin, input1);
    std::cout << "다항식 2 입력 : ";
    getline(cin, input2);

    CPolyList p1, p2, p3, p4;

    // 공백 검사 (항 사이의 공백 탐지, 연산기호 유무)
    if (HasInvalidSpaces(input1))
    {
        std::cout << "[오류] 다항식 1에 공백이 포함되어 있어 정확한 파싱이 어렵습니다.\n";
        return 1;
    }
    if (HasInvalidSpaces(input2))
    {
        std::cout << "[오류] 다항식 2에 공백이 포함되어 있어 정확한 파싱이 어렵습니다.\n";
        return 1;
    }

    // 파싱 시도
    if (!ParsePolynomial(input1, p1))
    {
        std::cout << "[오류] 다항식 1의 입력 형식이 잘못되었습니다." << endl;
        return 1;
    }
    if (!ParsePolynomial(input2, p2))
    {
        std::cout << "[오류] 다항식 2의 입력 형식이 잘못되었습니다." << endl;
        return 1;
    }


    // 입력 출력
    std::cout << "\n[입력된 다항식]" << endl;
    std::cout << "P1: "; p1.Print();
    std::cout << "P2: "; p2.Print();

    // 덧셈 결과
    p1.AddPoly(p2, p3);
    std::cout << "\n[덧셈 결과]" << endl;
    std::cout << "P3: "; p3.Print();

    // 곱셈 결과
    p1.MultiPoly(p2, p4);
    std::cout << "\n[곱셈 결과]" << endl;
    std::cout << "P4: "; p4.Print();

    return 0;
}
