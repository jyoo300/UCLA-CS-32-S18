#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include <string>

//Stores position of the blocks, mimicking their positions in the well
char saveScreen[12][19];

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_rows(5), posV(0), m_score(0), count(0)
{
    t = new Timer;
    v.push_back(new Piece);
}

Game::~Game() {
    delete t;
}

void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]
    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        for (int i = 1; i < 11; i++) {
            for (int j = 0; j < 18; j++) {
                eraseChar(i, j);
                m_screen.gotoXY(i, j);
                m_screen.printChar(' ');
            }
        }
        waitForEnter();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

bool Game::playOneLevel()
{
    displayStatus();
    m_rows = 5 * m_level; //The number of rows increased as the level increases
    v.push_back(new Piece);
    while(m_rows > 0) {
        count = 0;
        clearForNextPiece();
        v.push_back(new Piece); //Pushes next piece that will be dropped after current piece
        displaynextPiece();
        print();
        if(count == 1) //Increases the score based on how many rows were disintegrated
        {
            m_score += 100;
        }
        else if(count == 2) {
            m_score += 200;
        }
        else if(count == 3) {
            m_score += 400;
        }
        else if(count == 4) {
            m_score += 800;
        }
        else if(count == 5) {
            m_score += 1600;
        }
        displayStatus();
        posV++;
        changeBool(); //Checks to see if the conditions to end the game is true
        if(endGame == true) {
            return false;
        }
    }
    return true;
}

void Game::displayPrompt(std::string s)
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
    m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
    m_screen.printString("Next piece:");
    m_screen.gotoXY(SCORE_X, SCORE_Y);
    m_screen.printString("Score:            ");
    char a = '0' + m_score; //Converts score into a char
    m_screen.printChar(a);
    m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
    m_screen.printString("Rows left:        ");
    char b = '0' + m_rows; //Converts the number of rows left into a char
    m_screen.gotoXY(SCORE_X, 30);
    m_screen.printChar(b);
    m_screen.gotoXY(LEVEL_X, LEVEL_Y);
    m_screen.printString("Level:            ");
    char c = '0' + m_level; //Converts the current level into a char
    m_screen.gotoXY(LEVEL_X, 30);
    m_screen.printChar(c);
    // [Replace this with code to display the status.]
}

void Game::translateCommands(char ch) {
    getCharIfAny(ch);
    switch (ch) {
        case ARROW_LEFT: //Moves piece left
            if(v[posV]->accessType() == PIECE_CRAZY) { //If PIECE_CRAZY button ARROW_LEFT moves piece right
                shiftRight();
            }
            else {
                shiftLeft();
            }
            break;
        case ARROW_RIGHT: //Moves piece right
            if(v[posV]->accessType() == PIECE_CRAZY) { //If PIECE_CRAZY ARROW_RIGHT moves piece left
                shiftLeft();
            }
            else {
                 shiftRight();
            }
            break;
        case ARROW_DOWN: //Moves piece down
            shiftDown();
            break;
        case ARROW_UP: //Rotates piece (if not PIECE_VAPOR or PIECE_FOAM)
            if(v[posV]->accessType() == PIECE_VAPOR ||v[posV]->accessType() == PIECE_FOAM) {
                break;
            }
            rotateShape();
            break;
        case ' ':
            spaceDown();
            break;
        case 'Q': //End game immediately
        case 'q':
            endGame = true;
        default:
            break;
    }
}

void Game::spaceDown() {
    /*while(overlap() == false && v[posV]->coord[0].getY() != 17 && v[posV]->coord[1].getY() != 17 && v[posV]->coord[2].getY() && 17 && v[posV]->coord[3].getY() != 17) {
        shiftDown();
    }
    if(v[posV]->accessType() == PIECE_FOAM) {
        displayFoam('$');
        updateScreenFoam('$');
        m_screen.refresh();
    }
    else if(v[posV]->accessType() == PIECE_VAPOR) {
        displayVapor('$');
        updateScreenVapor('$');
        m_screen.refresh();
        
    }
    else {
        displayVapor('$');
        updateScreenVapor('$');
        m_screen.refresh();

    }*/
}

