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
    endwin();
}

int main()
{
    atexit(cleanUpCurses);

    initscr();
    noecho();
    WINDOW* window = newwin(0, 0, 0, 0);
    keypad(window, true);

    std::vector<Wall> walls = {
        Wall(DefaultVector2(-1, 5), DefaultVector2(1, 5))
    };

    measure_t angle = 0;
    measure_t turnSpeed = 5;
    measure_t speed = 0.1;
    DefaultVector2 position(0, 0);

    render(window, walls, position, angle, 90, 20);
    for (int i = 0; i < 100000; i ++)
    {
        wrefresh(window);
        char key = wgetch(window);
        waddstr(window, std::to_string(key).c_str());
        if (key == 97) angle -= turnSpeed; // a
        else if (key == 100) angle += turnSpeed; // d
        else if (key == 4) position.x -= speed; // left
        else if (key == 5) position.x += speed; // right
        render(window, walls, position, angle, 90, 20);
    }
    
    return 0;
}