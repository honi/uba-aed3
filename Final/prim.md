# Algoritmo de Prim

La idea de este algoritmo es comenzar eligiendo algún vértice arbitrario del grafo y colocarlo en un árbol. En cada paso extendemos este árbol agregando la arista de menor peso desde el árbol hacia algún vértice que aún no hayamos agregado. Una vez que colocamos todos los vértices, obtuvimos un AGM del grafo.

Para que sea eficiente usamos una cola de prioridad donde mantenemos los vértices que aún no están en el árbol, y utilizamos como clave de ordenamiento el peso mínimo de alguna arista que conecta el vértice afuera del árbol con algún otro que ya está en el árbol.

```python
def prim(G, r):
    for u in G.V:
        u.key = infty
        u.parent = None

    # Construimos el AGM a partir del vértice r.
    r.key = 0

    # Agregamos todos los vértices a la cola de prioridad.
    Q = []
    for u in G.V:
        Q.insert(u)

    while Q:
        # Colocamos u en el AGM.
        u = Q.extract_min()

        for v in G.Adj[u]:
            # El vecino v no está en el AGM y utilizando la arista (u, v)
            # reducimos el costo para llegar hasta v.
            if (v in Q) and (G.w(u, v) < v.key):
                v.parent = u
                v.key = G.w(u, v)
```

## Correctitud

Notemos que este algoritmo es goloso. En cada paso, tomamos una decisión golosa respecto de qué vértice agregar al árbol: tomamos el vértice que se conecta con el árbol usando la arista de menor peso.

Dicho más formalmente, tenemos un corte $(S, V-S)$ donde $S$ contiene los vértices ya agregados al árbol y $V-S$ son los vértices en la cola de prioridad que no están aún en el árbol. En cada paso, elegimos la arista $e=(u,v)$ de menor peso que cruza el corte, es decir $u \in S$, $v \in V-S$.

Veamos que la elección golosa es correcta. Sea $T$ algún AGM del grafo, y supongamos que la arista $e$ que recién elegimos es la primer arista que no está en $T$. Como $T$ es un AGM, necesariamente tiene que haber un camino que conecte $u$ con $v$. En particular, tiene que haber en $T$ una arista $f=(x,y)$ que es parte del camino entre $u$ y $v$, y además cruza el corte al igual que $e$, es decir $x \in S$, $y \in V-S$.

En la iteración que agregamos la arista $e$ podríamos haber agregado $f$, pero no lo hicimos. Elegimos la arista de menor peso que cruza el corte, entonces vale que $w(e) \leq w(f)$.

Definimos $T' = T - f + e$. Las aristas $f$ y $e$ pertenecen a un mismo ciclo, entonces al hacer este cambio $T'$ sigue siendo un AG. Para ver que es AGM, miremos cómo cambia el peso del árbol: $w(T') = w(T) - w(f) + w(e) \leq w(T)$. Tomamos $T$ como AGM, lo cual implica que $w(T) \leq w(T')$. Por lo tanto concluimos que $w(T') = w(T)$ y $T'$ es un AGM.

Este mismo proceso lo repetimos por cada arista que elegimos que no está en el AGM $T$ que tomamos originalmente, y así verificamos que el árbol que nuestro algoritmo encuentra es un AGM.

## Complejidad

La complejidad de Prim depende de la implementación de la cola de prioridad.

- Min heap: $O(E * log(V))$
- Fibonacci heap: $O(V * log(V) + E)$

Para grafos densos conviene usar la versión con Fibonacci heap, ya que en ese caso $E = O(V^2)$.
