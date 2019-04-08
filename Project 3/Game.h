#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <vector>
#include <string>
using namespace std;
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    ~Game();
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    void print(); //Prints out the piece on the screen every time it moves down
    void eraseChar(int col, int row); //Clears the screen at the position indicated
    void moveCharDown(int col, int row); //Moves the pos of the char down one
    char getChar(int col, int row) const; //Returns the char at the pos indicated
    double findMaximum(double x, double y) const; //Finds max of 2 doubles
    //Keeps track of existing blocks in the grid
    void updateScreen(char c);
    void updateScreenVapor(char c);
    void updateScreenFoam(char c);
    //Prints out the char at the coordinates of the Piece
    void display(char c);
    void displayVapor(char c);
    void displayFoam(char c);
    //Moves the piece down, left, or right
    void move(string direction);
    //Checks to see if a piece overlaps with an existing block in the grid
    bool overlap() const;
    //Translates keyboard commands
    void translateCommands(char ch);
    //Keyboard input to move the piece left
    void shiftLeft();
    //Keyboard input to move the piece right
    void shiftRight();
     //Keyboard input to move the piece down
    void shiftDown();
    //Moves the piece all the way down
    void spaceDown();
    //Rotates the piece
    void rotateShape();
    void changeBool();
    //Checks to see if a row if filled
    bool rowisFilled(int row) const;
    void rowisFilledHelper(int row);
    //Displays the next piece on the screen
    void displaynextPiece();
   //Clears the display of the next piece
    void clearForNextPiece();
    // [Add other members as necessary.]

  private:
    Well    m_well;
    Screen  m_screen;
    int     m_level;
    int     m_rows;
    int     posV;
    int     m_score;
    int     count; //Keeps track of how many rows were evaporated (by one piece)
    bool    endGame;
    vector<Piece*> v;
    Timer*  t; //Timer
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
