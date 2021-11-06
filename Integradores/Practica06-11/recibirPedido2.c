/**
 * ACLARACION: ESTA WIP (WORK IN PROGRESS)
 * **/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void* create_shared_memory(size_t size) {
	// Our memory buffer will be readable and writable:
	int protection = PROT_READ | PROT_WRITE;

	// The buffer will be shared (meaning other processes can access it), but
	// anonymous (meaning third-party processes cannot obtain an address for it),
	// so only this process and its children will be able to use it:
	int visibility = MAP_ANONYMOUS | MAP_SHARED;

	// The remaining parameters to `mmap()` are not important for this use case,
	// but the manpage for `mmap` explains their purpose.
	return mmap(NULL, size, protection, visibility, 0, 0);
}


void func(int signum)
{
	// Can not use printf, see: "man 7 signal-safety"
	char str[50] = "Ya recibi tu pedido exitosamente";
	wait(NULL);
	// stdout for write is 1
	write(1,str,strlen(str));
    exit(0);
}



int main() {
	char* parent_message = "Ingresa Pedido";	// parent process will write this message
	char* child_message = "1Carne,2Choclo,3JamonYQueso"; // child process will then write this one

	void* shmem = create_shared_memory(256);

	memcpy(shmem, parent_message, strlen(parent_message));

	int pid = fork();
    char auxPedido[100];
    int salirPadre = 1;

	if (pid == 0) {
		sleep(1);
		printf("Child read: %s\n", shmem);
        fgets(auxPedido,100,stdin);
		//memcpy(memoria compartida, mensaje , tamaño del mensaje);
		memcpy(shmem, auxPedido, strlen(auxPedido));
		printf("Child wrote: %s\n", shmem);
		sleep(1);
        salirPadre = -1;
	} else {
        signal(SIGCHLD,func);
		printf("Parent read: %s\n", shmem);
		while(salirPadre == 1) usleep(1000);
		printf("Despues de n segundos, el padre leyo: %s\n", shmem);
	}
	//munmap(memoria compartida, tamaño)
	munmap(shmem,128);
}