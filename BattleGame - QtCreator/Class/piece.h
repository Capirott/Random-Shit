#ifndef PIECE_H
#define PIECE_H

#include <string>
using std::string;

class Piece
{
protected:
    int x;
    int y;
public:

    Piece(int x = -1, int y = -1);

    void setX(int x);
    int getX() const;

    void setY(int y);
    int getY() const;

    bool operator ==(const Piece &piece) const;
    bool operator !=(const Piece &piece) const;

    virtual std::string type();

    virtual ~Piece();
};

#endif // PIECE_H
