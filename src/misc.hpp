#pragma once

#if defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #define SLEEP(ms) (ms)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 10)
#endif

#define LEFT_ARROW 4
#define RIGHT_ARROW 5