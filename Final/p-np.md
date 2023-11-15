# P / NP

Nos concentramos en problemas de decisión ya que permite uniformizar el estudio para todas las versiones de problemas.

Definiciones:

- $\Pi$: problema.
- $D_\Pi$: el conjunto de todas las instancias de $\Pi$.
- $I \in D_\Pi$: instancia de un $\Pi$.
- $Y_\Pi$: conjunto de todas las instancias $I$ tales que $\Pi(I) = $ sí.

## Máquina de Turing

Una máquina de Turing es una cinta infinita la cual se mueva hacia la izquierda o derecha pasando por un cabezal. Además, en todo momento la máquina tiene un estado interno. En cada paso, el cabezal lee el símbolo en esa posición de la cinta y determina cuál es el nuevo estado, hacia dónde mover y qué otro símbolo escribir en la cinta.

En la versión determinística (MTD), para cada combinación de estado y símbolo hay una única opción para hacer.

En cambio, la versión no determinística (MTND) puede tener muchas opciones para realizar para la misma combinación de estado y símbolo leído. No está especificado de antemano ningún criterio para elegir qué hacer.

## Clases de problemas

**P: clase de problemas polinomiales**. Existe una MTD polinomial que resuelve el problema de decisión. Es equivalente a decir que existe un algoritmo en la máquina RAM que resuelve el problema en tiempo polinomial.

**NP: clase de problemas polinomiales no-determinísticos**. Existe una MTND polinomial que para toda instancia del problema de decisión donde la respuesta es sí, la MTND responde sí. Es equivalente a decir que para una instancia del problema donde la respuesta es sí, existe un certificado de tamaño polinomial (respecto a la instancia) que garantiza que la respuesta es sí, existe un algoritmo que puede verificar la garantía del certificado en tiempo polinomial (respecto al certificado).

## Reducciones polinomiales

Una reducción o transformación polinomial de un problema $\Pi'$ a otro $\Pi$ es una función polinomial $f: D_{\Pi'} \rightarrow D_\Pi$ que transforma todas las instancias $I'$ de $\Pi'$ en instancias de $\Pi$ respetando que las respuestas se mantengan igual. Es decir, $I' \in Y_{\Pi'} \iff f(I') \in Y_\Pi$.

Si existe la transformación $f$ decimos que el problema $\Pi'$ se **reduce polinomialmente** a $\Pi$ y lo escribimos: $\Pi' \leq_P \Pi$.

Las reducciones polinomiales son transitivas: $\Pi_1 \leq_P \Pi_2 \leq_P \Pi_3$ entonces $\Pi_1 \leq_P \Pi_3$.

## NP-Completo

Un problema $\Pi$ es NP-Completo si cumple con las siguientes condiciones:

1. $\Pi \in$ NP: puedo verificar un certificado en tiempo polinomial.
2. Para todo problema $\Pi' \in$ NP, $\Pi' \leq_P \Pi$: el problema $\Pi$ es **al menos** tan difícil como cualquier otro problema de NP. Decimos que $\Pi$ es NP-Hard.

## Co-NP

La clase Co-NP son los problemas $\Pi$ tales que podemos verificar un certificado polinomial por "no" en tiempo polinomial.

Dado un problema $\Pi$, el problema complemento $\Pi^c$ tiene el mismo conjunto de instancias pero "da vuelta" la respuesta, responde sí cuando $\Pi$ responde no.

Más formalmente:
- $D_{\Pi^c} = D_\Pi$: mismas instancias.
- $Y_{\Pi^c} = D_\Pi - Y_\Pi$: responde al revés.

Si $\Pi \in$ P entonces $\Pi^c \in$ P. Ya tenemos un algoritmo polinomial que resuelve $\Pi$, podemos usarlo para computar $\Pi^c$ simplemente negando el resultado.

En cambio, si $\Pi \in$ NP, no necesariamente $\Pi^c \in$ NP. Por ejemplo, determinar si existe un circuito hamiltoniano en un grafo es NP. Pero no sabemos al día de hoy si el complemento, determinar que no existe un circuito hamiltoniano, es NP. A priori la mejor estrategia que tenemos es enumerar la permutación de todos los vértices y revisar que ninguna sea un circuito, y esto es exponencial.

Lo que sí podemos decir es que si $\Pi \in$ NP entonces $\Pi^c \in$ Co-NP.

## Teorema Cook-Levin

> SAT es NP-Completo.

Para demostrarlo, por un lado sabemos que SAT es NP porque una valuación de la fórmula es en sí un certificado, y podemos verificar que la valuación efectivamente satisface la fórmula en tiempo polinomial.

Por otro lado tenemos que mostrar que todos los otros problemas $\Pi \in$ NP son "más fáciles" que SAT, es decir $\Pi \leq_P$ SAT. La idea es tomar un problema arbitrario $\Pi \in$ NP, el cual tiene una MTND que lo resuelve. Muy high level, lo que hacemos es construir una fórmula lógica a partir de términos lógicos que codifican la ejecución de la MTND de forma tal que la fórmula se satisface si y solo si la MNTD llega a un estado final de "si".
