## Домашнее задание №3: ДЗ-3

### Программы с багами – примеры программ, которые надо починить.<br>
[bugs](https://github.com/AnnaSmelova/HPC/tree/main/hw3/bugs)<br>
**omp_bugreduction.c** – код для скалярного произведения двух векторов. <br>
Дополнить функцию dotprod, проверить баги в #pragma omp, проверить результат. (20 %)<br>

**omp_bugparfor.c** –Найти и устранить ошибки. (20 %)
<br><br>

### Написать параллельную программу, использующую метод Монте-Карло для оценки числа pi.<br>
[MonteCarlo.c](https://github.com/AnnaSmelova/HPC/blob/main/hw3/MonteCarlo/MonteCarlo.c)<br>
Случайным образом (аккуратнее с генератором случайных чисел! Пример в лекции) кидаете точку в единичный квадрат. В этот же квадрат вписан круг. Если точка попала в круг, увеличиваете счетчик. Затем находите отношение точек, попавших в круг к общему числу точек. Зная площади квадрата и круга, находите приблизительно число pi. (60 %)
<br><br>
Note: clock() measures the sum of wall clocks across all threads. Use omp_get_wtime() instead (it returns value in seconds).

