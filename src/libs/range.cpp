#include "range.hpp"

Range::Iterator::Iterator(int index) : index(index) {}

auto Range::Iterator::operator*() const -> int {
    return index;
}

auto Range::Iterator::operator++() -> Range::Iterator& {
    index += 1;
    return *this;
}

auto Range::Iterator::operator==(const Range::Iterator& other) const -> bool {
    return index == other.index;
}

auto Range::Iterator::operator!=(const Range::Iterator& other) const -> bool {
    return index != other.index;
}

Range::Range(int begin, int end) : beginIterator(begin), endIterator(end) {}

auto Range::begin() const -> Range::Iterator {
    return beginIterator;
}

auto Range::end() const -> Range::Iterator {
    return endIterator;
}
