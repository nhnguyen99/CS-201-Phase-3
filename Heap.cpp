#include <iostream>
#include "CDA.cpp"

using namespace std;

#ifndef _Heap_cpp
#define _Heap_cpp

template <class keytype, class valuetype>
class Heap
{
private:
    struct Node
    {
        keytype key;
        valuetype val;
        Node(keytype key, valuetype val)
        {
            this->key = key;
            this->val = val;
        }
    };

    void nodeSwap(Node *n1, Node *n2)
    {
        Node *temp = new Node(n1->key, n1->val);
        n1->key = n2->key;
        n1->val = n2->val;
        n2->key = temp->key;
        n2->val = temp->val;
        delete temp;
    }

    CDA<Node *> heap;

public:
    Heap()
    {
    }

    Heap(keytype k[], valuetype v[], int s)
    {
        for (int x = 0; x < s; x++)
        {
            Node *temp = new Node(k[x], v[x]);
            heap.AddEnd(temp);
        }
        for (int x = s; x >= 0; x--)
            heapify(x);
    }

    ~Heap()
    {
    }

    Heap(const Heap &obj)
    {
        heap = obj.heap;
    }

    Heap &operator=(const Heap &obj)
    {
        if (this != &obj)
        {
            heap = obj.heap;
        }
        return *this;
    }

    keytype peekKey()
    {
        return heap[0]->key;
    }

    valuetype peekValue()
    {
        return heap[0]->val;
    }

    keytype extractMin()
    {
        keytype min = heap[0]->key;
        int x = heap.Length();
        nodeSwap(heap[0], heap[x - 1]);
        heap.DelEnd();
        heapify(0);
        return min;
    }

    void insert(keytype k, valuetype v)
    {
        Node *temp = new Node(k, v);
        heap.AddEnd(temp);
        int x = heap.Length() - 1;
        while (x > 0 && (heap[(x - 1) / 2]->key > heap[x]->key))
        {
            nodeSwap(heap[x], heap[(x - 1) / 2]);
            x = (x - 1) / 2;
        }
    }

    void printKey()
    {
        int s = heap.Length();
        for (int x = 0; x < s; x++)
        {
            cout << heap[x]->key << " ";
        }
        cout << endl;
    }

    void heapify(int i)
    {
        int s = heap.Length();
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        if (left < s && heap[left]->key < heap[i]->key)
            smallest = left;
        if (right < s && heap[right]->key < heap[smallest]->key)
            smallest = right;
        if (smallest != i)
        {
            nodeSwap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }
};

#endif