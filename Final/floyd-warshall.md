# Algoritmo de Floyd-Warshall

El algoritmo de Floyd-Warshall encuentra el camino mínimo entre todo par de vértices. Este algoritmo acepta aristas con pesos negativos pero no puede haber ciclos negativos.

Recibimos como entrada el grafo $G=(V,E)$ representado por una matriz de adyacencia $W: \mathbb{R}^{|V| \times |V|}$ que además contiene el peso de las aristas.

$$w_{ij} = \begin{cases}
0 & \text{si } i = j \\
\text{el peso de la arista } i \rightarrow j & \text{si } (i, j) \in E \\
\infty & \text{caso contrario}
\end{cases}$$

Como salida obtenemos otra matriz $D: \mathbb{R}^{|V| \times |V|}$. Para cualquier par de vértices $i,j \in V$, tenemos $d_{ij} = \delta(i,j)$, el peso del camino mínimo de $i$ a $j$.

También podríamos resolver este problema utilizando algún algoritmo de camino mínimo uno a todos, como ser Bellman-Ford o Dijkstra, corriendolo $|V|$ veces, una vez por cada vértice $v \in V$. Pero Floyd-Warshall es más simple de implementar y nos da una muy buena complejidad en general.

## Correctitud

En vez de relajar aristas, Floyd-Warshall utiliza otra estrategia. Definimos un **vértice intermedio** de un camino mínimo $p = \langle v_0, \dots, v_t \rangle$ como cualquier vértice de $p$ que no sea $v_0$ ni $v_t$.

Con $n=|V|$ y numerando todos los vértices $1, \dots, n$, tomamos un conjunto cualquiera $\lbrace 1, \dots, k \rbrace$ para algún $k \leq n$. Para cualquier par de vértices $i,j \leq n$, consideramos algún camino mínimo $p$ desde $i$ a $j$ usando solamente vértices intermedios del conjunto $\lbrace 1, \dots, k \rbrace$.

Observemos la relación entre $p$ y cualquier otro camino mínimo de $i$ a $j$ usando solamente vértices intermedios del conjunto $\lbrace 1, \dots, k-1 \rbrace$. La clave es si $k$ está en $p$ o no. Esta intuición la vamos a usar para formular una definición recursiva del algoritmo.

Si $k$ no está en $p$, entonces $p$ es un camino mínimo de $i$ a $j$ usando solamente vértices intermedios del conjunto $\lbrace 1, \dots, k-1 \rbrace$, y por lo tanto podemos construir el mismo camino mínimo $p$ usando solamente vértices intermedios del conjunto $\lbrace 1, \dots, k \rbrace$. Pasar por $k$ no mejora el camino mínimo.

Si $k$ está en $p$, podemos descomponer $p$ en subcaminos: $p = i \leadsto k \leadsto j$. Por la subestructura óptima de los caminos mínimos, estos 2 subcaminos son también mínimos. Lo importante es que $k$ no es un vértice intermedio de $i \leadsto k$ ni de $k \leadsto j$ (por definición), entonces estos 2 subcaminos usan solamente vértices intermedios del conjunto $\lbrace 1, \dots, k-1 \rbrace$, y el peso del camino es $w(p) = w(i \leadsto k) + w(k \leadsto j)$

Formulamos entonces una definición recursiva del algoritmo usando estas observaciones. Sea $d_{ij}^k$ el peso del camino mínimo de $i$ a $j$ usando solamente vértices intermedios del conjunto $\lbrace 1, \dots, k \rbrace$.

Para el caso base $k=0$, el conjunto de vértices intermedios es vacío, por lo tanto el único camino mínimo posible de $i$ a $j$ es utilizar la arista $i \rightarrow j$ si existe, y $w_{ij}$ representa el peso de este camino mínimo. Para el caso general usamos las observaciones antes mencionadas.

$$d_{ij}^k = \begin{cases}
w_{ij} & \text{si } k = 0 \\
min \lbrace d_{ij}^{(k-1)}, d_{ik}^{(k-1)} + d_{kj}^{(k-1)} \rbrace & \text{si } k \geq 1
\end{cases}$$

Cuando $k=n$ obtenemos los caminos mínimos usando solamente vértices intermedios del conjunto $\lbrace 1, \dots, n \rbrace$, en efecto podemos usar cualquier vértice del grafo, y por lo tanto $d_{ij}^n = \delta(i,j)$ para todo par de vértices $i,j \in V$.

## Algoritmo

Usamos programación dinámica con una estrategia bottom-up, empezando con $k=1$, y en cada iteración calculamos $d_{ij}^k$ hasta llegar a $k=n$.

```python
def floyd_warshall(W, n):
    D[0] = W
    for k = 1 to n:
        D[k] = D[k-1].copy()
        for i = 1 to n:
            for j = 1 to n:
                D[k][i][j] = min(
                    D[k-1][i][j],
                    D[k-1][i][k] + D[k-1][k][j],
                )
    return D[n]
```

## Complejidad

Resulta evidente por los 3 `for` nesteados que la complejidad es $\Theta(V^3)$.
