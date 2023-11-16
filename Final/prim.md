# Algoritmo de Prim

La idea de este algoritmo es comenzar eligiendo algún vértice arbitrario del grafo y colocarlo en un árbol. En cada paso extendemos este árbol agregando la arista de menor peso desde el árbol hacia algún vértice que aún no hayamos agregado. Una vez que colocamos todos los vértices, obtuvimos un AGM del grafo.

Para que sea eficiente usamos una cola de prioridad donde mantenemos los vértices que aún no están en el árbol, y utilizamos como clave de ordenamiento el peso mínimo de alguna arista que conecta el vértice afuera del árbol con algún otro que ya está en el árbol.

```python
def prim(G, s):
    for u in G.V:
        u.key = infty
        u.parent = None

    # Construimos el AGM a partir del vértice r.
    s.key = 0

    # Agregamos todos los vértices a la cola de prioridad.
    Q = []
    for u in G.V:
        Q.insert(u, u.key)

    S = []
    while Q:
        # Colocamos u en el AGM.
        u = Q.extract_min()
        S += [u]

        for v in G.Adj[u]:
            # El vecino v no está en el AGM y utilizando la arista (u, v)
            # reducimos el costo para llegar hasta v.
            if v in Q and G.w(u, v) < v.key:
                v.parent = u
                v.key = G.w(u, v)
                q.decrease_key(v, v.key)
```

## Correctitud

Nos apoyamos en la [demostración del algoritmo goloso para construir un AGM](./agm.md). El algoritmo de Prim elige las aristas seguras de forma indirecta.

El conjunto de vértices $S$ y la cola $Q$ definen el corte $(S, Q)$. Los vértices en $s$ ya fueron agregados al AGM. Cuando extraemos el mínimo de $Q$, estamos eligiendo el vértice que tiene una arista de menor peso que atraviesa el corte, es decir, conecta el vértice con el resto del árbol (excepto en la primer iteración en donde extraemos $s$ por cómo lo inicializamos, por eso el AGM está enraizado en $s$).

Cada vez que agregamos un vértice $v$ en $S$ lo sacamos de $Q$, redefiniendo el corte. Además actualizamos el peso mínimo para llegar a los vecinos de $v$ que aún están en $Q$ usando aristas que cruzan el corte.

Cuando $Q = \empty$ vale $S = V$, y utilizando el atributo `parent` podemos reconstruir el AGM.

## Complejidad

La complejidad de Prim depende de la implementación de la cola de prioridad.

- Min heap: $O(E * log(V))$
- Fibonacci heap: $O(V * log(V) + E)$

Para grafos densos conviene usar la versión con Fibonacci heap, ya que en ese caso $E = O(V^2)$.
