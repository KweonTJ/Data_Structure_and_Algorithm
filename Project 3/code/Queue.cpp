#include "Queue.h"
#include <cstdlib>

Queue::Queue(int initialSize)
    : data(new int[initialSize]),
    front(0), rear(0), capacity(initialSize) 
{}

Queue::~Queue() 
{
    delete[] data; 
}

bool Queue::isEmpty() const 
{ 
    return front == rear; 
}

void Queue::resize() 
{
    int newCap = capacity * 2;
    int* newData = new int[newCap];
    int sz = rear - front;
    for (int i = 0; i < sz; ++i) 
        newData[i] = data[front + i];
    delete[] data;
    data = newData;
    capacity = newCap;
    rear = sz;
    front = 0;
}

void Queue::enqueue(int v) 
{
    if (rear == capacity) resize();
    data[rear++] = v;
}

int Queue::dequeue() 
{
    if (isEmpty()) return -1;
    return data[front++];
}