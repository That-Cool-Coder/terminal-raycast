#include "KeyChecker.hpp"

KeyChecker::KeyChecker(WINDOW* window)
{
    m_window = window;
    m_updateRate = 100;
}

KeyChecker::KeyChecker(WINDOW* window, int updateRate)
{
    m_window = window;
    m_updateRate = updateRate;
}

void KeyChecker::start()
{
    std::thread( [this] { mainLoop(); } ).detach();
}

bool KeyChecker::keyIsDown(int keyCode)
{
    return (std::find(m_inputBuffer.begin(), m_inputBuffer.end(), keyCode)
        != m_inputBuffer.end());
}

void KeyChecker::clearInputBuffer()
{
    m_inputBuffer.clear();
}

void KeyChecker::mainLoop()
{
    while (true)
    {
        int c = wgetch(m_window);
        m_inputBuffer.push_back(c);
        //SLEEP(m_updateRate);
    }
}