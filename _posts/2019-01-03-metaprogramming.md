---
layout: post
title: Метапрограммирование
author: siri3us
categories: C++
---

* decltype, auto: <https://habr.com/en/post/206458/>
* SFINAE, enable_if: <https://medium.com/@mortificador/choose-between-different-implementations-depending-on-type-properties-at-compile-time-in-c-68e3fd5cd2f8>

%%
template <typename T>
%%

type parameter

* type template parameter
* non-type template parameter
* 


* Шаблон (template). Просто кусок кода с шаблонным типом.
* Инстанциирование (instantiation) &mdash; процесс замены шаблона реальным кодом с конкретными типами
* В результае инстанциирования получается конкретный instance of template


Каждый шаблон проверяется в два этапа (two-phase lookup):
* В точке определения (definition time). На этом этапе проверяется все то, что может быть проверено без
явного знания шаблонных параметров
* В точке инстанциирования (instantiation time)

# Компиляция и линковка
**Inclusion model** &mdash; помещаем весь шаблонный код в заголовочные файлы. Таким образом, компилятор всегда может инстанциировать шаблон с требуемыми типами.

Плюсы: простота
Минусы: значительное увеличение времени компиляции, если для инстанцирования требуется подключать внешние заголовочные файлы.

* Precompiled headers
* Explicit instantiation


forward template declaration
```
template<typename T>
class C;

C<int>* p = nullptr;
```


### decltype

Очевидно, что decltype ведет себя по разному в trailing return type и вне его.

### Variable template (C++14)
