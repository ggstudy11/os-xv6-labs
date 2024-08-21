#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"


void find(char* dir, char* file) {

    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(dir, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", dir);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", dir);
        close(fd);
        return;
    }

    if (st.type != T_DIR) {

        fprintf(2, "find: %s is not a directory\n", dir);
        close(fd);
        return;
    }

    if (strlen(dir) + 1 + DIRSIZ + 1 > sizeof (buf)) {
        fprintf(2, "find: directory too long\n");
        close(fd);
        return;
    }

    strcpy(buf, dir);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
        if(de.inum == 0)
            continue;
        if (!strcmp(de.name, ".") || !strcmp(de.name, ".."))
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0)
        {
            fprintf(2, "find: cannot stat %s\n", buf);
            continue;
        }
        if (st.type == T_DIR)
        {
            find(buf, file);
        }else if (st.type == T_FILE && !strcmp(de.name, file))
        {
            printf("%s\n", buf);
        } 
    }

    close(fd);
}

int main(int argc, char** argv)
{
    // find dirName fileName
    if (argc != 3) {
        printf("usage: find dirname filename\n");
        exit(1);
    } 
    find(argv[1], argv[2]);
    exit(0);
}
