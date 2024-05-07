# Liquid

Liquid는 2024년 국민대학교 C++프로그래밍 강의의 팀 프로젝트를 위해 ncurses를 기반으로 개발된 라이브러리입니다. Liquid를 사용하면 기존 C++ 지식을 사용해 앱 전체에서 재사용 가능한 컴포넌트를 빌드할 수 있습니다. Liquid는 **반응성**을 사용해 컴포넌를 향상시킬 수 있는 도구를 제공합니다.

Liquid 앱은 컴포넌트라 부르는 함수로 구성됩니다. 아래의 `Counter` 함수를 살펴보세요. 컴포넌트 내에서 `Text`라는 컴포넌트를 사용하고 있습니다. `Counter` 함수를 선언하면, 앱 전체에서 `Counter`를 사용할 수 있습니다. 

모든 Liquid 앱의 진입점은 render 함수입니다. 애플리케이션 코드를 래핑하는 함수와 렌더링 옵션(터미널 너비, 높이), 이렇게 2개의 인자를 필요로 합니다.

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
