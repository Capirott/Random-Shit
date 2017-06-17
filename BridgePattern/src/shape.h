#ifndef SHAPE_H
#define SHAPE_H

#include "draw.h"
#include <memory>

class Shape 
{
protected:
    float x;
    float y;
    DrawAPI *implementor;
public:
    Shape(float x, float y, DrawAPI *implementor) : x(x), y(y), implementor(implementor) {}    

    void virtual draw() = 0;
};

class Circle : public Shape
{
public:
    Circle(float x, float y, DrawAPI *implementor) : Shape(x, y, implementor) {}
    void draw()
    {
        implementor->draw(x, y);
    }    
};

class Losange : public Shape
{
public:
    Losange(float x, float y, DrawAPI *implementor) : Shape(x, y, implementor) {}
    void draw()
    {
        implementor->draw(x, y);
    }  
};

class Rectangle : public Shape
{
public:
    Rectangle(float x, float y, DrawAPI *implementor) : Shape(x, y, implementor) {}
   void draw()
    {
        implementor->draw(x, y);
    }  
};

class Triangle : public Shape
{
public:
    Triangle(float x, float y, DrawAPI *implementor) : Shape(x, y, implementor) {}
    void draw()
    {
        implementor->draw(x, y);
    }  
};


#endif