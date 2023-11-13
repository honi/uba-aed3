# Algoritmo de Kruskal

Este algoritmo genera un bosque de AGMs. Pero si el grafo es conexo entonces nos retorna directamente un AGM. La idea del algoritmo es ir agregando la arista de menor peso al bosque siempre y cuando no genere ciclos.

Inicialmente colocamos cada vértice en un árbol distinto. En cada paso, elegimos la arista de menor peso que conecta 2 árboles distintos. La agregamos al bosque combinando esos 2 árboles en uno solo. Repetimos este paso hasta que no haya más aristas para procesar.

**Disjoint-set / union-find**

Para que el algoritmo sea eficiente necesitamos una forma eficiente de determinar si una arista conecta 2 árboles distintos, y consecuentemente combinarlos en un único árbol. Para esto se utiliza una estructura llamada "disjoint-set" (también conocida como "union-find") que nos provee las siguientes operaciones:

- `make_set(x)`: crea un nuevo conjunto con x como representante.
- `find_set(x)`: retorna el representante de x.
- `union(x, y)`: combina los conjuntos que contienen a x e y en uno solo.

Además existen algunas optimizaciones que funcionan muy bien en la práctica:

- Union by rank: al combinar 2 conjuntos se elige como representante al que tiene mayor rank, así solo tenemos que actualizar el conjunto más chico.
- Path compression: al buscar un representante se quitan los "representantes intermedios", así la próxima vez que se consulte por el representate de cualquier elemento dentro del mismo conjunto ya tenemos la respuesta inmediatamente.

**Algoritmo**

```python
def kruskal(G):
    A = []
    for v in G.V:
        make_set(v)
    edges = sorted(G.E) # Ordena por peso de menor a mayor.
    for (u, v) in edges:
        if find_set(u) != find_set(v):
            A += [(u, v)]
            union(u, v)
    return A
```

**Correctitud**

Primero probamos que el algoritmo obtiene un AG. Sea $G$ un grafo conexo y pesado, y $T$ el subgrafo generado por el algoritmo. $T$ no puede tener ciclos, ya que por definición una arista es descartada si forma un ciclo. $T$ no puede estar desconectado porque el algoritmo hubiese agregado la primer arista que encuentra que conecta las 2 componentes. Entonces $T$ es un AG de $G$.

Segundo probamos que el algoritmo obtiene un AGM por inducción en las iteraciones.

Hipótesis inductiva: si $A$ es el conjunto de aristas seleccionadas por el algoritmo en cualquier iteración, entonces existe un AGM $T$ que contiene a $A$ y ninguna de las aristas rechazadas por el algoritmo.

Caso base: $A = \emptyset$. Claramente vale pues $A$ está en cualquier AGM de un grafo $G$ conexo y pesado.

Paso inductivo. Si la arista $e$ que agrega el algoritmo está en $T$, entonces vale que $A+e \subset T$. Caso contrario significa que $T+e$ tiene un ciclo $C$. Notemos que $C$ tiene aristas que no están en $A$, ya que no hay ciclos en $A+e$.

Sea $f$ alguna arista en $C$ que además no está en $A$. Como el algoritmo eligió la arista $e$ en vez de $f$, necesariamente $w(e) \leq w(f)$. Podemos construir otro árbol $T' = T - f + e$ que tiene el mismo peso que $T$ o menor: $w(T') = w(T) - w(f) + w(e) \leq w(T)$. Como $T$ es un AGM vale que $w(T) \leq w(T')$. Por lo tanto $w(T') = w(T)$, $T'$ es un AGM, $A+e \subset T'$ y se cumple la hipótesis inductiva.

Cuando $A$ es un AG, por la hipótesis inductiva $A$ es también un AGM.

**Complejidad**

Inicializar los $|V|$ árboles cuesta $O(V)$. Ordenar las aristas es $O(sort(E))$, que lo dejamos sin especificar ya que quizás el problema admite algún ordenamiento que no sea por comparaciones lo cual brinda una mejor complejidad. El bucle realiza $O(E)$ iteraciones donde cada iteración tiene una complejidad de $O(\alpha(V))$ en el llamado a `union`.

La complejidad resulta: $O(V + sort(E) + E * \alpha(V))$.
