/* archivos de cabecera */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>          
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3550 /* El puerto que sera abierto */
#define BACKLOG 2 /* El numero de conexiones permitidas */

int main()
{

   int fd, fd2; /* file descriptors */

   struct sockaddr_in server; 
   /* para la informacion de la direccion del servidor */

   struct sockaddr_in client; 
   /* para la informacion de la direccion del cliente */

   int sin_size;

   /* llamada a socket() */
   //AF_INET para especificar protocolo, hay otro para IPV6 por ejemplo
   if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) 
   {  
      printf("error en socket()\n");
      exit(-1);
   }

   server.sin_family = AF_INET;         

   server.sin_port = htons(PORT); 

   //INADDR_ANY es para que acepte todas las direcciones asociadas a las interfaces
   server.sin_addr.s_addr = INADDR_ANY; 
   /* INADDR_ANY coloca la direccion IP automaticamente */

   //completa con ceros un string
   bzero(&(server.sin_zero),8); 
   /* escribimos ceros en el resto de la estructura */
   
   /* llamada a bind() */
   if(bind(fd,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1) 
   {
      printf("error en bind() \n");
      exit(-1);
   }     

   /* llamada a listen() */
   //BACKLOG especifica el nro maximo de conexiones en cola a ser atendidas
   if(listen(fd,BACKLOG) == -1) 
   {  
      printf("error en listen()\n");
      exit(-1);
   }

   while(1) {
      sin_size=sizeof(struct sockaddr_in);
      /* llamada a accept() */
      if ((fd2 = accept(fd,(struct sockaddr *)&client,&sin_size))==-1) 
      {
         printf("error en accept()\n");
         exit(-1);
      }

      printf("Se obtuvo una conexion desde %s\n",inet_ntoa(client.sin_addr) ); 
      /* muestra la IP del cliente */

      send(fd2,"Bienvenido al servidor.\n",22,0); 
      /* muestra el mensaje de bienvenida al cliente */

      close(fd2); /* cierra fd2 */
   }

   return 0;
}
