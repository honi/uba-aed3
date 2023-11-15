# Orden topológico

El orden topológico está definido para un grafo dirigido acíclico (DAG). Si los vértices representan tareas y las aristas representan dependencias entre las tareas, consistente en ordenar linealmente los vértices de forma tal que si se realizan las tareas en ese orden se respetan todas las dependencias.

Más formalmente, si existe una arita $(u, v)$ en el DAG, entonces $u$ aparece antes que $v$ en el orden topológico.

El siguiente DAG admite un único orden topológico: $A, B, C$.

```
A --> B --> C
```

Mientras que este otro DAG admite varios: $A, B, C$ o $B, A, C$.

```
A --.--> C
B -´
```

Si el grafo es dirigido pero tiene ciclos, entonces no existe ningún orden topológico posible.

## Algoritmo

Existen varias formas de obtener un orden topológico. Podemos extender una implementación de DFS para que agregue adelante de la lista enlazada `L` cada vértice que termina de visitar (es decir, cuando vuelve del llamado recursivo de todos sus vecinos).

Esta implementación tiene como precondición que G sea un DAG. Si no, se puede utilizar el mismo DFS para detectar los back edges (que indican que hay un ciclo) y retornar algún error.

```python
def topological_sort(G):
    L = []
    # Cada vez que terminamos de visitar un vértice
    # lo agregamos al principio de la lista enlazada L.
    dfs(G, L)
    return L
```

## Correctitud

**Lema**

Sea $G=(V,E)$ un grafo dirigido.

> $G$ es acíclico (es un DAG) $\iff$ DFS(G) no encuentra back edges.

Demo por el contrarrecíproco: un grafo dirigido $G$ tiene un ciclo $\iff$ DFS(G) encuentra un back edge.

$\Leftarrow$ Supongamos que DFS encuentra un back edge $(u, v)$. Entonces $v$ es un ancestro de $u$. Luego, $G$ tiene un camino de $v$ a $u$ y el back edge $(u, v)$ completa el ciclo.

$\Rightarrow$ Supongamos que $G$ tiene un ciclo. Sea $v$ el primer vértice visitado en ese ciclo y $(u, v)$ la arista precedente a $v$ en el ciclo. DFS visita todos los vértices desde $v$ hasta $u$ los cuales resultan descendientes de $v$. Entonces la arista $(u,v)$ es un back edge.

**Teorema**

Con este lema podemos probar más facilmente la correctitud del algoritmo. Lo que queremos ver es que al terminar el DFS, la lista enlazada $L$ contiene un orden topológico.

La lista enlazada $L$ comienza vacía. Solo agregamos vértices al principio de la lista (adelante de los que ya fueron agregados). Para toda arista $(u,v) \in E$ tiene que suceder que $u$ aparece antes que $v$ en el orden topológico. En otras palabras, $v$ se tiene que insertar en $L$ antes que $u$.

Supongamos que DFS tomó el camino por la arista $(u,v)$. Notemos que todavía no agregamos $u$ a la lista $L$. No puede pasar que $v$ ya esté visitado porque entonces $(u,v)$ sería un back edge, y por el lema anterior, como $G$ no tiene ciclos no pueden haber back edges.

Si $v$ ya fue visitado entonces vamos a terminar de visitar $v$ antes que $u$, en particular ya lo visitamos. Si $v$ no fue visitado aún, entonces es un descendiente de $u$ y también vamos a terminar de visitarlo antes que $u$.

En ambos casos, terminamos de visitar $v$ antes que $u$, entonces insertamos en $L$ primero $v$ y luego $u$, y como se inserta adelante de la lista, se cumple que $u$ aparece antes que $v$ en $L$.

## Complejidad

Lineal: $O(V + E)$.
