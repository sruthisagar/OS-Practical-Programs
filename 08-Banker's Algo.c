#include <stdio.h>
#include <stdlib.h>

int allocation[5][5], max[5][4], need[5][5], available[10], work[10];

int p, r, f[10], safe[10];

int safety ()
{

  int i, j, k, y, flag, ind = 0;
  
  for (j = 0; j < r; j++)
    work[j]=available[j];

  for (k = 0; k < p; k++)
    {
      for (i = 0; i < p; i++)
	{
	  if (f[i] == 0)
	    {
	      flag = 0;
	      for (j = 0; j < r; j++)
		if (need[i][j] > work[j])
		  {
		    flag = 1;
		    break;
		  }
	      if (flag == 0)
		{
		  safe[ind++] = i;
		  for (y = 0; y < r; y++)
		    work[y] += allocation[i][y];
		  f[i] = 1;
		}
	    }
	}
    }
  if (ind == p){
//         printf ("The safe sequence is \t");
//   for (j = 0; j < p - 1; j++)
//     printf ("P%d -> ", safe[j]);
//   printf ("P%d \n", safe[j]);
      return 1;
  }

  else
    return 0;
}

void display()
{
    int i, j;
    printf("\nProcess\t\tAllocation\t\t\t Max\t\t\t    Need\n");
    for (i = 0; i < p; i++)
    {
        printf("P%d\t", i);
        for (j = 0; j < r; j++)
            printf("%6d", allocation[i][j]);
        printf("    ");
        for (j = 0; j < r; j++)
            printf("%6d", max[i][j]);
        printf("    ");
        for (j = 0; j < r; j++)
            printf("%6d", need[i][j]);
        printf("\n");
    }
    printf("\n");
    printf("The safe sequence is \t");
    for (j = 0; j < p - 1; j++)
        printf("P%d -> ", safe[j]);
    printf("P%d \n", safe[j]);
}

void request()
{
    int i, pid, request[p];
    printf("Enter the process id  ");
    scanf("%d", &pid);

    printf("Enter the request  ");
    for (i = 0; i < r; i++)
        scanf("%d", &request[i]);
    for (i = 0; i < r; i++)
        if (request[i] > need[pid][i] || request[i] > available[i])
        {
            printf("Resourse cannot be allocated deadlock will occur \n");
            exit(0);
        }
    for (i = 0; i < r; i++)
    {
        available[i] -= request[i];
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }
}

void main()
{
    int x, i, j;
    printf("Enter the no of processes   ");
    scanf("%d", &p);
    printf("Enter the no of resources   ");
    scanf("%d", &r);

    for (i = 0; i < p; i++)
    {
        printf("Enter the allocation for process p%d ", i);
        for (j = 0; j < r; j++)
            scanf("%d", &allocation[i][j]);
    }

    for (i = 0; i < p; i++)
    {
        printf("Enter the max for process p%d ", i);
        for (j = 0; j < r; j++)
            scanf("%d", &max[i][j]);
    }

    printf("Enter the available resources for the processes  ");
    for (j = 0; j < r; j++)
        scanf("%d", &available[j]);

    for (i = 0; i < p; i++)
    {
        for (j = 0; j < r; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    }
    if (safety()) //check if safety sequence can be obtained
    {
        display();
        while (1)
        {
            printf("Do you have resource request (1/0) \t"); //extra resource request
            scanf("%d", &x);
            if (x)
            {
                request();
                if (safety())
                    display();
                else
                {
                    printf("Deadlock Occurred \n");
                    exit(0);
                }
            }
            else
                exit(0);
        }
    }
    else
    {
        printf("Deadlock Occurred \n");
        exit(0);
    }
}
