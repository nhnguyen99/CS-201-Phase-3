#include <iostream>
#include <string.h>
#include <cstring>
#include <cstdlib>

using namespace std;

#ifndef _CDA_cpp
#define _CDA_cpp

template <class elmtype>

class CDA
{

public:
    CDA();
    CDA(int s);
    ~CDA();
    CDA(const CDA<elmtype> &obj);
    CDA<elmtype> &operator=(const CDA<elmtype> &obj);
    elmtype &operator[](int i);
    void AddEnd(elmtype v);
    void AddFront(elmtype v);
    void DelEnd();
    void DelFront();
    int Length();
    int Capacity();
    void Clear();
    bool Ordered();
    int SetOrdered();

private:
    int size, capacity, front, rear;
    elmtype *arr;
    elmtype ret;
    bool flag;
    void DeepCopy(const CDA<elmtype> &obj);
};

template <typename elmtype>
CDA<elmtype>::CDA()
{
    size = 0;
    capacity = 1;
    arr = new elmtype[capacity];
    flag = false;
    front = -1;
    rear = 0;
}

template <typename elmtype>
CDA<elmtype>::CDA(int s)
{
    capacity = size = s;
    arr = new elmtype[s];
    flag = false;
    front = 0;
    rear = s - 1;
}

template <typename elmtype>
CDA<elmtype>::~CDA()
{
    delete[] arr;
}

template <typename elmtype>
CDA<elmtype>::CDA(const CDA<elmtype> &obj)
{
    DeepCopy(obj);
}

template <typename elmtype>
CDA<elmtype> &CDA<elmtype>::operator=(const CDA<elmtype> &obj)
{
    if (this != &obj)
    {
        delete[] arr;
        DeepCopy(obj);
    }
    return *this;
}

template <typename elmtype>
void CDA<elmtype>::DeepCopy(const CDA<elmtype> &obj)
{
    capacity = obj.capacity;
    size = obj.size;
    front = obj.front;
    rear = obj.rear;
    arr = new elmtype[capacity];
    for (int i = 0; i < obj.size; i++)
    {
        arr[(front + i) % capacity] = obj.arr[(front + i) % capacity];
    }
}

template <typename elmtype>
elmtype &CDA<elmtype>::operator[](int i)
{
    if (i >= size || i < 0)
    {
        cout << "Out of bounds reference: " << i << endl;
        return ret;
    }
    else
        return arr[(front + i) % capacity];
}

template <typename elmtype>
void CDA<elmtype>::AddEnd(elmtype v)
{
    if (size == capacity)
    {
        int cap = capacity;
        capacity *= 2;
        elmtype *temp = arr;
        arr = new elmtype[capacity];
        for (int i = 0; i < size; i++)
        {
            arr[i] = temp[(front + i) % cap];
        }
        size++;
        arr[size - 1] = v;
        front = 0;
        rear = size - 1;
        delete[] temp;
    }
    else
    {
        if (front == -1)
            front = 0;
        else if (rear == (capacity - 1))
            rear = 0;
        else
            rear += 1;
        size++;
        arr[rear] = v;
    }
}

template <typename elmtype>
void CDA<elmtype>::AddFront(elmtype v)
{
    if (size == capacity)
    {
        int cap = capacity;
        capacity *= 2;
        elmtype *temp = arr;
        arr = new elmtype[capacity];
        arr[0] = v;
        for (int i = 0; i < size; i++)
        {
            arr[i + 1] = temp[(front + i) % cap];
        }
        size++;
        front = 0;
        rear = size - 1;
        delete[] temp;
    }
    else
    {
        if (front == -1)
            front = 0;
        else if (front == 0)
            front = capacity - 1;
        else
            front = front - 1;
        size++;
        arr[front] = v;
    }
}

template <typename elmtype>
void CDA<elmtype>::DelEnd()
{
    if (size == 0)
    {
        return;
    }
    size--;
    if (4 * size <= capacity)
    {
        int cap = capacity;
        capacity /= 2;

        if (capacity < 1)
            return;
        elmtype *temp = arr;
        arr = new elmtype[capacity];
        for (int i = 0; i < (size); i++)
        {
            arr[i] = temp[(front + i) % cap];
        }
        front = 0;
        rear = size - 1;
        delete[] temp;
    }
    else
    {
        if (front == rear)
        {
            front = -1;
            rear = 0;
        }
        else if (rear == 0)
        {
            rear = capacity - 1;
        }
        else
            rear -= 1;
    }
}

template <typename elmtype>
void CDA<elmtype>::DelFront()
{
    if (size == 0)
    {
        return;
    }
    size--;
    if (4 * size <= capacity)
    {
        int cap = capacity;
        capacity /= 2;
        if (capacity < 1)
            return;
        elmtype *temp = arr;
        arr = new elmtype[capacity];
        for (int i = 0; i < size; ++i)
        {
            arr[i] = temp[(front + i + 1) % cap];
        }
        front = 0;
        rear = size - 1;
        delete[] temp;
    }
    else
    {
        if (front == rear)
        {
            front = -1;
            rear = 0;
        }
        else if (front == (capacity - 1))
            front = 0;
        else
            front += 1;
    }
}

template <typename elmtype>
int CDA<elmtype>::Length()
{
    return size;
}

template <typename elmtype>
int CDA<elmtype>::Capacity()
{
    return capacity;
}

template <typename elmtype>
void CDA<elmtype>::Clear()
{
    delete arr;
    arr = new elmtype[capacity = 1];
    size = 0;
    flag = false;
    front = -1;
    rear = 0;
}

template <typename elmtype>
bool CDA<elmtype>::Ordered()
{
    SetOrdered();
    return flag;
}

template <typename elmtype>
int CDA<elmtype>::SetOrdered()
{
    if (size == 0 || size == 1)
    {
        flag = true;
        return 1;
    }
    for (int i = 1; i < size; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            flag = false;
            return -1;
        }
    }
    flag = true;
    return 1;
}

#endif