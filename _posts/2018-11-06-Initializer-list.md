---
layout: post
title: Инициализация в C++
author: siri3us
categories: C++
---

#### Источники
* https://habr.com/en/post/330402/
* Основано на докладе на конференции CppCon 2018 <span>"The Nightmare of Initialization in C++"</span>
*


{% highlight cpp %}
struct S {
  S() { puts("S()"); }
  S(int i) : i(i) { puts("S(int)"); }
  ~S() { puts("~S()"); }
  S(const S&) { puts("S(const S&)"); }
  S(S&&) { puts("S(S&&)"); }

  int i{0};
};

int main {
	std::cout << "Start of main" << std::endl;
  std::vector<S> vec = {1, 2, 3};
	std::cout << "End of main" << std::endl;
	return 0;
}
{% endlighlight cpp %}

* Что будет распечатно в данном коде?


 

Тот факт, что в коде присутствует запись вида
```
{val1, val2, ..., valN}
```
не означает, что будет сконструирован std::intializer_list. Он конструируется только тогда, когда он
действительно нужен.

* Нельзя создавть std::initializer_list из некопируемых объектов. Например, следующий код не скомпилируется
{% highlight cpp %}
#include <vector>
#include <memory>

struct S {
};

int main() {
	std::vector<std::unique_ptr<S>> vec{std::make_unique<S>(), 
	                                    std::make_unique<S>(),
	                                    std::make_unique<S>()};
	return 0;
}
{% endlighlight cpp %}

## Инициализация в C++98/C++03

#### Инициализация простых типов

Для начала посмотрим на уже известные стили инициализации:
{% highlight cpp %}
int i1;                        // undefined value
int i2 = 41;                   // здесь все хорошо
int i3 = 42.8;                 // note: narrows down to 42
unsigned int ui1 = -1;         // возможно, но совсем нехорошо
{% endhighlight %}
Данный код представляет собой __старый стиль инициализации__ (о новом стиле поговорим дальше).
Конкретно к коду выше есть две претензии: потенциальное использование неинициализированной переменной (`i1`) и
сужающее преобразование типа (для `i3` и `ui1`). Так что скомплировав данные строки с помощью команды
```
g++ main.cpp -o main
```
можем получить следующий вывод для `./main`:
```
i1 = 0
i2 = 42
i3 = 59
ui1 = 4294967295
```
(Конкретное значение для `u1` зависит от размерности `unsigned int` в системе).
Но благо разработчики компилятора GCC позаботились о нас и можно просто не позволить программе скомпилироваться,
указав следующие опции при компиляции `-Wall -Wconversion -Werror`:
```
g++ main.cpp -o main -Wall -Wconversion -Werror
```
Вместо весьма общего флага `-Wconversion` для запрета неявного преобразования от формата с плавающей запятой к целому типу
можно указать опцию `-Wfloat-conversion`, но в таком случае не будет "поймано" преобразование от `-1` к беззнаковому типу.
Здесь нужна опеция `-Wsign-conversion`.

#### Инициализация массивов

{% highlight cpp %}
int values[] = {1, 2, 3}; // initialization of aggregates
{% endhighlight %}

{% highlight cpp %}
int i3(42.9);                      // initializes with 42
int i4 = int();                    // initializes with 0
{% endhighlight %}

#### Инициализация объектов
{% highlight cpp %}
std::complex<double> c(1.0, 2.0);  // initialization of classes
std::vector<std::string> cities;
cities.push_back("Moscow");
cities.push_back("Saint-Petersburg");
{% endhighlight %}

Как понять

### Однообразный способ инициализации
{% highlight cpp %}
int i1;
int i2 = 42;
int i3(42);
int i4 = int();
{% endhighlight %}

И вот получаем еще кучу способов
{% highlight cpp %}
int i5{};
int i6{42};
int i7 = {42};
int i8 = {};
int i9 = int{};
{% endhighlight %}

Возможно кто-то мог бы на этом остановиться, но только не мы: берем на вооружение `auto`
и продолажем инициализации:
{% highlight cpp %}
auto i10 = 42;            // int со значением 42
auto i11{42};             // результаты отличаются для C++11 и C++14
auto i12 = {42};          // std::initializer_list<int> с единственным элементом 42
auto i13 = int{42};       // int со значением 42 (но кто так делает!?)
{% endhighlight %}

