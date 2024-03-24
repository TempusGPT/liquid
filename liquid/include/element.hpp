#ifndef LIQUID_ELEMENT_HPP
#define LIQUID_ELEMENT_HPP

#include "color.hpp"

#include <functional>
#include <vector>

namespace Liquid {
    namespace Internal {
        void onCleanup(const std::function<void()> &callback);
    }

    class Element {
        friend void Internal::onCleanup(const std::function<void()> &callback);

    public:
        Element(const std::function<void(int, int)> &renderCallback = nullptr);

        void render(int x, int y) const;
        void cleanup() const;

    private:
        static Element *lastMounted;
        std::function<void(int, int)> renderCallback;
        std::vector<std::function<void()>> cleanupCallbacks;
    };
}

#endif
