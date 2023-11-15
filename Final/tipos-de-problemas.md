# Tipos de problemas e instancias

Un problema es la descripción de los datos de entrada y la salida esperada. En cambio, una instancia es una determinada configuración de los datos de entrada.

Por ejemplo, un problema podría ser: dado un número entero `n` decidir si `n` es primo. Una instancia de este problema sería un número en concreto, por ejemplo el `7`. En este caso en particular, hay infinitas instancias, pues hay infinitos números enteros.

Tomando como ejemplo el problema TSP: viajante de comercio (determinar un circuito hamiltoniano de distancia mínima), podemos buscar resolver varias versiones del problema:

- **Optimización**: Encontrar una solución óptima al problema (de valor mínimo o máximo). Para TSP obtenemos el circuito hamiltoniano.
- **Evaluación**: Determinar el valor de una solución óptima. Para TSP obtenemos la distancia (mínima) que recorre el circuito hamiltoniano.
- **Localización**: Dada una cota, determinar una solución factible que sea menor (o mayor) que la cota. Para TSP sería encontrar un circuito hamiltoniano que tenga distancia menor a la cota.
- **Decisión**: Dada una cota, determinar si existe una solución factible que sea menor (o mayor) que la cota. Para TSP sería responder si existe o no un circuito hamiltoniano con distancia menor a la cota.

Para problemas de optimización combinatoria todas las versiones son equivalentes, si existe un algoritmo eficiente resuelve todas las versiones.
