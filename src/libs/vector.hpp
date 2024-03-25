#ifndef LIBS_VECTOR_HPP
#define LIBS_VECTOR_HPP

struct Vector {
    int x;
    int y;

    Vector() : x(0), y(0) {}
    Vector(int x, int y) : x(x), y(y) {}

    Vector operator+(const Vector &other) const {
        return { x + other.x, y + other.y };
    }

    Vector operator-(const Vector &other) const {
        return { x - other.x, y - other.y };
    }

    bool operator==(const Vector &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector &other) const {
        return x != other.x || y != other.y;
    }

    static Vector zero() {
        return { 0, 0 };
    }

    static Vector up() {
        return { 0, -1 };
    }

    static Vector down() {
        return { 0, 1 };
    }

    static Vector left() {
        return { -1, 0 };
    }

    static Vector right() {
        return { 1, 0 };
    }
};

#endif
