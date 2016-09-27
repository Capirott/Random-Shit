#ifndef STACK_H
#define STACK_H

#include <iostream>
class RenderArea;
namespace capiroto
{
    class Exception
    {
    public:
        std::string msg_Error;
        int id_Error;
        Exception(int id_Error) : id_Error(id_Error)
        {
            this->id_Error = id_Error;
            switch(id_Error)
            {
            case 0:
                msg_Error = "Empty Stack";
                break;
            }
        }
    };

    template <typename Type>
    class Stack
    {
    private:
        friend class ::RenderArea;
        class Node
        {
        public:
            Type x;
            Node *next;
            Node(Type x) : x(x), next(0) {}
        };

        Node *top;
        void print(std::ostream&, Node*);
        void clear(Node*);
    public:
        Stack() : top(0) {}
        ~Stack() { clear(); }
        void push(Type);
        Type pop();
        Type get_Top();
        bool is_Empty() { return !top; }
        void clear() { clear(top), top = 0; }
        int size();
        void invert();
        void print(std::ostream&,bool);
    };
}

#include "stack.cpp"
#endif // STACK_H
