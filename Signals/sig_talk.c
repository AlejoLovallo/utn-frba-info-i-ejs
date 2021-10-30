/* sig_talk.c --- Example of how 2 processes can talk */
/* to each other using kill() and signal() */
/* We will fork() 2 process and let the parent send a few */
/* signals to it`s child	*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

/* routines child will call upon sigtrap */
void sighup();
void sigint();
void sigquit();

int main(void)
{ int pid;

    	switch(pid=fork()) {
		case -1:
			perror("fork");
		    exit(1);		 /* parent exits */

		case 0:
			signal(SIGHUP, sighup);
		    signal(SIGINT, sigint);
		    signal(SIGQUIT, sigquit);
            printf("GET CHILD PROCESS %d \n",getpid());
		    while(1) {
		    	/* infinite loop */
		    	usleep(1000);
		    }

		default:
			/* parent, pid hold id of child */
		    printf("\nPARENT: sending SIGHUP\n\n");
		    kill(pid,SIGHUP);
		    sleep(3); /* pause for 3 secs */
		    printf("\nPARENT: sending SIGINT\n\n");
		    kill(pid,SIGINT);
		    sleep(3); /* pause for 3 secs */
		    printf("\nPARENT: sending SIGQUIT\n\n");
		    kill(pid,SIGQUIT);
		    sleep(3);
	}
}

void sighup() {
	signal(SIGHUP, sighup); /* reset signal */
	printf("CHILD: I have received a SIGHUP\n");
}

void sigint() {
	signal(SIGINT, sigint); /* reset signal */
	printf("CHILD: I have received a SIGINT\n");
}

void sigquit() {
	printf("My DADDY has Killed me!!!\n");
	exit(0);
}