---
layout: post
title: Агрегаты в C++
author: siri3us
categories: C++
---

Основано на докладе на конференции CppCon 2018 <span>"The Nightmare of Initialization in C++"</span>



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

[jekyll-docs]: https://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