На самом деле это еще далеко не конец
{% highlight cpp %}
int i14 = (4, 5);         // int со значением 5
int i15 = (1, 2, 3);      // int со значением 3
auto i16 = (7, 9);        // int со значением 9
{% endhighlight %}


{% highlight cpp %}
int i17();                // функция
int i18(1, 2);            // compile-time error
int i19 = int(7, 9);      // compile-time error
auto i20(7, 9);           // compile-time error
{% endhighlight %}

Правило: если есть возможность, не стоит использоваить ()-инициализацию

### Проблемы с auto
```
auto i9 = 42;             // int со значением 4
auto i10{42};             
auto i11{42, 43};
```

`auto i10{42}` делает не то, что ожидается.

Тем не менее было принято решение оставить результат
```
auto i12 = {42};
```
тем же самым

{% highlight cpp %}
std::initializer_list<auto> l = {42} // OK since C++32
auto a[] = {42};                     // OK since C++23?
{% endhighlight %}

Рекомендация: не использовать = в инициализациях

### AAA (Almost Always Auto)
Таким образом, приходим к следующей рекомендации: использовать `auto` почти всегда.

{% highlight cpp %}
auto x = ...;
using T = ...;
{% endhighlight %}

* `auto` следует использовать, если не тип сам по себе не важен.
```
auto x = __initializer__;
```
Например, неважно, какой контейнер будет использоваться, важно лишь то, что у него есть
методы `begin()` и `end()`

Но если тип все таки явно нужен, то можно сделать так:
```
auto x = __type{expr}__;
```

Последняя запись несколько озадачивает: раз тип так или иначе уже появился в записи, то может
лучше сделать так
```
__type__ x(__expr__);
```

{% highlight cpp %}
int i = 42;
long v = 42;
Customer c{"Jim", 77};
std::vector<int>::const_iterator p = v.begin();
{% endhighlight %}

{% highlight cpp %}
auto i = 42;
auto v = 42l;
auto c = Customer{"Jim", 77};  // ?
auto p = v.cbegin();
{% endhighlight %}

```
std::string x = "42"
```

```
using namespace str::literals;
auto x = "42"s;
```

std::atomic<int> a{9};
std::array<int, 6> r{};

В C++17 данная проблема была решена.
```
auto a = std::atomic<int>{9};
auto r = std::array{};
```

```
long long ll{getInt()};
```

```
auto ll = long long{getInt()}; // ERROR
auto ll = int64_t(getInt());   // may be different type
auto ll = static_cast<long long>(getInt()); // works but too verbose
```
Во всех случаях полчим не то, что нужно
* Синтаксическая ошибка: так с чего же данное выражение вдруг должно стать корректно, оказавшись
в правой части.
* int64_t может отличаться от `long long`. Здесь нет никаких гарантий.
* Работает, но слишком длинно.

```
auto r = static_cast<const C&>(foo());   // different
auto& r = static_cast<const C&>(foo());  // OK
auto&& r = static_cast<const C&>(foo()); // OK
```

AAAA (Always Auto&&)

temprary materialization conversion &mdash; созданием константной ссылки
на временное значение мы фактически его материализуем.

Copy elision с C++17 стало обязательным (P0135). Но надо понимать, что
таким образом при компиляции с флагом -std=gnu++17 уже не получится
вернуть в себе явный вызов конструкторов указав опцию -fno-copy-elision

### Достоинства равномерной инициализации
```
template <typename T>
void foo() {
  T x1();       // Это вообще функция
  T x2 = T();   // Не выглядит как инициализация
  T x3{};       // Доступно с C++11
}
```

#### Most Vexing Parse
```
using namespace std;
vector<int> v(istream_iterator<int>(cin), istream_iterator<int>()); // Обяъявление функции
cout << v.size() << '\n';      // Ооочень большая ошибка...
```
```
vector<int> v((istream_iterator<int>(cin)), (istream_iterator<int>()));
```

```
vector<int> v{istream_iterator<int>(cin), istream_iterator<int>()};
```

Check out the [Jekyll docs][jekyll-docs] for more info on how to get the most out of Jekyll. File all bugs/feature requests at [Jekyll’s GitHub repo][jekyll-gh]. If you have questions, you can ask them on [Jekyll Talk][jekyll-talk].


[jekyll-docs]: https://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
