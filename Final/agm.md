# AGM: árbol generador mínimo

Un árbol se caracteriza por:

- Es un grafo conectado y acíclico.
- Si sacamos cualquier arista se desconecta.
- Si agregamos cualquiera arista se forma un ciclo.

Un árbol generador (AG) de un grafo es un subgrafo que tiene el mismo conjunto de vértices y es un árbol. Todo grafo conexo tiene al menos un AG.

Un árbol generador mínimo (AGM) es un AG que a su vez tiene costo mínimo. El costo proviene de sumar el peso de todas las aristas utilizadas en el AGM.

Sea $G = (V, E)$ un grafo pesado con $w: E \rightarrow \mathbb{R}$ el peso de las aristas. Sea $T \subseteq E$ un AG de $G$. Definimos T como un grafo inducido por sus aristas. $T$ es AGM de $G$ si minimiza:

$$w(T) = \sum_{e \in T} w(e)$$

## Algoritmo goloso para construir un AGM

Sea $G=(V,E)$ un grafo conexo pesado con $w: E \rightarrow \mathbb{R}$ el peso de las aristas.

```python
def agm(G):
    A = []
    while len(A) < len(G.V) - 1: # A no es AGM.
        e = elegimos una arista segura
        A += [e]
    return A
```

Si $(S, V-S)$ es un corte que respeta $A$, es decir, ninguna arista de $A$ cruza este corte, todas las aristas de peso mínimo que cruzan el corte son seguras para agregar a $A$. Elegir una de estas aristas en cada paso es una elección golosa que construye un AGM. Veamos que es correcta por invariante.

**Invariante**: $A \subseteq T$ para algún $T$ AGM de $G$.

Antes de iniciar el ciclo vale $A = \emptyset$ que está incluído en todos los AGM trivialmente.

**Conservación**: Sea $T$ un AGM de $G$ tal que $A \subseteq T$. Sea $(S, V-S)$ un corte que respeta $A$ y $e=(u,v)$ una arista de peso mínimo que cruza el corte. Queremos ver que existe algún AGM $T'$ de $G$ tal que $A+e \subseteq T'$.

Si $e \in T$ entonces $A+e \subseteq T$ y podemos tomar $T' = T$.

Caso contrario, como $T$ es un árbol, en $T + e$ hay un ciclo formado por la arista $e$ y un camino que conecta $u$ y $v$. En particular, en $T$ hay una arista $f=(x,y)$ que está en el camino entre $u$ y $v$, y además cruza el corte al igual que $e$, es decir $x \in S$, $y \in V-S$.

Definimos $T' = T - f + e$, el cual sigue siendo un AG porque las aristas $f$ y $e$ pertenecen al mismo ciclo. Para ver que $T'$ es AGM, miremos cómo cambia el peso: $w(T') = w(T) - w(f) + w(e)$. Como elegimos una arista de menor peso que cruza el corte vale que $w(e) \leq w(f)$, y entonces $w(T') \leq w(T)$. A su vez, tomamos $T$ AGM, entonces $w(T) \leq w(T')$. Por lo tanto $w(T') = w(T)$, y $T'$ es un AGM.

Después de $|V|-1$ iteraciones, $A$ es un árbol y está incluído en algún $AGM$. Por lo tanto $A$ es un AGM.
