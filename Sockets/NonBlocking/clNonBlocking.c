#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    memset((void *) &serv_addr, '\0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    printf("Escriba su mensaje: ");
    memset((void *) buffer, '\0', 256);
    fgets(buffer,255,stdin);
    n = send(sockfd,buffer,strlen(buffer),0);

    if (n < 0) 
         error("ERROR writing to socket");

    memset((void *) buffer, '\0', 256);

    /*
     * Por un buffer de printf() debo hacer lo siguiente
     * 		http://stackoverflow.com/questions/1716296/why-does-printf-not-flush-after-the-call-unless-a-newline-is-in-the-format-strin
     */
    setbuf(stdout, NULL);

    printf("wait...");
    do {
        /*
         * Trabajando en modo no bloqueante
         * Retorna:
         *     -1 si no llegÃ³ nada
         *     >0 si llegaron datos
         */
        n = recv(sockfd,buffer,255,MSG_DONTWAIT);
        printf(".");
        sleep(1);
    } while (n == -1);

    if (n < 0)
         error("ERROR reading from socket");

    printf("%s\n",buffer);

    int respuesta = 0;
    printf("Desea seguir enviando mensajes\n");
    scanf("%d",&respuesta);

    char msg[255];
    memset((void *) msg, '\0', 255);

    while(respuesta != -1){
        printf("Escriba el mensaje a enviar\n");
        scanf("%s",msg);
        strcpy(buffer,msg);
        n = write(sockfd,buffer,strlen(buffer));
        printf("Enviar otro mensaje?\n");
        scanf("%d",&respuesta);
    }

    close(sockfd);
    return 0;
}