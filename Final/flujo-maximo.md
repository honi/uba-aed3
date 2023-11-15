# Flujo máximo

Los datos de entrada a este problema son un grafo dirigido $G=(V,E)$, un vértice fuente $s \in V$, otro vértice sumidero $t \in V$ y una función de capacidad para las aristas $c: E \rightarrow \mathbb{Z}^+$. Además, pedimos que si $(u,v) \in E$ entonces $(v,u) \notin E$ (esto se puede arreglar fácil agregando un vértice intermedio).

El problema de flujo máximo consistente en encontrar la máxima cantidad de flujo que puede circular desde $s$ hacia $t$, respetando las restricciones de capacidad de cada arista. El vértice $s$ produce unidades de flujo y $t$ las consume. Según el problema real que estemos resolviendo una unidad de flujo puede representar corriente eléctrica, litros de agua, información viajando por una red de comunicación, etc.

Se deben cumplir las siguientes propiedades para que el flujo circulando por la red sea factible. Usamos $f(u,v)$ para indicar la cantidad de flujo pasando por la arista $(u,v) \in E$. Dado un flujo factible $f$, el valor $F$ del flujo es la cantidad neta de unidades de flujo que salen de la fuente $s$.

**Restricción de capacidad**: el flujo circulando por una arista no puede superar su capacidad ni ser negativo.

Para toda arista $(u,v) \in E$ vale que $0 \leq f(u,v) \leq c(u,v)$.

**Conservación de flujo**: la cantidad de flujo que entra en un vértice es igual a la cantidad que sale (excepto para los vértices especiales $s$ y $t$). No se acumula flujo en ningún vértice.

Para todo $u \in V - \lbrace s,t \rbrace$ vale que $\sum\limits_{v \in V} f(v, u) = \sum\limits_{v \in V} f(u, v)$.

## Red residual

La red residual $G_f = (V, E_f)$ del grafo $G = (V,E)$ es un grafo que modela por dónde puede circular el flujo en la red original $G$. Las aristas de $G_f$ se definen según el flujo pasando por las aristas de $G$.

Si una arista $(u,v) \in E$ todavía tiene capacidad disponible para que circule flujo entonces está en $G_f$, y su capacidad es $c(u,v) - f(u,v)$. Modela la capacidad disponible de flujo que aún podemos usar.

Si hay flujo pasando por una arista $(u,v) \in E$, es decir $f(u,v) > 0$, entonces en $G_f$ tenemos la arista invertida $(v,u)$ con capacidad igual a $f(u,v)$. Modela la posibilidad de revertir algún flujo enviado por la arista $(u,v)$, operación necesaria por algunos algoritmos para encontrar el flujo máximo.

Con este criterio definimos la función de capacidad de la red residual:

$$c_f(u,v) = \begin{cases}
c(u,v) - f(u,v) & \text{si } (u,v) \in E \text{\color{gray} (flujo disponible)} \\
f(v,u) & \text{si } (v,u) \in E \text{\color{gray} (flujo actual)} \\
0 & \text{caso contrario}
\end{cases}$$

El conjunto de aristas de la red residual es inducido por la función de capacidad: $E_f = \lbrace (u,v) : c_f(u,v) > 0 \rbrace$. Notemos que si una arista $(u,v) \in E$ está saturada: $f(u,v) = c(u,v)$, entonces $c_f(u,v) = 0$ y no está en $G_f$.

## Caminos de aumento

La idea de un camino de aumento es encontrar caminos en la red residual por donde podamos aumentar el valor de flujo $F$ circulando por la red, para eventualmente llegar al flujo máximo.

Definimos un camino de aumento $p$ en la red residual $G_f$ como un camino orientado de $s$ a $t$. Hay varias estrategias para encontrarlo, por ejemplo con DFS/BFS podemos encontrar uno en $O(V+E)$.

La capacidad residual de $p$ es el valor máximo de flujo que podemos circular por las aristas de $p$ respetando las capacidades. Definimos $c_f(p) = min \lbrace c_f(u,v) : (u,v) \in p \rbrace$.

Una vez encontrado un camino de aumento, tenemos que actualizar el flujo $f$ pasando por todas las aristas de $G$. Para toda arista $(u,v) \in E$ definimos $f'$ como:

$$f'(u,v) = \begin{cases}
f(u,v) & \text{si } (u,v) \notin p \text{\color{gray} (se mantiene igual)} \\
f(u,v) + c_f(p) & \text{si } (u,v) \in p \text{\color{gray} (aumenta el flujo)} \\
f(u,v) - c_f(p) & \text{si } (v,u) \in p \text{\color{gray} (revertimos flujo antes enviado)}
\end{cases}$$

