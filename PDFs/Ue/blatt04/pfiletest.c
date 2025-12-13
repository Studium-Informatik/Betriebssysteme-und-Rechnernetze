#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

/*
 * This file is for accademic puposes only
 * For simplicity sake error handling
 * and coding styles are ignored.
 */

/*
 * Compiler Command: gcc -pthread -O0 -g -o pfiletest pfiletest.c
*/

char* str1="first write\n";
char str2[14]="second write\n";
char str3[L_tmpnam]= "/tmp/tempfileXXXXXX";
int fptr;
pthread_barrier_t *barrier;

void* run(void* v)
{
    write(fptr,str2,13);
    pthread_barrier_wait(barrier);
    pthread_barrier_wait(barrier);
    return NULL;
}

int main()
{
    pthread_t thread;
    barrier=malloc(sizeof(pthread_barrier_t));
    if(barrier==NULL){
        perror("Can't malloc");
        exit(1);
    }

    if(pthread_barrier_init(barrier, NULL, 2)) {
        perror("can't create barrier");
        exit(1);
    }

    printf("My PID is %d \n",getpid());
    // use appropriate location if you are using MacOS or Linux
    if ((fptr=mkstemp(str3)) == -1) {
        perror("could not create temp file:");
        exit(1);
    }

    if(pthread_create(&thread,NULL, run, NULL)!=0) {
        perror("can't create thread:");
        exit(1);
    }
    printf("Writing strings to File\n");
    write(fptr,str1,12);
    sleep(180);
    pthread_barrier_wait(barrier);
    printf("Closing File Deskriptor\n");
    close(fptr);
    sleep(180);
    pthread_barrier_wait(barrier);
    pthread_join(thread, NULL);
    
        return 0;
}
