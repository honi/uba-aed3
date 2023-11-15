# Algoritmo de Bellman-Ford

El algoritmo de Bellman-Ford encuentra todos los caminos mínimos desde algún vértice fuente hacia todo el resto de los vértices alcanzables.

La entrada del algoritmo es un grafo dirigido pesado $G=(V,E)$ y un vértice fuente $s \in V$. Este algoritmo acepta aristas con pesos negativos y permite detectar ciclos negativos alcanzables desde $s$.

El algoritmo relaja todas las aristas, progresivamente decrementando $v.d$, el peso estimado del camino mínimo desde $s$ a todos los vértices $v \in V$. Se repite este proceso hasta que $v.d$ converge a $\delta(s, v)$. Al finalizar, retorna `True` si y solo si no hay ciclos negativos alcanzables desde $s$, caso contrario retorna `False`.

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

def bellman_ford(G, s):
    init_single_source(G, s)

    # Relajamos |V|-1 veces todas las aristas.
    for i = 1 to len(G.V) - 1:
        for (u, v) in G.E:
            relax(u, v, G.w)

    # Revisamos si podemos mejorar una vez más el camino mínimo
    # para detectar ciclos negativos alcanzables desde s.
    for (u, v) in G.E:
        if v.d > u.d + G.w(u, v):
            return False

    return True
```

## Correctitud

**Lema**

Sea $G=(V,E)$ un grafo dirigido pesado con función de peso $w:E \rightarrow \mathbb{R}$, y $s \in V$ el vértice fuente. La propiedad $v.d$ de los vértices es la distancia estimada desde $s$ a $v$. Supongamos además que $G$ no tiene ciclos negativos alcanzables desde $s$.

> Después de $|V|-1$ iteraciones vale $v.d = \delta(s,v)$ para todo vértice $v \in V$ alcanzable desde $s$.

Para cualquier vértice $v \in V$ no alcanzable desde $s$ ya inicializamos $v.d = \delta(s,v) = \infty$, por la **propiedad de los vértices no alcanzables** este valor ya no cambia.

Tomemos ahora cualquier vértice $v \in V$ alcanzable desde $s$. Existe algún camino mínimo $p = \langle v_0, \dots, v_k \rangle$ con $s = v_0$ y $v = v_k$. Como un camino mínimo es simple, $p$ tiene a lo sumo $|V|-1$ aristas y entonces $k \leq |V|-1$.

En cada una de las $|V|-1$ iteraciones, el algoritmo relaja **todas** las aristas. En particular relaja las de $p$. En algún momento de la primer iteración relaja la arista $(v_0, v_1)$. Luego, en algún momento de la segunda iteración relaja la arista $(v_1, v_2)$. En la iteración $k$ relajamos la arista $(v_{k-1}, v_k)$. Fuimos relajando cada arista de $p$ en orden, entonces por la **propiedad de relajación** al terminar la iteración $k$ vale $v.d = \delta(s,v)$ y ya no cambia más por la **propiedad del límite superior**.

**Teorema**

Sea $G=(V,E)$ un grafo dirigido pesado con función de peso $w:E \rightarrow \mathbb{R}$, y $s \in V$ el vértice fuente. La propiedad $v.d$ de los vértices es la distancia estimada desde $s$ a $v$.

> Si $G$ no tiene ciclos negativos alcanzables desde $s$, luego de ejecutar Bellman-Ford vale $v.d = \delta(s,v)$ para todos los vértices $v \in V$ alcanzables por $s$, y los predecesores en $v.p$ forman un árbol de caminos mínimos enraizado en $s$. Si $G$ tiene ciclos negativos alcanzables desde $s$ entonces retorna False.

Si $G$ no tiene ciclos negativos alcanzables desde $s$, por el **lema** anterior vale el teorema, y por la **propiedad del límite superior** el segundo for no puede retornar `False` (ya no se puede mejorar la distancia mínima).

Veamos el caso cuando $G$ contiene un ciclo negativo alcanzable desde $s$. Sea $C = \langle v_0, \dots, v_k \rangle$ con $v_0 = v_k$ tal que $w(C) = \sum\limits_{i=1}^k w(v_{i-1}, v_i) < 0$.

Supongamos para llegar a un absurdo que el algoritmo retorna `True`. Eso significa que ninguna arista cumple la desigualdad del `if` adentro del segundo `for`. En particular, nos interesan las aristas de $C$: $v_i.d \leq v_{i-1}.d + w(v_{i-1}, v_i)$ para todo $0 \leq i \leq k$.

Aplicamos una sumatoria de ambos lados: $\sum\limits_{i=1}^k v_i.d \leq \sum\limits_{i=1}^k v_{i-1} + \sum\limits_{i=1}^k w(v_{i-1}, v_i)$

Notemos que en realidad $\sum\limits_{i=1}^k v_i.d = \sum\limits_{i=1}^k v_{i-1}$ pues $v_0 = v_k$ y cada vértice del ciclo $C$ aparece exactamente una vez en la sumatoria.

Luego resulta $0 \leq \sum\limits_{i=1}^k w(v_{i-1}, v_i) = w(C)$, pero esto es absurdo porque $C$ es un ciclo de peso negativo.

## Complejidad

- Inicializar los vértices: $O(V)$.
- Relajar los vértices: $O(V(V+E)) = O(V^2 + VE)$. En cada una de las $|V|$ iteraciones relajamos todas las aristas. Representando el grafo con listas de adyacencias cuesta $O(V+E)$ recorrer todas las aristas.
- Detectar ciclos negativos: $O(V+E)$.

La complejidad final resulta $O(V^2 + VE)$.
