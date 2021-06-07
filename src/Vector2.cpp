#include "Vector2.hpp"
#include <iostream>
#include <string>
#include <cmath>

#ifndef PI
    #define PI 3.141592653589793238462643383279502884L
#endif

// Constructors
// ------------

template <typename T>
Vector2<T>::Vector2() : x(0), y(0) {}

template <typename T>
Vector2<T>::Vector2(T ix, T iy) : x(ix), y(iy) {}

// Misc
// ----

template <typename T>
std::string Vector2<T>::toString()
{
    std::string xString = std::to_string(this->x);
    std::string yString = std::to_string(this->y);
    return "{" + xString + ", " + yString + "}";
}

// Operators
// -----------------

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T> v)
{
    return Vector2<T>(this->x + v.x, this->y + v.y);
}

template <typename T>
void Vector2<T>::operator+=(const Vector2<T> v)
{
    this->x += v.x;
    this->y += v.y;
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T> v)
{
    return Vector2<T>(this->x - v.x, this->y - v.y);
}

template <typename T>
void Vector2<T>::operator-=(const Vector2<T> v)
{
    this->x -= v.x;
    this->y -= v.y;
}

template <typename T>
Vector2<T> Vector2<T>::operator*(const T a)
{
    return Vector2<T>(this->x * a, this->y * a);
}

template <typename T>
void Vector2<T>::operator*=(const T a)
{
    this->x *= a;
    this->y *= a;
}

template <typename T>
Vector2<T> Vector2<T>::operator/(const T a)
{
    return Vector2<T>(this->x / a, this->y / a);
}

template <typename T>
void Vector2<T>::operator/=(const T a)
{
    this->x /= a;
    this->y /= a;
}

template <typename T>
bool Vector2<T>::operator==(const Vector2<T> v)
{
    return this->x == v.x && this->y == v.y;
}

// Vector math
// -----------

template <typename T>
float Vector2<T>::heading(bool degrees)
{
    float angle = atan2(this->y, this->x);

    if (degrees)
    {
        angle *= 180.0 / PI;
    }
    return angle;
}

template <typename T>
void Vector2<T>::rotate(float angle, bool degrees)
{

    if (degrees)
    {
        angle /= 180.0 / PI;
    }
    // Calc sin and cos values before to save recalculating
    float sinVal = sin(angle);
    float cosVal = cos(angle);

    // Assign to a temp variable to avoid messing with the this->x below
    T newX = this->x * cosVal - this->y * sinVal;

    this->y = this->x * sinVal + this->y * cosVal;

    this->x = newX;
}

template <typename T>
T Vector2<T>::magSq()
{
    return pow(this->x, 2) + pow(this->y, 2);
}

template <typename T>
T Vector2<T>::mag()
{
    return (T) sqrt(this->magSq());
}

template <typename T>
T Vector2<T>::distSq(Vector2<T> v)
{
    return ((v - *this) / 2).magSq();
}

template <typename T>
T Vector2<T>::dist(Vector2<T> v)
{
    return (T) sqrt(this->distSq(v));
}

template <typename T>
Vector2<T> Vector2<T>::halfwayTo(Vector2<T> v)
{
    return *this + ((v - *this) / (T) 2);
}

template <typename T>
void Vector2<T>::normalize()
{
    this->operator/=(this->mag());
}

template <typename T>
T Vector2<T>::dotProduct(Vector2<T> v)
{
    T result = this->x * v.x;
    result += this->y * v.y;
    return result;
}

// Compile for different types

// Create a 2-dimensional vector representing a position or velocity
template class Vector2<int>;
template class Vector2<float>;
template class Vector2<double>;
template class Vector2<long>;
template class Vector2<long long>;
template class Vector2<long double>;