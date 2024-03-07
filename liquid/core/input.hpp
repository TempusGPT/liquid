#ifndef LIQUID_INPUT_HPP
#define LIQUID_INPUT_HPP

#include <functional>
#include <unordered_map>
#include <ncurses.h>

enum class Key
{
    None,
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

namespace Liquid
{
    std::unordered_map<int, std::function<void(const Key)>> inputCallbacks;

    void initInput()
    {
        keypad(stdscr, true);
        nodelay(stdscr, true);
        curs_set(0);
        noecho();
    }

    void notifyInput(const Key key)
    {
        for (const auto &callback : inputCallbacks)
        {
            callback.second(key);
        }
    }

    void processInput()
    {
        static std::unordered_map<int, Key> keyMap = {
            {'a', Key::A},
            {'A', Key::A},
            {'b', Key::B},
            {'B', Key::B},
            {'c', Key::C},
            {'C', Key::C},
            {'d', Key::D},
            {'D', Key::D},
            {'e', Key::E},
            {'E', Key::E},
            {'f', Key::F},
            {'F', Key::F},
            {'g', Key::G},
            {'G', Key::G},
            {'h', Key::H},
            {'H', Key::H},
            {'i', Key::I},
            {'I', Key::I},
            {'j', Key::J},
            {'J', Key::J},
            {'k', Key::K},
            {'K', Key::K},
            {'l', Key::L},
            {'L', Key::L},
            {'m', Key::M},
            {'M', Key::M},
            {'n', Key::N},
            {'N', Key::N},
            {'o', Key::O},
            {'O', Key::O},
            {'p', Key::P},
            {'P', Key::P},
            {'q', Key::Q},
            {'Q', Key::Q},
            {'r', Key::R},
            {'R', Key::R},
            {'s', Key::S},
            {'S', Key::S},
            {'t', Key::T},
            {'T', Key::T},
            {'u', Key::U},
            {'U', Key::U},
            {'v', Key::V},
            {'V', Key::V},
            {'w', Key::W},
            {'W', Key::W},
            {'x', Key::X},
            {'X', Key::X},
            {'y', Key::Y},
            {'Y', Key::Y},
            {'z', Key::Z},
            {'Z', Key::Z},
            {'0', Key::Number0},
            {')', Key::Number0},
            {'1', Key::Number1},
            {'!', Key::Number1},
            {'2', Key::Number2},
            {'@', Key::Number2},
            {'3', Key::Number3},
            {'#', Key::Number3},
            {'4', Key::Number4},
            {'$', Key::Number4},
            {'5', Key::Number5},
            {'%', Key::Number5},
            {'6', Key::Number6},
            {'6', Key::Number6},
            {'^', Key::Number6},
            {'7', Key::Number7},
            {'&', Key::Number7},
            {'8', Key::Number8},
            {'*', Key::Number8},
            {'9', Key::Number9},
            {'(', Key::Number9},
            {'`', Key::Backtick},
            {'~', Key::Backtick},
            {'-', Key::Hyphen},
            {'_', Key::Hyphen},
            {'=', Key::Equal},
            {'+', Key::Equal},
            {'[', Key::LeftBracket},
            {'{', Key::LeftBracket},
            {']', Key::RightBracket},
            {'}', Key::RightBracket},
            {'\\', Key::Backslash},
            {'|', Key::Backslash},
            {';', Key::Semicolon},
            {':', Key::Semicolon},
            {'\'', Key::Apostrophe},
            {'"', Key::Apostrophe},
            {',', Key::Comma},
            {'<', Key::Comma},
            {'.', Key::Period},
            {'>', Key::Period},
            {'/', Key::Slash},
            {'?', Key::Slash},
            {' ', Key::Space},
            {KEY_F(1), Key::F1},
            {KEY_F(2), Key::F2},
            {KEY_F(3), Key::F3},
            {KEY_F(4), Key::F4},
            {KEY_F(5), Key::F5},
            {KEY_F(6), Key::F6},
            {KEY_F(7), Key::F7},
            {KEY_F(8), Key::F8},
            {KEY_F(9), Key::F9},
            {KEY_F(10), Key::F10},
            {KEY_F(11), Key::F11},
            {KEY_F(12), Key::F12},
            {'\t', Key::Tab},
            {KEY_BTAB, Key::Tab},
            {KEY_BACKSPACE, Key::Backspace},
            {127, Key::Backspace},
            {KEY_ENTER, Key::Enter},
            {10, Key::Enter},
            {KEY_IC, Key::Insert},
            {KEY_DC, Key::Delete},
            {KEY_HOME, Key::Home},
            {KEY_END, Key::End},
            {KEY_NPAGE, Key::PageUp},
            {KEY_PPAGE, Key::PageDown},
            {KEY_UP, Key::UpArrow},
            {KEY_SR, Key::UpArrow},
            {KEY_DOWN, Key::DownArrow},
            {KEY_SF, Key::DownArrow},
            {KEY_LEFT, Key::LeftArrow},
            {KEY_SLEFT, Key::LeftArrow},
            {KEY_RIGHT, Key::RightArrow},
            {KEY_SRIGHT, Key::RightArrow},
        };

        const auto iter = keyMap.find(getch());
        const auto key = iter != keyMap.end() ? iter->second : Key::None;
        notifyInput(key);
    }
}

int onInput(const Key key, const std::function<void()> &callback)
{
    static auto newID = 0;
    const auto id = newID++;

    Liquid::inputCallbacks[id] = [=](const Key keyCode)
    {
        if (key == keyCode)
        {
            callback();
        }
    };

    return id;
};

void clearInput(const int id)
{
    Liquid::inputCallbacks.erase(id);
}

#endif
