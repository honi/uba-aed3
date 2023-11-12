# Programación dinámica

Los problemas de optimización que presentan las siguientes 2 características se pueden resolver con programación dinámica de forma eficiente.

**Subestructura óptima**

La solución óptima al problema se compone de soluciones óptimas a los subproblemas más chicos. Es fácil ver que esto vale por el argumento "cut and paste" del Cormen. Dada una solución que realmente es óptima, podemos descomponerla en las soluciones a los subproblemas, que a su vez también son óptimos. Si no lo fueran, podríamos "cortar y pegar" una solución óptima a un subproblema y así generar una mejor solución al problema original (absurdo pues dijimos que ya teníamos una solución óptima).

**Superposición de subproblemas**

El espacio de búsqueda de soluciones es lo suficientemente chico como para que se superpongan los subproblemas. Es decir, a medida que vamos particionando el problema original en subproblemas, y luego estos nuevos problemas en más subproblemas (sub-subproblemas del problema original) llegamos al punto en donde se repiten los problemas a resolver. Si miramos el árbol de llamadas recursivas, veríamos que el mismo problema se resuelva muchas veces.

Si queremos calcular de forma recursiva el término 42 de Fibonacci `F42 = F41 + F40`, necesitamos también calcular el término `F41 = F40 + F39`. Observemos que en ambas instancias necesitamos la solución al término `F40`. Si bien hay solo 42 subproblemas, en esta solución recursiva naive estaríamos calculando los mismos términos una y otra vez.

Programación dinámica resuelve esto calculando cada subproblema una única vez. Existen 2 formas para lograrlo.

**Top-down**

Esta estrategia es la que resulta de forma directa a partir de una solución recursiva a un problema de optimización que cumple con las 2 características mencionadas: subestructura óptima y superposición de subproblemas.

Partiendo del problema original, se utiliza recursión para resolver los subproblemas y luego construir la solución óptima al problema original. Para evitar recalcular los mismos subproblemas más de una vez, se utiliza una matriz de memoización, en donde se guardan los resultados previamente calculados. De esta forma, cuando necesitamos resolver un subproblema, primero nos fijamos si ya fue calculado, y en tal caso devolvemos el valor memoizado. Caso contrario se procede a calcularlo y guardarlo en la matriz de memoización para futuros llamados recursivos por el mismo subproblema.

La matriz de memoización se "indexa" por el estado (subproblema) que estamos resolviendo. En el caso de Fibonacci, basta con una matriz de una sola dimensión del tamaño del término que queremos calcular. Antes de calcular un término `i`, nos fijamos si la posición `i` de la matriz ya contiene el valor calculado. Otros problemas requieren matrices de 2, 3 o más dimensiones en función de cómo modelemos los estados.

Para utilizar memoización es necesario inicializar la matriz antes de hacer la recursión. Generalmente se inicializa en `-inf` o `-1` o algún valor que nunca sería una solución válida, para así poder determinar si un subproblema ya fue calculado o no.

**Bottom-up**

Esta estrategia construye la solución óptima partiendo de la solución de los subproblema más chicos y avanzando hasta llegar al problema original que queríamos resolver. En vez de recursión se utilizan bucles, y requiere un poco más de ingenio para determinar cuáles son los subproblemas que hay que resolver primero (no siempre es evidente a primera vista la dependencia entre los subproblemas). Los resultados se van guardando en una matriz o tabla para ser utilizados más adelante cuando se resuelven problemas más grandes.

A diferencia de top-down, esta estrategia calcula el resultado para todos los subproblemas posibles, porque a priori no sabemos cuáles vamos a necesitar para la solución final. En cambio top-down solamente calcula los subproblemas que realmente son necesarios.

**Problema: rod cutting (top-down)**

Tenemos una vara de longitud `n` y queremos hacerle cortes para formar varas más chicas y así maximizar la ganancia al vender todas las varas cortadas. El precio de una vara de longitud `i` está dado por `p(i)`. Nos interesa saber cuál es la ganancia máxima que podemos obtener.

Este problema presenta una subestructura óptima: después de elegir dónde hacer el primer corte, resultan 2 varas las cuales una vamos a dejar fija sin más cortes, y la otra vamos a nuevamente optimizar sus cortes para maximizar la ganancia (utilizando el mismo algoritmo).

Definimos `r(n) = max{p(i) + r(n-i) : 1 <= i <= n}` como la ganancia máxima para una vara de longitud `n`. Probamos realizar todos los posibles cortes para obtener una vara de longitud `i` que se vende a un precio `p(i)`, y luego buscamos la ganancia máxima de la otra vara de longitud `n-i`.

```python
def rod_cutting(n, p):
    memo = [-1] * (n+1)

    def r(n):
        if n == 0:
            memo[n] = 0
        elif memo[n] == -1:
            for i in range(1, n+1):
                memo[n] = max(memo[n], p[i] + r(n-i))
        return memo[n]

    return r(n)
```

Inicializamos la matriz de memoización `memo` en `-1` lo cual indica que aún no calculamos ese resultado. La función `r` calcula el resultado una sola vez para cada valor distinto de `n`. La ganancia máxima se obtiene con el algoritmo descripto anteriormente.

La complejidad de esta implementación resulta `O(n^2)` pues hay `n` valores distintos de longitudes (es decir hay `n` estados), y por cada longitud hacemos un bucle de `n` iteraciones para probar cada uno de los `n` cortes posibles para buscar la máxima ganancia (es decir nos cuesta `O(n)` calcular cada estado).

**Problema: rod cutting (bottom-up)**

La versión bottom-up también utiliza una matriz (o tabla) para ir computando las soluciones para las varas de longitud `1, ..., n`. Por cada vara de longitud `j`, probamos realizar todos los cortes entre `1` y `j`. Notemos que para cualquier valor `j`, ya calculamos las soluciones para todos los cortes más chicos que `j`.

Luego de computar toda la tabla completa, obtenemos el resultado indexando en la longitud `n`.

```python
def rod_cutting_bottom_up(n, p):
    memo = [-1] * (n+1)
    memo[0] = 0

    # Por cada longitud j.
    for j in range(1, n+1):
        # Probamos todos los posibles cortes en 1 <= i <= j.
        for i in range(1, j+1):
            memo[j] = max(memo[j], p[i] + memo[j-i])

    return memo[n]
```

La complejidad de esta versión resulta igual que top-down: `O(n^2)`. Es evidente por los 2 bucles.
