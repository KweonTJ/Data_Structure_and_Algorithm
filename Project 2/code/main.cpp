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

// ���ڿ��� �Ľ��Ͽ� ���׽��� CPolyList�� ��ȯ
bool ParsePolynomial(const string& raw_input, CPolyList& poly) 
{   
    // 1. ���� ����
    string input = RemoveSpace(raw_input);

    // 2. ��� �׸� ��Ī
    regex term_regex(R"(([+-]?\d*)x(?:\^(\d+))?|([+-]?\d+))"); 
    auto terms_begin = sregex_iterator(input.begin(), input.end(), term_regex);
    auto terms_end = sregex_iterator();

    if (terms_begin == terms_end) return false;

    // 3. ���Խ� ��Ī�� �� ����, ��ü �Է°� ��ġ�ϴ��� �˻�
    string matched_combined;
    for (auto it = terms_begin; it != terms_end; ++it) {
        matched_combined += it->str();
    }

    if (matched_combined != input) {
        std::cout << "[����] �Է� ������ �߸��� ���� ���ԵǾ� �ֽ��ϴ�.\n";
        return false;
    }

    // 4. �� �� �Ľ�
    for (auto i = terms_begin; i != terms_end; ++i) 
    {
        smatch match = *i;
        int coef = 0, expo = 0;

        // �Ϲ� �� (���X^����)
        if (match[1].matched) 
        {
            string coef_str = match[1].str();
            if (coef_str == "" || coef_str == "+") coef = 1;
            else if (coef_str == "-") coef = -1;
            else coef = stoi(coef_str);

            // ������ ó�� (x^1 -> x) 
            expo = match[2].matched ? stoi(match[2].str()) : 1;
        }

        // ����� (������ ���� ��)
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
    // �� ���̿� ������ ���� ���� ������ �ִ��� �˻�
    regex bad_space(R"(\dx\s+\d|x\^\d\s+\d|x\s+\d|x\s+x|\^\d\s+\d)");
    return regex_search(input, bad_space);
}

int main() 
{
    string input1, input2;
    std::cout << "���׽� 1 �Է� : ";
    getline(cin, input1);
    std::cout << "���׽� 2 �Է� : ";
    getline(cin, input2);

    CPolyList p1, p2, p3, p4;

    // ���� �˻� (�� ������ ���� Ž��, �����ȣ ����)
    if (HasInvalidSpaces(input1))
    {
        std::cout << "[����] ���׽� 1�� ������ ���ԵǾ� �־� ��Ȯ�� �Ľ��� ��ƽ��ϴ�.\n";
        return 1;
    }
    if (HasInvalidSpaces(input2))
    {
        std::cout << "[����] ���׽� 2�� ������ ���ԵǾ� �־� ��Ȯ�� �Ľ��� ��ƽ��ϴ�.\n";
        return 1;
    }

    // �Ľ� �õ�
    if (!ParsePolynomial(input1, p1))
    {
        std::cout << "[����] ���׽� 1�� �Է� ������ �߸��Ǿ����ϴ�." << endl;
        return 1;
    }
    if (!ParsePolynomial(input2, p2))
    {
        std::cout << "[����] ���׽� 2�� �Է� ������ �߸��Ǿ����ϴ�." << endl;
        return 1;
    }


    // �Է� ���
    std::cout << "\n[�Էµ� ���׽�]" << endl;
    std::cout << "P1: "; p1.Print();
    std::cout << "P2: "; p2.Print();

    // ���� ���
    p1.AddPoly(p2, p3);
    std::cout << "\n[���� ���]" << endl;
    std::cout << "P3: "; p3.Print();

    // ���� ���
    p1.MultiPoly(p2, p4);
    std::cout << "\n[���� ���]" << endl;
    std::cout << "P4: "; p4.Print();

    return 0;
}