El nuevo valor de flujo $F'$ resulta $F' = F + c_f(p)$.

Es importante que $f'$ siga siendo un flujo factible: tiene que respetar las capacidades y la conservación.

**Restricción de capacidad**: $0 \leq f'(u,v) \leq c(u,v)$

Caso $(u,v) \notin p$:

Se mantiene el mismo flujo que antes $f'(u,v) = f(u,v)$, que ya era factible.

Caso $(u,v) \in p$:

Como $c_f(p)$ es el mínimo del camino $p$, podemos acotarlo por $c_f(u,v)$.

$f'(u,v) = f(u,v) + c_f(p) \leq f(u,v) + c_f(u,v) \leq f(u,v) + c(u,v) - f(u,v) = c(u,v)$

Por otro lado para ver que $f'(u,v) = f(u,v) + c_f(p) \geq 0$ notemos que $c_f(p) \geq 0$ por definición.

Caso $(v,u) \in p$:

$f'(u,v) = f(u,v) - c_f(p) \geq f(u,v) - c_f(v,u) = f(u,v) - f(u,v) = 0$

Por otro lado para ver que $f'(u,v) \leq c(u,v)$ notemos que $f(u,v)$ ya era un flujo factible y le estamos restando $c_f(p) \geq 0$, por lo tanto vamos a seguir respetando la capacidad.

**Conservación de flujo** (idea)

Para probar que se conserva el flujo para un vértice que es parte del camino de aumento tenemos que analizar todos los casos para las orientaciones de las aristas que conectan este vértice con el resto del camino.

En líneas generales, tiene que pasar que la misma cantidad de flujo nuevo que llega por una arista sale por la otra (puede ser una cantidad positiva o negativa), o bien que llega una cantidad positiva por una arista y llega la misma cantidad negativa por la otra arista.

## Cortes

Definimos un corte de la red como una partición de $V$ en $S$ y $T = V - S$ tal que $s \in S$ y $t \in T$. Nos interesa mirar el flujo y las capacidades de las aristas que cruzan el corte.

El flujo neto que atraviesa el corte está dado por $f(S,T) = \sum\limits_{u \in S} \sum\limits_{v \in T} f(u, v) - \sum\limits_{u \in S} \sum\limits_{v \in T} f(v, u)$.

La capacidad del corte está dado por $c(S,T) = \sum\limits_{u \in S} \sum\limits_{v \in T} c(u, v)$, la suma de las capacidades de las aristas que van de $S$ a $T$.

Conceptualmente el corte define un cuello de botella. Para cualquier valor de flujo $F$ circulando por la red, y cualquier corte $(S,T)$, vale que $F \leq c(S,T)$.

**Corte mínimo**

Definimos el corte mínimo como la partición $(S,T)$ que minimiza $c(S,T)$ entre todos los cortes posibles de la red.

## Teorema flujo máximo / corte mínimo

Este teorema nos dice que el valor de flujo máximo $F$ es igual a la capacidad del corte mínimo. Formalmente se define de la siguiente manera.

Sea una red $G=(V,E)$ con fuente $s$ y sumidero $t$. Si $f$ es un flujo factible de la red con valor $F$, entonces estas 3 afirmaciones son equivalentes:

1. $f$ es un flujo máximo en $G$.
2. No existe camino de aumento en la red residual de $G$.
3. $F = c(S,T)$ para algún corte $(S,T)$ de $G$.

Idea para la demostración:

- $1 \Rightarrow 2$: Por el absurdo, suponer que existe un camino de aumento y que se puede incrementar $F$ que es el flujo máximo.
- $2 \Rightarrow 3$: Como no existe camino de aumento, podemos inducir un corte $(S,T)$ donde en $S$ están todos los vértices alcanzables desde $s$, y $T = V - S$. Además, y esto es lo importante, no hay aristas que cruzan el corte desde $T$ hacia $S$, no hay flujo que "vuelve". Entonces si planteamos la fórmula del flujo que atraviesa el corte, obtenemos que en realidad $f(S,T) = c(S,T)$.
- $3 \Rightarrow 1$: Por lo expuesto anteriormente vimos que cualquier valor de flujo es a lo sumo la capacidad de cualquier corte. En particular para todo flujo $F'$ vale que $F' \leq c(S, T) = F$. Entonces para todo flujo $F'$, $F' \leq F$ y resulta que $F$ es máximo.
