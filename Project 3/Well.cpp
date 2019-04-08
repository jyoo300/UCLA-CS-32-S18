#include "Well.h"
#include "UserInterface.h"

void Well::display(Screen& screen, int x, int y) //Creases the well
{
    if (x == 0 && y == 0)
    {
    while(y<19) {
        if(x == 0 || x == 11) { //Inserts the boundaries of the well on the sides
            screen.printChar('@');
        }
        if(x < 11) {
            x++;
            screen.gotoXY(x, y);
        }
        else {
            x = 0;
            y++;
            screen.gotoXY(x, y);
        }
    }
    x = 1;
    y--;
    while(x <= 10) //Inserts the bottom boundaries of the well
    {
        screen.gotoXY(x, y);
        screen.printChar('@');
        x++;
    }
    }
}
