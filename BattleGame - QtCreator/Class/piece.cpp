#include "piece.h"

Piece::Piece(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Piece::setX(int x)
{
    this->x = x;
}

int Piece::getX() const
{
    return x;
}

void Piece::setY(int y)
{
    this->y = y;
}

int Piece::getY() const
{
    return y;
}

bool Piece::operator ==(const Piece &piece) const
{
    if (x == piece.getX() && y == piece.getY())
        return true;
    return false;
}

bool Piece::operator !=(const Piece &piece) const
{
    if (x == piece.getX() && y == piece.getY())
        return false;
    return true;
}

std::string Piece::type()
{
    return "Piece";
}

Piece::~Piece()
{

}
