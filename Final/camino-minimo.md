# Camino mínimo

A diferencia de BFS que encuentra caminos mínimos en cantidad de aristas, este problema aplica a grafos pesados y consiste en encontrar un camino de peso mínimo entre dos vértices. Esto es útil si por ejemplo tenemos un mapa con las distancias entre cada ciudad, y queremos encontrar la ruta más rápida para llegar de una ciudad A a otra ciudad B.

El peso de un camino $p = \langle v_0, \dots, v_k \rangle$ está definido por la suma de los pesos de las aristas que contiene.

$$w(p) = \sum_{i=1}^k w(v_{i-1}, v_i)$$

Definimos el peso del camino mínimo $\delta(u,v)$ desde $u$ a $v$ así:

$$\delta(u,v) = \begin{cases}
min\{ w(p) : p = u \leadsto v \} & \text{si existe camino de }u\text{ a }v \\
\infty & \text{caso contrario}
\end{cases}$$

Un ciclo $C$ es negativo si $w(C) < 0$. Si el grafo contiene un ciclo negativo alcanzable desde $u$ entonces $\delta(u,v)$ no está bien definido, ya que podríamos recorrer el ciclo $C$ una cantidad arbitraria de veces para reducir el peso del camino. En estos casos definimos $\delta(u,v) = -\infty$.

Los caminos mínimos presentan subestructura óptima: cualquier subcamino de un camino mínimo, es también mínimo. Por eso las técnicas greedy o de programación dinámica suelen funcionar muy bien. Idea: supongamos que un camino mínimo tiene un subcamino que no es mínimo. Entonces podríamos reemplazar ese subcamino por otro que sí es mínimo, y así obtener un camino de peso menor. Absurdo porque dijimos que el camino ya era mínimo, necesariamente todos los subcaminos son también mínimos.

## Topologías de problemas de camino mínimo

**Uno a todos**: busca el camino mínimo desde un vértice fuente hacia todos los otros vértices del grafo.

Entrada: grafo $G=(V,E)$, función de peso $w:E \rightarrow \mathbb{R}$, vértice fuente $s \in V$.

Salida: la distancia mínima $\delta(s, v)$ desde $s$ a cada vértice $v \in V$ y el árbol de caminos mínimos (por si necesitamos obtener un camino concreto y no solo el peso mínimo).

Algoritmos:
- Bellman-Ford: detecta ciclos negativos.
- Dijkstra: requiere aristas con pesos positivos, greedy.
- Topological Sort: requiere que el grafo sea un DAG.

**Uno a uno**: busca el camino mínimo desde un vértice fuente hacia otro vértice. Este es un caso particular de uno a todos, agregando a la entrada el vértice destino $u \in V$. Se suele resolver primero el problema uno a todos desde $s$ y luego extraer de la solución el camino mínimo $v \leadsto u$ que nos interesa.

**Todos a todos**: busca el camino mínimo entre todo par de vértices del grafo.

Entrada: grafo $G=(V,E)$, función de peso $w:E \rightarrow \mathbb{R}$.

Salida: la distancia mínima $\delta(u, v)$ para todo par de vértices $u,v \in V$ y la estructura de caminos mínimos (por si necesitamos obtener los caminos concretos y no solo los pesos mínimos).

Algoritmos:
- Floyd-Warshall: más eficiente en grafos densos, programación dinámica.
- Johnson: más eficiente en grafos ralos.

## Ejemplos de problemas reales

- Encontrar la ruta más corta entre 2 ciudades. Los vértices son ciudades, las aristas son rutas que conectan las ciudades y el peso de las aristas es la distancia entre las ciudades.

- Minimizar el costo monetario de viajar en auto por la ciudad utilizando una app para compartir viajes, en donde podemos levantar pasajeros que nos pagan por llevarlos. Los vértices son las intersecciones de la ciudad. Hay dos tipos de aristas, las de peso positivo conectan intersecciones adyacentes, y representan el costo del combustible. Las de peso negativo conectan 2 intersecciones cualquiera y representan levantar a un pasajero que nos paga por llevarlo. Nosotros queremos viajar entre 2 puntos de la ciudad por razones personales, y queremos ver si nos conviene ir directo y pagar el costo del combustible, o si hay alguna ruta alternativa (quizás un poco más larga) en donde levantamos un pasajero y el costo total del combustible resulta menor.

- Minimizar el esfuerzo que realizamos en un sendero de montaña. Los vértices son las intersecciones de los distintos senderos de la montaña, las aristas representan los senderos y pueden tener peso positivo si requieren mucho esfuerzo (es una subida), o peso negativo si son fáciles (es una bajada). Queremos encontrar la ruta entre 2 puntos de la montaña que minimiza el esfuerzo total que realizamos.

- Precomputar los caminos mínimos en un mapa para un servicio online como Google Maps. Los vértices son los puntos en el mapa y las aristas las rutas. En este escenario utilizaríamos Floyd-Warshall ya que no nos interesa ningún camino en particular, sino que queremos encontrar todos los caminos mínimos para guardarlos en una cache y así optimizar el tiempo de consulta de los usuarios.
