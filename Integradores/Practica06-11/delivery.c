#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

#define TRUE 1
#define FALSE 0

typedef struct client{
    int telefono;
    char nombre[100];
    char direccion[100];
} Cliente;

/**
 * PASO 0 ==> PEDIR TELEFONO
 * PASO 1 ==> PEDIR NOMBRE
 * PASO 2 ==> PEDIR DIRECCION
 * **/

void solicitarDatoCliente(int paso,int fifo){
    char aux[100];
    switch (paso)
    {
    case 0:
        strcpy(aux,"INGRESA TU NUMERO DE TELEFONO\n");
        write(fifo, aux, strlen(aux)+1); 
        break;
    case 1:
        strcpy(aux,"INGRESA TU NOMBRE\n");
        write(fifo, aux, strlen(aux)+1); 
        break;
    case 2:
        strcpy(aux,"INGRESA TU DIRECCION\n");
        write(fifo, aux, strlen(aux)+1); 
        break;
    default:
        break;
    }
}

int recibirDatoCliente(int paso,Cliente *client,int fifo){
    char aux[100];
    int terminoDePedirDatos = FALSE;
    if(paso == 0){
        // Read from FIFO 
        read(fifo, aux, sizeof(aux));
        printf("TELEFONO RECIBIDO: %s\n",aux);
        client->telefono = atoi(aux);
    }else if(paso == 1){
        // Read from FIFO 
        read(fifo, aux, sizeof(aux));
        printf("NOMBRE RECIBIDO: %s\n",aux);
        //ME GUARDO EL NOMBRE RECIBIDO
        strcpy(client->nombre,aux);
    }else if(paso == 2){
        // Read from FIFO 
        read(fifo, aux, sizeof(aux));
        printf("DIRECCION RECIBIDO: %s\n",aux);
        //ME GUARDO LA DIRECCION RECIBIDA
        strcpy(client->direccion,aux);
        terminoDePedirDatos = TRUE;
    }else{
        printf("ERROR");
    }
    return terminoDePedirDatos;
}
  
int main() 
{ 
    
    //FIFO DESCRIPTOR (o HANDLER)
    int fd; 

    //PASOS PARA OBTENER DATOS CLIENTE
    int paso = 0, terminoCargaDeDatos = FALSE;
  
    // FIFO RUTA AL FIFO
    char * myfifo = "/tmp/myfifo"; 

    //DECLARO UN CLIENTE
    Cliente client;
  
    // CREO EL FIFO
    // mkfifo(<pathname>, <permission>) 
    mkfifo(myfifo, 0666); 
    if(mkfifo < 0 ) printf("Error creando fifo");

    while (!terminoCargaDeDatos) 
    { 
        // ABRO FIFO MODO SOLO ESCRITURA
        fd = open(myfifo, O_WRONLY); 

        solicitarDatoCliente(paso,fd);
        close(fd); 
  
        // ABRO FIFO MODO SOLO LECTURA
        fd = open(myfifo, O_RDONLY); 
  
        terminoCargaDeDatos = recibirDatoCliente(paso,&client,fd);
        //INCREMENTO EL PASO PARA LA CARGA DE DATOS.
        paso = paso + 1;
        //CIERRO EL FIFO NUEVAMNETE.
        close(fd); 
    } 

    printf("---- TERMINE LA CARGA DE DATOS ---- \n");

    return 0; 
} 