---
layout: post
title: Модель памяти, атомарные переменные
author: siri3us
categories: C++
---


* https://habr.com/en/post/197520/
* https://preshing.com/20120913/acquire-and-release-semantics/

Три модели памяти:
* sequential consistency (последовательная согласованность)
* acquire/release семантика
* relaxed memory ordering (слабый порядок)

На самом деле порядок действий не тот, в котором он описан в вашем коде. 
Компилятор умеет оптимизировать действия. Процессор умеет оптимизировать действия.


int x, y, z;
(x + 1) + (y + 1) + (z + 1);

* Доступ к оперативной памяти 300ns
* Выполнение в порядке исходного кода &mdash; 900ns
* Можно переставить операции и выпонить код за 300ns

* На самом деле считываем сразу 3 значения, а потом складываем. В итоге
300ns

{% highlight cpp %}
bool a = false;
bool b = false;

// thread1
a = true;
b = true;

// thread2
printf("%d %d\n", a, b);

// thread3
printf("%d %d\n", a, b);
{% endhighlight %}

0 0
0 0

1 1
1 1

1 0
1 0

0 1
1 0

0 1
0 1

Все зависит от модели.

Компилятор переставляет местами действия
Процессор переставляет местами действия


Какое решение? Ввести Memory Model.
* Описывает взаимодействие потоков через
* 
* 
* Определяет границы "корректного" кода 

Модель памяти в приведенном примере говорит, что код некорректен.

В примере выше есть **data race**

Ячейка памяти &mdash; объект скалярного типа
* Конфликтующие действия &mdash; два или более действий над одной и той же ячейкой памяти, и по крайней мере одно из действий &mdash; запись.
* Data race &mdash; два или более неупорядоченных конфликтующих действий (без happensbefore)

Data race можно избежать с помощью `std::mutex` и `std::atomic<T>`

* Data race free variable
* Реализованы на уровне CPU, используя специальные инструкции
* Все операции изменяют операции атомарно
* К операциям может быть добавлен memory-barrier, создающий happens-before порядок для других переменных в текущем потоке
* Если работа ведется только c std::atomic<T>, то в коде не может быть data race-ов
* Все еще могут быть логические race-ы

Memory-barrier-ами можно управлять.
* Все операции выше барьера не могут просочиться ниже
* Все операции ниже барьера не могут просочиться выше

#### std::memory_order_seq_cst
* Тип барьера по умолчанию
* Самые сильные гарантии
* Все seq_cst опреаци со всеми переменнными выполняются в одном глобальном порядке


```
std::atomic<int> x;
int tmp = x.load(std::memory_order_seq_cst);
x.store(tmp + 1, std::memory_order_seq_cst);
```

#### std::memory_order_relaxed
* Нет барьера
* Все операции над ячейкой памяти выполняются атомарно
* Но операции могу быть переупорядочены с другими в данном потоке
* Нельзя использовать для синхронизации потоков
* Можно использовать, когда синхронизация не нужно
* Можно использовать, когда синхронизация достигается другими способами

* Атомарные переменные не позволяют "усыпить" поток, т.е. будут потребляться ресурсы, пока крутимся в цикле

{% highlight cpp %}
std::atomic<bool> a{false}, b{false};
auto order = std::memory_order_relaxed;

// thread 1
a.store(true, order); b.store(true, order);

// thread 2
printf("%d %d\n", a.load(order), b.load(order));

// thread 3
printf("%d %d\n", a.load(order), b.load(order));
{% endlighlight %}

Все также все ситуации могут быть, хотя data race-ов нет.


{% highlight cpp %}
std::atomic<bool> locked;

void lock() {
	while(locked.exchange(true)) {}
}

void unlock() {
	locked.store(false);
}
{% endlighlight %}

* std::memory_order_acquire Можно переезжать вверх, но нельзя вверх
* std::memory_order_release Можно переезжать вниз, но нельзя ввех

* T load()
* void store(T value)
* T exchange(T value)
* T fetch_add(T delta)
* T fetch_sub(T delta) 
* bool compare_exchange_strong(T& expected, T desired)
* bool compare_exchange_weak(T& expected, T desired)



