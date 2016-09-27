#ifndef STACK_CPP
#define STACK_CPP

#include "stack.h"
#include <iomanip>

namespace capiroto
{
    template <typename Type>
    void Stack<Type>::push(Type x)
    {
        Node *n = new Node(x);
        n->next = top;
        top = n;
    }

    template <typename Type>
    Type Stack<Type>::pop()
    {
        if (!top)
            throw Exception(0);
        Node tmp = *top;
        delete top;
        top = tmp.next;
        return tmp.x;
    }

    template <typename Type>
    Type Stack<Type>::get_Top()
    {
        if (!top)
            throw Exception(0);
        return top->x;
    }

    template <typename Type>
    void Stack<Type>::clear(Node *top)
    {
        if (top)
        {
            clear(top->next);
            delete top;
        }
    }

    template <typename Type>
    int Stack<Type>::size()
    {
        int i = 0;
        for (Node*ptr = top; ptr ; ptr = ptr->next)
            ++i;
        return i;
    }

    template <typename Type>
    void Stack<Type>::invert()
    {
        Stack<Type> tmpStack, tmpStack2;
        while(top)
            tmpStack.push(pop());
        while(tmpStack.top)
            tmpStack2.push(tmpStack.pop());
        while(tmpStack2.top)
            push(tmpStack2.pop());
    }

    template <typename Type>
    void Stack<Type>::print(std::ostream &out, bool opc = 0)
    {
        if (opc)
            print(out,top);
        else
        {
            for (Node *pto = top; pto; pto = pto->next )
                out << std::setprecision(3) << std::setw(6) << std::left << pto->x;
        }
        out << std::endl;
    }

    template <typename Type>
    void Stack<Type>::print(std::ostream &out, Node *pto)
    {
        if (pto)
        {
            print(out, pto->next);
            out << std::setprecision(3) << std::setw(6) << std::left << pto->x;
        }
    }
}
#endif //STACK_CPP
