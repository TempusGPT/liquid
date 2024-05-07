# Liquid

1. [Introduction](#introduction)
2. [Reactivity](#reactivity)
3. [Components](#components)
4. [Control Flow](#control-flow)

## Introduction

Liquid는 2024년 국민대학교 C++프로그래밍 강의의 팀 프로젝트를 위해 ncurses를 기반으로 개발된 라이브러리입니다. Liquid를 사용하면 기존 C++ 지식을 사용해 앱 전체에서 재사용 가능한 컴포넌트를 빌드할 수 있습니다.

모든 Liquid 앱의 진입점은 `render` 함수입니다. `render` 함수의 첫 번째 인자로는 컴포넌트라 부르는 함수를, 두 번째 인자로는 터미널 너비와 높이 등의 옵션을 필요로 합니다.

```cpp
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

State는 Liquid에서 반응성의 토대가 됩니다. State는 `*`, `->`, `=` 연산자를 포함합니다. State에 값을 할당하면 해당 State를 사용하는 모든 것이 자동으로 업데이트됩니다.

```cpp
auto count = State(0);
auto doubled = State(0);
```

다음으로, 컴포넌트 내에서 State 값을 사용합니다. Liquid에서는 문자열 뒤에 `_f`를 붙여 포맷 문자열로 지정하고, `%` 연산자를 사용하여 변수 값을 삽입할 수 있습니다.

```cpp
return Text("Count: %0%"_f % *count);
```

State를 단순히 컴포넌트의 인자로 넘기면 해당 State 값이 변경될 때 자동으로 업데이트되지 않습니다. `GET` 매크로를 사용하여 State 값이 변경될 때 실제로 화면에 반영되도록 할 수 있습니다.

```cpp
return Text(GET("Count: %0%"_f % *count));
```

### Effect

Effect는 관련 State의 값이 변경될 때마다 재실행되는 함수입니다. Effect는 옵저버 중 하나이며, State에 의존하는 사이드 이펙트를 실행합니다.

```cpp
auto effect = Effect();

effect([=]() {
    doubled = *count * 2;
});
```

Liquid는 Effect 함수의 반환값을 클린업 함수로 사용합니다. 클린업 함수는 컴포넌트가 언마운트될 때 실행되며, 사용한 리소스를 정리하는 용도로 사용할 수 있습니다.

```cpp
effect([=]() {
    auto timer = setInterval(1000, [=]() mutable {
        count = *count + 1;
    });

    return [=]() { clearTimer(timer) };
});
```

### Memo

Memo는 캐시된 계산 값으로, State와 Effect의 속성을 공유합니다. 관련 State가 변경되었을 때만 다시 실행되며, Memo 자체도 추적 가능한 State입니다.

```cpp
auto doubled = Memo(GET(*count * 2));
```

## Component

### Core

### Props

## Control Flow

### When

### Each
