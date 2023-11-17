# Reducciones

## TSP es NP-Completo

TSP: dado un grafo pesado $G$ con función de peso $w:E \rightarrow \mathbb{R}$ y $k \in \mathbb{R}$. ¿existe un circuito hamiltoniano de peso menor igual a $k$?

Mostramos que TSP es NP-Completo sabiendo que HAM: circuito hamiltoniano es NP-Completo. Para esto primero mostramos que TSP es NP presentando un certificado polinomial y su respectivo verificador polinomial.

**Certificado**: permutación de vértices de $G$.

**Verificador**: revisamos que sea una permutación válida de todos los vértices de $G$ y que existan aristas entre todo par de vértices consecutivos y entre el primero y el último. Luego sumamos el peso de todas las aristas del circuito y vemos que sea menor igual a $k$.

Ahora mostramos que existe una reducción polinomial $f$ tal que HAM $\leq_P$ TSP.

Sea $G=(V,E) \in D_{HAM}$ una instancia cualquiera. $f((V,E)) = (K_{|V|}, |V|) \in D_{TSP}$ con $K_{|V|}$ pesado con función de peso $w:E \rightarrow \mathbb{N}$.

$$w(e) = \begin{cases}
1 & \text{si } e \in E \\
2 & \text{si } e \notin E \\
\end{cases}$$

Armamos un grafo completo pesado con los mismos vértices que el grafo $G$ de HAM, y les ponemos peso 1 si la arista está en $G$ o 2 si no está en $G$. Si existe un circuito hamiltoniano en $G$ entonces vamos a poder encontrarlo en TSP usando las aristas originales de $G$ que tienen peso 1 y por lo tanto el circuito tiene peso total igual a $|V|$. Si no existe el circuito hamiltoniano, entonces TSP va a poder encontrar uno porque $K_{|V|}$ es completo, pero necesariamente va a tener que utilizar alguna arista que no estaba en el grafo original $G$, la cual tiene peso 2, y luego el peso total del circuito (que tiene $|V|$ aristas) será mayor a $|V|$ por lo que TSP responderá que *no*.

## Conjunto independiente máximo (MIS) es NP-Completo

Reducción Clique $\leq_P$ MIS.
