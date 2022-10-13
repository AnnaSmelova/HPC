## Домашнее задание №4: ДЗ-4

### Сгенерируйте случайные графы и протестируйте пересчет числа маршрутов в графе через вычисление степени матрицы связности $A^m$.
Реализуйте через быстрое возведение в степень за $log_2(m)$ 
матричных умножений.<br><br>
[matpow_project](https://github.com/AnnaSmelova/HPC/tree/main/hw4/matpow_project)<br>
Запустить Makefile: `make`<br>
Запустить приложение и сохранить вывод в файл: `./matpow.exe > task_result.txt`<br>
Удаление: `make clean`<br>

Результат: [task_result.txt](https://github.com/AnnaSmelova/HPC/blob/main/hw4/matpow_project/task_result.txt)


### Сгенерируйте (или предложите) небольшой случайный граф и реализуйте процедуру вычисления вектора Pagerank. 
Сопоставьте с наивным ранжированием по числу входящих ссылок ranking.<br>
Воспользуйтесь всеми трюками по оптимизации производительности: optimization, blas, openmp, loops placing<br>
Tip: Moscow subway graph is a nice example (but rather tiny). <br><br>
Данные по станциям метро: <br>
<a href='https://gist.github.com/altsoph/56c38e76bae853655b962979346d194e'>routes_data</a> / 
<a href='https://gist.github.com/altsoph/6d3bfc97e26a4614d07fa74657739163'>stations_data</a><br>
Генерация матрицы для метро: [Get_Moscow_Subway_data.ipynb](https://github.com/AnnaSmelova/HPC/blob/main/hw4/Get_Moscow_Subway_data.ipynb)<br><br>
[pagerank_project](https://github.com/AnnaSmelova/HPC/tree/main/hw4/pagerank_project)<br>
Запустить Makefile: `make`<br>
Запустить приложение и сохранить вывод в файл: `./pagerank.exe > task_result.txt`<br>
Удаление: `make clean`<br>

Результат: [task_result.txt](https://github.com/AnnaSmelova/HPC/blob/main/hw4/pagerank_project/task_result.txt)<br>
Наиболее популярная станция по pagerank: 69,**Киевская**,Филевская линия, а по наивному ранжированию: 10,**Библиотека имени Ленина**,Сокольническая линия.

![Subway Graph](https://github.com/AnnaSmelova/HPC/blob/main/hw4/subway.png)




