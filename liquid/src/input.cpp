#include "include/input.hpp"

#include <ncurses.h>
#include <unordered_map>

namespace Liquid {
    static const auto keyMap = std::unordered_map<int, Key> {
        { 'a', Key::A },
        { 'A', Key::A },
        { 'b', Key::B },
        { 'B', Key::B },
        { 'c', Key::C },
        { 'C', Key::C },
        { 'd', Key::D },
        { 'D', Key::D },
        { 'e', Key::E },
        { 'E', Key::E },
        { 'f', Key::F },
        { 'F', Key::F },
        { 'g', Key::G },
        { 'G', Key::G },
        { 'h', Key::H },
        { 'H', Key::H },
        { 'i', Key::I },
        { 'I', Key::I },
        { 'j', Key::J },
        { 'J', Key::J },
        { 'k', Key::K },
        { 'K', Key::K },
        { 'l', Key::L },
        { 'L', Key::L },
        { 'm', Key::M },
        { 'M', Key::M },
        { 'n', Key::N },
        { 'N', Key::N },
        { 'o', Key::O },
        { 'O', Key::O },
        { 'p', Key::P },
        { 'P', Key::P },
        { 'q', Key::Q },
        { 'Q', Key::Q },
        { 'r', Key::R },
        { 'R', Key::R },
        { 's', Key::S },
        { 'S', Key::S },
        { 't', Key::T },
        { 'T', Key::T },
        { 'u', Key::U },
        { 'U', Key::U },
        { 'v', Key::V },
        { 'V', Key::V },
        { 'w', Key::W },
        { 'W', Key::W },
        { 'x', Key::X },
        { 'X', Key::X },
        { 'y', Key::Y },
        { 'Y', Key::Y },
        { 'z', Key::Z },
        { 'Z', Key::Z },
        { '0', Key::Number0 },
        { ')', Key::Number0 },
        { '1', Key::Number1 },
        { '!', Key::Number1 },
        { '2', Key::Number2 },
        { '@', Key::Number2 },
        { '3', Key::Number3 },
        { '#', Key::Number3 },
        { '4', Key::Number4 },
        { '$', Key::Number4 },
        { '5', Key::Number5 },
        { '%', Key::Number5 },
        { '6', Key::Number6 },
        { '6', Key::Number6 },
        { '^', Key::Number6 },
        { '7', Key::Number7 },
        { '&', Key::Number7 },
        { '8', Key::Number8 },
        { '*', Key::Number8 },
        { '9', Key::Number9 },
        { '(', Key::Number9 },
        { '`', Key::Backtick },
        { '~', Key::Backtick },
        { '-', Key::Hyphen },
        { '_', Key::Hyphen },
        { '=', Key::Equal },
        { '+', Key::Equal },
        { '[', Key::LeftBracket },
        { '{', Key::LeftBracket },
        { ']', Key::RightBracket },
        { '}', Key::RightBracket },
        { '\\', Key::Backslash },
        { '|', Key::Backslash },
        { ';', Key::Semicolon },
        { ':', Key::Semicolon },
        { '\'', Key::Apostrophe },
        { '"', Key::Apostrophe },
        { ',', Key::Comma },
        { '<', Key::Comma },
        { '.', Key::Period },
        { '>', Key::Period },
        { '/', Key::Slash },
        { '?', Key::Slash },
        { ' ', Key::Space },
        { KEY_F(1), Key::F1 },
        { KEY_F(2), Key::F2 },
        { KEY_F(3), Key::F3 },
        { KEY_F(4), Key::F4 },
        { KEY_F(5), Key::F5 },
        { KEY_F(6), Key::F6 },
        { KEY_F(7), Key::F7 },
        { KEY_F(8), Key::F8 },
        { KEY_F(9), Key::F9 },
        { KEY_F(10), Key::F10 },
        { KEY_F(11), Key::F11 },
        { KEY_F(12), Key::F12 },
        { '\t', Key::Tab },
        { KEY_BTAB, Key::Tab },
        { KEY_BACKSPACE, Key::Backspace },
        { 127, Key::Backspace },
        { KEY_ENTER, Key::Enter },
        { 10, Key::Enter },
        { KEY_IC, Key::Insert },
        { KEY_DC, Key::Delete },
        { KEY_HOME, Key::Home },
        { KEY_END, Key::End },
        { KEY_NPAGE, Key::PageUp },
        { KEY_PPAGE, Key::PageDown },
        { KEY_UP, Key::UpArrow },
        { KEY_SR, Key::UpArrow },
        { KEY_DOWN, Key::DownArrow },
        { KEY_SF, Key::DownArrow },
        { KEY_LEFT, Key::LeftArrow },
        { KEY_SLEFT, Key::LeftArrow },
        { KEY_RIGHT, Key::RightArrow },
        { KEY_SRIGHT, Key::RightArrow },
    };

    static auto inputCallbacks = std::unordered_multimap<Key, std::function<void()>>();

    void bindInput(const std::initializer_list<Key> &keys, const std::function<void()> &callback) {
        for (const auto &key : keys) {
            inputCallbacks.insert({ key, callback });
        }
    }

    namespace Internal {
        void initializeInput() {
            keypad(stdscr, true);
            nodelay(stdscr, true);
            curs_set(0);
            noecho();
        }

        void processInput() {
            const auto key = keyMap.find(getch());
            if (key == keyMap.end()) {
                return;
            }

            for (const auto &callback : inputCallbacks) {
                if (callback.first == key->second) {
                    callback.second();
                }
            }
        }
    }
}
