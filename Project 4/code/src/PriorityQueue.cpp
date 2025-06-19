#include "../include/PriorityQueue.h"
#include <limits>

PriorityQueue::PriorityQueue(int n) : _pos(n, -1) {}
// 정수 ID, doubel key 기반

double PriorityQueue::key(int v) const
{
    return contains(v) ? _heap[_pos[v]].key
        : std::numeric_limits<double>::infinity();
}

void PriorityQueue::swapn(int a, int b)
{
    std::swap(_heap[a], _heap[b]);
    _pos[_heap[a].id] = a; // 노드 ID -> 힙 인덱스 맵핑
    _pos[_heap[b].id] = b;
}

void PriorityQueue::up(int i)
{
    while (i && _heap[(i - 1) / 2].key > _heap[i].key)
    {
        swapn(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void PriorityQueue::down(int i)
{
    for (;;) 
    {
        int l = 2 * i + 1, r = l + 1, m = i;
        if (l < (int)_heap.size() && _heap[l].key < _heap[m].key) m = l;
        if (r < (int)_heap.size() && _heap[r].key < _heap[m].key) m = r;
        if (m == i) break;
        swapn(i, m); i = m;
    }
}

void PriorityQueue::push(int v, double k)
{
    if (contains(v)) { if (k < key(v)) decrease(v, k); return; }
    _heap.push_back({ v, k });
    _pos[v] = (int)_heap.size() - 1;
    up(_pos[v]);
}

void PriorityQueue::decrease(int v, double k)
{
    int i = _pos[v];
    if (k >= _heap[i].key) return;
    _heap[i].key = k;
    up(i);
}

int PriorityQueue::pop()        // 최우선 값 반환
{
    int v = _heap[0].id;
    swapn(0, (int)_heap.size() - 1);
    _pos[v] = -1;
    _heap.pop_back();
    if (!_heap.empty()) down(0);
    return v;
}
