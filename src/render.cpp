#include "render.hpp"

// Look at the bottom of this file for the main rendering function

const std::string darkToLightAscii =
    "@#8f|+";
    //"$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

std::vector<Ray> createRays(int rayAmount, DefaultVector2 cameraPosition,
    measure_t cameraAngle, measure_t fieldOfView, measure_t rayLength)
{
    std::vector<Ray> rays;

    measure_t angleBetweenRays = fieldOfView / rayAmount;
    measure_t crntAngle = cameraAngle - fieldOfView / 2;
    for (int i = 0; i < rayAmount; i ++)
    {
        DefaultVector2 endPosition(0, rayLength);
        endPosition.rotate(crntAngle, true);
        endPosition += cameraPosition;
        rays.push_back(Wall(cameraPosition, endPosition));
        crntAngle += angleBetweenRays;
    }

    return rays;
}

std::vector<Intersection> calculateIntersections(std::vector<Wall>& walls,
    std::vector<Ray> rays)
{
    std::vector<Intersection> intersections;

    // Use a basic for loop here so we can get index
    for (int rayNumber = 0; rayNumber < rays.size(); rayNumber ++)
    {
        Ray ray = rays[rayNumber];

        measure_t closestIntersectionDist = INFINITY;
        Wall* closestWall;
        for (auto wall : walls)
        {
            auto intersection = wall.intersection(ray);
            if (! intersection) continue; // If there is no intersection then skip
                measure_t dist = ray.start.dist(*intersection);
                if (dist < closestIntersectionDist)
                {
                    closestWall = &wall;
                    closestIntersectionDist = dist;
                }
        }
        // If an intersection took place, record it
        if (closestIntersectionDist != INFINITY)
        {
            intersections.push_back(Intersection(closestIntersectionDist,
                closestWall, rayNumber));
        }
    }

    return intersections;
}

void render(WINDOW* window, std::vector<Wall>& walls,
    DefaultVector2 cameraPosition, measure_t cameraAngle,
    measure_t fieldOfView, measure_t viewDistance)
{
    int rows, cols;
    getmaxyx(window, rows, cols);

    int rayAmount = cols;

    std::vector<Ray> rays = createRays(rayAmount, cameraPosition, cameraAngle,
        fieldOfView, viewDistance);
    std::vector<Intersection> intersections = calculateIntersections(walls, rays);

    wclear(window);
    measure_t verticalFieldOfView = rows / cols * fieldOfView;
    for (auto intersection : intersections)
    {
        int columnHeight = rows / intersection.distance;
        measure_t darkness = intersection.distance / viewDistance;
        int characterIndex = (int) (darkness * darkToLightAscii.length());
        char fillCharacter = darkToLightAscii[characterIndex];
        for (int row = 0; row < columnHeight; row ++)
        {
            wmove(window, rows / 2 - columnHeight / 2 + row,
                intersection.rayNumber);
            waddch(window, fillCharacter);
        }
    }

    wrefresh(window);
}