void Game::rotateShape() {
    if(v[posV]->accessType() == PIECE_L) //Ensures that PIECE_L won't extend past the boundaries of the well if it rotates
    {
        if(v[posV]->returnOrientation() == 1 && v[posV]->coord[3].getX() == 1) {
            return;
        }
    }
    else if(v[posV]->accessType() == PIECE_J) //Ensures that PIECE_J won't extend past the boundaries of the well if it rotates
    {
        if(v[posV]->returnOrientation() == 2 && v[posV]->coord[0].getX() == 1) {
            return;
        }
    }
    if((v[posV]->coord[0].getX() == 1 && v[posV]->coord[1].getX() == 1) ||(v[posV]->coord[0].getX() == 1 && v[posV]->coord[2].getX() == 1) || (v[posV]->coord[0].getX() == 1 && v[posV]->coord[3].getX() == 1) ||(v[posV]->coord[1].getX() == 1 && v[posV]->coord[2].getX() == 1) || (v[posV]->coord[1].getX() == 1 && v[posV]->coord[3].getX() == 1)|| (v[posV]->coord[2].getX() == 1 && v[posV]->coord[3].getX() == 1))
    //Ensures that piece won't extend past the boundaries of the well if it rotates
    {
        return;
    }
    else if((v[posV]->coord[0].getX() == 10 && v[posV]->coord[1].getX() == 10) ||(v[posV]->coord[0].getX() == 10 && v[posV]->coord[2].getX() == 10) || (v[posV]->coord[0].getX() == 10 && v[posV]->coord[3].getX() == 10) ||(v[posV]->coord[1].getX() == 10 && v[posV]->coord[2].getX() == 10) || (v[posV]->coord[1].getX() == 10 && v[posV]->coord[3].getX() == 10)|| (v[posV]->coord[2].getX() == 10 && v[posV]->coord[3].getX() == 10))
    
        //Ensures that piece won't extend past the boundaries of the well if it rotates
    {
        return;
    }
    else if(overlap() == true) //If the rotation would overlap with the blocks already in thr well
    
    {
        return;
    }
    move("none");
    m_screen.refresh();
    v[posV]->rotate();
    display('#');
    m_screen.refresh();
}

