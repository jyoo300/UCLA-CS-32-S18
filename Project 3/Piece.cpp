#include "Piece.h"

int Coord::getX() const { 
    return x;
}

int Coord::getY() const {
    return y;
}

int Coord::setX(int m_x) {
    x = m_x;
    return x;
}

int Coord::setY(int m_y) {
    y = m_y;
    return y;
}



Piece::Piece()
:orientation(0), mType(chooseRandomPieceType()) //Creates a random piece
{
    //Each piece is set to its original orientation
    if(mType == PIECE_O) //Initializes the location of each piece
    {
        coord[0].setX(3);
        coord[0].setY(0);
        coord[1].setX(3);
        coord[1].setY(1);
        coord[2].setX(4);
        coord[2].setY(0);
        coord[3].setX(4);
        coord[3].setY(1);
        mSquares[coord[0].getX()][coord[0].getY()] = '#';
        mSquares[coord[1].getX()][coord[1].getY()] = '#';
        mSquares[coord[2].getX()][coord[2].getY()] = '#';
        mSquares[coord[3].getX()][coord[3].getY()] = '#';
    }
    else if(mType == PIECE_I) {
        coord[0].setX(4);
        coord[0].setY(1);
        coord[1].setX(5);
        coord[1].setY(1);
        coord[2].setX(6);
        coord[2].setY(1);
        coord[3].setX(7);
        coord[3].setY(1);
        mSquares[coord[0].getX()][coord[0].getY()]= '#';
        mSquares[coord[1].getX()][coord[1].getY()]= '#';
        mSquares[coord[2].getX()][coord[2].getY()]= '#';
        mSquares[coord[3].getX()][coord[3].getY()]= '#';
    }
    else if(mType == PIECE_L) {
        coord[0].setX(3);
        coord[0].setY(1);
        coord[1].setX(4);
        coord[1].setY(1);
        coord[2].setX(5);
        coord[2].setY(1);
        coord[3].setX(3);
        coord[3].setY(2);
        mSquares[coord[0].getX()][coord[0].getY()]= '#';
        mSquares[coord[1].getX()][coord[1].getY()]= '#';
        mSquares[coord[2].getX()][coord[2].getY()]= '#';
        mSquares[coord[3].getX()][coord[3].getY()]= '#';
    }
    else if(mType == PIECE_J) {
        coord[0].setX(4);
        coord[0].setY(1);
        coord[1].setX(5);
        coord[1].setY(1);
        coord[2].setX(6);
        coord[2].setY(1);
        coord[3].setX(6);
        coord[3].setY(2);
        mSquares[coord[0].getX()][coord[0].getY()]= '#';
        mSquares[coord[1].getX()][coord[1].getY()]= '#';
        mSquares[coord[2].getX()][coord[2].getY()]= '#';
        mSquares[coord[3].getX()][coord[3].getY()]= '#';
    }
    else if(mType == PIECE_T) {
        coord[0].setX(3);
        coord[0].setY(1);
        coord[1].setX(4);
        coord[1].setY(1);
        coord[2].setX(4);
        coord[2].setY(0);
        coord[3].setX(5);
        coord[3].setY(1);
        mSquares[coord[0].getX()][coord[0].getY()]= '#';
        mSquares[coord[1].getX()][coord[1].getY()]= '#';
        mSquares[coord[2].getX()][coord[2].getY()]= '#';
        mSquares[coord[3].getX()][coord[3].getY()]= '#';
    }
    else if(mType == PIECE_S) {
        coord[0].setX(3);
        coord[0].setY(2);
        coord[1].setX(4);
        coord[1].setY(2);
        coord[2].setX(4);
        coord[2].setY(1);
        coord[3].setX(5);
        coord[3].setY(1);
        mSquares[coord[0].getX()][coord[0].getY()]= '#';
        mSquares[coord[1].getX()][coord[1].getY()]= '#';
        mSquares[coord[2].getX()][coord[2].getY()]= '#';
        mSquares[coord[3].getX()][coord[3].getY()]= '#';
    }
    else if(mType == PIECE_Z) {
        coord[0].setX(3);
        coord[0].setY(1);
        coord[1].setX(4);
        coord[1].setY(1);
        coord[2].setX(4);
        coord[2].setY(2);
        coord[3].setX(5);
        coord[3].setY(2);
        mSquares[coord[0].getX()][coord[0].getY()]= '#';
        mSquares[coord[1].getX()][coord[1].getY()]= '#';
        mSquares[coord[2].getX()][coord[2].getY()]= '#';
        mSquares[coord[3].getX()][coord[3].getY()]= '#';
    }
    else if(mType == PIECE_CRAZY) {
        coord[0].setX(3);
        coord[0].setY(0);
        coord[1].setX(4);
        coord[1].setY(1);
        coord[2].setX(5);
        coord[2].setY(1);
        coord[3].setX(6);
        coord[3].setY(0);
        mSquares[coord[0].getX()][coord[0].getY()]= '#';
        mSquares[coord[1].getX()][coord[1].getY()]= '#';
        mSquares[coord[2].getX()][coord[2].getY()]= '#';
        mSquares[coord[3].getX()][coord[3].getY()]= '#';
    }
    else if(mType == PIECE_VAPOR) {
        coord[0].setX(4);
        coord[0].setY(0);
        coord[1].setX(5);
        coord[1].setY(0);
        coord[2].setX(0);
        coord[2].setY(0);
        coord[3].setX(0);
        coord[3].setY(0);
        mSquares[coord[0].getX()][coord[0].getY()]= '#';
        mSquares[coord[1].getX()][coord[1].getY()]= '#';
        mSquares[coord[2].getX()][coord[2].getY()]= ' ';
        mSquares[coord[3].getX()][coord[3].getY()]= ' ';
    }
    else if(mType == PIECE_FOAM) {
        coord[0].setX(4);
        coord[0].setY(1);
        coord[1].setX(0);
        coord[1].setY(0);
        coord[2].setX(0);
        coord[2].setY(0);
        coord[3].setX(0);
        coord[3].setY(0);
        mSquares[coord[0].getX()][coord[0].getY()]= '#';
        mSquares[coord[1].getX()][coord[1].getY()]= ' ';
        mSquares[coord[2].getX()][coord[2].getY()]= ' ';
        mSquares[coord[3].getX()][coord[3].getY()]= ' ';
    }
}


