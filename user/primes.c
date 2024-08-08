#include "kernel/types.h"
#include "user/user.h"

void primes(int p[], int t[]);

int main(int argc, char** argv)
{
    // file descriptor
    int p[2];
    // pipe
    pipe(p);

    int t[2];
    pipe(t);

    // create a child process
    int pid = fork();

    if (pid == 0) {
        // child process
        close(p[0]); // close read end of p
        for (int i = 2; i <= 35; ++i) {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]); // close write end of p
        exit(0);
    } else {
        close(p[1]); // close write end of p
        wait(0); // wait for child process
        primes(p, t);
        close(p[0]); // close read end of p
        exit(0);
    }
}

void primes(int p[], int t[])
{
    // current num
    int pre, next;
    
    if (read(p[0], &pre, sizeof(int)) > 0) {
        // output
        printf("prime %d\n", pre);
        
        // create a child process
        int pid = fork();
        if (pid == 0) {
            // child process
            close(p[0]); // close read end of p

            while (read(p[0], &next, sizeof(int)) > 0) {
                if (next % pre != 0) {
                    printf("%d\n", next);
                    write(t[1], &next, sizeof(int));
                }
            }
            close(t[1]); // close write end of t

            while (read(t[0], &next, sizeof(int)) > 0) {
                printf("%d\n", next);
                write(p[1], &next, sizeof(int));
            }
            close(t[0]); // close read end of t
            close(p[1]); // close write end of p

            exit(0);
        } else {
            // parent process
            close(t[0]); // close read end of t
            close(t[1]); // close write end of t

            wait(0); // wait for child process
            primes(p, t); // recursively call primes
            close(p[1]); // close write end of p
            exit(0);
        }
    }
}