# Tipos de problemas e instancias

Un problema es la descripción de los datos de entrada y la salida esperada. En cambio, una instancia es una determinada configuración de los datos de entrada.

Por ejemplo, un problema podría ser: dado un número entero `n` decidir si `n` es primo. Una instancia de este problema sería un número en concreto, por ejemplo el `7`. En este caso en particular, hay infinitas instancias, pues hay infinitos números enteros.

Los problemas pueden ser de varios tipos:

**Decisión**

Responder si/no a una pregunta sobre los datos de entrada. Ejemplo: dado un arreglo de números enteros y un entero `k`, decidir si `k` se encuentra en el arreglo.

**Optimización**

Encontrar la mejor solución dentro del conjunto de soluciones factibles.

`z* = max{f(x) : x in S}` o bien `z* = min{f(x) : x in S}`

- La función `f: S -> R` se denomina función objetivo del problema.
- El conjunto `S` es la región factible y los elementos `x in S` son soluciones factibles.
- El valor `z*` es el valor óptimo del problema. A veces nos interesa obtener `z*` y otras veces obtener algún `x` tal que `f(x) = z*`.

Cuando se trata de un problema de optimización combinatoria, la región factible es un conjunto definido por consideraciones combinatorias (por ejemplo subconjuntos o permutaciones de un conjunto finito de elementos).

**Localización**

**Evaluación**
