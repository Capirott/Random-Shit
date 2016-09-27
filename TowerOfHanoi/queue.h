#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

namespace capiroto
{
    template <typename Type>
    class Queue
    {
    private:

        class Node
        {
        public:
            Type x;
            Node *next;
            Node(Type x) : x(x), next(0) {}
        };
        Node *front;
        Node *rear;
    public:
        Queue() : front(0), rear(0) {}
        void queue(Type);
        Type deQueue();
        Type getFirst();
        Type getLast();
        bool is_Empty() { return !front; }
        void clear();
        int size();
        void invert();
        void print(std::ostream&);
    };
}

#include "queue.cpp"
#endif // QUEUE_H
