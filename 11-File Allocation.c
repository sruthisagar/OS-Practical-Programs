#include <stdlib.h>
#include <stdio.h>

int file[50], start[50], len[50], block[10][10], n;
int st, l;

void clear()
{
    int i = 20;
    while(i--)
        file[i] = 0;
}

void sequential()
{
    int i, k, flag;

    printf("\nEnter the no of files \n");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        flag = 0;
        printf("Enter the starting index and length of file %d \n", i);
        scanf("%d %d", &st, &l);

        for (k = st; k < st + l; k++)
            if (file[k] == 0)
                flag++;

        if (flag == l)
        {
            for (k = st; k < st + l; k++)
                file[k] = 1;
            start[i] = st;
            len[i] = l;
        }
        else
        {
            start[i] = -1;
            len[i] = 0;
        }
    }

    printf("\nThe allocated files are \n");
    printf("File \tStart \tLength\n");
    for (i = 1; i <= n; i++)
        if (start[i] != -1)
            printf("%d  \t%d \t%d\n", i, start[i], len[i]);
    printf("\n");
}

void indexed()
{

    int i, k, flag;

    printf("\nEnter the no of files \n");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        flag = 0;
        printf("Enter the index and length of file %d \n", i);
        scanf("%d %d", &st, &l);

        printf("Enter the blocks \n");
        for (k = 0; k < l; k++)
        {
            scanf("%d", &block[i][k]);
            if (file[block[i][k]] == 0)
                flag++;
        }
        if (file[st] == 0)
            flag++;

        if (flag == l + 1)
        {
            for (k = 0; k < l; k++)
                file[block[i][k]] = 1;

            file[st] = 1;
            start[i] = st;
            len[i] = l;
        }
        else
        {
            start[i] = -1;
            len[i] = 0;
        }
    }

    printf("\nThe allocated files are \n");
    printf("File \tStart \tLength\n");
    for (i = 1; i <= n; i++)
        if (start[i] != -1)
            printf("%d  \t%d \t%d\n", i, start[i], len[i]);
    printf("\n");
}

void linked()
{

    int i, k, flag;

    printf("\nEnter the no of files \n");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        flag = 0;
        printf("Enter the index and length of file %d \n", i);
        scanf("%d %d", &st, &l);

        printf("Enter the blocks \n");
        for (k = 0; k < l; k++)
        {
            scanf("%d", &block[i][k]);
            if (file[block[i][k]] == 0)
                flag++;
        }
        if (file[st] == 0)
            flag++;

        if (flag == l + 1)
        {
            for (k = 0; k < l; k++)
                file[block[i][k]] = 1;

            file[st] = 1;
            start[i] = st;
            len[i] = l;
        }
        else
        {
            start[i] = -1;
            len[i] = 0;
        }
    }

    printf("\nThe allocated files are \n");
    printf("File \tStart \tLength \tBlocks\n");
    for (i = 1; i <= n; i++)
    {
        if (start[i] != -1)
        {
            printf("%d  \t%d \t%d\t", i, start[i], len[i]);
            for (k = 0; k < len[i] - 1; k++)
                printf("%d -> ", block[i][k]);
            printf("%d\n", block[i][k]);
        }
    }
    printf("\n");
}

void main()
{
    int ch, flag = 1;
    while (flag)
    {
        printf("1. Sequential \n2. Indexed \n3. Linked \n4. Exit \n");
        printf("Enter your choice\n");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
                clear();
                sequential();
                break;
            case 2:
                clear();
                indexed();
                break;
            case 3:
                clear();
                linked();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
}
