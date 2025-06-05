#include <iostream>
#include <string>
#include <iomanip>
#include "stack.h"

using namespace std;

int main() 
{
    string expr;
    cout << "수식 입력 : ";
    getline(cin, expr);

    string postfix = infixToPostfix(expr);
    cout << "[후위표기식] " << postfix << endl;
    
    double result;
    if (evaluatePostfix(postfix, result)) {
        cout << fixed << setprecision(4);
        cout << "[계산 결과] " << result << endl;
    }
    else {
        cout << "[실패] 수식 계산 중 오류가 발생했습니다.\n";
    }

    return 0;
}
