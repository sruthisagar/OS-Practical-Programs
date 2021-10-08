#include <stdio.h>

int process[10];
int n, m, holeNo, temp, flag;
int holes1[10], holes2[10], holes3[3];

void display(int arr[10])
{
    printf("\nHole No \t Hole size \n");
    for (int i = 0; i < n; i++)
        printf("   %d \t\t    %d \n", i, arr[i]);
    printf("\n");
}

void firstfit()
{
    for (int i = 0; i < m; i++)
    {
        flag = 0;
        for (int j = 0; j < n; j++)
        {
            if (holes1[j] >= process[i])
            {
                holes1[j] = holes1[j] - process[i];
                printf("%d allocated at H%d \n", process[i], j);
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            printf("%d not allocated \n", process[i]);
    }
}

void bestfit()
{
    for (int i = 0; i < m; i++)
    {
        temp = 10000;
        holeNo = 0;
        flag = 0;
        for (int j = 0; j < n; j++)
        {
            if ((holes2[j] >= process[i]) && (holes2[j] < temp))
            {
                holeNo = j;
                temp = holes2[j];
                flag = 1;
            }
        }
        if (flag == 1)
        {
            holes2[holeNo] = holes2[holeNo] - process[i];
            printf("%d allocated at H%d \n", process[i], holeNo);
        }
        else
            printf("%d not allocated \n", process[i]);
    }
}

void worstfit()
{
    for (int i = 0; i < m; i++)
    {
        temp = 0;
        holeNo = 0;
        flag = 0;
        for (int j = 0; j < n; j++)
        {
            if ((holes3[j] >= process[i]) && (holes3[j] > temp))
            {
                holeNo = j;
                temp = holes3[j];
                flag = 1;
            }
        }
        if (flag == 1)
        {
            holes3[holeNo] = holes3[holeNo] - process[i];
            printf("%d allocated at H%d \n", process[i], holeNo);
        }
        else
            printf("%d not allocated \n", process[i]);
    }
}

int main()
{
    printf("Enter the no. of holes: \n");
    scanf("%d", &n);

    printf("\nEnter the hole sizes:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &holes1[i]);
        holes2[i] = holes3[i] = holes1[i];
    }

    printf("\nEnter the no. of process: \n");
    scanf("%d", &m);

    printf("\nEnter the process sizes: \n");
    for (int i = 0; i < m; i++)
        scanf("%d", &process[i]);

    printf("\nFIRST-FIT \n");
    firstfit();
    display(holes1);

    printf("BEST-FIT \n");
    bestfit();
    display(holes2);

    printf("WORST-FIT \n");
    worstfit();
    display(holes3);
}
