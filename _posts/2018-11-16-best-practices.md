---
layout: post
title: Преобразование типов в C++
author: siri3us
categories: C++
---

* CppCon 2017 <span<"Practical C++17"<span> <https://www.youtube.com/watch?v=nnY4e4faNp0&t=33s>
* Основано на докладе на конференции CppCon 2018 <span>"Applied Best Practices"</span>



#### Accessors

%%
template <typename Type, typename CRTP>
struct StronglyTyped {
  const Type data_;
};
%%
**Проблема:** константность значительно снижает возможности по использованию.

В качестве решения можно воспользоваться функциями доступа (accessors). Но тут возникает дилемма:
стоит ли возвращать значение по константной ссылке или значению:
%%
template <typename Type, typename CRTP>
struct StronglyTyped {
 public:
  auto Value() { return value_; }
  const auto& Value() { return value_; }
 protected:
  Type data_; // reduces usabitly
};
%%

Возврат по значению подходит для небольших тривиальных типов, например встроенных. Но что если кто-то
передаст в качестве типа %%Type%%, например, строку %%std::string%% или %%std::vector<int>%%? Можно избежать этой ситуации
поставив проверку на этапе компиляции
%%
template <typename Type, typename CRTP>
struct StronglyTyped {
 public:
  // enforce the expectation of trivial type
  static_assert(std::is_trivial_v<Type>);
  auto Value() { return value_; }
 protected:
  Type data_; // reduces usabitly
};
%%

Тривиальный тип: trivially copyable, trivially constructable, trivially movable.
Мы ничего не определили, а автоматические операции не бросают исключения.

Но мы кое что упустили:
* Что относительно константности функции доступа
* Что относительно безопасности исключений
* Раз имеем дело с тривиальным типом, может имеет смысл сделать функцию доступа constexpr
* А что если не используем значение (%%[[nodiscard]]%%)?
Очевидно, что с точки зрения архитектуры функция доступа должна быть константной (мы ведь не меняем объект).
Так что в случае тривиальных типов функция безопасна относительно исключений. Поэтому приходим к следующему коду:
%%
template <typename Type, typename CRTP>
struct StronglyTyped {
 public:
  // enforce the expectation of trivial type
  static_assert(std::is_trivial_v<Type>);
  [[nodiscard]] constexpr auto Value() const noexcept { return value_; }
 protected:
  Type data_; // reduces usabitly
};
%%

%%
/// A
[[nodiscard]] constexpr auto Value() const noexcept { return value_; }
/// B
[[nodiscard]] constexpr auto Value() const noexcept -> Type { return value_; }
/// C
[[nodiscard]] constexpr Type Value() const noexcept { return value_; }
%%

#### Trailing return types

%%
[[nodiscard]] constexpr auto Value() const noexcept -> Type;
[[nodiscard]] constexpr auto Op() const noexcept -> std::pair<bool, uint32_t>;
[[nodiscard]] constexpr auto Type() const noexcept -> OpType;
%%

%%
[[nodiscard]] constexpr Type Value() const noexcept;
[[nodiscard]] constexpr std::pair<bool, uint32_t> Op() const noexcept;
[[nodiscard]] constexpr OpType Type() const noexcept;
%%

Trailing return types
* Удобнее увидеть имя типа
* Удобнее возвращать вложенный тип


Что не может быть %%constexpr%%?

Недостатки %%constexpr%%:
* Увеличение времени компиляции?
* Увеличение памяти?

На практике время компиляции связано с
* Большая тиблица символов
* Длинные имена, большое количество символов

С помощью %%constexpr%% можно поймать undefined behavior
%%

int main() {
  return
}
%%


### C++ defaults
%%
[[nodiscard]] constexpr auto Value() const noexcept -> TYpe { return value_; }
%%

%%

%%

### Выводы
* %%constexpr%%, %%[[nodiscard]]%%
* 
* Чтобы проверить, что все действительно %%constexpr%%, нужны %%constexpr%%-тесты
* %%constexpr%% может поймать undefined behaviour на этапе компиляции
* clang-format

