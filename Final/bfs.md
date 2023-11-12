# BFS: Breadth-first search

**Objetivo**

Visitar todos los vértices alcanzables desde algún vértice fuente $s$ realizando un recorrido en anchura. Durante este proceso podemos resolver los siguientes problemas:

- Encontrar caminos mínimos (en cantidad de aristas) desde $s$ a todos los otros vértices.
- Medir la distancia (en cantidad de aristas) desde $s$ a todos los otros vértices.
- Encontrar todos los vértices alcanzables desde $s$.
- Encontrar componentes conexas.

**Idea**

Empezando por $s$, descubrimos todos su vecinos (están a distancia 1 de $s$). Luego, descubrimos todos los vecinos de sus vecinos (están a distancia 2 de $s$). Así sucesivamente hasta que no haya más vecinos para descubrir. En otras palabras, descubrimos todos los vértices a distancia $k$ de $s$ antes de descubrir los que están a distancia $k+1$. BFS recorre el grafo en "anchura", o por niveles. Es como una onda expansiva desde $s$.

**Algoritmo**

```python
def bfs(G, s):
    for v in G.V:
        v.visited = False
        v.distance = -1 # -infty
        v.parent = None

    s.visited = True
    s.distance = 0
    s.parent = None

    Q = [s]
    while Q:
        u = Q.pop(0)
        for v in G.Adj[u]:
            if not v.visited:
                v.visited = True
                v.distance = u.distance + 1
                v.parent = u
                Q.append(v)
```

Utilizamos una cola FIFO para procesar los vértices. Cada vez que procesamos un vértice, revisamos todos sus vecinos y agregamos a la cola los que aún no fueron visitados.

Cuando descubrimos un vértice no visitamos, le agregamos algunos atributos que nos brindan información al finalizar el algoritmo:

- `visited`: indica si visitamos ese vértice o no. Al terminar de correr BFS, todos los vértices que no fueron visitados pertenecen a otra componente conexa del grafo. Si visitamos todos los vértices entonces el grafo es conexo.
- `parent`: indica quién es el padre en el árbol BFS. Con esta información podemos construir un árbol enraizado en $s$. El camino en este árbol desde $s$ a cualquier otro vértice es un camino mínimo en cantidad de aristas.
- `distance`: indica la distancia mínima en cantidad de aristas desde $s$.

**Complejidad**

Inicialmente ningún vértice está marcado como visitado, y el algoritmo una vez que marca uno como visitado, nunca lo desmarca. Como ésta es la condición para encolar vértices (que no estén visitados), en la cola entran a lo sumo todos los vértices una única vez: $O(V)$.

Por otro lado, cada vez que descubrimos un vértice revisamos su lista de adyacencia. Como esto sucede una única vez por vértice, en total revisamos una vez cada arista: $O(E)$.

Asumimos que podemos encolar y desencolar en $O(1)$ (por ejemplo con una lista enlazada). El resto de las operaciones realizadas son $O(1)$. La inicialización de los atributos es: $O(V)$.

La complejidad final resulta $O(V+E)$.

El espacio requerido es $O(V)$ pues en el peor caso encolamos todos los vértices al mismo tiempo (por ejemplo si fuese un grafo completo).