void Piece::rotate() { //Rotates the piece clockwise
     if(mType == PIECE_I) //Depending on the piecetype
     {
         if(orientation == 0) {
             coord[0].setX(coord[0].getX()+1);
             coord[0].setY(coord[0].getY()-1);
             coord[2].setX(coord[2].getX()-1);
             coord[2].setY(coord[2].getY()+1);
             coord[3].setX(coord[3].getX()-2);
             coord[3].setY(coord[3].getY()+2);
             orientation = 1;
         }
         else if(orientation == 1) {
             coord[0].setX(coord[0].getX()-1);
             coord[0].setY(coord[0].getY()+1);
             coord[2].setX(coord[2].getX()+1);
             coord[2].setY(coord[2].getY()-1);
             coord[3].setX(coord[3].getX()+2);
             coord[3].setY(coord[3].getY()-2);
             orientation = 0;
         }
     }
     else if(mType == PIECE_O) {
         
     }
     else if(mType == PIECE_T) {
         if(orientation == 0) {
             coord[0].setX(coord[0].getX()+1);
             coord[0].setY(coord[0].getY()-1);
             coord[2].setX(coord[2].getX()+1);
             coord[2].setY(coord[2].getY()+1);
             coord[3].setX(coord[3].getX()-1);
             coord[3].setY(coord[3].getY()+1);
             orientation = 1;
         }
         else if(orientation == 1) {
             coord[0].setX(coord[0].getX()+1);
             coord[0].setY(coord[0].getY()+1);
             coord[2].setX(coord[2].getX()-1);
             coord[2].setY(coord[2].getY()+1);
             coord[3].setX(coord[3].getX()-1);
             coord[3].setY(coord[3].getY()-1);
             orientation = 2;
         }
         else if(orientation == 2) {
             coord[0].setX(coord[0].getX()-1);
             coord[0].setY(coord[0].getY()+1);
             coord[2].setX(coord[2].getX()-1);
             coord[2].setY(coord[2].getY()-1);
             coord[3].setX(coord[3].getX()+1);
             coord[3].setY(coord[3].getY()-1);
             orientation = 3;
         }
         else if(orientation == 3) {
             coord[0].setX(coord[0].getX()-1);
             coord[0].setY(coord[0].getY()-1);
             coord[2].setX(coord[2].getX()+1);
             coord[2].setY(coord[2].getY()-1);
             coord[3].setX(coord[3].getX()+1);
             coord[3].setY(coord[3].getY()+1);
             orientation = 0;
             
         }
    }
     else if(mType == PIECE_J) {
         if(orientation == 0) {
             coord[0].setX(coord[0].getX()+1);
             coord[0].setY(coord[0].getY()-0);
             coord[1].setX(coord[1].getX()+0);
             coord[1].setY(coord[1].getY()+1);
             coord[2].setX(coord[2].getX()-1);
             coord[2].setY(coord[2].getY()+2);
             coord[3].setX(coord[3].getX()-2);
             coord[3].setY(coord[3].getY()+1);
             orientation = 1;
         }
         else if(orientation == 1) {
             coord[0].setX(coord[0].getX()+1);
             coord[0].setY(coord[0].getY()+1);
             coord[1].setX(coord[1].getX()-0);
             coord[1].setY(coord[1].getY()+0);
             coord[2].setX(coord[2].getX()-1);
             coord[2].setY(coord[2].getY()-1);
             coord[3].setX(coord[3].getX()+0);
             coord[3].setY(coord[3].getY()-2);
             orientation = 2;
         }
         else if(orientation == 2) {
             coord[0].setX(coord[0].getX()-2);
             coord[0].setY(coord[0].getY()+0);
             coord[1].setX(coord[1].getX()-1);
             coord[1].setY(coord[1].getY()-1);
             coord[2].setX(coord[2].getX()+0);
             coord[2].setY(coord[2].getY()-2);
             coord[3].setX(coord[3].getX()+1);
             coord[3].setY(coord[3].getY()-1);
             orientation = 3;
         }
         else if(orientation == 3) {
             coord[0].setX(coord[0].getX()-0);
             coord[0].setY(coord[0].getY()-1);
             coord[1].setX(coord[1].getX()+1);
             coord[1].setY(coord[1].getY()-0);
             coord[2].setX(coord[2].getX()+2);
             coord[2].setY(coord[2].getY()+1);
             coord[3].setX(coord[3].getX()+1);
             coord[3].setY(coord[3].getY()+2);
             orientation = 0;
         }
     }
     else if(mType == PIECE_L) {
         if(orientation == 0) {
             coord[0].setX(coord[0].getX()+2);
             coord[0].setY(coord[0].getY()-1);
             coord[1].setX(coord[1].getX()+1);
             coord[1].setY(coord[1].getY()+0);
             coord[2].setX(coord[2].getX()+0);
             coord[2].setY(coord[2].getY()+1);
             coord[3].setX(coord[3].getX()+1);
             coord[3].setY(coord[3].getY()-2);
             orientation = 1;
         }
         else if(orientation == 1) {
             coord[0].setX(coord[0].getX()+0);
             coord[0].setY(coord[0].getY()+2);
             coord[1].setX(coord[1].getX()-1);
             coord[1].setY(coord[1].getY()+1);
             coord[2].setX(coord[2].getX()-2);
             coord[2].setY(coord[2].getY()+0);
             coord[3].setX(coord[3].getX()+1);
             coord[3].setY(coord[3].getY()+1);
             orientation = 2;
         }
         else if(orientation == 2) {
             coord[0].setX(coord[0].getX()-1);
             coord[0].setY(coord[0].getY()+1);
             coord[1].setX(coord[1].getX()-0);
             coord[1].setY(coord[1].getY()+0);
             coord[2].setX(coord[2].getX()+1);
             coord[2].setY(coord[2].getY()-1);
             coord[3].setX(coord[3].getX()+0);
             coord[3].setY(coord[3].getY()+2);
             orientation = 3;
         }
         else if(orientation == 3) {
             coord[0].setX(coord[0].getX()-1);
             coord[0].setY(coord[0].getY()-2);
             coord[1].setX(coord[1].getX()-0);
             coord[1].setY(coord[1].getY()-1);
             coord[2].setX(coord[2].getX()+1);
             coord[2].setY(coord[2].getY()-0);
             coord[3].setX(coord[3].getX()-2);
             coord[3].setY(coord[3].getY()-1);
             orientation = 0;
         }
     }
     else if(mType == PIECE_S) {
         if(orientation == 0) {
             coord[0].setX(coord[0].getX()+1);
             coord[0].setY(coord[0].getY()-2);
             coord[1].setX(coord[1].getX()+0);
             coord[1].setY(coord[1].getY()-1);
             coord[2].setX(coord[2].getX()+0);
             coord[2].setY(coord[2].getY()+1);
             coord[3].setX(coord[3].getX()-0);
             coord[3].setY(coord[3].getY()+1);
             orientation = 1;
         }
         else if(orientation == 1) {
             coord[0].setX(coord[0].getX()-1);
             coord[0].setY(coord[0].getY()+2);
             coord[1].setX(coord[1].getX()+0);
             coord[1].setY(coord[1].getY()+1);
             coord[2].setX(coord[2].getX()-0);
             coord[2].setY(coord[2].getY()-1);
             coord[3].setX(coord[3].getX()-0);
             coord[3].setY(coord[3].getY()-1);
             orientation = 0;
         }
     }
     else if(mType == PIECE_Z) {
         if(orientation == 0) {
             coord[0].setX(coord[0].getX()+2);
             coord[0].setY(coord[0].getY()-1);
             coord[1].setX(coord[1].getX()+1);
             coord[1].setY(coord[1].getY()-0);
             coord[2].setX(coord[2].getX()+0);
             coord[2].setY(coord[2].getY()-1);
             coord[3].setX(coord[3].getX()-1);
             coord[3].setY(coord[3].getY()+0);
             orientation = 1;
         }
         else if(orientation == 1) {
             coord[0].setX(coord[0].getX()-2);
             coord[0].setY(coord[0].getY()+1);
             coord[1].setX(coord[1].getX()-1);
             coord[1].setY(coord[1].getY()+0);
             coord[2].setX(coord[2].getX()-0);
             coord[2].setY(coord[2].getY()+1);
             coord[3].setX(coord[3].getX()+1);
             coord[3].setY(coord[3].getY()-0);
             orientation = 0;
         }
     }
     else if(mType == PIECE_CRAZY) {
         if(orientation == 0) {
             coord[0].setX(coord[0].getX()+3);
             coord[0].setY(coord[0].getY()+0);
             coord[1].setX(coord[1].getX()+1);
             coord[1].setY(coord[1].getY()+0);
             coord[2].setX(coord[2].getX()-0);
             coord[2].setY(coord[2].getY()+1);
             coord[3].setX(coord[3].getX()+0);
             coord[3].setY(coord[3].getY()+3);
             orientation = 1;
         }
         else if(orientation == 1) {
             coord[0].setX(coord[0].getX()+0);
             coord[0].setY(coord[0].getY()+3);
             coord[1].setX(coord[1].getX()+0);
             coord[1].setY(coord[1].getY()+1);
             coord[2].setX(coord[2].getX()-1);
             coord[2].setY(coord[2].getY()+0);
             coord[3].setX(coord[3].getX()-3);
             coord[3].setY(coord[3].getY()+0);
             orientation = 2;
         }
         else if(orientation == 2) {
             coord[0].setX(coord[0].getX()-3);
             coord[0].setY(coord[0].getY()+0);
             coord[1].setX(coord[1].getX()-1);
             coord[1].setY(coord[1].getY()+0);
             coord[2].setX(coord[2].getX()-0);
             coord[2].setY(coord[2].getY()-1);
             coord[3].setX(coord[3].getX()-0);
             coord[3].setY(coord[3].getY()-3);
             orientation = 3;
         }
         else if(orientation == 3) {
             coord[0].setX(coord[0].getX()-0);
             coord[0].setY(coord[0].getY()-3);
             coord[1].setX(coord[1].getX()-0);
             coord[1].setY(coord[1].getY()-1);
             coord[2].setX(coord[2].getX()+1);
             coord[2].setY(coord[2].getY()-0);
             coord[3].setX(coord[3].getX()+3);
             coord[3].setY(coord[3].getY()-0);
             orientation = 0;
         }
     }
     else if(accessType() == PIECE_VAPOR) {
         
     }
     else if(accessType() == PIECE_FOAM) {
         
     }
}
PieceType Piece::accessType() const //Returns the Piecetype
{
    return mType;
}

int Piece::returnOrientation() const //Returns the orientation of the piece
{
    return orientation;
}

