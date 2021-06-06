#include <iostream>
#include <vector>
#include <experimental/optional>
#include <stdlib.h>

#include "crossPlatformCurses.hpp"

#include "Vector2.hpp"
#include "structs.hpp"
#include "render.hpp"

void cleanUpCurses()
{
    echo();
    nocbreak();
    endwin();
}

int main()
{
    atexit(cleanUpCurses);

    initscr();
    noecho();
    cbreak();
    WINDOW* window = newwin(0, 0, 0, 0);
    keypad(window, true);

    std::vector<Wall> walls = {
        Wall(DefaultVector2(-1, 5), DefaultVector2(1, 5))
    };

    measure_t angle = 0;
    measure_t turnSpeed = 5;

    render(window, walls, DefaultVector2(0, 0), angle, 90, 20);
    for (int i = 0; i < 100000; i ++)
    {
        wrefresh(window);
        char key = wgetch(window);;
        if (key == 4) angle -= turnSpeed;
        else if (key == 5) angle += turnSpeed;
        render(window, walls, DefaultVector2(0, 0), angle, 90, 20);
    }
    
    return 0;
}