#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"
char buf[1024];

int main(int argc, char *argv[])
{
    int idx = 0;
    if (argc <= 1)
    {
        fprintf(2, "usage: xargs commands...");
        exit(0);
    }
    char *params[MAXARG];

    for (int i = 1; i < argc; i++)
    {
        params[i - 1] = argv[i];
    }
    params[argc] = 0;
    
    while (read(0, buf + idx, 1))
    {
        if (buf[idx] != '\n')
        {
            idx++;
            continue;
        }
        buf[idx] = 0;
        if (fork() == 0)
        {
            params[argc - 1] = buf;

            exec(params[0], params);
            fprintf(2, "command failed:");
            for (int i = 0; i < argc + 1; i++)
            {
                fprintf(2, "%s ", params[i]);
            }
            fprintf(2, "\n");
            exit(1);
        }
        else
        {
            wait(0);
            idx = 0;
        }
    }
    exit(0);
}