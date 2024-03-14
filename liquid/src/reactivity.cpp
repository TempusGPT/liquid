#include "include/reactivity.hpp"

#include <string>

namespace Liquid {
    Effect createEffect() {
        return Effect();
    }

    Effect::~Effect() {
        for (const auto &callback : callbacks) {
            Data(callback).run();
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

    Effect::Data::Data() : id(-1), callback(nullptr) {}
    Effect::Data::Data(const std::function<void()> &callback) : id(newId++), callback(callback) {}

    Effect::Data &Effect::Data::getCurrent() {
        return current;
    }

    void Effect::Data::run() const {
        if (callback) {
            current = *this;
            callback();
            current = {};
        }
    }

    bool Effect::Data::operator==(const Data &other) const {
        return id == other.id;
    }

    Effect::Data::operator bool() const {
        return id != -1;
    }

    int Effect::Data::newId = 0;
    Effect::Data Effect::Data::current = {};

    Signal<std::string> createSignal(const char *value) {
        return Signal<std::string>(value);
    }
}