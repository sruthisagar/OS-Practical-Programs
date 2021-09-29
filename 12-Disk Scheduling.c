#include <stdio.h>
#include <stdlib.h>

int requests[50], diff[10][10], seekseq[50], lowq[50], uppq[50], l, u, head, scount, n, h, dsize;
char dir;

void fcfs()
{
    int i;
    head = h;
    scount = 0;

    printf("\nFCFS\n");
    for (i = 0; i < n; i++)
    {
        scount += abs(requests[i] - head);
        head = requests[i];
    }

    printf("Seek Sequence \n%d -> ", h);
    for (i = 0; i < n - 1; i++)
        printf("%d -> ", requests[i]);
    printf("%d\n", requests[i]);
    printf("Total seek time\n%d\n", scount);
}

void calcdiff(int head)
{
    for (int i = 0; i < n; i++)
        diff[i][0] = abs(requests[i] - head);
}

int minindex()
{
    int ind = -1;
    int min = 1e9;

    for (int i = 0; i < n; i++)
    {
        if (!diff[i][1] && min > diff[i][0])
        {
            min = diff[i][0];
            ind = i;
        }
    }
    return ind;
}

void sstf()
{
    int i, ind;
    head = h;
    scount = 0;

    printf("\nSSTF\n");
    for (i = 0; i < n; i++)
    {
        seekseq[i] = head;
        calcdiff(head);
        ind = minindex();

        diff[ind][1] = 1;
        scount += diff[ind][0];
        head = requests[ind];
    }
    seekseq[i] = head;

    printf("Seek Sequence \n");
    for (i = 0; i < n; i++)
        printf("%d -> ", seekseq[i]);
    printf("%d\n", seekseq[i]);
    printf("Total seek time\n%d\n", scount);
}

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void scan()
{
    int i, j, y, ss = 1;
    head = h;
    scount = 0;
    l = u = 0;
    seekseq[0] = head;

    printf("\nSCAN\n");

    if (dir == 'l')
        lowq[l++] = 0;
    else
        uppq[u++] = dsize - 1;

    for (i = 0; i < n; i++)
    {
        if (requests[i] < head)
            lowq[l++] = requests[i];
        else
            uppq[u++] = requests[i];
    }
    qsort(lowq, l, sizeof(int), cmpfunc);
    qsort(uppq, u, sizeof(int), cmpfunc);

    for (i = 0; i < 2; i++)
    {
        if (dir == 'l')
        {
            for (j = ss, y = l - 1; y >= 0; y--, j++)
            {
                seekseq[j] = lowq[y];
                scount += abs(lowq[y] - head);
                head = lowq[y];
            }
            ss = j;
            dir = 'r';
        }
        else if (dir == 'r')
        {
            for (j = ss, y = 0; y < u; y++, j++)
            {
                seekseq[j] = uppq[y];
                scount += abs(uppq[y] - head);
                head = uppq[y];
            }
            ss = j;
            dir = 'l';
        }
    }

    printf("Seek Sequence \n");
    for (i = 0; i < ss - 1; i++)
        printf("%d -> ", seekseq[i]);
    printf("%d\n", seekseq[i]);
    printf("Total seek time\n%d\n", scount);
}

void cscan()
{
    int i, j, y, ss = 1;
    head = h;
    scount = 0;
    l = u = 0;
    seekseq[0] = head;

    printf("\nCSCAN\n");

    lowq[l++] = 0;
    uppq[u++] = dsize - 1;

    for (i = 0; i < n; i++)
    {
        if (requests[i] < head)
            lowq[l++] = requests[i];
        else
            uppq[u++] = requests[i];
    }
    qsort(lowq, l, sizeof(int), cmpfunc);
    qsort(uppq, u, sizeof(int), cmpfunc);

    if (dir == 'l')
    {
        for (j = ss, y = l - 1; y >= 0; y--, j++)
        {
            seekseq[j] = lowq[y];
            scount += abs(lowq[y] - head);
            head = lowq[y];
        }
        for (y = u - 1; y >= 0; y--, j++)
        {
            seekseq[j] = uppq[y];
            scount += abs(uppq[y] - head);
            head = uppq[y];
        }
        ss = j;
    }
    else if (dir == 'r')
    {
        for (j = ss, y = 0; y < u; y++, j++)
        {
            seekseq[j] = uppq[y];
            scount += abs(uppq[y] - head);
            head = uppq[y];
        }
        for (y = 0; y < l; y++, j++)
        {
            seekseq[j] = lowq[y];
            scount += abs(lowq[y] - head);
            head = lowq[y];
        }
        ss = j;
    }

    printf("Seek Sequence \n");
    for (i = 0; i < ss - 1; i++)
        printf("%d -> ", seekseq[i]);
    printf("%d\n", seekseq[i]);
    printf("Total seek time\n%d\n", scount);
}

