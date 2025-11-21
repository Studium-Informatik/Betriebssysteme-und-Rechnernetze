/* credits to Stuart Sechrest: An Introductory 4.4 BSD Interprocess
 * Communication Tutorial
 *
 * Child writes DATA to parent.
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 80

int main(int argc, char* argv[])
{
    int pipefd[2], child;
    FILE* infilep;
    char data [MAX_LEN];

    /* create a pipe */
    if (pipe(pipefd) < 0) {
        perror ("opening pipe");
        exit(EXIT_FAILURE);
    }
    /* input from file foo,
    child: makes several writes
    parent: makes one read;
    -> race conditions: child maybe too slow and parent
    has already finished */
    if ((child = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (child) {
        /* This is still the parent process. */
        char buf[1024];

        close (pipefd[1]);
        if (read(pipefd[0], buf, 1024) < 0) {
            perror("reading message from pipe");
        }
        close(pipefd[0]);
        printf("Parent reads:  %s\n", buf);

    } else {
        /* This is the child */
        close(pipefd[0]);

        if ((infilep = fopen("foo", "r")) == NULL) {
            perror("foo");
            exit(EXIT_FAILURE);
        }

        /* read from file line by line and write the data into the pipe */
        printf("child reads from file: \n");
        while (fgets(data, MAX_LEN, infilep) != NULL) {
            fputs (data, stdout);
            if (write(pipefd[1], data, strlen(data)) < 0)
                perror("writing message");
        }
        close(pipefd[1]);
    }
}
