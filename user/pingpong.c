/*
    In this .c we need to realize 
    communication between parent and child process

*/

#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char** argv)
{
    // fork to create a child process
    
    int fd1[2]; // one direction communicate
    int fd2[2]; // another direction communicate
    
    // a couple of pipes for communication
    pipe(fd1);
    pipe(fd2);

    // buffer
    char buf[512];

    int pid = fork(); // pid
     
    if(pid == 0){
        // child
        read(fd1[0], buf, 4); // read
        close(fd1[0]);
        printf("%d: received %s\n", getpid(), buf); // print msg
        write(fd2[1], "pong", 4); // write
        close(fd2[1]);
    } else {
        // parent
        write(fd1[1], "ping", 4); // write
        close(fd1[1]);
        read(fd2[0], buf, 4); // read
        close(fd2[0]);
        wait(0); // no confict in output
        printf("%d: received %s\n", getpid(), buf); // print msg
    }
    exit(0);
}