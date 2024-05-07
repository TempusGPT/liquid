#ifndef LIQUID_REF_HPP
#define LIQUID_REF_HPP

#include <memory>

namespace liquid {
    template <typename T>
    class Ref {
    public:
        Ref(const T& value = T()) : value(std::make_shared<T>(value)) {}

        auto operator*() -> T& {
            return *value;
        }

        auto operator*() const -> const T& {
            return *value;
        }

        auto operator->() -> T* {
            return value.get();
        }

        auto operator->() const -> const T* {
            return value.get();
        }

    private:
        const std::shared_ptr<T> value;
    };
}

#endif
