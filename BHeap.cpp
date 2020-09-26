#include <iostream>
#include "CDA.cpp"

using namespace std;

#ifndef _BHeap_cpp
#define _BHeap_cpp

template <class keytype, class valuetype>
class BHeap
{
private:
    struct Node
    {
        keytype key;
        valuetype value;
        int degree;
        Node *child, *sibling, *parent;
    };

    Node *root = nullptr;

    Node *heapCreate()
    {
        Node *temp;
        temp = nullptr;
        return temp;
    }

    void heapLink(Node *y, Node *z)
    {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree = z->degree + 1;
    }

    Node *heapUnion(Node *h1, Node *h2)
    {
        Node *temp = heapCreate();
        temp = heapMerge(h1, h2);
        if (temp == nullptr)
            return temp;
        Node *prev_x = nullptr;
        Node *x = temp;
        Node *next_x = x->sibling;
        while (next_x != nullptr)
        {
            if ((x->degree != next_x->degree) || ((next_x->sibling != nullptr) && (next_x->sibling)->degree == x->degree))
            {
                prev_x = x;
                x = next_x;
            }
            else
            {
                if (x->key <= next_x->key)
                {
                    x->sibling = next_x->sibling;
                    heapLink(next_x, x);
                }
                else
                {
                    if (prev_x == nullptr)
                        temp = next_x;
                    else
                        prev_x->sibling = next_x;
                    heapLink(x, next_x);
                    x = next_x;
                }
            }
            next_x = x->sibling;
        }
        return temp;
    }

    Node *heapMerge(Node *h1, Node *h2)
    {
        Node *H = NULL;
        Node **pos = &H;

        while (h1 && h2)
        {
            if (h1->degree < h2->degree)
            {
                *pos = h1;
                h1 = h1->sibling;
            }
            else
            {
                *pos = h2;
                h2 = h2->sibling;
            }
            pos = &(*pos)->sibling;
        }
        if (h1)
            *pos = h1;
        else
            *pos = h2;

        return H;
    }

    void revertList(Node *y)
    {
        if (y->sibling != nullptr)
        {
            revertList(y->sibling);
            (y->sibling)->sibling = y;
        }
        else
        {
            root = y;
        }
    }

    Node *parentCopy(Node *obj)
    {
        Node *temp = new Node();
        temp->key = obj->key;
        temp->value = obj->value;
        temp->parent = obj->parent;
        temp->sibling = obj->sibling;
        temp->degree = obj->degree;
        temp->child = obj->child;
        return temp;
    }

    void childCopy(Node *h, Node *obj)
    {
        if (obj->child != nullptr)
        {
            h->child = parentCopy(obj->child);
            childCopy(h->child, obj->child);
        }
        if (obj->sibling != nullptr)
        {
            h->sibling = parentCopy(obj->sibling);
            childCopy(h->sibling, obj->sibling);
        }
    }

    void heapDelete(Node *h)
    {
        if (h != nullptr)
        {
            heapDelete(h->child);
            delete h;
        }
    }

public:
    BHeap()
    {
    }

    BHeap(keytype k[], valuetype v[], int s)
    {
        for (int i = 0; i < s; i++)
        {
            insert(k[i], v[i]);
        }
    }

    ~BHeap()
    {
        heapDelete(root);
    }

    BHeap(const BHeap &obj)
    {
        root = parentCopy(obj.root);
        childCopy(root, obj.root);
    }

    BHeap &operator=(const BHeap &obj)
    {
        if (this != &obj)
        {
            heapDelete(root);
            root = parentCopy(obj.root);
            childCopy(root, obj.root);
        }
        return *this;
    }

    keytype peekKey()
    {
        Node *min = root;
        Node *temp = root->sibling;
        while (temp != nullptr)
        {
            if (temp->key < min->key)
                min = temp;
            temp = temp->sibling;
        }
        return min->key;
    }

    valuetype peekValue()
    {
        Node *min = root;
        Node *temp = root->sibling;
        while (temp != nullptr)
        {
            if (temp->key < min->key)
                min = temp;
            temp = temp->sibling;
        }
        return min->value;
    }
    keytype extractMin()
    {
        Node *min = extractMin(root);
        return min->key;
    }

    Node *extractMin(Node *temp)
    {
        root = nullptr;
        Node *t = nullptr;
        Node *x = temp;
        if (x == nullptr)
        {
            cout << "Empty heap" << endl;
            return x;
        }
        keytype min = x->key;
        Node *p = x;
        while (p->sibling != nullptr)
        {
            if ((p->sibling)->key < min)
            {
                min = (p->sibling)->key;
                t = p;
                x = p->sibling;
            }
            p = p->sibling;
        }
        if (t == nullptr && x->sibling == nullptr)
            temp = nullptr;
        else if (t == nullptr)
            temp = x->sibling;
        else if (t->sibling == nullptr)
            t = nullptr;
        else
            t->sibling = x->sibling;
        if (x->child != nullptr)
        {
            revertList(x->child);
            (x->child)->sibling = nullptr;
        }
        temp = heapUnion(temp, root);
        return x;
    }

    void insert(keytype k, valuetype v)
    {
        Node *temp = new Node();
        temp->key = k;
        temp->value = v;
        root = heapInsert(root, temp);
    }

    Node *heapInsert(Node *t, Node *x)
    {
        Node *temp = heapCreate();
        x->parent = nullptr;
        x->child = nullptr;
        x->sibling = nullptr;
        x->degree = 0;
        temp = x;
        t = heapUnion(t, temp);
        return t;
    }

    void merge(BHeap<keytype, valuetype> &temp)
    {
        if (temp.root != NULL)
            root = heapUnion(root, temp.root);
    }

    void printKey()
    {
        Node *temp = root;
        while (temp != nullptr)
        {
            cout << "B" << temp->degree << endl;
            cout << temp->key << " ";
            heapPrint(temp->child);
            temp = temp->sibling;

            if (temp != nullptr)
            {
                cout << endl
                     << endl;
            }
        }
        cout << endl;
    }

    void heapPrint(Node *b)
    {
        if (b == nullptr)
        {
            return;
        }
        cout << b->key << " ";
        if (b->child != nullptr)
        {
            heapPrint(b->child);
        }
        if (b->sibling != nullptr)
        {
            heapPrint(b->sibling);
        }
    }
};

#endif