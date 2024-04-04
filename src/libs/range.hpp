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

        bool operator==(const Iterator& other) const {
            return index == other.index;
        }

        bool operator!=(const Iterator& other) const {
            return index != other.index;
        }

    private:
        int index;
    };

    Iterator begin() const {
        return beginIterator;
    }

    Iterator end() const {
        return endIterator;
    }

    Range(int begin, int end) : beginIterator(begin), endIterator(end) {}

private:
    Iterator beginIterator;
    Iterator endIterator;
};

#endif
