---
layout: post
title: Правило пяти, правило трех, правило нуля
author: siri3us
categories: C++
---

#### Accessors

* [[https://akrzemi1.wordpress.com/2015/09/08/special-member-functions/]]

* [[Mayers42]] По умолчанию сгенерированные функции %%inline%% и %%public%%. Все невиртуальные, кроме, возможно, деструктора. Деструктор виртуальный, если в базовом классе деструктор виртуальный.
* [[Mayers42]] Copy-конструктор и copy-присваивание независимы: объявление одного не препятствует автоматическому созданию другого (как в C++98, так и в C++11). 
* [[Mayers42]] Move-конструктор и move-присваивание связаны: если объявлено хотя бы одно, то и второе также требуется. Объявление лишь одной из этих функций приводит к пометке %%deleted%% для второй.
* [[Mayers42]] Объявление copy-конструктора блокирует создание move-конструктора. **Блокирует ли создание move-присваивания?** [???]
* [[Mayers42]] Move-присваивание не будет сгенерировано, если есть copy-присваивание [???]
* Объявление деструктора блокирует автоматическое создание move-конструктора и move-присваивания
* Объявление деструктора требует объявления copy-конструктора (иное поведение deprecated, начиная с C++11)
* Объявление деструктора не требуется объявления copy-присваивания (это странно, но оно так)
* Функции перемещения не будут неявно сгенерированы компилятором, если есть хотя бы одна явно объявленная функция из 5ки
* Функции копирования не будут сгенерированы, если есть хотя бы одна явно объявленная функция перемещения

Для исследования различных возможностей рассмотрим следующий код:
%%
struct A {
  // Everything is set to noexcept to model the automatic code generation
  A() noexcept { puts("A()"); }
  A(const A&) noexcept { puts("A(const A&)"); }
  A(A&&) noexcept { puts("A(A&&)"); }
  A& operator=(const A&) noexcept { puts("A& operator=(const A&)"); return *this; }
  A& operator=(A&&) noexcept { puts("A& operator=(A&&)"); return *this; }
  // Noexcept here is not necessary
  ~A() noexcept { puts("~A()"); }
};

struct S {
  S();
  ~S();
  S(const& S);
  S(S&&);
  S& operator(const& S);
  S& operator(S&&);

	A a;
};

int main() {
  S s1;                  // default constructor
  S s2 = s1;             // copy constructor
  S s3 = std::move(s1);  // move constructor
  s2 = s1;               // copy assignment
  s3 = std::move(s1);    // move assignment
  return 0;
}
%%


Везде ниже компиляция идет с флагом %%-Wdeprecated%%, но без %%-Werror%%. Это используется для того, чтобы проверить предположения о том, кто и кого блокирует, и какое поведение deprecated.

* Рассмотрим случай, когда у %%S%% вообще ничего не задано
%%
A()
A(const A&)
A(A&&)
A& operator=(const A&)
A& operator=(A&&)
%%
* <{Задан только деструктор у S..
%%
A()
A(const A&)
A(const A&)
A& operator=(const A&)
A& operator=(const A&)
%%
Здесь демонстрируется, что объявление деструктора блокирует создание move-операций.
При компиляции также будут предупреждения о том, что надо явно определить copy-операции у %%S%% для строк
%%
s2 = s1
s3 = std::move(s1);
%%
}>
* <{Задан только copy-конструктор у S (также задан дефолтный конструктор, иначе будет ошибка компиляции).
%%
A()
A(const A&)
A(const A&)
A& operator=(const A&)
A& operator=(const A&)
%%
Как и следовало ожидать, определение copy-конструктора заблокировало генерирование move-операций.
При компиляции будет предупреждение о том, что надо определить copy-присваивание у %%S%% для строки %%s2 = s1%%.
}>
* <{Задано только copy-присваивание у S
%%
A()
A(const A&)
A(const A&)
A& operator=(const A&)
A& operator=(const A&)
%%
Как и следовало ожидать, определение copy-присваивания заблокировало генерирование move-операций.
При компиляции будет предупреждение о том, что надо определить copy-присваивание у %%S%% для строки %%S s2 = s1%%.
}>
* <{Задан только move-конструктор у S
Ошибка компиляции. Определение move-конструктора привело к удалению copy-конструктора, copy-присваивания и move-присваивания. В результате все, что можем сделать, это
%%
S s1;                   // default-конструктор
S s2 = std::move(s1);   // move-конструктор
%%
}>
* <{Задано только move-присваивание у S
Ошибка компиляции. Определение move-присваивания привело к удалению copy-конструктора, copy-присваивания и move-конструктора. В результате все, что может сделать, это
%%
S s1;   // default-конструктор
S s2;   // default-конструктор
s2 = std::move(s1);
%%
}>
* <{Заданы copy-конструктор и copy-присваивание.
В данном случае нет предупреждений компиляции.
%%
A()
A(const A&)
A(const A&)
A& operator=(const A&)
A& operator=(const A&)
%%
}>
* <{Заданы move-конструктор и move-присвивание.
Будет ошибка компиляции, так как copy-конструктор и copy-присваивание удалены.
}>
* <{Заданы copy-конструктор, copy-присваивание и move-конструктор
В этом случае нет автогенерируемого move-присваивания. Оно автоматически сходит к copy-присваиванию:
%%
A()
A(const A&)
A(AA&)
A& operator=(const A&)
A& operator=(const A&)
%%
}>
* <{Заданы copy-конструктор, copy-присваивание и move-присваивание.
В этом случае нет автогенерируемого move-конструктора. Оно автоматически сходит к copy-конструктору:
%%
A()
A(const A&)
A(const A&)
A& operator=(const A&)
A& operator=(AA&)
%%
}>
* <{Задан copy-конструктор и move-конструктор.
Из-за move-конструктора удалено copy-присваивание.
}>
* <{Задан copy-конструктор и move-присваивание.
Из-за move-присваивания удалено copy-присваивание &mdash; ошибка компиляции.
}>
* <{Задан move-присваивание и copy-присваивание.
Из-за move-присваивания удален copy-конструктор &mdash; ошибка компиляции.
}>


### Препятствует ли объявление `= default` автоматическому созданию методов?
Стандарт дает однозначный ответ на этот вопрос: **да, препятствует**.
```
N3337 [class.copy]/9: If the definition of a class X does not explicitly declare a move constructor, one will be implicitly declared as defaulted if and only if
* X does not have a user-declared copy constructor,
* X does not have a user-declared copy assignment operator,
* X does not have a user-declared move assignment operator,
* X does not have a user-declared destructor, and
*the move constructor would not be implicitly defined as deleted.
```
Всякий раз, когда программист пишет, что какой-то из методов `= default`, это подходит под определение **user-defined**. Поэтому
```
struct S() {
	...
	~S() = default;
	...
}
```
заблокирует создание move-конструктора и move-присваивания. Copy-конструктор и copy-деструктор при необходимости будут созданы, но опять-таки наличие опции `-Wdeprecated` приведет к предупреждению, если эти операции где-то используются.
```
struct S() {
	~S() = default;
	S(const S&) = default;
	S(S&&) = default;
	S& operator=(const S&) = default;
	S& operator=(S&&) = default;
}
```
