#pragma once

#include <vector>
#include <string>

#include "crossPlatformCurses.hpp"

#include "Vector2.hpp"
#include "structs.hpp"

void render(WINDOW* window, std::vector<Wall>& walls,
    DefaultVector2 cameraPosition, measure_t cameraAngleDeg,
    measure_t fieldOfView, measure_t viewDistance);