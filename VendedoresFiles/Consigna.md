# Ejercicio Vendedores Archivos 

### Archivo vendedor (vendedores.csv)
```
    Nombre y apellido
    Numero de legajo
    Antiguedad (años)
```

* Se tienen 20 vendedores como máximo

### Comisiones

* Por cada año de trabajo un 1% mas
* La comisión es por precio de venta (no margen)
* Se tienen distintos archivos con las ventas diarias. Tendremos un archivo por dia, y el formato del nombre del archivo será: AAAAMMDD.csv

* Campos del archivo de ventas:
```
    Cantidad de productos vendidos
    Monto total
    Legajo del vendedor
```

* Se pide:

    * Que el programa tome el año y mes para calcular las comisiones de cada vendedor para ese mes.
    * Que el programa permita cargar los vendedores y las ventas diarias.
    * Una vez terminado el programa con archivos CSV, cambiarlo para trabajar con estructuras guardadas directamente (use fread() y fwrite()).