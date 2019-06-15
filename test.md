---
layout: default
title: 'Not Awesome Shoes'
---

{% if page.title == 'Awesome Shoes' %}
  These shoes are awesome!
{% endif %}

{% unless page.title == 'Awesome Shoes' %}
  These shoes are not awesome.
{% endunless %}

<table>
{% assign numbers = '1 2 3 4' | split: ' ' %}
{% tablerow number in numbers %}
{{ number }}
{% endtablerow %}
</table>
