#include "sock-lib.h"

int main ()
{
	int sockfd; /* File Descriptor del socket por el que el servidor "escucharÃ¡" conexiones*/
	char message[] = "Hello, world!";
	struct sockaddr_in my_addr;	/* contendrÃ¡ la direcciÃ³n IP y el nÃºmero de puerto local */
	int sockdup; 

	if ((sockfd = Open_conection (&my_addr)) == -1)
	{
		perror ("FallÃ³ la creaciÃ³n de la conexiÃ³n"); 
		exit (1);
	}

	while(1)
	{
		sockdup = Aceptar_pedidos (sockfd);
		
		if (write (sockdup, message , sizeof (message)) == -1)
		{
			perror("Error escribiendo mensaje en socket");
			exit (1);
		}
		close(sockdup);
	}
	exit(0);
}