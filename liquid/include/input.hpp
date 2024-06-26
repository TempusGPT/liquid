#ifndef LIQUID_INPUT_HPP
#define LIQUID_INPUT_HPP

#include <functional>
#include <unordered_set>
#include <vector>

namespace liquid {
    enum class Key {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Number0,
        Number1,
        Number2,
        Number3,
        Number4,
        Number5,
        Number6,
        Number7,
        Number8,
        Number9,
        Backtick,
        Hyphen,
        Equal,
        LeftBracket,
        RightBracket,
        Backslash,
        Semicolon,
        Apostrophe,
        Comma,
        Period,
        Slash,
        Space,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        Tab,
        Backspace,
        Enter,
        Insert,
        Delete,
        Home,
        End,
        PageUp,
        PageDown,
        UpArrow,
        DownArrow,
        LeftArrow,
        RightArrow,
    };

    class Input {
    public:
        ~Input();
        auto operator()(
            const std::vector<Key>& keys,
            const std::function<void()>& callback
        ) -> void;

    private:
        std::unordered_set<int> idSet;
    };

    namespace detail {
        auto initializeInput() -> void;
        auto processInput() -> void;
    }
}

#endif
