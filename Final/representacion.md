# Representación de grafos

Existen dos formas principales para representar un grafo en memoria. Cada representación tiene ventajas y desventajas según el tipo de grafo y los algoritmos que queremos ejecutar.

En ambas representaciones enumeramos los vértices: `1, ..., |V|`.

# Matriz de adyacencia

Consistente en utilizar una matriz `A` de `|V| x |V|` para codificar las aristas del grafo. Si existe una arista `(i, j)` que conecta el vértice `i` con el vértice `j` entonces `A[i][j] = A[j][i] = 1`, caso contrario vale `0`.

Notemos que si el grafo no es dirigido entonces `A` es simétrica. Pero si el grafo fuese dirigido, la existencia de la arista `(i, j)` se representa únicamente con `A[i][j] = 1`. Para que también tengamos `A[j][i] = 1` debería existir la arista `(j, i)`.

Por otro lado, estamos utilizando los valores `1` y `0` para representar si existe o no la arista en el grafo. Esto aplica para grafos no pesados. Si tuviésemos un grafo pesado podemos codificar el peso de las aristas como valores en la matriz. Si nuestro problema no admite pesos nulos (valor `0`), entonces podemos usar el `0` para representar la no existencia de una arista. Caso contrario, necesitamos encontrar algún valor especial que no sea ningún peso válido para indicar que una arista no existe en el grafo. Otra opción es utilizar la matriz solo para la existencia de las aristas, y luego utilizar una función de peso para obtener el peso de dichas aristas.

Más formalmente podemos definir la matriz de adyacencia de la siguiente manera (para grafos no pesados):

$$
A \in \{0, 1\}^{|V| \times |V|}
\hspace{40pt}
a_{ij} = \begin{cases}
    1 & \text{si} \; \exists (i,j) \in E \\
    0 & \text{caso contrario}
\end{cases}$$

**Complejidades**

- Inicialización: $O(V^2)$
- Recorrer todos los vértices y aristas: $O(V^2)$
- Comprobar si existe, agregar o remover una arista: $O(1)$
- Recorrer el vecindario de un vértice: $O(V)$
- Espacio requerido para la estructura: $O(V^2)$

# Listas de adyacencia

Esta representación utiliza un vector `A` de listas enlazadas (en la implementación podrían ser vectores también). El tamaño de `A` es `|V|` porque cada vértice tiene su propia lista de vecinos. En la lista que se encuentra en `A[i]` tenemos los vecinos del vértice `i`.

A diferencia de la matriz de adyacencia, con esta representación no desperdiciamos memoria. El espacio requerido para codificar los vecinos de un vértice `i` es exactamente la cantidad de vecinos que tiene en el grafo. Es decir, `|A[i]| = |N(i)|` donde `N(i)` son los vecinos del vértice `i`.

**Complejidades**

- Inicialización: $O(V + E)$
- Recorrer todos los vértices y aristas: $O(V + E)$
    - No obstante, si el grafo es denso, entonces $E = O(V^2)$ y la complejidad asintótica resulta igual que la matriz de adyacencia: $O(V^2)$.
- Comprobar si existe, agregar o remover una arista que incide sobre $v$: $\Theta(|N(v)|) = O(V)$
- Recorrer el vecindario de un vértice $v$: $\Theta(|N(v)|) = O(V)$
- Espacio requerido para la estructura: $O(V + E)$

En general esta representación es más eficiente para la mayoría de los algoritmos que vamos a utilizar.

# Otras representaciones

A veces el grafo que modela nuestro problema puede resultar muy grande (como por ejemplo los estados de un cubo rubik o un tablero de ajedrez). En estos casos se puede optar por otro tipo de representación en donde no se precomputa el grafo de forma explícita, sino que a partir de un estado inicial (un vértice), vamos generando las aristas y vecinos a medida que recorremos el grafo. No se persisten los vértices ya procesados, y las aristas solo existen conceptualmente, son las reglas que definen a qué vértices podemos llegar desde el vértice actual.
