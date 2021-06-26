#pragma once
#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>

#include "crossPlatformCurses.hpp"

#include "misc.hpp"

class KeyChecker
{
public:
    KeyChecker(WINDOW* window);
    KeyChecker(WINDOW* window, int updateRate);

    void start();
    bool keyIsDown(int keyCode);
    void clearInputBuffer();

private:
    int m_updateRate;
    WINDOW* m_window;
    std::vector<int> m_inputBuffer;

    void mainLoop();
};