void Game::print() {
    displayStatus();
    if(v[posV]->accessType() == PIECE_FOAM) {
        while(v[posV]->coord[0].getY() < 18 && endGame == false) {
            if(overlap() == true) {
                endGame = true;
                break;
            }
            displayFoam('#'); //Displays # in the current squares of the piece
            m_screen.refresh();
            double d = findMaximum(1000-(100*(m_level-1)), 1000); //Sets the timer
            t->start();
            char ch;
            while(t->elapsed() <= d) {
                translateCommands(ch);
                if(ch == ARROW_DOWN) {
                    move("down");
                    if(overlap() == false) {
                         t->start();
                    }
                     v[posV]->coord[0].setY(v[posV]->coord[0].getY()-1);
                }
            }
            //If the piece is in the last row of the well it doesn't move down
            if(v[posV]->coord[0].getY() == 17) {
            }
            else {
                move("down");
            }
            if(overlap() == true) //Sets the piece in back to original pos and then breaks
            {
                v[posV]->coord[0].setY(v[posV]->coord[0].getY()-1);
                displayFoam('$');
                updateScreenFoam('$');
                m_screen.refresh();
                break;
            }
            else {
                displayFoam('#');
                m_screen.refresh();
            }
            if(v[posV]->coord[0].getY() == 17) //If piece in the last row, breaks
            {
                break;
            }
        }
        displayFoam('$');
        updateScreenFoam('$');
        m_screen.refresh();
        for(int i = 17; i >= 0; i--) //Checks to see if the row can be destroyed and how many rows are destroyed
        {
            if(rowisFilled(i) == true) {
                rowisFilledHelper(i);
                m_screen.refresh();
                m_rows--;
                i++;
                count++;
            }
            else {
            }
        }
    }
    else if(v[posV]->accessType() == PIECE_VAPOR) {
        while((v[posV]->coord[0].getY() < 18  || v[posV]->coord[1].getY() < 18) && endGame == false) {
            if(overlap() == true) {
                endGame = true;
                break;
            }
            displayVapor('#');
            m_screen.refresh();
            double d = findMaximum(1000-(100*(m_level-1)), 1000);
            t->start();
            char ch;
            while(t->elapsed() <= d) {
                translateCommands(ch);
                if(ch == ARROW_DOWN) {
                    move("down");
                    if(overlap() == false) {
                        t->start();
                    }
                    v[posV]->coord[0].setY(v[posV]->coord[0].getY()-1);
                    v[posV]->coord[1].setY(v[posV]->coord[1].getY()-1);
                }
            }
            if(v[posV]->coord[0].getY() == 17  || v[posV]->coord[1].getY() == 17) {
            }
            else {
                move("down");
            }
            if(overlap() == true) {
                v[posV]->coord[0].setY(v[posV]->coord[0].getY()-1);
                v[posV]->coord[1].setY(v[posV]->coord[1].getY()-1);
                displayVapor('$');
                updateScreenVapor('$');
                m_screen.refresh();
                break;
            }
            else {
                displayVapor('#');
                m_screen.refresh();
            }
            if(v[posV]->coord[0].getY() == 17 || v[posV]->coord[1].getY() == 17) {
                break;
            }

        }
        displayVapor('$');
        updateScreenVapor('$');
        m_screen.refresh();
        for(int i = 17; i >= 0; i--) {
            if(rowisFilled(i) == true) {
                rowisFilledHelper(i);
                m_screen.refresh();
                m_rows--;
                i++;
                count++;
            }
            else {
            }
        }
    }
    else {
        while((v[posV]->coord[0].getY() < 18  ||v[posV]->coord[1].getY() < 18 ||v[posV]->coord[2].getY() < 18 ||v[posV]->coord[3].getY() < 18) && endGame == false) {
            if(overlap() == true) {
                endGame = true;
                break;
            }
            display('#');
            m_screen.refresh();
            double d = findMaximum(1000-(100*(m_level-1)), 1000);
            t->start();
            char ch;
            while(t->elapsed() <= d) {
                translateCommands(ch);
                if(ch == ARROW_DOWN) {
                    move("down");
                    if(overlap() == false) {
                        t->start();
                    }
                    v[posV]->coord[0].setY(v[posV]->coord[0].getY()-1);
                    v[posV]->coord[1].setY(v[posV]->coord[1].getY()-1);
                    v[posV]->coord[2].setY(v[posV]->coord[2].getY()-1);
                    v[posV]->coord[3].setY(v[posV]->coord[3].getY()-1);
                }
            }
            if(v[posV]->coord[0].getY() == 17  ||v[posV]->coord[1].getY() == 17 ||v[posV]->coord[2].getY() == 17 ||v[posV]->coord[3].getY() == 17) {
            }
            else {
                move("down");
            }
            if(overlap() == true) {
                v[posV]->coord[0].setY(v[posV]->coord[0].getY()-1);
                v[posV]->coord[1].setY(v[posV]->coord[1].getY()-1);
                v[posV]->coord[2].setY(v[posV]->coord[2].getY()-1);
                v[posV]->coord[3].setY(v[posV]->coord[3].getY()-1);
                display('$');
                updateScreen('$');
                m_screen.refresh();
                break;
            }
            else {
                display('#');
                m_screen.refresh();
            }
            if(v[posV]->coord[0].getY() == 17  ||v[posV]->coord[1].getY() == 17 ||v[posV]->coord[2].getY() == 17 ||v[posV]->coord[3].getY() == 17) {
                break;
            }
        }
        display('$');
        updateScreen('$');
        m_screen.refresh();
        for(int i = 17; i >= 0; i--) {
            if(rowisFilled(i) == true) {
                rowisFilledHelper(i);
                m_screen.refresh();
                m_rows--;
                i++;
                count++;
            }
            else {
            }
        }
    }
}

//Checks to see if the top row is filled
void Game::changeBool() {
    for(int i = 1; i < 11; i++) {
        if (saveScreen[i][0] == '$') {
            endGame = true;
        }
    }
}

//Checks to see if the current row is filled
bool Game::rowisFilled(int row) const {
    int count = 0;
    for(int i = 1; i < 11; i++) {
        if (saveScreen[i][row] == '$') {
            count++;
        }
    }
    if(count == 10) {
        return true;
    }
    else {
        return false;
    }
}

//If the row is filled, this funct is called to ensure current row is erased and the blocks of the above row are moved down one row
void Game::rowisFilledHelper(int row) {
    for (int i = 1; i < 11; i++) {
        eraseChar(i, row);
    }
    for(int i = 1; i < 11; i++) {
        for(int j = row - 1; j >= 0; j--) //Moves contents of row above row erased dow
        {
            if(saveScreen[i][j] == '$') {
                eraseChar(i, j);
                moveCharDown(i, j);
            }
        }
    }
}

