# DFS: Depth-first search

## Objetivo

Visitar todos los vértices realizando un recorrido en profundidad y generando un bosque. Durante este proceso podemos resolver los siguientes problemas:

- Encontrar ciclos.
- Clasificar aristas.
- Ordenar los vértices (topological sort).
- Encontrar todos los vértices alcanzables desde $s$.
- Encontrar componentes conexas y fuertemente conexas.

## Idea

Empezamos por algún vértice cualquiera, usando alguna de sus aristas descubrimos a un vecino, luego a un vecino de ese vecino, etc. Así sucesivamente hasta que no haya más vecinos para descubrir, o que descubramos un vértice que ya visitamos (encontramos un ciclo). En otras palabras, descubrimos la mayor cantidad posible de vértices realizando un recorriendo en profunidad. Cuando ya no podemos avanzar más, hacemos backtracking y repetimos el proceso usando una arista nueva.

Podemos pensarlo como si los vértices son bolitas y las aristas son sogas que unen a las bolitas. Elegimos un vértice cualquiera y levantamos todo el grafo desde esa bolita. Por efecto de la gravedad el resto de las bolitas van a caer y quedar colgadas, representando la profunidad a la cual llegaría DFS. Las bolitas que pertenecen a otra componente conexa caerían al piso.

## Algoritmo

```python
def dfs(G):
    time = 1

    def dfs_visit(u):
        nonlocal time
        u.visited = True
        u.start = time
        time += 1
        for v in G.Adj[u]:
            if not v.visited:
                v.parent = u
                dfs_visit(v)
        u.finish = time
        time += 1

    for u in G.V:
        u.visited = False
        u.parent = None

    for u in G.V:
        if not u.visited:
            dfs_visit(u)
```

Esta es una implementación recursiva de DFS. Por la naturaleza de los problemas que resuelve DFS, no especificamos un vértice fuente ya que nos interesa visitar todos los vértices y generar un bosque.

El ciclo en `dfs` dispara los recorridos en profundidad para todo vértice aún no visitado. La función recursiva `dfs_visit` realiza propiamente dicho el recorrido en profunidad, tomando un vecino no visitado de $u$ y avanzando por ahí.

Cuando visitamos un vértice, le agregamos algunos atributos que nos brindan información al finalizar el algoritmo:

- `visited`: indica si visitamos ese vértice o no. Al terminar de correr DFS todos los vértices fueron visitados. Este atributo lo usamos internamente en el algoritmo, pero no nos dice nada al finalizar.
- `parent`: indica quién es el padre en el bosque DFS. Con esta información podemos construir un bosque de componentes conexas.
- `start` y `finish`: indican el tiempo cuando se visitó el vértice y cuando se terminó el recorrido en profunidad desde ese vértice. Esta información es muy útil para luego obtener información acerca del grafo, por ejemplo si un vértice es descendiente de otro en el bosque DFS.

## Clasificación de aristas

Mientras realizamos el DFS podemos ir clasificando las aristas lo cual nos aporta información adicional sobre grafo.

- Tree edges: son las aristas que forman el bosque, en esencia las que usamos para avanzar en el recorrido en profunidad.
- Back edges: cuando estamos visitando un vértice $u$ y detectamos que la arista $(u,v)$ nos lleva a un vértice $v$ que ya fue visitado, entonces la arista $(u,v)$ es un back edge. El vértice $v$ es un ancestro de $u$ y si colocamos esta arista en el árbol se formaría un ciclo.

En grafos dirigidos hay además otros 2 tipos de aristas:

- Forward edges: conectan un vértice $u$ con algún descendiente $v$ al cual ya llegamos por otro camino.
- Cross edges: conectan un vértice $u$ con un vértice $v$ que está en otra rama del árbol o directamente en otro árbol dentro del bosque.

## Complejidad

Inicialmente ningún vértice está marcado como visitado, y el algoritmo una vez que marca uno como visitado, nunca lo desmarca. Como ésta es la condición para visitar vértices, cada vértice se visita una única vez: $O(V)$.

Por otro lado, cada vez que descubrimos un vértice revisamos su lista de adyacencia. Como esto sucede una única vez por vértice, en total revisamos una vez cada arista: $O(E)$.

El resto de las operaciones realizadas son $O(1)$. La inicialización de los atributos es: $O(V)$.

La complejidad final resulta $O(V+E)$.

El espacio requerido es $O(V)$ el cual es usado en el stack de llamados recursivos. En el peor caso realizamos un solo recorrido en profunidad y visitamos todos los vértices del grafo en una sola recursión.
