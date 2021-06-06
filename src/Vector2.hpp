#pragma once
#include <iostream>
#include <string>
#include <cmath>

template <typename T>
class Vector2
{
public:

    // Variables
    // ---------

    T x;
    T y;

    // Constructors
    // ------------

    Vector2(); // set everything to 0
    Vector2(T ix, T iy); // init x and y

    // Misc
    // ----

    std::string toString();

    // Operators
    // ---------

    Vector2<T> operator+(const Vector2<T> v);
    void operator+=(const Vector2<T> v);

    Vector2<T> operator-(const Vector2<T> v);
    void operator-=(const Vector2<T> v);

    Vector2<T> operator*(const T a);
    void operator*=(const T a);

    Vector2<T> operator/(const T a);
    void operator/=(const T a);

    bool operator==(const Vector2<T> v);

    // Vector math
    // -----------

    float heading(bool degrees=false);
    
    void rotate(float angle, bool isDegrees=false);

    T magSq();
    T mag();

    T distSq(Vector2<T> v);
    T dist(Vector2<T> v);

    Vector2<T> halfwayTo(Vector2<T> v);

    T dotProduct(Vector2<T> v);

    void normalize();

private:

};