//Checks to see if the piece overlaps with existing blocks
bool Game::overlap() const {
    for (int i = 0; i < 4; i++) {
        if(saveScreen[v[posV]->coord[i].getX()][v[posV]->coord[i].getY()] == '$') {
            return true;
        }
    }
    return false;
}

//Displays on the screen the char in the squares of the current piece
void Game::display(char c) {
    for(int i = 0; i < 4; i++) {
            m_screen.gotoXY(v[posV]->coord[i].getX(), v[posV]->coord[i].getY());
            m_screen.printChar(c);
            v[posV]->mSquares[v[posV]->coord[i].getX()][v[posV]->coord[i].getY()] = c;
    }
}

//Display for vapor
void Game::displayVapor(char c) {
    for(int i = 0; i < 2; i++) {
        m_screen.gotoXY(v[posV]->coord[i].getX(), v[posV]->coord[i].getY());
        m_screen.printChar(c);
        v[posV]->mSquares[v[posV]->coord[i].getX()][v[posV]->coord[i].getY()] = c;
    }
}

//Display for foam
void Game::displayFoam(char c) {
    m_screen.gotoXY(v[posV]->coord[0].getX(), v[posV]->coord[0].getY());
    m_screen.printChar(c);
    v[posV]->mSquares[v[posV]->coord[0].getX()][v[posV]->coord[0].getY()] = c;
}

//Inserts char into the squares of the piece
void Game::updateScreen(char c) {
    saveScreen[v[posV]->coord[0].getX()][v[posV]->coord[0].getY()] = c;
    saveScreen[v[posV]->coord[1].getX()][v[posV]->coord[1].getY()] = c;
    saveScreen[v[posV]->coord[2].getX()][v[posV]->coord[2].getY()] = c;
    saveScreen[v[posV]->coord[3].getX()][v[posV]->coord[3].getY()] = c;
}

//Update screen for vapor
void Game::updateScreenVapor(char c) {
    saveScreen[v[posV]->coord[0].getX()][v[posV]->coord[0].getY()] = c;
    saveScreen[v[posV]->coord[1].getX()][v[posV]->coord[1].getY()] = c;
}

//Update screen for foam
void Game::updateScreenFoam(char c) {
    saveScreen[v[posV]->coord[0].getX()][v[posV]->coord[0].getY()] = c;
}

void Game::move(string direction) {
    if(v[posV]->accessType() == PIECE_FOAM) {
        displayFoam(' '); //Clears current pos of the piece
        if(direction == "down") //Moves pos down
        {
            v[posV]->coord[0].setY(v[posV]->coord[0].getY()+1);
        }
        else if (direction == "left") //Moves pos left
        {
            v[posV]->coord[0].setX(v[posV]->coord[0].getX()-1);
        }
        else if (direction == "right") //Moves pos right
        {
            v[posV]->coord[0].setX(v[posV]->coord[0].getX()+1);
        }
        else if(direction == "none") //Doesn't move pos at all
        {
        }
    }
    else if(v[posV]->accessType() == PIECE_VAPOR){
        displayVapor(' ');
        if(direction == "down") {
            v[posV]->coord[0].setY(v[posV]->coord[0].getY()+1);
            v[posV]->coord[1].setY(v[posV]->coord[1].getY()+1);
        }
        else if (direction == "left") {
            v[posV]->coord[0].setX(v[posV]->coord[0].getX()-1);
            v[posV]->coord[1].setX(v[posV]->coord[1].getX()-1);
        }
        else if (direction == "right") {
            v[posV]->coord[0].setX(v[posV]->coord[0].getX()+1);
            v[posV]->coord[1].setX(v[posV]->coord[1].getX()+1);
        }
        else if(direction == "none") {
        }
    }
    else {
        display(' ');
        if(direction == "down") {
            v[posV]->coord[0].setY(v[posV]->coord[0].getY()+1);
            v[posV]->coord[1].setY(v[posV]->coord[1].getY()+1);
            v[posV]->coord[2].setY(v[posV]->coord[2].getY()+1);
            v[posV]->coord[3].setY(v[posV]->coord[3].getY()+1);
        }
        else if (direction == "left") {
            v[posV]->coord[0].setX(v[posV]->coord[0].getX()-1);
            v[posV]->coord[1].setX(v[posV]->coord[1].getX()-1);
            v[posV]->coord[2].setX(v[posV]->coord[2].getX()-1);
            v[posV]->coord[3].setX(v[posV]->coord[3].getX()-1);
        }
        else if (direction == "right") {
            v[posV]->coord[0].setX(v[posV]->coord[0].getX()+1);
            v[posV]->coord[1].setX(v[posV]->coord[1].getX()+1);
            v[posV]->coord[2].setX(v[posV]->coord[2].getX()+1);
            v[posV]->coord[3].setX(v[posV]->coord[3].getX()+1);
        }
        else if(direction == "none") {
        }
    }
}

