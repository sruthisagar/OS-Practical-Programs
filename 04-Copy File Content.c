#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void main()
{
    int n;
    char file1[20], file2[20], ch[100];

    printf("Enter two file names \n");
    scanf("%s %s", file1, file2);

    // printf("%s %s", file1, file2);

    int fp1 = open(file1, O_RDONLY);
    if (fp1 == -1)
    {
        printf("%s not found \n", file1);
        exit(1);
    }

    int fp2 = open(file2, O_WRONLY | O_CREAT);
    printf("\nContent of %s : \n", file2);

    do
    {
        n = read(fp1, ch, sizeof(ch));
        write(fp2, ch, n);
        write(1, ch, n);
    } while (n > 0);

    close(fp1);
    close(fp2);
}