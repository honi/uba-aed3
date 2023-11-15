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

Existen varias formas de obtener un orden topológico. Si tenemos una implementación de DFS que retorna los tiempos de finalización para cada vértice, entonces se puede obtener un orden topológico muy fácilmente con el siguiente algoritmo.

```python
def topological_sort(G):
    dfs(G)
    return sorted(G.V, key=-v.finish)
```

Esta implementación tiene como precondición que G sea un DAG. Si no, se puede utilizar el mismo DFS para detectar los back edges (que indican que hay un ciclo) y retornar algún error.

## Correctitud

Lema: un grafo dirigido $G$ es acíclico $\iff$ DFS(G) no encuentra back edges.

Demo por el contrarrecíproco: un grafo dirigido $G$ tiene un ciclo $\iff$ DFS(G) encuentra un back edge.

$\Leftarrow$ Supongamos que DFS encuentra un back edge $(u, v)$. Entonces $v$ es un ancestro de $u$. Luego, $G$ tiene un camino de $v$ a $u$ y el back edge $(u, v)$ completa el ciclo.

$\Rightarrow$ Supongamos que $G$ tiene un ciclo. Sea $v$ el primer vértice visitado en ese ciclo y $(u, v)$ la arista precedente a $v$ en el ciclo. DFS visita todos los vértices desde $v$ hasta $u$ los cuales resultan descendientes de $v$. Entonces la arista $(u,v)$ es un back edge.

Con este lema podemos probar más facilmente la correctitud del algoritmo. Lo que queremos ver es que ordenar por el tiempo de finalización de forma decreciente genera un orden topológico.

Supongamos que corremos DFS sobre un DAG $G$ para determinar el tiempo de finalización $v.f$ de cada vértice $v \in G.V$. Para toda arista $(u,v)$ tiene que valer $v.f < u.f$ para que $u$ aparezca antes que $v$ en el orden topológico.

Consideremos una arista cualquiera $(u,v)$. Cuando exploramos esta arista, $v$ no puede estar siendo explorado, pues sino $v$ sería un ancestro de $u$ y la arista $(u,v)$ sería un back edge. Esto no puede pasar por el lema que probamos al principio.

Entonces solo pueden pasar 2 cosas: $v$ aún no fue visitado y va a ser un descendiente de $u$, por lo tanto $v.f < u.f$. O sino $v$ y sus descendientes ya fueron visitados, y por lo tanto $v.f$ ya está definido. Como $u$ está siendo explorado en este momento, aún no tiene definido $u.f$, pero cualquier valor que tome será más grande que $v.f$.

## Complejidad

Lineal: $O(V + E)$.
