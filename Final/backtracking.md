# Fuerza bruta

Un algoritmo de fuerza bruta genera y analiza de forma exhaustiva todas las posibles soluciones a un problema hasta encontrar una solución válida. Si se trata de un problema de decisión, es suficiente con encontrar una solución válida cualquiera. En cambio, si se trata de un algoritmo de optimización, es necesario recorrer todas las posibles soluciones válidas para encontrar la óptima.

Este tipo de algoritmos son fáciles de inventar e implementar si tenemos bien definido nuestro problema a resolver, y además es un algoritmo exacto: si hay solución la encuentra. El problema principal es que suelen ser muy ineficientes, habitualmente de orden exponencial, justamente porque analizan todas las posibles soluciones.

Estudiemos el problema subset sum. Dado `S` un multiconjunto de números naturales y `T` una suma deseada, queremos encontrar un subconjunto de `S` tal que la suma de todos sus elementos sea `T`. Si no existe ese subconjunto, devolvemos el conjunto vacío.

Podemos resolver este problema con el siguiente algoritmo de fuerza bruta:

```python
def subset_sum_brute_force(S, T):
    n = len(S)
    res = []

    def f(a, i):
        nonlocal res
        if i == n:
            if sum(a) == T: res = a
        else:
            e = S[i]
            f(a + [e], i + 1)
            f(a, i + 1)

    f([], 0)
    return res
```

Todas las posibles soluciones forman el conjunto de partes de `S`, es decir, todos los subconjuntos de `S`. Si el tamaño de `S` es `n`, entonces existen `2^n` posibles soluciones, y nuestro algoritmo debe generar y analizarlas a todas. Iniciamos la generación desde el conjunto vacío, y por cada elemento de `S`, hacemos 2 llamados recursivos: en uno agregamos ese elemento a la posible solución y en el otro no. Cuando ya no hay más elementos de `S`, estamos en el caso base de la recursión y tenemos generada una posible solución al problema. Verificamos si la suma de los elementos del subconjunto solución es igual `T` en `O(n)`. En tal caso guardamos este resultado para ser retornado al finalizar la búsqueda exhaustiva, caso contrario se descarta el subconjunto generado. La complejidad de este algoritmo resulta `O(2^n * n) = O(2^n)`.

Si existe un subconjunto de `S` que sume `T`, lo vamos a encontrar. Pero en el proceso vamos a generar y evaluar muchos otros subconjuntos innecesariamente.

# Backtracking

Un algoritmo de backtracking construye una solución de forma incremental descartando soluciones parciales cuando detectamos que no pueden ser extendidas a una solución válida. En ese momento es que hacemos "backtracking" y volvemos a la solución parcial anterior para explorar otras extensiones. A diferencia de un algoritmo de fuerza bruta, existen instancias del problema en donde ya no necesitamos generar y analizar todas las posibles soluciones.

Conceptualmente el conjunto de soluciones parciales representan vértices en un árbol de búsqueda, en donde una solución parcial `a` es el padre de `a'` si podemos extender `a` para obtener `a'`. Las hojas representan soluciones parciales que ya no pueden ser extendidas.

El algoritmo de backtracking recorre este árbol en profundidad desde la raíz, de forma recursiva. En cada vértice, revisa si se puede extender esa solución parcial a una solución válida. En tal caso, continúa el recorrido por sus hijos. Caso contrario, descartamos todo el subárbol enraizado en este vértice. En efecto, "podamos" el árbol y evitamos revisar soluciones que ya sabemos que nunca pueden ser válidas.

La complejidad de estos algoritmos está dominada por la cantidad de vértices que realmente visitamos. En la práctica suelen ser mucho más rápidos que fuerza bruta, en especial si logramos realizar podas inteligentes que recortan grandes partes del árbol con un test eficiente (si el test para podar tarda tanto como recorrer todo ese subárbol entonces no obtenemos ninguna mejora).

Para podar el árbol de búsqueda utilizamos propiedades específicas del problema que estamos resolviendo, no hay una regla general. No obstante, estas podas pueden ser por:

- Factibilidad: ninguna extensión de la solución parcial puede generar una solución válida.
- Optimalidad: ninguna extensión de la solución parcial puede generar una solución mejor de la que ya encontramos (solo para problemas de optimización).

El siguiente algoritmo utiliza backtracking para resolver el problema subset sum.

```python
def subset_sum_backtracking(S, T):
    n = len(S)
    res = []

    def f(a, i, sum_a):
        nonlocal res

        # Encontramos una solución válida.
        if sum_a == T:
            res = a
            return True

        # Hay elementos para agregar y no nos pasamos de T.
        if i < n and sum_a < T:
            e = S[i]
            return f(a + [e], i + 1, sum_a + e) or f(a, i + 1, sum_a)

        # No hay solución por esta rama.
        return False

    f([], 0, 0)
    return res
```

La generación de las posibles soluciones es igual a la versión de fuerza bruta, solo que gracias a las podas no necesitamos generar todas las posibles soluciones si detectamos que una solución parcial no puede ser extendida a una solución factible. Además, cuando encontramos una solución válida frenamos la búsqueda, no necesitamos seguir explorando otras soluciones posibles.

El algoritmo implementa la siguiente poda: si la suma parcial es > `T` entonces no existe ninguna extensión que sume exactamente `T`, pues cualquier elemento que agreguemos a la solución solo puede incrementar la suma (los elementos de `S` son todos números naturales).

También se podrían implementar otras podas, por ejemplo si la suma parcial + la suma de todos los elementos de `S` que aún no consideramos es < `T` entonces no existe ninguna extensión que sume exactamente `T`. En particular, este test verifica que si la extensión que agrega todos los elementos restantes de `S` resulta en una suma menor a `T`, entonces cualquier otra extensión agrega menos elementos y por lo tanto la suma va a ser aún menor.

Si bien no es una poda, también se podrían ordenar los elementos de `S` con algún criterio para priorizar la generación temprana de ciertas soluciones parciales. Por ejemplo, si ordenamos de mayor a menor, vamos a comenzar agregando a las soluciones parciales los elementos más grandes, y así podar más rápido los subconjuntos que suman más que `T`.

La complejidad de este algoritmo en el peor caso sigue siendo `O(2^n)`. Esto sucede cuando no pudimos aplicar ninguna poda. Pero en la práctica se obtienen tiempos mucho mejores asumiendo que la instancia del problema permite aplicar varias veces la poda implementada.
