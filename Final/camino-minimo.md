# Camino mínimo

A diferencia de BFS que encuentra caminos mínimos en cantidad de aristas, este problema aplica a grafos dirigidos pesados y consiste en encontrar un camino de peso mínimo entre dos vértices. Esto es útil si por ejemplo tenemos un mapa con las distancias entre cada ciudad, y queremos encontrar la ruta más rápida para llegar de una ciudad A a otra ciudad B.

El peso de un camino $p = \langle v_0, \dots, v_k \rangle$ está definido por la suma de los pesos de las aristas que contiene.

$$w(p) = \sum_{i=1}^k w(v_{i-1}, v_i)$$

Definimos el peso del camino mínimo $\delta(u,v)$ desde $u$ a $v$ así:

$$\delta(u,v) = \begin{cases}
min \lbrace w(p) : p = u \leadsto v \rbrace & \text{si existe camino de }u\text{ a }v \\
\infty & \text{caso contrario}
\end{cases}$$

Un ciclo $C$ es negativo si $w(C) < 0$. Si el grafo contiene un ciclo negativo alcanzable desde $u$ entonces $\delta(u,v)$ no está bien definido, ya que podríamos recorrer el ciclo $C$ una cantidad arbitraria de veces para reducir el peso del camino. En estos casos definimos $\delta(u,v) = -\infty$.

## Subestructura óptima

Los caminos mínimos presentan subestructura óptima: cualquier subcamino de un camino mínimo, es también mínimo. Por eso las técnicas greedy o de programación dinámica suelen funcionar muy bien.

Sea $p = \langle v_0, \dots, v_k \rangle$ un camino mínimo y para cualquier par de $i,j$ tales que $0 \leq i \leq j \leq k$, sea $p_{ij} = \langle v_i, \dots, v_j \rangle$ un subcamino de $p$. Entonces $p_{ij}$ es un camino mínimo de $v_i$ a $v_j$.

Supongamos que existe otro camino $q_{ij} = \langle v_i, \dots, v_j \rangle$ tal que $w(q_{ij}) < w(p_{ij})$. Podemos construir un nuevo camino $p' = p_{0i} + q_{ij} + p_{jk}$ que va de $v_0$ a $v_k$, y tiene peso $w(p') = w(p_{0i}) + w(q_{ij}) + w(p_{jk}) < w(p)$. Absurdo pues $p$ es un camino de peso mínimo.

## Topologías de problemas de camino mínimo

**Uno a todos**: busca el camino mínimo desde un vértice fuente hacia todos los otros vértices del grafo.

Entrada: grafo dirigido pesado $G=(V,E)$ con función de peso $w:E \rightarrow \mathbb{R}$ y un vértice fuente $s \in V$.

Salida: la distancia mínima $\delta(s, v)$ desde $s$ a cada vértice $v \in V$ y el árbol de caminos mínimos (por si necesitamos obtener un camino concreto y no solo el peso mínimo).

Algoritmos:
- Bellman-Ford: detecta ciclos negativos.
- Dijkstra: requiere aristas con pesos no negativos, greedy.
- Topological Sort: requiere que el grafo sea un DAG.

**Uno a uno**: busca el camino mínimo desde un vértice fuente hacia otro vértice. Este es un caso particular de uno a todos, agregando a la entrada el vértice destino $u \in V$. Se suele resolver primero el problema uno a todos desde $s$ y luego extraer de la solución el camino mínimo $v \leadsto u$ que nos interesa.

**Todos a todos**: busca el camino mínimo entre todo par de vértices del grafo.

Entrada: grafo dirigido pesado $G=(V,E)$ con función de peso $w:E \rightarrow \mathbb{R}$.

Salida: la distancia mínima $\delta(u, v)$ para todo par de vértices $u,v \in V$ y la estructura de caminos mínimos (por si necesitamos obtener los caminos concretos y no solo los pesos mínimos).

Algoritmos:
- Floyd-Warshall: más eficiente en grafos densos, programación dinámica.
- Johnson: más eficiente en grafos ralos.

## Ejemplos de problemas reales

- Encontrar la ruta más corta entre 2 ciudades. Los vértices son ciudades, las aristas son rutas que conectan las ciudades y el peso de las aristas es la distancia entre las ciudades.

