# Liquid

Liquid는 2024년 국민대학교 C++프로그래밍 강의의 팀 프로젝트를 위해 개발된 라이브러리입니다. ncurses를 기반으로 개발되었으며, C++17을 사용합니다. 다음 Counter 예제를 `main.cpp`에 붙여넣고, 터미널에 `./run.sh` 명령어를 입력하여 실행 가능합니다.

```cpp
#include "liquid.hpp"

using namespace liquid;

auto Counter() -> Element {
    auto input = Input();
    auto count = State(0);

    input({ Key::Enter }, [=]() mutable {
        count = *count + 1;
    });

    return Text(GET("Count: %0%"_f % *count));
}

auto main() -> int {
    return render(Counter(), { 80, 25 });
}
```

## Reactivity

### State

### Effect

### Memo

## Components

### Basics

### Props

## Control Flow

### When

### Each
