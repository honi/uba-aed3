# Práctica 1 / Ejercicio 6

Argumentos de entrada:
- `N` (cantidad de ejecuciones para cada benchmark)
- `c`
- `|B|`
- `B` (cada elemento separado por un espacio)

```bash
make
./bin/app 100 200 20 1 2 3 4 5 10 15 20 22 25 26 27 28 30 32 33 35 37 39 40
```

Output
```bash
c: 200
n: 20
B: {1, 2, 3, 4, 5, 10, 15, 20, 22, 25, 26, 27, 28, 30, 32, 33, 35, 37, 39, 40}

Running top down with memoization (x 100 times)...
time: 0ms
amount payed: 200
number of bills: 6

Running bottom up (x 100 times)...
time: 1ms
amount payed: 200
number of bills: 6

Running backtracking without memoization (x 10 times, this takes a long time)...
time: 11ms
amount payed: 200
number of bills: 6
```
