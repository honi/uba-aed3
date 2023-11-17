# Algoritmo de Dijkstra

El algoritmo de Dijkstra encuentra todos los caminos mínimos desde algún vértice fuente hacia todo el resto de los vértices alcanzables.

La entrada del algoritmo es un grafo dirigido pesado $G=(V,E)$ y un vértice fuente $s \in V$. Este algoritmo **no** acepta aristas con pesos negativos.

El algoritmo mantiene un conjunto $S$ de vértices que genera un corte $(S, V-S)$. El invariante del ciclo es que ya tenemos calculada la distancia mínima desde $s$ a todos los vértices que están en $S$. En cada iteración, elegimos un vértice en $V-S$ con la menor estimación de distancia, y lo agregamos a $S$. En este momento relajamos todas las aristas que salen de este vértice y cruzan el corte. Terminamos cuando $S = V$.

Para que sea eficiente, usamos una cola de prioridad $Q$ para mantener los vértices en $V-S$ ordenados por su estimación de distancia.

## Algoritmo

```python
def init_single_source(G, s):
    for v in G.V:
        v.d = infty
        v.p = None
    s.d = 0

def relax(u, v, w):
    if v.d > u.d + w(u, v):
        v.d = u.d + w(u, v)
        v.p = u
        return True
    return False

def dijkstra(G, s):
    init_single_source(G, s)

    S = []
    Q = []
    for v in G.V:
        Q.insert(v)

    while Q:
        u = Q.extract_min()
        S += [u]
        for v in G.Adj[u]:
            if relax(u, v, G.w):
                Q.decrease_key(v, v.d)
```

## Correctitud

Sea $G=(V,E)$ un grafo dirigido pesado con función de peso no negativo $w:E \rightarrow \mathbb{R}_{\geq0}$, y $s \in V$ el vértice fuente. La propiedad $v.d$ de los vértices es la distancia estimada desde $s$ a $v$.

Con inducción en la cantidad de iteraciones, vamos a mostrar que al comienzo de cada iteración, vale $v.d = \delta(s,v)$ para todos los vértices $v \in S$, y el algoritmo termina cuando $S=V$.

Al comienzo de cada iteración, $|S|$ representa la cantidad de iteraciones realizadas. Tenemos 2 casos base:

- $|S| = 0$: vale trivialmente pues no hay ningún vértice en $S$.
- $|S| = 1$: vale pues en la inicialización, $v.d = \infty$ para todos los vértices $v \in V - \lbrace s \rbrace$, y $s.d = 0$. El primer vértice que extraemos de la cola es $s$. Entonces cuando $|S| = 1$ tenemos $S = \lbrace s \rbrace$ y se cumple que $s.d = \delta(s,s) = 0$.

La hipótesis inductiva es que $v.d = \delta(s,v)$ para todos los vértices $v \in S$. Sea $u \in V - S$ el vértice que extraemos de la cola. Tenemos que mostrar que al momento de agregar $u$ en $S$ vale que $u.d = \delta(s,u)$.

Si $u$ no es alcanzable desde $s$, entonces por la propiedad de los **vértices no alcanzables** $u.d = \delta(s,u) = \infty$.

Asumimos entonces que existe un camino desde $s$ a $u$. Sea $x \rightarrow y$ la primer arista en el camino mínimo de $s$ a $u$ que cruza el corte $(S, V-S)$, es decir, $x \in S$, $y \in V-S$. Notemos que podría ser que $x=s$ o $y=u$.

Por hipótesis inductiva $x.d = \delta(s,x)$. A su vez, cuando agregamos $x$ en $S$ relajamos todas las aristas que salen de $x$ y cruzan el corte. En particular relajamos la arista $x \rightarrow y$. Por la **propiedad de convergencia** tenemos que $y.d = \delta(s, y)$.

Como $y$ aparece antes que $u$ en el camino mínimo de $s$ a $u$, y además todas las aristas tienen peso no negativo, vale que $\delta(s,y) \leq \delta(s,u)$. Además, si extraímos $u$ de la cola de prioridad es porque $u.d$ es la menor estimación de distancia entre todos los vértices en $V-S$, entonces vale que $u.d \leq y.d$ (recordemos que $y \in V-S$), y por la **propiedad del límite superior** tenemos $\delta(s,d) \leq u.d$.

Juntando todas estas desigualdades obtenemos:

$\delta(s,y) \leq \delta(s,u) \leq u.d \leq y.d = \delta(s,y) \Rightarrow u.d = \delta(s,u)$

## Complejidad

- Inicializar los vértices: $O(V)$.
- Insertar todos los vértices en $Q$: $O(V)$.
- `while`: $(V * \text{extract-min})$.
    - Hace $O(V)$ iteraciones ya que nunca se vuelven a insertar vértices en $Q$.
    - El costo de cada iteración es el costo de extraer el mínimo, depende de la cola utilizada.
- `for`: $O(E * \text{decrease-key})$
    - Cada vértice sale de la cola de prioridad una única vez, por lo tanto en total recorremos cada arista una única vez.
    - El costo de cada iteración es el costo de decrementar la clave, ya que `relax` es $O(1)$.

Las operaciones con la cola de prioridad dependen de su implementación.

- Vector: $O(V)$ para extraer el mínimo, $O(1)$ para decrementar una clave.
- Min binary heap: $O(log(V))$ para extraer el mínimo y decrementar una clave.
- Fibonacci heap: $O(log(V))$ para extraer el mínimo, $O(1)$ amortizado para decrementar una clave.

La complejidad final resulta: $O(V + V + V * \text{extract-min} + E * \text{decrease-key}) = O(V * \text{extract-min} + E * \text{decrease-key})$.

- Cola de prioridad con vector: $O(V^2 + E) = O(V^2)$ pues $O(E) = O(V^2)$.
- Cola de prioridad con min heap: $O(V * log(V) + E * log(V)) = O(E * log(V))$.
    - Para grafos ralos donde $E \approx V$: $O(V * log(V))$
- Cola de prioridad con Fibonacci heap: $O(V * log(V) + E)$.
    - Para grafos densos donde $E \approx V^2$ no conviene esta implementación.
