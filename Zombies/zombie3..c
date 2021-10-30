// A C program to demonstrate handling of
// SIGCHLD signal to prevent Zombie processes.
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include <signal.h>

void func(int signum)
{
	// Can not use printf, see: "man 7 signal-safety"
	char str[50] = "Hello there, I'm the signal handler";
	wait(NULL);
	// stdout for write is 1
	write(1,str,strlen(str));
    exit(0);
}

int main()
{
	int i;
	int pid = fork();
	if (pid == 0) {
		for (i=0; i<10; i++) {
			usleep(500000);
			printf("I am Child (wait %d)\n", i);
		}
	} else {
		signal(SIGCHLD, func);
		printf("I am Parent\n");
		while(1) usleep(1000);
	}
}