- Minimizar el costo monetario de viajar en auto por la ciudad utilizando una app para compartir viajes, en donde podemos levantar pasajeros que nos pagan por llevarlos. Los vértices son las intersecciones de la ciudad. Hay dos tipos de aristas, las de peso positivo conectan intersecciones adyacentes, y representan el costo del combustible. Las de peso negativo conectan 2 intersecciones cualquiera y representan levantar a un pasajero que nos paga por llevarlo. Nosotros queremos viajar entre 2 puntos de la ciudad por razones personales, y queremos ver si nos conviene ir directo y pagar el costo del combustible, o si hay alguna ruta alternativa (quizás un poco más larga) en donde levantamos un pasajero y el costo total del combustible resulta menor.

- Minimizar el esfuerzo que realizamos en un sendero de montaña. Los vértices son las intersecciones de los distintos senderos de la montaña, las aristas representan los senderos y pueden tener peso positivo si requieren mucho esfuerzo (es una subida), o peso negativo si son fáciles (es una bajada). Queremos encontrar la ruta entre 2 puntos de la montaña que minimiza el esfuerzo total que realizamos.

- Precomputar los caminos mínimos en un mapa para un servicio online como Google Maps. Los vértices son los puntos en el mapa y las aristas las rutas. En este escenario utilizaríamos Floyd-Warshall ya que no nos interesa ningún camino en particular, sino que queremos encontrar todos los caminos mínimos para guardarlos en una cache y así optimizar el tiempo de consulta de los usuarios.

- Determinar el diámetro de un grafo, es decir el camino mínimo más largo. Para esto podemos calcular todos los caminos mínimos con Floyd-Warshall y luego buscar el máximo entre ellos. Esta aplicación sirve por ejemplo si el grafo modela una red de comunicaciones, donde el peso de las aristas representa el tiempo necesario para que un mensaje viaje por ese cable. El diámetro de la red nos dice el tiempo máximo de latencia para cualquier mensaje.

## Propiedades de caminos mínimos

Estas propiedades las usamos en las demostraciones de los algoritmos de camino mínimo. Sea $G=(V,E)$ un grafo dirigido pesado con función de peso $w:E \rightarrow \mathbb{R}$, y $s \in V$ el vértice fuente. La propiedad $v.d$ de los vértices es la distancia estimada desde $s$ a $v$ la cual converge a $\delta(s,v)$ mediante una sucesión de pasos de relajación.

**Desigualdad triangular** (triangle inequality)

Para cualquier arista $(u,v) \in E$ vale $\delta(s,v) \leq \delta(s,u) + w(u,v)$.

**Límite superior** (upper-bound property)

Siempre tenemos $v.d \geq \delta(s, v)$ para todos los vértices $v \in V$. Cuando $v.d$ vale exactamente $\delta(s, v)$ ya no cambia más.

**Vértices no alcanzables** (no-path property)

Si no existe camino de $s$ a $v$, entonces siempre tenemos $v.d = \delta(s, v) = \infty$.

**Convergencia** (convergence property)

Si $s \leadsto u \rightarrow v$ es un camino mínimo de $s$ a $v$ y tenemos $u.d = \delta(s,u)$ antes de relajar la arista $(u,v)$, entonces luego de relajarla vale $v.d = \delta(s,v)$ y ya no cambia.

**Relajación** (path-relaxation property)

Si tenemos un camino mínimo $p = \langle v_0, \dots, v_k \rangle$ desde $s = v_0$ a $v_k$, y relajamos todas las aristas en orden $(v_0, v_1), (v_1, v_2), \dots, (v_{k-1}, v_k)$, entonces $v_k.d = \delta(s, v_k)$. Esta propiedad también vale si en el medio se relajan otras aristas.

**Subgrafo de predecesores** (predecessor-subgraph property)

Una vez que $v.d = \delta(s,v)$ para todos los vértices $v \in V$, el subgrafo de predecesores es un árbol de caminos mínimos enraizado en $s$. Esto nos dice que podemos obtener los vértices de un camino mínimo utilizando la información guardada de padres en cada paso de relajación.
