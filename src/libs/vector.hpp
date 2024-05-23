#ifndef LIBS_VECTOR_HPP
#define LIBS_VECTOR_HPP

struct Vector {
    int x;
    int y;

    auto operator+(const Vector& other) const -> Vector;
    auto operator-(const Vector& other) const -> Vector;
    auto operator==(const Vector& other) const -> bool;
    auto operator!=(const Vector& other) const -> bool;

    static auto zero() -> Vector;
    static auto up() -> Vector;
    static auto down() -> Vector;
    static auto left() -> Vector;
    static auto right() -> Vector;
};

#endif
