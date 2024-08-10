// types header
#include "kernel/types.h"
// sys func header
#include "user/user.h"

// argc for num, argv for string
int main(int argc, char** argv)
{
    // sleep ticks
    int ticks;

    if (argc <= 1) {
        fprintf(2, "usage: sleep n(ticks)\n");
        // error exit
        exit(1);
    }

    // string to num
    ticks = atoi(argv[1]);
    // sys sleep
    sleep(ticks);
    // normal exit
    exit(0);
}
