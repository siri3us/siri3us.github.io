---
layout: post
title: Преобразование типов в C++
author: siri3us
categories: C++
---

Основано на докладе на конференции CppCon 2018 <span>"The Nightmare of Initialization in C++"</span>

Старый способ преобразования `(type) value` &mdash; самый "настырный" способ преобразования. Если даже он не работает,
то ситуацию уже ничто не спасет.

### `const_cast`

Может убрать cv-квалификаторы (**c**onst, **v**olatile). Примеров с volatile не знаю &mdash; пока с данным
квалификатором не имел дела. А вот необходимость убрать константность время от времени возникает.

TODO: пример из mayers-а

{% hightlight cpp %}
class SomeClass {
  Getter
}
{% endhightlight %}

Вообще, это единственная ситуация, в которой я когда-либо использовал `const_cast`.

* Что будет, если снять `const` с переменной, которая с момента своего создания была `const`?
* Может добавить `const` или убрать `const`. А зачем добавлять с помощью `const_cast`?

TODO about `volatile`

TODO Put into hidden part

Достаточно часто в процессе обучения языку C++ просят реализовать свои классы-аналоги для std::vector и std::deque.
Между данными классами есть принципиальное различие: в vector-е данные хранятся последовательно в одном C-style массиве,
а в deque-е блоками (chunks, blocks), причем далеко не смежнами. Если на то пошло, то в простейшем виде deque &mdash;
это список из блоков.

Стоит понимать, что в отличие от vector-а память в deque хранится не последовательно, а блоками (chunks, blocks), поэтому
функция доступа `const T& operator[](size_t index)` это не просто 

Мы могли бы реализовать класс вектор в следующем виде:
{% highlight cpp %}
template <typename T>
class Vector {
  public:
    ...
    const T& operator[](size_t index) const {
      return data_[index];
    }
    T& operator[](size_t index) const {
      return data_[index];
    }
    ...
  private:
    T* data_;
    std::size_t size_;
};
{% endhighlight %}

{% highlight cpp %}
class Deque {
  public:
    ...
    const T& operator[](size_t index) const {
      // Здесь много строк с поиском трубемого элемена
      return chunks_[chunk_index][element_index];
    }
    T& operator[](size_t index) const {
      return const_cast<T&>(static_cast<const Deque&>(*this)[index]);
    }

  private:
    T** chunks_;
};
{% endhighlight %}

### `static_cast`
Один из наиболее часто встречающихся способов преобразования типа в C++.

Может быть использован для приведения одного типа к другому. Если это встроенные типы, то будут использованы встроенные в C++ правила их приведения. Если это типы, определенные программистом, то будут использованы правила приведения, определенные программистом.

static_cast между указателями корректно, только если один из указателей - это указатель на void или если это приведение между объектами классов, где один класс является наследником другого. То есть для приведения к какому-либо типу от void*, который возвращает malloc, следует использовать static_cast.

Преобразования типов, которые позволяет совершать `static_cast`
* Допустимые приведения между **не указателями**:
  * Допустимые преобразования встроенных типов (int -> char, signed -> unsigned и т.п.)
  * Преобразования между пользовательскими типами с использованием правил приведения, определенных программистом.
  * Преобразование от типа наследника к типу прародителю (от Derived к Base)
*  Допустимые приведения между **указателями**:
  * static_cast между указателями корректен, только если один из указателей &mdash; это указатель на void.
  * Преобразование от Derived* к Base* и от Base* к Derived* (один из классов является наследником другого)

`static_cast` не может убрать cv-qualifiers (`const` и `volatile`).

#### malloc: C vs C++
Язык C++ не столь лояльно относится к преобразованиям между типами указателей, как язык C. В частности
при мигрировании с C на C++ возникает ошибка компиляции в следущем коде:
```
int* p = malloc(1000);
```
Конечно, решить данную проблему можно в стиле C:
```
int* p = (int*) malloc(1000);
```
Но раз уж принято решение о переходе на C++, то гораздо лучше использовать более явное приведение
```
int* p = static_cast<int*>(malloc(1000));
```


Если приведение не удалось, возникнет ошибка на этапе компиляции. Однако, если это приведение между указателями на объекты классов вниз по иерархии и оно не удалось, результат операции undefined. То есть, возможно такое приведение: static_cast<Derived*>(pBase), даже если pBase не указывает на Derived, но программа при этом будет вести себя странно.


### `dynamic_cast`

Вокруг `dynamic_cast` много непонятного, особенно касательно скорости его работы.


### `reinterpret_cast`

Здесь я знаю только одно место когда может потребоваться использовать `reinterpret_cast`:
когда нужно преобразование между `uintptr_t` и указателем на некоторый тип. `uintptr_t` &mdash;
интегральное значение, достаточное для хранения указателя (32-битное беззнаковое целое на x86,
и 64-битное беззнаковое целое на x64). 
```
uintptr_t ptr = reinterpret_cast<uintptr_t>(p);
p = reinterpret_cast<T*>(ptr);
```

Для меня reinterpret_cast служил неким способом изучения расположения объектов в памяти. Для этого
была написана следующая функция

