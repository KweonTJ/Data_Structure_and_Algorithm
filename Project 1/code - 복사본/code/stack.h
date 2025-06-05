#ifndef STACK_H
#define STACK_H

#include <string>
using namespace std;

template <class T>
class Stack {
private:
    T* data;
    int top;
    int capacity;

public:
    Stack(int size = 100);
    ~Stack();

    bool isEmpty() const;
    bool isFull() const;
    void push(T value);
    T pop();
};

string infixToPostfix(const string& expr);
bool evaluatePostfix(const string& postfix, double& result);

#endif

