# EigenValues
 QR-algorithm for finding all the eigenvalues of a matrix, reducing it to an almost triangular form by the rotation method and finding the QR decomposition at each step by the reflection method.

Программа получает все параметры в качестве аргументов командной строки. Аргументы командной строки:
1) n – размерность матрицы,
2) m – количество выводимых значений в матрице,
3) ε – точность нахождения собственных значений матрицы,
4) k – задает номер формулы для инициализации матрицы, должен быть равен 0 при вводе матрицы из файла
5) filename – имя файла, откуда надо прочитать матрицу. Этот аргумент отсутствует, если k! = 0.
Например, запуск
./a.out 4 4 1e-15 0 a.txt
означает, что матрицу 4x4 надо прочитать из файла a.txt, выводить не более 4-х строк и столбцов матрицы, и решить задачу с точностью 10−15, а запуск
./a.out 2000 6 1e-14 1
означает, что матрицу 2000x2000 надо инициализировать по формуле номер 1, выводить не более 6-ти строк и столбцов матрицы, и решить задачу с точностью 10−14.