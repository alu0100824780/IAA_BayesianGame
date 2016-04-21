
# IAA Bayesian Bot
Calcula el comportamiento de un bot (_estado_) en función de la información obtenida del entorno y de sus estado anterior.

Una vez calculado el primer st+1, permite modificar el entorno para evaluar la evolución de su comportamiento. 

## Compilar 
    g++ *.cpp -std=c++11 -O3 -o IAA_BOT

## Ejecutar 
    ./IAA_BOT

## Entrada
La información que caracteriza el comportamiento del bot se encuentra codificada en el fichero [values](https://github.com/alu0100824780/IAA_BayesianGame/blob/master/values). Este define tanto los posibles estados del bot como los sensores que posee y la relación existente entre ambas partes.

La sintaxis es la siguiente:

- La priemera tabla define los estados del bot y la probabilidad de pasar a otros estados en el siguiente isntante de tiempo. Sólo debe existir una.
- El resto de tablas definien un sensor y cómo aumentan o disminuyen la probabilidad de cada estado para cada uno de los valores. Pueden existir un número arbitrario de los mismos sin necesidad de especificarlo a priori.

### Sintaxis Tabla Estados
    N   // Número de estados que se van a definir
    ESTADO_1    ESTADO_2    ...     ESTADO_N   // strings 
    prob_1_1    prob_1_2    ...     prob_1_N    
    ...         ...         ...     ...
    prob_N_1    prob_N_2    ...     prob_N_N

Dónde prob_X_Y corresponde a la probabilidad de pasar al estado Y estando en el estado X

**La suma de todos los elementos de una fila debe ser 1**

### Sintaxis Tabla Sensores
    NOMBRE_SENSOR // string
    N             // número de valores del sensor 
    VALOR_1 ... VALOR_K //valores que puede adoptar(mucho/poco, si/quizá/no...)
    prob_E1_1   prob_E1_K
    prob_E2_1   prob_E2_K
    ...         ...
    prob_EN_1   prob_EN_K

Dónde prob_A_B corresponde a la probabilidad de pasar al estado A al tener el sensor el calor B

**La suma de todos los elementos de una fila debe ser 1**