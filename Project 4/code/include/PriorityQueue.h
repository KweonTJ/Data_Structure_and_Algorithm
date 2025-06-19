#pragma once
#include <vector>

struct PQNode { int id; double key; };

class PriorityQueue 
{
public:
    explicit PriorityQueue(int n);
    bool empty()    const { return _heap.empty(); }
    bool contains(int v) const { return _pos[v] != -1; }
    double key(int v) const;

    void push(int v, double k);
    void decrease(int v, double k);
    int  pop();                                     

private:
    std::vector<PQNode> _heap;
    std::vector<int>    _pos;

    void swapn(int a, int b);
    void up(int i);
    void down(int i);
};
#pragma once
