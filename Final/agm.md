# AGM: árbol generador mínimo

Un árbol se caracteriza por:

- Es un grafo conectado y acíclico.
- Si sacamos cualquier arista se desconecta.
- Si agregamos cualquiera arista se forma un ciclo.

Un árbol generador (AG) de un grafo es un subgrafo que tiene el mismo conjunto de vértices y es un árbol. Todo grafo conexo tiene al menos un AG.

Un árbol generador mínimo (AGM) es un AG que a su vez tiene costo mínimo. El costo proviene de sumar el peso de todas las aristas utilizadas en el AGM.

Sea $G = (V, E)$ un grafo pesado con $w: E \rightarrow \mathbb{R}$ el peso de las aristas. Sea $T \subseteq E$ un AG de $G$. Definimos T como un grafo inducido por sus aristas. $T$ es AGM de $G$ si minimiza:

$$w(T) = \sum_{e \in T} w(e)$$
