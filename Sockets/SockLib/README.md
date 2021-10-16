# UTN FRBA SOCK LIB 

* Libreria de la catedra

### Funciones 

* CLIENTE
    int	conectar (int, char **);

* SERVIDOR
    int	Open_conection (struct sockaddr_in *); /* FunciÃ³n que crea la conexiÃ³n*/
    
    int	Aceptar_pedidos (int);	/* FunciÃ³n que acepta una conexiÃ³n entrante*/
