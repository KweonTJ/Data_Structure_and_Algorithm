#pragma once
#ifndef QUEUE_H
#define QUEUE_H

class Queue 
{
private:
    int* data;
    int front;
    int rear;
    int capacity;
    void resize();
public:
    explicit Queue(int initialSize = 16);
    ~Queue();
    bool isEmpty() const;
    void enqueue(int v);
    int  dequeue();
};

#endif