void Game::shiftLeft() //Moves piece left with ARROW_LEFT command
{
    if(v[posV]->accessType() == PIECE_FOAM) {
        if(v[posV]->coord[0].getX() == 1) //If piece is in the 1st column of well
        {
        }
        else {
            move("left");
        }
        if (overlap() == true)  //If the piece is located in the last row of the well
        {
            displayFoam('$');
            move("right");
            m_screen.refresh();
        }
        displayFoam('#');
        m_screen.refresh();
        
    }
    else if(v[posV]->accessType() == PIECE_VAPOR) {
        if(v[posV]->coord[0].getX() == 1 || v[posV]->coord[1].getX() == 1) {
        }
        else {
            move("left");
        }
        if (overlap() == true) {
            displayVapor('$');
            move("right");
            m_screen.refresh();
        }
        displayVapor('#');
        m_screen.refresh();
    }
    else {
        if(v[posV]->coord[0].getX() == 1 || v[posV]->coord[1].getX() == 1 ||v[posV]->coord[2].getX() == 1 ||v[posV]->coord[3].getX() == 1) {
        }
        else {
            move("left");
        }
        if (overlap() == true) {
            display('$');
            move("right");
            m_screen.refresh();
        }
        display('#');
        m_screen.refresh();
    }
}

void Game::shiftRight() {
    if(v[posV]->accessType() == PIECE_FOAM) //Moves piece right with ARROW_RIGHT
    
    {
        if(v[posV]->coord[0].getX() == 10) //if Piece is the last column of the well
        {
        }
        else {
            move("right");
        }
        if (overlap() == true)  //If the piece is located in the last row of the well
        {
            displayFoam('$');
            m_screen.refresh();
            move("left");
            m_screen.refresh();
        }
        displayFoam('#');
        m_screen.refresh();
        
    }
    else if(v[posV]->accessType() == PIECE_VAPOR) {
         if(v[posV]->coord[0].getX() == 10 || v[posV]->coord[1].getX() == 10) {
         }
         else {
             move("right");
         }
         if (overlap() == true) {
             displayVapor('$');
             m_screen.refresh();
             move("left");
             m_screen.refresh();
         }
         displayVapor('#');
         m_screen.refresh();
     }
     else {
         if(v[posV]->coord[0].getX() == 10 || v[posV]->coord[1].getX() == 10 ||v[posV]->coord[2].getX() == 10 ||v[posV]->coord[3].getX() == 10) {
         }
         else {
             move("right");
         }
         if (overlap() == true) {
             display('$');
             m_screen.refresh();
             move("left");
             m_screen.refresh();
         }
         display('#');
         m_screen.refresh();
     }
}

void Game::shiftDown()  //Moves piece down with ARROW_DOWN command

{
    if(v[posV]->accessType() == PIECE_FOAM) {
        if(v[posV]->coord[0].getY() == 17) //If the piece is located in the last row of the well
        {
        }
        else {
            move("down");
        }
        if(overlap() == true) //Moves piece back in original position if new position overlaps with another block
        {
            v[posV]->coord[0].setY(v[posV]->coord[0].getY()-1);
            m_screen.refresh();
        }
        displayFoam('#');
        m_screen.refresh();
    }
    else if(v[posV]->accessType() == PIECE_VAPOR) {
        if(v[posV]->coord[0].getY() == 17 || v[posV]->coord[1].getY() == 17) {
        }
        else {
            move("down");
        }
        if(overlap() == true) {
            v[posV]->coord[0].setY(v[posV]->coord[0].getY()-1);
            v[posV]->coord[1].setY(v[posV]->coord[1].getY()-1);
            m_screen.refresh();
        }
        displayVapor('#');
        m_screen.refresh();
    }
    else {
        if(v[posV]->coord[0].getY() == 17 || v[posV]->coord[1].getY() == 17 ||v[posV]->coord[2].getY() == 17 ||v[posV]->coord[3].getY() == 17) {
        }
        else {
            move("down");
        }
        if(overlap() == true){
            v[posV]->coord[0].setY(v[posV]->coord[0].getY()-1);
            v[posV]->coord[1].setY(v[posV]->coord[1].getY()-1);
            v[posV]->coord[2].setY(v[posV]->coord[2].getY()-1);
            v[posV]->coord[3].setY(v[posV]->coord[3].getY()-1);
            m_screen.refresh();
        }
        display('#');
        m_screen.refresh();
    }
}

