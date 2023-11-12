# Algoritmos golosos

Los algoritmos golosos sirven para problemas de optimización, y se destacan por su eficiencia y simplicidad de implementación. Pero no funcionan siempre, y probar que son correctos no suele ser trivial.

La estrategia consistente en construir una solución óptima de forma incremental. En cada paso se toma una decisión localmente óptima de cómo extender la solución, y esta decisión nunca se vuelve a revisar (no hay backtracking).

**Heurísticas**

Hay problemas para los cuales un algoritmo goloso no encuentra la solución óptima. No obstante, igual se puede utilizar esta técnica como heurística para acercarse a una solución aceptable.

Esto es particularmente útil en problemas NP-Hard, como ser el problema del viajante de comercio. No se conoce un algoritmo polinomial para este problema. Pero podemos utilizar una estrategia golosa y en cada paso elegir visitar el vecino más cercano que aún no fue visitado. Aunque esta heurística no siempre produce la solución óptima, se acerca bastante y las soluciones obtenidas suelen ser razonables. Y más importante aún, se obtiene también en un tiempo razonable.

**Comparación con programación dinámica**

Ambas técnicas aplican a problemas de optimización, y requieren que el problema posea subestructura óptima. Programación dinámica encuentra la solución exacta, mientras que un algoritmo goloso no siempre puede encontrar la solución exacta. No obstante, si se tiene un algoritmo goloso que encuentra la solución exacta, es más conveniente que programación dinámica porque generalmente son algoritmos más rápidos.

**Problema: tiempo de espera**

Un servidor tiene que atender $n$ clientes, en cualquier orden. Cada cliente $i$ requiere de un tiempo $t(i)$ para ser atendido. Se busca determinar en qué orden atender a los clientes para minimizar la suma del tiempo de espera de todos los clientes.

Este problema se puede resolver de manera eficiente con el siguiente algoritmo goloso: simplemente atender a los clientes por orden creciente de su tiempo de atención. Es decir, primero atendemos a los clientes que requieren poco tiempo, y luego a los que requiren más.

Si $S = (i_1, \dots, i_n)$ es el orden de atención de los clientes, el tiempo total de espera está dado por:

$$T = t(i_1) + (t(i_1) + t(i_2)) + (t(i_1) + t(i_2) + t(i_3)) + \dots$$

Cada cliente debe esperar la suma de los tiempos de atención de todos los clientes atendidos previamente.

Podemos simplificar la expresión de la siguiente forma:

$$T = \sum_{k=1}^n (n-k) * t(i_k)$$

El tiempo de atención del cliente $i_1$ impacta en el tiempo de espera del resto de los $n-1$ clientes. La del cliente $i_2$ en el resto de los $n-2$ clientes, y así sucesivamente. Al ordenar los clientes por su tiempo de atención minimizamos cada término de la sumatoria, y así minimizamos el tiempo total de espera.
