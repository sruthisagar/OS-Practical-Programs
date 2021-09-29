#include <stdlib.h>
#include <stdio.h>

int npage, nframe, i, j, k, fault;
int available, f1, f2, f3, max, min, ind, temp[50], pages[50];

int frames[50];

void fifo()
{
    j = 0;
    printf("\tFIFO  \n");
    printf(" PageNo\t\tPgFrames\n");

    for (i = 0; i < npage; i++)
    {
        printf("  %d\t\t", pages[i]);
        available = 0;

        for (k = 0; k < nframe; k++)
            if (frames[k] == pages[i])
            {
                available = 1;
                break;
            }

        if (available == 0)
        {
            frames[j] = pages[i];
            j = (j + 1) % nframe;
            fault++;
        }

        for (k = 0; k < nframe; k++)
            printf("%d  ", frames[k]);
        printf("\n");
    }

    printf("\nPage Faults is  %d\n\n", fault);
}

void optimal()
{
    printf("\tOPTIMAL  \n");
    printf(" PageNo\t\tPgFrames\n");

    for (i = 0; i < npage; i++)
    {
        printf("  %d\t\t", pages[i]);
        f1 = f2 = 0;

        for (j = 0; j < nframe; j++)
            if (frames[j] == pages[i])
            {
                f1 = f2 = 1;
                break;
            }

        if (f1 == 0)
        {
            for (j = 0; j < nframe; j++)
                if (frames[j] == -1)
                {
                    frames[j] = pages[i];
                    fault++;
                    f2 = 1;
                    break;
                }
        }

        if (f2 == 0)
        {
            f3 = 0;
            for (j = 0; j < nframe; j++)
            {
                temp[j] = -1;
                for (k = i + 1; k < npage; k++)
                    if (frames[j] == pages[k])
                    {
                        temp[j] = k;
                        break;
                    }
            }

            for (j = 0; j < nframe; j++)
                if (temp[j] == -1)
                {
                    ind = j;
                    f3 = 1;
                }

            if (f3 == 0)
            {
                max = temp[0];
                ind = 0;
                for (j = 1; j < nframe; j++)
                    if (temp[j] > max)
                    {
                        max = temp[j];
                        ind = j;
                    }
            }

            frames[ind] = pages[i];
            fault++;
        }

        for (k = 0; k < nframe; k++)
            printf("%d  ", frames[k]);
        printf("\n");
    }
    printf("\nPage Faults is  %d\n\n", fault);
}

void lru()
{
    printf("\tLRU  \n");
    printf(" PageNo\t\tPgFrames\n");

    for (i = 0; i < npage; i++)
    {
        printf("  %d\t\t", pages[i]);
        f1 = f2 = 0;

        for (j = 0; j < nframe; j++)
            if (frames[j] == pages[i])
            {
                f1 = f2 = 1;
                break;
            }

        if (f1 == 0)
        {
            for (j = 0; j < nframe; j++)
                if (frames[j] == -1)
                {
                    frames[j] = pages[i];
                    fault++;
                    f2 = 1;
                    break;
                }
        }

        if (f2 == 0)
        {
            f3 = 0;
            min = i;
            for (j = 0; j < nframe; j++)
            {
                for (k = i - 1; k >= 0; k--)
                    if (frames[j] == pages[k])
                    {
                        if (k < min)
                        {
                            min = k;
                            ind = j;
                        }
                        break;
                    }
            }

            frames[ind] = pages[i];
            fault++;
        }

        for (k = 0; k < nframe; k++)
            printf("%d  ", frames[k]);
        printf("\n");
    }
    printf("\nPage Faults is  %d\n\n", fault);
}

void clear()
{
    fault = 0;
    for (i = 0; i < nframe; i++)
        frames[i] = -1;
}

int main()
{
    printf("Enter the no of pages\n");
    scanf("%d", &npage);

    printf("Enter the reference string\n");
    for (i = 0; i < npage; i++)
        scanf("%d", &pages[i]);

    printf("Enter the no of frames\n");
    scanf("%d", &nframe);
    printf("\n");

    int ch;
    do
    {
        clear();
        printf("1. FIFO \n2. Optimal \n3. LRU \n4. Exit\n");
        printf("Enter your choice\n");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            fifo();
            break;
        case 2:
            optimal();
            break;
        case 3:
            lru();
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice \n");
        }
    } while (ch != 0);

    return 0;
}
