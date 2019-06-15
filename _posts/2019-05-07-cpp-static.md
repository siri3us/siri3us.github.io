---
layout: post
title: Спецификатор static
author: siri3us
categories: C++
---

* https://stackoverflow.com/questions/4590626/c-static-variables-in-multithreaded-program
* Видео Джейсена Тернера: <https://www.youtube.com/watch?v=B3WWsKFePiM>
* https://www.modernescpp.com/index.php/thread-local-data
* https://pabloariasal.github.io/2019/02/28/cpp-inlining/
* https://eli.thegreenplace.net/2011/08/30/construction-of-function-static-variables-in-c-is-not-thread-safe

# Статические переменные классов

static 
* Глобальная переменная
* Глобальная функция
* Локальная переменная



```
[inline] [static] [const|constexpr] {type} {id} [ = {initializer} ];
```

{% highlight cpp %}
int a;
int b = 0;
static int c;
static int d = 1;
static const int e;
static const int f = 2;
{% endhighlight %}

А еще вся эта конструкция может находиться внутри структуры, объявляя (определяя) таким образом статический элемент данных (static member):
```
struct S {
	[inline] [static] [const|constexpr] {type} {id} [ = {initializer} ];
};
```
Подобное многообразие может ввести в заблуждение не только новичков в программировании на C++, но и бывалых разработчиков. Поэтому попробуем разобраться со смыслом
каждого из используемых спецификаторов.

Если у статической переменной нет инциализатора, то так или иначе ее придется определить вовне, где и будет предоставлен инициализатор.
```
struct S {
	static int uninit_a;
	static const int const_uninit_b;
};
```

Далее временно забудем о существовании ключевого слова `constexpr` и будем рассмативать все остальные слуаи.


### Ключевое слово inline
Ключевое слово inline позволяет избежать проблемы с множественными определениями одной и той же сущности.
```
struct S {
	inline static const int value = 777;
};
```
или
```
struct S
{
    static const int sValue;
};

inline int const S::sValue = 777;
```

Начиная с C++17 ключевое слово constexpr, примененное к стаитческому элементу данных, подразумевает inline

#### Неконстантные статические переменные
{% highlight cpp %}
struct S {
    static int value;   // It is a declaration!
};

int S::value = 15;      // It is a definition!
{% endhighlight %}
Инициализация неконстантных статических элементов в теле класса запрещена во всех версия стандарта [TODO check]
А что если элемент inline?

Каждый expression является либо unevaluated expression или potentially evaluated expression. Иного не дано. 

* `static`. В этом случае нужно определение и объявление. Если нет инициализатора, то [TODO: zero initialized?]
* `static const`. Просто `const` не являюется исключением из ODR-правила. Поэтому требуется как объявление, так и определение. Где именно
при этом расположен initializer не важно.
* `static constexpr` [>= С++11]. В отличие от `const` требуется `in-class initializer`.



* `constexpr` всегда вынуждает писать initializer в точке декларации. Вопрос лишь в необходимости 
наличия определения. До С++17 определение требовалось, с C++17 больше не требуется.

В С++17 `constexpr` в определенном смысле равен `const + inline`, так как
* `constexpr` теперь неявно `inline`
* `constexpr` требует инициализации на месте.

Когда не нужен out-of-class definition:
* `C++17`:
	* `inline static int n = 1`
	* `constexpr static int n = 1` В С++17 `static constexpr` подразумевается `inline`


В C++03 создание локальной статической переменной не было потокобезопасным. Ситуация изменилась с выходом C++11,
где процесс инициализации статической переменной является потокобезопасным (согласно **разделу 6.7** стандарта)

Доступ:
* При входе в блок видимости локального статического объекта всякий раз приходится проверять, инициализирован ли данный объект.
Очевидно, это занимает вычислительный ресурсы. Если обращений много, то это может существенно тормозить выполнение.
* Компилятор не может оптимизировать статические переменные, так как они могут быть изменены из других потоков.

* Является ли . Но важно, чтобы была поддержка
компилятора.
* Процесс доступа и обновления потокобезопасным не является

Если знаем, что у нас ровно один поток и нет смысла вводить дополнительные guard-ы и проверки, то можно передать компилятору опцию
`-fno-threadsafe-statics` (только следует проверить, что компилятор ее поддерживает).


{% highlight cpp %}
struct S {
	static std::string&
};
{% endhighlight %}


Компилятору глубоко... наплевать на ваше мнение о inline-ах
* __attribute((always_inline))
* __attribute((no_inline))

### thread_local

### Статические переменные в лямбдах
