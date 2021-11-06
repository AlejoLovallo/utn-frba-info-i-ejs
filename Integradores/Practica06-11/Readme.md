# Ejercicio integrador 1

* Una conocida casa de empanadas con servicio de delivery quiere disponer de un sistema para optimizar la gestión de pedidos.

* En primer lugar, se cuenta con una base de datos con los siguientes datos:
    * Teléfono (se utilizará como código de cliente)
    * Nombre
    * Dirección
    * Cantidad de pedidos acumulados

* Cuando un cliente llama, se solicita en primer lugar su número de teléfono. Si
dicho teléfono ya está registrado se procede a ingresar su pedido; en caso
contrario, se procede al alta del mismo en la base de datos, solicitando nombre y
dirección.
* A continuación, tanto si ya era cliente como si fue dado de alta en ese llamado,
se toma nota de su pedido. Para ello se ingresará el gusto elegido (los gustos
disponibles son carne, pollo, jamón y queso y humita) y la cantidad de
empanadas de cada uno. Tenga en cuenta que esta información NO FORMARÁ PARTE de la base de datos, aunque se incrementará en 1 (uno) la cantidad de pedidos acumulados.

* Resolver utilizando
    * FIFO para la comunicación inicial del cliente.
    * Sockets para las consultas del cliente
    * CLASE PRACTICA ALEJO-HECTOR ES CON SHARED MEMORY. (Cuando el cliente hace un pedido primero tiene que decir su numero de cliente) 
    * Consultas del cliente
        * Opcion 1: Sockets
        * Opcion 2: Shared memory
