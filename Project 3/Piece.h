#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include <iostream>


enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z, PIECE_CRAZY, PIECE_VAPOR, PIECE_FOAM, NUM_PIECE_TYPES};

// PIECE_FOAM,

PieceType chooseRandomPieceType();

class Coord //Stores coordinate of each square
{
public:
    int getX() const;
    int getY() const;
    int setX(int m_x);
    int setY(int m_y);
private:
    int x;
    int y;
};

class Piece {
public:
    Piece();
    ~Piece() {}
    PieceType accessType() const;
    int returnOrientation() const;
    char mSquares[12][19]; //Stores the location of the piece regarding its position of the well
    Coord coord[4]; //Stores the coordinates of the screen of each square
    void rotate();
private:
    PieceType mType;
    int orientation;
};


#endif // PIECE_INCLUDED
