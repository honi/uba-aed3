# Algoritmo de Ford-Fulkerson

Los datos de entrada y definiciones están en el documento de [Flujo Máximo](./flujo-maximo.md).

El algoritmo de Ford-Fulkerson encuentra el flujo máximo de la red $G$ incrementando el valor del flujo en cada iteración buscando **algún** camino de aumento. Termina cuando ya no hay ningún camino de aumento posible.

```python
def ford_fulkerson(G, s, t):
    for (u, v) in G.E:
        f(u, v) = 0
    while (existe camino de aumento p en Gf):
        cf(p) = min(cf(u, f) for (u, f) in p)
        for (u, v) in p:
            if (u, v) in G.E:
                f(u, v) += cf(p)
            else:
                f(u, v) -= cf(p)
    return f
```

**Correctitud**

Por el teorema de flujo máximo / corte mínimo, cuando ya no hay más caminos de aumento, $f$ es un flujo máximo en $G$.

**Complejidad**

Considerando capacidades enteras, en cada iteración se incrementa al flujo en al menos 1 unidad, por lo tanto se hacen a lo sumo $|F|$ iteraciones. Si las capacidades son racionales, podemos convertirlas en enteras con una transformación. Si son irracionales el algoritmo puede no converger y colgarse.

Buscamos utilizar una representación eficiente y un algoritmo lineal en las aristas para encontrar caminos de aumento, por ejemplo DFS. Si bien la red residual puede tener más aristas que la red original, a lo sumo hay $O(2E) = O(E)$.

Actualizar el flujo una vez encontrado el camino de aumento es $O(E)$.

La complejidad final resulta: $O(F*E)$.
