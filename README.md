# JSON_google.benchmark
## Постановка задачи

Реализовать разбор JSON-документа в представление в памяти с помощью генераторов парсеров 
[flex](https://github.com/westes/flex/) (лексический анализ) и [bison](https://www.gnu.org/software/bison/) (синтаксический анализ)
После разбора документа в память вывести результат поиска по заданному указателю [JSON Pointer](https://tools.ietf.org/html/rfc6901)

## Резултат
Результаты замеров предоставлены в output.txt, график на основе полученных данных выглядит следующим образом (шкала логарифмическая):

![log result plot](/plot.jpeg)

В loglog:

![loglog result plot](/loglogplot.jpeg)
