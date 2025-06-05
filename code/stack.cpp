#include "stack.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cctype>

using namespace std;

template <class T>
Stack<T>::Stack(int size)  
{
    capacity = size;
    top = -1;
    data = new T[capacity];
}

template <class T>
Stack<T>::~Stack() 
{
    delete[] data;
}

template <class T>
bool Stack<T>::isEmpty() const 
{
    return top == -1;
}

template <class T>
bool Stack<T>::isFull() const 
{
    return top == capacity - 1;
}

template <class T>
void Stack<T>::push(T value) 
{
    if (isFull()) 
    {
        cout << "[Error] Stack Overflow\n";
        exit(1);
    }
    data[++top] = value;
}

template <class T>
T Stack<T>::pop() 
{
    if (isEmpty()) 
    {
        cout << "[Error] Stack Underflow\n";
        exit(1);
    }
    return data[top--];
}

int precedence(char op) 
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOperator(char ch) 
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isUnnecessaryParentheses(const string& inner, char prevOp) 
{
    bool hasMulDiv = false;
    bool hasPlusMinus = false;

    for (char ch : inner) 
    {
        if (isOperator(ch)) 
        {
            if (ch == '+' || ch == '-') hasPlusMinus = true;
            if (ch == '*' || ch == '/') hasMulDiv = true;
        }
    }

    if (!hasPlusMinus && !hasMulDiv) return true;

    if ((prevOp == '*' || prevOp == '/') && hasPlusMinus)
        return false;

    if ((prevOp == '*' || prevOp == '/') && hasMulDiv && !hasPlusMinus)
        return true;
    
    return false;
}

string infixToPostfix(const string& expr) 
{
    Stack<char> opStack(100);
    string postfix, number;
    int paren = 0;

    for (size_t i = 0; i < expr.length(); ++i) 
    {
        char ch = expr[i];

        if (isspace(ch)) continue;

        if (isdigit(ch) || ch == '.') 
        {
            number += ch;
        }
        else 
        {
            if (!number.empty()) 
            {
                postfix += number + " ";
                number.clear();
            }

            if (ch == '(') 
            {
                paren++;
                opStack.push(ch);

                string inner;
                int level = 1;
                size_t j = i + 1;
                while (j < expr.length() && level > 0) 
                {
                    if (expr[j] == '(') level++;
                    else if (expr[j] == ')') level--;
                    if (level > 0) inner += expr[j];
                    j++;
                }
                if (isUnnecessaryParentheses(inner, (i > 0 ? expr[i - 1] : '+')))
                {
                    cout << "[Error] 불필요한 괄호 사용\n" << endl;
                    exit(1);
                }

            }
            else if (ch == ')') 
            {
                paren--;
                while (!opStack.isEmpty()) 
                {
                    char temp = opStack.pop();
                    if (temp == '(') break;
                    postfix += temp;
                    postfix += " ";
                }
            }
            else if (isOperator(ch)) 
            {
                while (!opStack.isEmpty()) 
                {
                    char top = opStack.pop();
                    if (top == '(') 
                    {
                        opStack.push(top);
                        break;
                    }
                    if (precedence(top) >= precedence(ch)) 
                    {
                        postfix += top;
                        postfix += " ";
                    }
                    else 
                    {
                        opStack.push(top);
                        break;
                    }
                }
                opStack.push(ch);
            }
            else 
            {
                cout << "[Error] 유효하지 않은 문자: " << ch << endl;
                exit(1);
            }
        }
    }

    if (!number.empty()) postfix += number + " ";
    if (paren != 0) 
    {
        cout << "[Error] 괄호 개수 오류\n";
        exit(1);
    }

    while (!opStack.isEmpty()) 
    {
        char op = opStack.pop();
        if (op == '(' || op == ')') 
        {
            cout << "[Error] 괄호 짝 오류\n";
            exit(1);
        }
        postfix += op;
        postfix += " ";
    }

    return postfix;
}

bool evaluatePostfix(const string& postfix, double& result)
{
    Stack<double> valStack(100);
    stringstream ss(postfix);
    string token;

    result = 0.0;

    while (ss >> token) 
    {
        if (token.empty()) {
            cout << "[Error] 잘못된 피연산자: (빈 문자열)" << endl;
            return false;
        }

        // 숫자인지 확인 (음수, 실수 모두 포함)
        char* endptr = nullptr;
        double val = strtod(token.c_str(), &endptr);
        if (*endptr == '\0')
        {
            valStack.push(val);
        }
        else if (token.length() == 1 && isOperator(token[0]))
        {
            if (valStack.isEmpty()) {
                cout << "[Error] 피연산자 부족" << endl;
                return false;
            }
            double b = valStack.pop();

            if (valStack.isEmpty()) {
                cout << "[Error] 피연산자 부족" << endl;
                return false;
            }
            double a = valStack.pop();

            if (token[0] == '/' && b == 0.0)
            {
                cout << "[Error] 0으로 나눌 수 없습니다" << endl;
                return false;
            }

            double resultVal = 0;
            switch (token[0])
            {
            case '+': resultVal = a + b; break;
            case '-': resultVal = a - b; break;
            case '*': resultVal = a * b; break;
            case '/': resultVal = a / b; break;
            }
            valStack.push(resultVal);
        }
        else 
        {
            cout << "[Error] 잘못된 연산자: " << token << endl;
            return false;
        }
    }

    result = valStack.pop();
    if (!valStack.isEmpty()) 
    {
        cout << "[Error] 스택에 값이 남아 있음\n";
        return false;
    }

    return true;
}

template class Stack<char>;
template class Stack<double>;