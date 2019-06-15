---
layout: post
title: Оптимизация программ (`clang`, `perf`)
author: siri3us
categories: C++
---

Почему Clang хороший?
* Санитайзеры (`sanitizers`)
* Инфраструктура (`clang-format`, `clang-tidy`)

* LTO (Link-time-optimization)
* inline threshold


`perf`

-fno-omit-frame-pointer Не оптимизировать стек вызова функций. rbp обычно хранит адрес на начало
текущего фрейма, который в свою очередь хранит указатель на начало фрейма вызова выше. Может замедлить
выполнение программы на 2-3%. 

```
sudo perf record -g -p 
```

sudo нужен для получения адресов вызова в ядре

* -F, --freq Частота сэмплирования выполнения 
* -g Enables call-graph (stack chain/backtrace) recording
* --call-graph

Библиотека FlameGraph (на Perl-е)

Благодаря флагу

Настройка inline threshold

-O3 -march=native
