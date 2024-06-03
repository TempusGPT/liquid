#ifndef LIBS_VECTOR_HPP
#define LIBS_VECTOR_HPP

#include <cstddef>
#include <functional>

struct Vector {
    int x;
    int y;

    auto operator+(const Vector& other) const -> Vector;
    auto operator-(const Vector& other) const -> Vector;
    auto operator==(const Vector& other) const -> bool;
    auto operator!=(const Vector& other) const -> bool;

    auto rotateLeft() const -> Vector;
    auto rotateRight() const -> Vector;

    static auto zero() -> Vector;
    static auto up() -> Vector;
    static auto down() -> Vector;
    static auto left() -> Vector;
    static auto right() -> Vector;
};

namespace std {
    template <>
    struct hash<Vector> {
        std::size_t operator()(const Vector& v) const {
            auto hash = std::hash<int>();
            return hash(v.x) ^ (hash(v.y) << 1);
        }
    };
}

#endif
