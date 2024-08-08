/*
    In this .c we need to realize 
    communication between parent and child process

*/

#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char** argv)
{
    // fork to create a child process
    
    int d1[2]; // one direction communicate
    int d2[2]; // another direction communicate
    
    // a couple of pipes for communication
    pipe(d1);
    pipe(d2);

    // buffer
    char buf[512];

    int pid = fork();
     
    if(pid == 0){
        read(d1[0], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        write(d2[1], "pong", 4);
    } else {
        write(d1[1], "ping", 4);
        read(d2[0], buf, 4);
        wait(0);
        printf("%d: received %s\n", getpid(), buf);
    }
    exit(0);
}