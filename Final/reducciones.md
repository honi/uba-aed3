# Reducciones

## TSP es NP-Completo

TSP: dado un grafo pesado $G$ con función de peso $w:E \rightarrow \mathbb{R}$ y $k \in \mathbb{R}$. ¿existe un circuito hamiltoniano de peso menor igual a $k$?

Mostramos que TSP es NP. Para esto presentamos un certificado polinomial y su respectivo verificador polinomial.

**Certificado**: permutación de vértices de $G$.

**Verificador**: revisamos que sea un circuito hamiltoniano y luego sumando el peso de todas las aristas del circuito vemos que sea menor igual a $k$.

Usamos el problema HAM: circuito hamiltoniano, que ya sabemos que es NP-Completo, para mostrar que existe una reducción polinomial $f$ tal que HAM $\leq_P$ TSP.
