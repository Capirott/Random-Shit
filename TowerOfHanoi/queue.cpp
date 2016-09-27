#ifndef QUEUE_CPP
#define QUEUE_CPP

#include <iomanip>
#include "queue.h"
#include "stack.h"

namespace capiroto
{

    template <typename Type>
    void Queue<Type>::queue(Type x)
    {
        if (!front)
            rear = front = new Node(x);
        else
        {
            rear->next = new Node(x);
            rear = rear->next;
        }
    }

    template <typename Type>
    Type Queue<Type>::deQueue()
    {
        if (!front)
            throw static_cast<std::string>("Empty Queue");
        Node *tmpPtr = front;
        front = front->next;
        Type x = tmpPtr->x;
        delete tmpPtr;
        return x;
    }

    template <typename Type>
    Type Queue<Type>::getFirst()
    {
        if (!front)
            throw static_cast<std::string>("Empty Queue");
        return front->x;
    }

    template <typename Type>
    Type Queue<Type>::getLast()
    {
        if (!front)
            throw static_cast<std::string>("Empty Queue");
        return rear->x;
    }

    template <typename Type>
    void Queue<Type>::clear()
    {
        while (front)
        {
            Node *tmpPtr = front;
            front = front->next;
            delete tmpPtr;
        }
        front = rear = 0;
    }

    template <typename Type>
    int Queue<Type>::size()
    {
        int i = 0;
        for (Node *tmpPtr = front; tmpPtr; tmpPtr = tmpPtr->next)
            ++i;
        return i;
    }

    template <typename Type>
    void Queue<Type>::invert()
    {
        Stack<Type> tmp;
        while(!is_Empty())
            tmp.push(deQueue());
        while(!tmp.is_Empty())
            queue(tmp.pop());
    }

    template <typename Type>
    void Queue<Type>::print(std::ostream &out)
    {
        if (is_Empty())
            out << "Empty Queue\n";
        else
        {
            for (Node *tmpPtr = front; tmpPtr; tmpPtr = tmpPtr->next)
                out << std::setw(6) << std::left << tmpPtr->x;
            out << std::endl;
        }
    }
}
#endif
