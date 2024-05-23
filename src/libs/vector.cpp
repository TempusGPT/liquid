#include "vector.hpp"

auto Vector::operator+(const Vector& other) const -> Vector {
    return { x + other.x, y + other.y };
}

auto Vector::operator-(const Vector& other) const -> Vector {
    return { x - other.x, y - other.y };
}

auto Vector::operator==(const Vector& other) const -> bool {
    return x == other.x && y == other.y;
}

auto Vector::operator!=(const Vector& other) const -> bool {
    return x != other.x || y != other.y;
}

auto Vector::zero() -> Vector {
    return { 0, 0 };
}

auto Vector::up() -> Vector {
    return { 0, -1 };
}

auto Vector::down() -> Vector {
    return { 0, 1 };
}

auto Vector::left() -> Vector {
    return { -1, 0 };
}

auto Vector::right() -> Vector {
    return { 1, 0 };
}
