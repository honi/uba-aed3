# Algoritmo de Kruskal

Este algoritmo genera un bosque de AGMs. Pero si el grafo es conexo entonces nos retorna directamente un AGM. La idea del algoritmo es ir agregando la arista de menor peso al bosque siempre y cuando no genere ciclos.

Inicialmente colocamos cada vértice en un árbol distinto. En cada paso, elegimos la arista de menor peso que conecta 2 árboles distintos. La agregamos al bosque combinando esos 2 árboles en uno solo. Repetimos este paso hasta que no haya más aristas para procesar.

## Disjoint-set / union-find

Para que el algoritmo sea eficiente necesitamos una forma eficiente de determinar si una arista conecta 2 árboles distintos, y consecuentemente combinarlos en un único árbol. Para esto se utiliza una estructura llamada "disjoint-set" (también conocida como "union-find") que nos provee las siguientes operaciones:

- `make_set(x)`: crea un nuevo conjunto con x como representante.
- `find_set(x)`: retorna el representante de x.
- `union(x, y)`: combina los conjuntos que contienen a x e y en uno solo.

Además existen algunas optimizaciones que funcionan muy bien en la práctica:

- Union by rank: al combinar 2 conjuntos se elige como representante al que tiene mayor rank, así solo tenemos que actualizar el conjunto más chico.
- Path compression: al buscar un representante se quitan los "representantes intermedios", así la próxima vez que se consulte por el representate de cualquier elemento dentro del mismo conjunto ya tenemos la respuesta inmediatamente.

## Algoritmo

```python
def kruskal(G):
    A = []
    for v in G.V:
        make_set(v)
    for (u, v) in sorted(edges): # Ordenado por peso de menor a mayor.
        if find_set(u) != find_set(v):
            A += [(u, v)]
            union(u, v)
    return A
```

## Correctitud

Nos apoyamos en la [demostración del algoritmo goloso para construir un AGM](./agm.md).

En cada iteración, agregamos en $A$ la arista $e=(u,v)$ de menor peso que conecta dos componentes conexas distintas (determinamos esto con el `if` usando las operaciones del disjoint-set). Podemos definir el corte $(S, T)$ simplemente poniendo en $S$ la componente conexa de $u$ y en $T$ la componente conexa de $v$. El resto de las componentes en $A$ las podemos agregar en $S$ o $T$, es indistinto.

Entonces el corte $(S,T)$ respeta $A$ y $e$ es una arista de peso mínimo que cruza el corte.

## Complejidad

- Inicializar los $|V|$ árboles: $O(V)$.
- Ordenar las aristas: $O(sort(E))$.
    - Lo dejamos sin especificar ya que quizás el problema admite algún ordenamiento que no sea por comparaciones lo cual brinda una mejor complejidad, o quizás las aristas ya vienen ordenadas.
- El `for` realiza $O(E)$ iteraciones.
- Cada iteración tiene una complejidad de $O(\alpha(V))$ en las operaciones del disjoint-set si se usa una implementación optimizada con union by rank y path compression.

La complejidad resulta: $O(V + sort(E) + E * \alpha(V))$.
