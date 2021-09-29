# Redes y Sockets 

***************

## Servidor TCP/IP

* Paso a paso
    * socket
    * bind
    * listen
    * accept

### Socket

* ``` int socket(int domain, int type, int protocol); ```
* Domain: 
    * AF_UNIX, AF_INET (Por lo general se utiliza AF_INET)
    * AF_INET IPV4
* Type: 
    * SOCK_STREAM, SOCK_DGRAM (Por lo general se utiliza SOCK_STREAM)
    * SOCK_STREAM --> Protocolo TCP/IP
    * SOCK_DGRAM ---> UDP
* Protocols: se setea en cero

* Struct sockaddr_in

    ```   struct sockaddr_in {
	            __uint8_t       sin_len;
	            sa_family_t     sin_family;
	            in_port_t       sin_port;
	            struct  in_addr sin_addr;
	            char            sin_zero[8];
        };```

#### Htons

* ```unsigned short htons (unsigned short hostshort); ```
* Convierte un long del formato de la máquina al de la red
* ```server.sin_port = htons(PORT);```

### Bind

* ```int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);```
* sockfd: el socket creado anteriormente
* sockaddr: Es un **puntero a una estructura** de direcciones. ( (struct sockaddr*)&server) ) 
* addrlen : Tamaño de la estructura pasada en sockaddr. ( sizeof(struct sockaddr ))

### Listen

* ```int listen(int sockfd, int backlog);```
* sockfd: el socket creado anteriormente
* backlog: cantidad de conexiones que pueden quedar en la cola.

### Accept

* ```int accept(int sockfd, struct sockaddr *addr,socklen_t *addrlen);```
* sockfd: el socket creado anteriormente
* sockaddr: Es un **puntero a una estructura** de direcciones pero del **cliente**. 
* addrlen: Tamaño de la estructura pasada en sockaddr.

* Es una funcion **bloqueante**.

*************

## Cliente TCP/IP

* Paso a paso
    * socket
    * connect

### Connect

* ```int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);```
* sockfd: socket creado anteriormente
* sockaddr: Es un **puntero a una estructura** del mismo tipo que el **servidor**.
* addrlen: Tamaño de la estructura pasada en sockaddr.

**************

## Funciones de comunicacion

### Send / Rcv

* ```ssize_t send(int sockfd, const void *buf, size_t len, int flags);```
    * sockfd: socket correspondiente (depnde de que lado se envie)
    * buf: Buffer 
    * len: Tamaño del buffer
    * flags: 

* ```ssize_t recv(int sockfd, void *buf, size_t len, int flags);```

* Devuelve ssize_t en int.


******************************

### Ejemplo para correrlo local

* Servidor ---> servidor.c
* Cliente ----> cliente.c

* Compilacion
    ```
        gcc -o srv servidor.c && gcc -o client cliente.c 
    ```

* Correr ambos archivos
    * Primero el servidor: ./srv
    * Segundo el cliente: ./client 127.0.0.1