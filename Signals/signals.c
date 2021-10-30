#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void sigproc(void);

void quitproc(void);

int main(void)
{	signal(SIGINT, sigproc);
	signal(SIGQUIT, quitproc);
	printf("Process ID: %d\n", getpid());
	printf("ctrl-c disabled use ctrl-\\ to quit\n");
	while(1) {
		/* infinite loop */
		usleep(1000);
	}
	return 0;
}

void sigproc()
{ 		 signal(SIGINT, sigproc); /*  */
		 /* NOTE some versions of UNIX will reset signal to default
		 after each call. So for portability reset signal each time */

		 printf("you have pressed ctrl-c \n");
}

void quitproc()
{ 		 printf("ctrl-\\ pressed to quit\n");
		 exit(0); /* normal exit status */
}