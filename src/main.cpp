#include <iostream>
#include <vector>
#include <experimental/optional>
#include <stdlib.h>

#include "crossPlatformCurses.hpp"

#include "Vector2.hpp"
#include "KeyChecker.hpp"
#include "structs.hpp"
#include "misc.hpp"
#include "render.hpp"

#define FRAME_RATE 100

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

    KeyChecker keyChecker(window);
    keyChecker.start();

    render(window, walls, position, angle, 90, 10);
    while (true)
    {
        if (keyChecker.keyIsDown('q')) break;

        if (keyChecker.keyIsDown(LEFT_ARROW)) angle -= turnSpeed; // left arrow
        if (keyChecker.keyIsDown(RIGHT_ARROW)) angle += turnSpeed; // right arrow

        DefaultVector2 movement;
        if (keyChecker.keyIsDown('j')) movement.x += speed;
        if (keyChecker.keyIsDown('l')) movement.x -= speed;
        if (keyChecker.keyIsDown('i')) movement.y += speed;
        if (keyChecker.keyIsDown('k')) movement.y -= speed;
        keyChecker.clearInputBuffer();

        movement.rotate(angle, true);
        position += movement;

        render(window, walls, position, angle, 90, 10);
        SLEEP(FRAME_RATE);
    }
    
    return 0;
}