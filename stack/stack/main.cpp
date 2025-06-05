#include <iostream>
#include <string>
#include <iomanip>
#include "stack.h"

using namespace std;

int main() 
{
    string expr;
    cout << "���� �Է� : ";
    getline(cin, expr);

    string postfix = infixToPostfix(expr);
    cout << "[����ǥ���] " << postfix << endl;
    
    double result;
    if (evaluatePostfix(postfix, result)) {
        cout << fixed << setprecision(4);
        cout << "[��� ���] " << result << endl;
    }
    else {
        cout << "[����] ���� ��� �� ������ �߻��߽��ϴ�.\n";
    }

    return 0;
}
