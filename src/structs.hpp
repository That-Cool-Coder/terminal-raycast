#pragma once

#include <experimental/optional>

#include "Vector2.hpp"

typedef float measure_t;
typedef Vector2<measure_t> DefaultVector2;

class Ray
{
public:
    Vector2<measure_t> start;
    Vector2<measure_t> end;

    Ray(Vector2<measure_t> i_start, Vector2<measure_t> i_end)
    {
        start = i_start;
        end = i_end;
    }

    measure_t heading(bool degrees=false)
    {
        return (end - start).heading(degrees);
    }

    void rotate(measure_t angle, bool degrees=false)
    {
        DefaultVector2 delta = end - start;
        delta.rotate(angle, degrees);
        end = start + delta;
    }

    std::experimental::optional<DefaultVector2> intersection(Ray ray)
    {
        /* Return an optional containing the intersection position
        Get the stuff out like this:
        if (auto intersectionData = r.intersection(r2))
        {
            DefaultVector2 intersection = *intersectionData;
            std::cout << intersection.toString();
        }
        else
        {
            std::cout << "Nothing";
        }
        */

        bool found = false;
        DefaultVector2 intersection;

        measure_t den = (start.x - end.x) * (ray.start.y - ray.end.y) - 
            (start.y - end.y) * (ray.start.x - ray.end.x);

        // // if lines intersect (simple check)
        if (den != 0)
        {
            measure_t t = (start.x - ray.start.x) * (ray.start.y - ray.end.y) -
                (start.y - ray.start.y) * (ray.start.x - ray.end.x);
            t /= den;
            measure_t u = -((start.x - end.x) * (start.y - ray.start.y) -
                (start.y - end.y) * (start.x - ray.start.x));
            u /= den;
            // // if lines intersect (cpu intensive check)
            if (t > 0 && t < 1 && u > 0)
            {
                intersection = DefaultVector2(
                    start.x + t * (end.x - start.x),
                    start.y + t * (end.y - start.y)
                );
                found = true;
            }
        }

        if (found) return intersection;
        else return std::experimental::nullopt;
    }

    std::string toString()
    {
        return "{" + start.toString() + "," + end.toString() + "}";
    }
};

// Yes, a wall can be stored the same as a ray
typedef Ray Wall;

struct Intersection
{
    measure_t distance;
    Wall* wall;
    int rayNumber;
    Intersection(measure_t i_distance, Wall* i_wall, int i_rayNumber)
    {
        distance = i_distance;
        wall = i_wall;
        rayNumber = i_rayNumber;
    }
};