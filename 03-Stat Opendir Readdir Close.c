#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

void main()
{
    struct stat buf;
    DIR *d;
    struct dirent *de;
    int exists;

    d = opendir("/media/dingusagar/Data1/Sruthi/OSLab/Exp-3");
    if (d == NULL)
    {
        fprintf(stderr, "Couldn't open \n");
        exit(1);
    }

    for (de = readdir(d); de != NULL; de = readdir(d))
    {
        exists = stat(de->d_name, &buf);
        if (exists < 0)
            fprintf(stderr, "%s not found \n", de->d_name);
        else
            printf("%s, %ld \n", de->d_name, buf.st_size);
    }

    closedir(d);
}