### Система сборки и флаги компиляции
Важно на самом старте проекта использовать все флаги компиляции с предупреждениями
%%g++ -std=gnu++17 

%%-Wconversions%%

#### Предупреждения со %%switch%%-ами

%%
enum class Types { Option1, Option2 };

auto Process(Types t) {
  switch (t) {
    case Types::Option1: return handle(T1{t});
    case Types::Option2: return handle(T2{t});
  }
}
%%

%%
enum class Types { Option1, Option2 };

struct T1 { Types v; };
struct T2 { Types v; };

int handle(T1);
int handle(T2);

auto Process(Types t) {
  switch (t) {
    case Types::Option1: return handle(T1{t});
    case Types::Option2: return handle(T2{t});
  }
}
%%
В этом случае компилятор GCC генерирует код с фактически одним if-ом (можно посмотреть дизассемблировав полученный бинарь).


Но что будет в этом случае 



%%
enum class Types { Option1, Option2, Option3 };

struct T1 { Types v; };
struct T2 { Types v; };

int handle(T1);
int handle(T2);

auto Process(Types t) {
  switch (t) {
    case Types::Option1: return handle(T1{t});
    case Types::Option2: return handle(T2{t});
  }
}
%%

Компилятор делает то же самое, т.е. генерирует тот же ассемблерный код. Но тогда
получается следующее. Если на вход пришла Option1, то будет возвращен handle(T1{t}), а если **не Option1**, то handle(T2{t});

%%
enum class Types { Option1, Option2, Option3 };

struct T1 { Types v; };
struct T2 { Types v; };

int handle(T1);
int handle(T2);

auto Process(Types t) {
  switch (t) {
    case Types::Option1: return handle(T1{t});
    case Types::Option2: return handle(T2{t});
  }
}

int main() {
  process(static_cast<Types>(3));
}
%%

Not all paths return a value

[dcl.enum]

%%
enum class Types { Option1, Option2, Option3 };

struct T1 { Types v; };
struct T2 { Types v; };

int handle(T1);
int handle(T2);

auto Process(Types t) {
  switch (t) {
    case Types::Option1: return handle(T1{t});
    case Types::Option2: return handle(T2{t});
  }
  assert(!"Cannot reach here!");
  // abort(); ?
  // throw ; No, the function must remain constexpr
}
%%



%%cmake-format%% --- форматриование для Cmake-а

  return Eigen::Quaterniond(Eigen::AngleAxisd(Yaw(state), Eigen::Vector3d::UnitZ()));


### Structured bindings
{% highlight cpp %}
auto [a, b, c] = {expression};
{% endhighlight %}

```
std::string func() {
	auto value = get_some_string();
	return value;
}

std::string func() {
	auto value = get_some_string();
	return std::move(value); // Breaks NRVO since move is forced
}
```

```
std::string func() {
	auto pair = get_some_pair();
	return pair.second;  // Cannot apply NRVO to subobject
}

std::string func() {
	auto pair = get_some_pair();
	return std::move(pair.second);
}
```


```
std::string func() {
	auto [succeeded, value] = get_some_pair();
	// auto pair = get_some_pair();
	// auto& succeeded = pair.first;
	// auto& value = pair.second;
	return value;  // Cannot apply NRVO to subobject
}

std::string func() {
	auto [succeeded, value] = get_some_pair();
  // auto pair = get_some_pair();
	// auto& succeeded = pair.first;
	// auto& value = pair.second;
	return std::move(pair.second);
}
```

### if-init expressions
* https://skebanga.github.io/if-with-initializer/

Область видимости одна и та же для всех веток.
```

```

{% highlight cpp %}

{
	auto&& value = get_some_value();
	if (value > 5) {

	} else {
	
	}
}
{% endhighlight %}

#### emplace_back
```
container.emplace_back();
auto& value = container.back();
```

```
auto& value = container.emplace_back();
```

### string_view

#### Nested namespaces
```
namespace Namespace::Nested {

}
```

