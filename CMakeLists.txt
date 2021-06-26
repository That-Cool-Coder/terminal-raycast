cmake_minimum_required(VERSION 3.10)

project(terminal-raycast VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/*.cpp")
add_executable(terminal-raycast ${SOURCES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

if(WIN32 OR MSVC)
    find_path(PDC_INCLUDES curses.h)
    find_library(PDC_LIBS pdcurses REQUIRED)
    include_directories(${PDC_INCLUDES})
    target_link_libraries(${PROJECT_NAME} ${PDC_LIBS} Threads::Threads)
else()
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES} Threads::Threads)
endif()

target_include_directories(terminal-raycast PUBLIC
    "${PROJECT_BINARY_DIR}"
)