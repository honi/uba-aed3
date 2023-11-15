# Algoritmo de Edmonds-Karp

Los datos de entrada y definiciones están en el documento de [Flujo Máximo](./flujo-maximo.md).

El algoritmo de Edmonds-Karp en realidad utiliza el método de Ford-Fulkerson, pero en vez de utilizar DFS para encontrar caminos de aumento, utiliza BFS.

Este cambio obtiene una complejidad $O(V*E^2)$ que no depende del valor del flujo máximo. Además, prioriza los caminos de aumento con menor cantidad de aristas. En la práctica esto puede resultar mucho más eficiente si el flujo máximo es muy grande y hay mucha varianza entre las capacidades de las aristas.
