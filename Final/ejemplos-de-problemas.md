# Ejemplos de problemas P / NP

## Problemas P

- Determinar si un grafo $G$ es **conexo**.
    - DFS/BFS y luego revisamos si visitamos todos los vértices.
- Determinar si un grafo $G$ es **bipartito**.
    - DFS para detectar ciclos y verificar que no existe un ciclo de longitud impar.
- Encontrar un **camino mínimo** en $G=(V,E)$ desde $s \in V$.
    - Dijkstra o Bellman-Ford.
- Determinar el **diámetro** de un grafo $G$, es decir el camino mínimo más largo.
    - Floyd-Warshall para calcular todos los caminos mínimos y luego buscamos el más largo entre esos.
- Encontrar un **flujo máximo** $F$ en una red $G$ tal que $F \geq k \in \mathbb{N}$.
    - Ford-Fulkerson para obtener $F$ y luego comparamos con $k$.
- Dado un conjunto $C \subset \mathbb{Z}$ encontrar el **mínimo** $x \in C$.
    - Revisamos todos los elementos de $C$ y buscamos el mínimo.
- Determinar si un arreglo $A$ de números enteros está **ordenado**.
    - Recorremos una vez $A$ desde el primer elemento hasta el anteúltimo y verificamos que cada elemento sea menor o igual que su sucesor.

## Problemas NP

- **SAT**
    - Entrada: una fórmula proposicional $f$ en forma normal conjuntiva.
    - Salida: ¿existe una valuación que satisface $f$?
    - Certificado: una valuación para las variables de $f$.
    - Verificador: revisamos si la valuación hace verdadera a $f$.
- **3-SAT**
    - Es una restricción de SAT donde cada cláusula de $f$ tiene exactamente 3 variables.
- **MIS**: Conjunto independiente máximo
    - Un conjunto independiente en un grafo es un conjunto de vértices con son vecinos entre sí.
    - Entrada: un grafo $G$ y $k \in \mathbb{Z}^+$
    - Salida: ¿existe un conjunto independiente en $G$ de tamaño mayor o igual a $k$.
    - Certificado: un conjunto $S$ de vértices.
    - Verificador: revisamos que $|S| \geq k$, que todos los vértices de $S$ estén en $G$, y que no haya ninguna arista que conecte 2 vértices en $S$.
- Circuito hamiltoniano
    - Un circuito hamiltoniano es aquel que pasa por todos los vértices del grafo. Como es un circuito empieza y termina en el mismo vértice.
    - Entrada: un grafo $G$.
    - Salida: ¿existe un circuito hamiltoniano?
    - Certificado: permutación de vértices de $G$.
    - Verificador: revisamos que existan aristas entre todo par de vértices consecutivos y entre el primero y el último.
- **TSP**: Problema del viajante de comercio
    - Entrada: un grafo pesado $G$ con función de peso $w:E \rightarrow \mathbb{R}$ y $k \in \mathbb{R}$.
    - Salida: ¿existe un circuito hamiltoniano de peso menor igual a $k$?
    - Certificado: permutación de vértices de $G$.
    - Verificador: revisamos que sea un circuito hamiltoniano y luego sumando el peso de todas las aristas del circuito vemos que sea menor igual a $k$.

## Problemas NP-Completo

Notemos que todos los problemas NP también son NP-Completos.

- **Clique**
    - Entrada: un grafo $G$ y $k \in \mathbb{Z}^+$.
    - Salida: ¿exite un subgrafo completo de $k$ o más vértices en $G$?
- **Coloreo**
    - Entrada: un grafo $G$ y $k \in \mathbb{Z}^+$.
    - Salida: ¿se puede colorear $G$ con $k$ colores?
- **Matching 3D**
    - Entrada: un conjunto $M \subseteq A \times B \times C$ donde $|A| = |B| = |C| = k \in \mathbb{Z}$.
    - Salida: ¿existe un conjunto $M' \in M$ tal que $|M'| = k$ y no hay dos elementos en $M'$ que coincidan en alguna coordenadas?
