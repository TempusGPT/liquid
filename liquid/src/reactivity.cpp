#include "include/reactivity.hpp"

#include <string>

namespace Liquid {
    namespace Internal {
        EffectCore::EffectCore() : id(-1), callback(nullptr) {}
        EffectCore::EffectCore(const std::function<void()> &callback) : id(newId++), callback(callback) {}

        EffectCore &EffectCore::getCurrent() {
            return current;
        }

        void EffectCore::run() const {
            if (callback) {
                current = *this;
                callback();
                current = {};
            }
        }

        bool EffectCore::operator==(const EffectCore &other) const {
            return id == other.id;
        }

        EffectCore::operator bool() const {
            return id != -1;
        }

        int EffectCore::newId = 0;
        EffectCore EffectCore::current = {};
    }

    Effect createEffect() {
        return Effect();
    }

    Effect::~Effect() {
        for (const auto &callback : callbacks) {
            Internal::EffectCore(callback).run();
        }

        for (const auto &callback : cleanupCallbacks) {
            // add callback to element.cleanupCallbacks
        }
    }

    void Effect::operator()(const std::function<void()> &callback) {
        callbacks.push_back(callback);
    }

    void Effect::cleanup(const std::function<void()> &callback) {
        cleanupCallbacks.push_back(callback);
    }

    Signal<std::string> createSignal(const char *value) {
        return Signal<std::string>(value);
    }
}