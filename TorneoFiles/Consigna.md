# Torneo de futbol

* Se requiere desarrollar un programa que informe sobre la posición actual de cada uno de los equipos de fútbol que participan de un torneo.

* Archivos

    * Resultados
    ```
    Id Equipo1
    Id Equipo2
    Id CodigoResultado
    ```

    * Equipos
    ```
    Nombre equipo
    Id Equipo
    Puntos
    ```
* El valor del campo idCR indica qué equipo ganó el partido. Si idCR<0 significa que ganó idEq1. Si idCR>0 entonces el ganador fue idEq2. Si id idCR==0 el partido resultó empatado.

* El equipo ganador acumula 3 puntos. Si empataron acumulan 1 punto cada uno. El perdedor no acumula puntos.

* 1. Informar, la tabla de posiciones actualizada al día del proceso.