void look()
{
    int i, j, y, ss = 1;
    head = h;
    scount = 0;
    l = u = 0;
    seekseq[0] = head;

    printf("\nLOOK\n");

    for (i = 0; i < n; i++)
    {
        if (requests[i] < head)
            lowq[l++] = requests[i];
        else
            uppq[u++] = requests[i];
    }
    qsort(lowq, l, sizeof(int), cmpfunc);
    qsort(uppq, u, sizeof(int), cmpfunc);

    for (i = 0; i < 2; i++)
    {
        if (dir == 'l')
        {
            for (j = ss, y = l - 1; y >= 0; y--, j++)
            {
                seekseq[j] = lowq[y];
                scount += abs(lowq[y] - head);
                head = lowq[y];
            }
            ss = j;
            dir = 'r';
        }
        else if (dir == 'r')
        {
            for (j = ss, y = 0; y < u; y++, j++)
            {
                seekseq[j] = uppq[y];
                scount += abs(uppq[y] - head);
                head = uppq[y];
            }
            ss = j;
            dir = 'l';
        }
    }

    printf("Seek Sequence \n");
    for (i = 0; i < ss - 1; i++)
        printf("%d -> ", seekseq[i]);
    printf("%d\n", seekseq[i]);
    printf("Total seek time\n%d\n", scount);
}

void clook()
{
    int i, j, y, ss = 1;
    head = h;
    scount = 0;
    l = u = 0;
    seekseq[0] = head;

    printf("\nCLOOK\n");

    for (i = 0; i < n; i++)
    {
        if (requests[i] < head)
            lowq[l++] = requests[i];
        else
            uppq[u++] = requests[i];
    }
    qsort(lowq, l, sizeof(int), cmpfunc);
    qsort(uppq, u, sizeof(int), cmpfunc);

    if (dir == 'l')
    {
        for (j = ss, y = l - 1; y >= 0; y--, j++)
        {
            seekseq[j] = lowq[y];
            scount += abs(lowq[y] - head);
            head = lowq[y];
        }
        for (y = u - 1; y >= 0; y--, j++)
        {
            seekseq[j] = uppq[y];
            scount += abs(uppq[y] - head);
            head = uppq[y];
        }
        ss = j;
    }
    else if (dir == 'r')
    {
        for (j = ss, y = 0; y < u; y++, j++)
        {
            seekseq[j] = uppq[y];
            scount += abs(uppq[y] - head);
            head = uppq[y];
        }
        for (y = 0; y < l; y++, j++)
        {
            seekseq[j] = lowq[y];
            scount += abs(lowq[y] - head);
            head = lowq[y];
        }
        ss = j;
    }

    printf("Seek Sequence \n");
    for (i = 0; i < ss - 1; i++)
        printf("%d -> ", seekseq[i]);
    printf("%d\n", seekseq[i]);
    printf("Total seek time\n%d\n", scount);
}

void main()
{
    printf("Enter the no of requests\n");
    scanf("%d", &n);
    printf("Enter the request sequence\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);
    printf("Enter the head position and direction\n");
    scanf("%d %c", &h, &dir);
    printf("Enter the disk size\n");
    scanf("%d", &dsize);

    fcfs();
    sstf();
    scan();
    cscan();
    look();
    clook();
}