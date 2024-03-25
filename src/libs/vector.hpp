#ifndef LIBS_VECTOR_HPP
#define LIBS_VECTOR_HPP

struct Vector {
    int x;
    int y;

    auto operator+(const Vector& other) const -> Vector {
        return { x + other.x, y + other.y };
    }

    auto operator-(const Vector& other) const -> Vector {
        return { x - other.x, y - other.y };
    }

    auto operator==(const Vector& other) const -> bool {
        return x == other.x && y == other.y;
    }

    auto operator!=(const Vector& other) const -> bool {
        return x != other.x || y != other.y;
    }

    static auto zero() -> Vector {
        return { 0, 0 };
    }

    static auto up() -> Vector {
        return { 0, -1 };
    }

    static auto down() -> Vector {
        return { 0, 1 };
    }

    static auto left() -> Vector {
        return { -1, 0 };
    }

    static auto right() -> Vector {
        return { 1, 0 };
    }
};

#endif
