//#include "stdafx.h"
#include <iostream>
using namespace std;

//параметризованный однонаправленный список
template <typename T>
class List
{
private:
    //----single list node
    class node
    {
    public:
        T data;

        node* next;
    public:
        node(node* _next):next(_next) {}
    };

     node* head, * tail;

public:
    void push_front(const T& val)
    {
        if (empty())
        {
            head = new node(tail);
            head->data = val;
        }
        else
        {
            head = new node(head);
            head->data = val;
        }
    }

    void push_back(const T& val)
    {
        if (empty())
        {
            head = new node(tail);
            head->data = val;
        }
        else
        {
            node* srh_node = head;
            for (; srh_node->next != tail; srh_node = srh_node->next);

            srh_node->next = new node(tail);
            srh_node->next->data = val;
        }
    }

    T pop_front()
    {
        T val = head->data;
        node* to_del = head;
        head = head->next;

        delete to_del;
        return val;
    }

    T pop_back()
    {
        node* srh_node = head;

        if (srh_node->next == tail)
        {
            head = tail;
            T val = srh_node->data;
            delete srh_node;

            return val;
        }
        else
        {
            for (; (srh_node->next->next != tail); srh_node = srh_node->next);

            T val = srh_node->next->data;
            node* to_del = srh_node->next;
            srh_node->next = srh_node->next->next;
            delete to_del;

            return val;
        }
    }

    bool empty() const
    {
        return head == tail;
    }

    virtual void clear()
    {
        node* dl_node;
        for (node* cr_node = head; cr_node != tail;)
        {
            dl_node = cr_node;
            cr_node = cr_node->next;

            delete dl_node;
        }

        head = tail;
    }

    List()
    {
        head = tail = new node(0);
    }

    List(const List& l)
    {
        clear();
        node* cur_node = head;

        for (node* srh_node = l.head; srh_node != l.tail; srh_node=srh_node->next)
        {
            cur_node->next = new node(tail);
            cur_node->data = srh_node->data;
        }

    }

    virtual ~List()
    {
        clear();
    }

};

template <typename T>
class Queue : protected List<T>
{
public:
    Queue()//:List() 
    {}

    Queue(const Queue& rhs)
        :List(rhs)
    {}

    ~Queue()
    {}

    inline void push(const T& value)
    {
        List<T>::push_back(value);
    }

    inline T pop()
    {
        return List<T>::pop_front();
    }
};

template <typename T>
class Stack : protected List<T>
{
public:
    Stack() //:List()
    {}

    Stack(const Stack &rhs)
        :List(rhs)
    {}

    ~Stack()
    {}


    inline void push(const T& value)
    {
        List<T>::push_front(value);
    }

    inline T pop()
    {
        return List<T>::pop_front();
    }
};

int main()
{
    Queue<int> qi;
    qi.push(1);    qi.push(2);    qi.push(3);

    cout << qi.pop() << endl;
    cout << qi.pop() << endl;
    cout << qi.pop() << endl;

    Stack<int> si;
    si.push(1);    si.push(2);    si.push(3);

    cout << si.pop() << endl;
    cout << si.pop() << endl;
    cout << si.pop() << endl;
    system("pause");
}
/*2.	Создать базовый класс список. Реализовать на базе
списка стек и очередь с виртуальными функциями
вставки и вытаскивания.*/