void Game::eraseChar(int col, int row) {
    m_screen.gotoXY(col, row);
    m_screen.printChar(' ');
    saveScreen[col][row] = ' ';
}

void Game::moveCharDown(int col, int row) {
    m_screen.gotoXY(col, row+1);
    m_screen.printChar('$');
    saveScreen[col][row+1] = '$';
}

double Game::findMaximum(double x, double y) const {
    if (x < y) {
        return y;
    }
    else {
        return x;
    }
}

void Game::clearForNextPiece() //Clears the next piece that was printed in the display
{
    if(v[posV]->accessType() == PIECE_O) {
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X+1, NEXT_PIECE_Y);
        m_screen.printChar(' ');
    }
    else if(v[posV]->accessType() == PIECE_I) {
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y+1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y+1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y+1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 3, NEXT_PIECE_Y+1);
        m_screen.printChar(' ');
    }
    else if(v[posV]->accessType() == PIECE_T) {
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
    }
    else if(v[posV]->accessType() == PIECE_L) {
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y+1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
        m_screen.printChar(' ');
    }
    else if(v[posV]->accessType() == PIECE_J) {
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 3, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 3, NEXT_PIECE_Y + 2);
        m_screen.printChar(' ');
    }
    else if(v[posV]->accessType() == PIECE_S) {
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 2);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
    }
    else if(v[posV]->accessType() == PIECE_Z) {
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 2);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y + 2);
        m_screen.printChar(' ');
    }
    else if(v[posV]->accessType() == PIECE_VAPOR) {
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y);
        m_screen.printChar(' ');
    }
    else if(v[posV]->accessType() == PIECE_FOAM) {
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y+1);
        m_screen.printChar(' ');
    }
    else if(v[posV]->accessType() == PIECE_FOAM) {
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y + 1);
        m_screen.printChar(' ');
        m_screen.gotoXY(NEXT_PIECE_X + 3, NEXT_PIECE_Y);
        m_screen.printChar(' ');
    }
    
}

void Game::displaynextPiece() //Displays the next piece that will come after the current piece on the screen
{
    if(v[posV+1]->accessType() == PIECE_O) {
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X+1, NEXT_PIECE_Y);
        m_screen.printChar('#');
    }
    else if(v[posV+1]->accessType() == PIECE_I) {
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y+1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y+1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y+1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 3, NEXT_PIECE_Y+1);
        m_screen.printChar('#');
    }
    else if(v[posV+1]->accessType() == PIECE_T) {
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
    }
    else if(v[posV+1]->accessType() == PIECE_L) {
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y+1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
        m_screen.printChar('#');
    }
    else if(v[posV+1]->accessType() == PIECE_J) {
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 3, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 3, NEXT_PIECE_Y + 2);
        m_screen.printChar('#');
    }
    else if(v[posV+1]->accessType() == PIECE_S) {
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 2);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 2);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
    }
    else if(v[posV+1]->accessType() == PIECE_Z) {
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 2);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y + 2);
        m_screen.printChar('#');
    }
    else if(v[posV+1]->accessType() == PIECE_VAPOR) {
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y);
        m_screen.printChar('#');
    }
    else if(v[posV+1]->accessType() == PIECE_FOAM) {
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y+1);
        m_screen.printChar('#');
    }
    else if(v[posV+1]->accessType() == PIECE_FOAM) {
        m_screen.gotoXY(NEXT_PIECE_X, NEXT_PIECE_Y);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 1, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 2, NEXT_PIECE_Y + 1);
        m_screen.printChar('#');
        m_screen.gotoXY(NEXT_PIECE_X + 3, NEXT_PIECE_Y);
        m_screen.printChar('#');
    }
}
