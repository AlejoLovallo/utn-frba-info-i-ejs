/* archivos de cabecera */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>        
/* netbd.h se necesita por la estructura hostent */

#define PORT 3550         
/* El Puerto Abierto del nodo remoto */

#define MAXDATASIZE 100   
/* El numero maximo de datos en bytes */

int main(int argc, char *argv[])
{
   /* file descriptors */
   int fd, numbytes;       

   /* en donde se almacenara el texto recibido */
   char buf[MAXDATASIZE];  

   /* estructura que recibira informacion sobre el nodo remoto */
   struct hostent *he;         

   /* informacion sobre la direccion del servidor */
   struct sockaddr_in server;  

   if (argc !=2) { 
      /* el programa solo necesitar un argumento (la IP) */
      printf("Uso: %s <Direccion IP>\n",argv[0]);
      exit(-1);
   }

   /* llamada a gethostbyname() */
   if ((he=gethostbyname(argv[1]))==NULL){          
       printf("gethostbyname() error\n");
       exit(-1);
   }

   /* llamada a socket() */
   if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){  

      printf("socket() error\n");
      exit(-1);
   }

   server.sin_family = AF_INET;
   server.sin_port = htons(PORT); 

   /*he->h_addr pasa la informacion de *he a h_addr */
   server.sin_addr = *((struct in_addr *)he->h_addr);  

   bzero(&(server.sin_zero),8);

   /* llamada a connect() */
   if(connect(fd, (struct sockaddr *)&server,sizeof(struct sockaddr))==-1){ 
      printf("connect() error\n");
      exit(-1);
   }

   /* llamada a recv() */
   if ((numbytes=recv(fd,buf,MAXDATASIZE,0)) == -1){  
      printf("Error en recv() \n");
      exit(-1);
   }

   buf[numbytes]='\0';

   /* muestra el mensaje de bienvenida del servidor */
   printf("Mensaje del Servidor: %s\n",buf); 

   close(fd);   /* cerramos fd */

   return 0;	
}