{% highlight cpp %}
template <typename T>
void PrintMemoryLayout(const std::string& name, const T& object, size_t n_cols = 8) {
  unsigned char* ptr = (unsigned char*)(&object);
  const size_t size = sizeof(T);
  bool end_of_line = false;
  std::cout << "The layout of type \"" << name << "\" with size " << std::dec << size << ":\n";
  for (size_t byte_index = 0; byte_index < size; ++byte_index) {
    auto byte_ptr = ptr + byte_index;
    std::cout << std::setw(2) << std::setfill('0') << std::uppercase << std::hex
              << static_cast<int>(*byte_ptr) << " ";
    if ((byte_index + 1) % n_cols == 0) {
      std::cout << '\n';
      end_of_line = true;
    } else {
      end_of_line = false;
    }
  }
  if (end_of_line) {
    std::cout << std::dec << std::endl;
  } else {
    std::cout << std::dec << std::flush;
  }
}
{% endhighlight %}

### Приведение типов в старом стиле
* `(new_type) expression`

C++ добавил наследование и полиморфизм, что

C-style Casts

A C-style cast in C++ tries the following casts in order, using the first C++ cast that works:

*    const_cast
*    static_cast
*    static_cast, then const_cast (change type + remove const)
*    reinterpret_cast
*    reinterpret_cast, then const_cast (chagne type + remove const)

Note that dynamic_cast is never considered when using a C-style cast.

### Зачем вообще нужны привдения нового типа
* Лучшая читаемость: старый стиль гораздо сложнее идентифицировать в коде
* Логическое разбиение работы C-style преобразования на уровни. С наличием в C++ наследования
и полиморфизма возникает потребность в более "тонких" инструментах преобразования типа. Выше
была приведена последовательность C++-style преобразований, которым эквивалентно C-style преобразованием.
Как можно понять, C-style преоб

Лучший отлов ошибок.

Читаемость.
```
double d = (double) 10/20;
```
Что будет записано в d: 0 или 0.5. Разумеется, можно открыть таблицу приоритетов операндов, но гораздо проще
написать
```
double b = static_cast<double>(10) /20;  // C++ style cast
```
Альтернативный вариант
```
double b = 10. / 20;                     // C++ style implicit cast
```

### Выводы

А теперь немного формальных (и не очень) выводов
* const_cast &mdash;
* static_cast &mdash;
* dynamic_cast &mdash;
* reinterpret_cast --- отбойный молоток, которым можно забить любой шуруп (да-да, именно шуруп): главное, чтобы подходил размер отверстия.
С помощью reinterpret_cast как и C-cast можно творить самые ужасные (и не очень) вещи с памятью.

* Побайтовое конструирование объектов
* Замена указателя на виртуальную таблицу у полиморфных объектов
* Чтение стековых фреймов: создаем в функции переменную `int a`. По идее она должна лежать в нижней точке стека, а до нее должен
идти адрес возврата из функции.

{% highlight cpp %}
int i1;                   // undefined value
int i2 = 42.8;            // note: narrows down to 42
int values[] = {1, 2, 3}; // initialization of aggregates
{% endhighlight %}


{% highlight cpp %}
std::complex<double> c(1.0, 2.0);  // initialization of classes
int i3(42.9);                      // initializes with 42
int i4 = int();                    // initializes with 0
{% endhighlight %}

Check out the [Jekyll docs][jekyll-docs] for more info on how to get the most out of Jekyll. File all bugs/feature requests at [Jekyll’s GitHub repo][jekyll-gh]. If you have questions, you can ask them on [Jekyll Talk][jekyll-talk].

### Вопросы
Данный раздел посвящен некоторым вопросам, которые возникали у меня в процессе изучения
преобразования типов в C и C++.

* Что будет, если изначально константную переменную попытаться изменить, применив `const_cast`?
{% highlight cpp %}
const int a = 10;
int* pa = static_const<int*>(&a);
*pa += 1;
std::cout << *pa << " " << a << std::endl;
{% endhighlight %}
А вот и вывод программы:
```
11 10
```
Что же произошло? Ответ нашелся на [stackoverflow][changing-const-variable] (ну еще бы!). Если вкратце, то компилятор,
зная, что переменная `a` &mdash; константа, заменяет ее в коде, т.е. вместо строки
```
std::cout << *pa << " " << a << std::endl;
```
мы по сути получаем
```
std::cout << *pa << " " << 10 << std::endl;
```
В общем случае стандарт утверждает, что результат подобной операции &mdash; **неопределенное поведение** ($5.2.11/7).
На практике же все зависит от того, в какую область памяти будет помещено константное значение. Если в защищенную, то
выполнение программы скорее всего программа просто упадет. На самом деле в планах изучить бинари и посмотреть, что и куда
помещается.


[changing-const-variable]: https://stackoverflow.com/questions/19208560/can-we-use-const-cast-to-modify-a-constant-variable

[C++ Casting, or: "Oh No, They Broke Malloc!"]: https://embeddedartistry.com/blog/2017/2/28/c-casting-or-oh-no-we-broke-malloc
[Reinterpret cast Trap]: https://blog.galowicz.de/2017/01/22/reinterpret_cast_trap/
[Virtual Method Table and accident prevention]: http://www.cplusplus.com/articles/iy6AC542/
[C++ style cast]: http://cppblogs.blogspot.com/2013/08/c-style-casts.html
