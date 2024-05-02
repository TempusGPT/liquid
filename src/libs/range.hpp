#ifndef LIBS_RANGE_HPP
#define LIBS_RANGE_HPP

class Range {
public:
    class Iterator {
    public:
        Iterator(int index) : index(index) {}

        auto operator*() const -> int {
            return index;
        }

        auto operator++() -> Iterator& {
            index += 1;
            return *this;
        }

        auto operator==(const Iterator& other) const -> bool {
            return index == other.index;
        }

        auto operator!=(const Iterator& other) const -> bool {
            return index != other.index;
        }

    private:
        int index;
    };

    auto begin() const -> Iterator {
        return beginIterator;
    }

    auto end() const -> Iterator {
        return endIterator;
    }

    Range(int begin, int end) : beginIterator(begin), endIterator(end) {}

private:
    Iterator beginIterator;
    Iterator endIterator;
};

#endif
