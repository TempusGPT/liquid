#ifndef LIBS_RANGE_HPP
#define LIBS_RANGE_HPP

class Range {
public:
    class Iterator {
    public:
        Iterator(int index);

        auto operator*() const -> int;
        auto operator++() -> Iterator&;
        auto operator==(const Iterator& other) const -> bool;
        auto operator!=(const Iterator& other) const -> bool;

    private:
        int index;
    };

    Range(int begin, int end);
    auto begin() const -> Iterator;
    auto end() const -> Iterator;

private:
    Iterator beginIterator;
    Iterator endIterator;
};

#endif
