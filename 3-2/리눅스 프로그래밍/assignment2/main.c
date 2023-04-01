#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MSG_LEN 512

void handler(int signo)
{
    if (signo == SIGINT)
    {
        printf("\nDon't try to kill this program with signal! You have 'exit' command!\n");
    }
    else if (signo == SIGUSR1)
    {
    }
    else if (signo == SIGALRM)
    {
    }
}

void parent_handler(int signo)  // SIGINT 메시지가 두번 나오지 않게 하기 위해
{
	if (signo == SIGINT) 
	{
	}
}

int main (int argc, char **argv)
{
    int nsec;
    int ctp[2], ptc[2];
    pid_t pid, ppid;
    char inbuf[MSG_LEN];
    static struct sigaction act;

    /* Signal Handling */
    /* Your Code */
    sigemptyset(&(act.sa_mask));
    act.sa_flags = SA_RESTART;
    act.sa_handler = handler;
    sigaction(SIGALRM, &act, NULL);
    
    /* Pipe communications. */
    /* Your Code */
    pipe(ctp);
    pipe(ptc);
    
    switch (pid = fork())
    {
        case -1:
            perror("fork call");
            exit(2);
        case 0:     // child
            ppid = getppid();
	        char* cmd;
            
            close(ptc[1]);
	        close(ctp[0]);
	        sigaction(SIGINT, &act, NULL);
            
            while (1) 
            {
    		    /* Your Code */
		        fgets(inbuf, MSG_LEN, stdin);	
		        cmd = strtok(inbuf, "\n");

                if (strcmp(cmd, "exit") == 0)
                {
                    write(ctp[1], inbuf, MSG_LEN);
                    kill(ppid, SIGUSR1);
                    exit(0);
                }
                else
                {
                    nsec = atoi(inbuf);
                    
                    if (nsec >= 1 && nsec <= 60)
                    {
                        // nsec만큼 기다리기(parent)
                        write(ctp[1], inbuf, MSG_LEN);
			            printf("-------------------\n");
			            kill(ppid, SIGUSR1);   	
			            alarm(nsec);
			            pause();
                        read(ptc[0], inbuf, MSG_LEN);
			            printf("%s\n", inbuf);
                    }
                    else
                    {
                        // 다른 커맨드의 경우 무시
                        continue;
                    }
                }
            }
            break;
        default:    // parent
	        close(ptc[0]);
	        close(ctp[1]);
	        
            /* Signal Handling */
	        /* Your Code */
	        sigaction(SIGUSR1, &act, NULL);
	        act.sa_handler = parent_handler;
	        sigaction(SIGINT, &act, NULL);	    
            
            while(1) 
            {
	    	    /* Your Code */
		        pause();
                read(ctp[0], inbuf, MSG_LEN);
                
                if (strcmp(inbuf, "exit") == 0)
                {
		            wait(NULL);
                    break;
                }
                nsec = atoi(inbuf);
                
                for (int i = nsec; i > 0; i--)
                {
                    printf("%d\n", i);
                    sleep(1);
                }
		        strcpy(inbuf, "Wake Up!");
               	write(ptc[1], inbuf, MSG_LEN);
            }
    }
    return 0;
}
