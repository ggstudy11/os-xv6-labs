#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char** argv)
{
    // sleep ticks
    int ticks;
    if (argc <= 1) {
        printf("usage: sleep n(ticks)\n");
        exit(0);
    }
    ticks = atoi(argv[1]);
    sleep(ticks);
    exit(0);
}
