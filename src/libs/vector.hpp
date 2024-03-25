#ifndef LIBS_VECTOR_HPP
#define LIBS_VECTOR_HPP

struct Vector {
    int x;
    int y;

    Vector operator+(const Vector &other) const {
        return { x + other.x, y + other.y };
    }

    Vector operator-(const Vector &other) const {
        return { x - other.x, y - other.y };
    }
};

#endif
