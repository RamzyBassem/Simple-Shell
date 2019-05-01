#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
void signalHandler(int signal)
{    FILE *log;
    log = fopen ("/home/ramzy/Desktop/tokens/log","a");
	if (signal==SIGCHLD) {
		printf("Child ended\n");
		fprintf(log,"CHILD PROCESS WAS TERMINATED\n");
		wait(NULL);
	}
	fclose(log);
}




int main()
{
char *string,*found[100]; // start reading input and splitting it into array of pointer " found "
    int i=0 , waitsignal=1,forkreturn,wpid,j;
    char S1[100];
    found[0]="blaa";

    while(strcmp(found[0],"exit")!=0){ // exit condition
            for(j=0;j<100;j++){  // to make sure that all the array is reset every command maybe redundant but too make sure
                found[j]=NULL;
            }
    gets(S1); // get input from user
    string = strdup(S1); // make it string with strdup return value is a pointer to string so i can use strsep which takes pointer as an argument
    while( (found[i] = strsep(&string," ")) != NULL ){ // splitting the input on space and every index of found array is a pointer to the array of commands
        i++;
    }  // end of reading and splitting the input
    found[i]== NULL; // execute function takes argument NULL terminated

   int status;  // for the wait algorithm
                  	signal(SIGCHLD,signalHandler); // log algorithm

    if(strcmp(found[i-1],"&")==0){
        waitsignal=0; // don't wait
	found[i-1]= NULL; // to remove the & from the array so i can send it to execute function
    }
    if(strcmp(found[0],"cd") == 0 ){ // built in functions {
        printf("\n hello from built in function");
        if (chdir(found[1]) != 0) {       // using chdir instead of execute
      perror("ERROR IN CD FUNCTION IS : ");
    }
    }
    else{

        forkreturn = fork();  // forking

        if(forkreturn==0){   // child
            if (execvp(found[0], found) == -1) {
                printf("\n ERROR IN EXECUTION \n");
            perror("error is");
            }
        exit(0);  // to exit from child
        }
        else if(forkreturn<0){

            printf("ERROR IN FORKING \n");
        }

        else{    // parent
                if(waitsignal==1){
                do {  // wait algorithm
                      wpid = waitpid(forkreturn, &status, WUNTRACED);
                    } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        }

      }

    }

    i=0; // to reset it to take inputs again
     }


            return 0;
}
