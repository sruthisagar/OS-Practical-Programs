#include <stdio.h>
#include <stdlib.h>

int process[10], arrival[10], burst[10], bt[10], prio[10], turnaround[10], waiting[10], ct[10], n, tq;
int front = -1, rear = -1, readyq[100];
float avgwt, avgtt;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int k)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (arrival[j] > arrival[j + 1])
            {
                swap(&arrival[j], &arrival[j + 1]);
                swap(&burst[j], &burst[j + 1]);
                swap(&process[j], &process[j + 1]);

                if (k == 3)
                    swap(&prio[j], &prio[j + 1]);
            }
        }
    }
}

void display(int k)
{
    if (k == 1 || k == 2 || k == 4)
    {
        printf("\nProcess    Arrival Time    Burst Time    Waiting Time    Turnaround Time\n");
        for (int i = 0; i < n; i++)
            printf("   P%i\t\t%i\t\t%i\t\t%i\t\t%i\n", process[i], arrival[i], burst[i], waiting[i], turnaround[i]);
    }
    else
    {
        printf("\nProcess    Arrival Time    Burst Time      Priority      Waiting Time    Turnaround Time\n");
        for (int i = 0; i < n; i++)
            printf("   P%i\t\t%i\t\t%i\t\t%i\t\t%i\t\t%i\n", process[i], arrival[i], burst[i], prio[i], waiting[i], turnaround[i]);
    }

    if (k == 4)
        printf("\nTime quantum = %d", tq);

    printf("\nAverage turnaround time = %.2f\n", avgtt);
    printf("Average waiting time = %.2f\n\n", avgwt);
}

void avg()
{
    avgtt = avgwt = 0;

    for (int i = 0; i < n; i++)
    {
        avgtt += turnaround[i];
        avgwt += waiting[i];
    }

    avgwt /= n;
    avgtt /= n;
}

void fcfs()
{

    int tim = 0;
    avgwt = avgtt = 0;
    for (int i = 0; i < n; i++)
    {
        if (tim >= arrival[i])
        {
            waiting[i] = tim - arrival[i];
            tim += burst[i];
        }
        else
        {
            tim++;
            i--;
        }
        avgwt += waiting[i];
    }
    for (int i = 0; i < n; i++)
    {
        turnaround[i] = burst[i] + waiting[i];
        avgtt += turnaround[i];
    }

    avgwt /= n;
    avgtt /= n;

    display(1);
}

void sjf()
{

    int temp, val, low;

    ct[0] = arrival[0] + burst[0];
    turnaround[0] = ct[0] - arrival[0];
    waiting[0] = turnaround[0] - burst[0];

    for (int i = 1; i < n; i++)
    {
        temp = ct[i - 1];
        low = burst[i];
        for (int j = i; j < n; j++)
        {
            if (temp >= arrival[j] && low >= burst[j])
            {
                low = burst[j];
                val = j;
            }
        }
        ct[val] = temp + burst[val];
        turnaround[val] = ct[val] - arrival[val];
        waiting[val] = turnaround[val] - burst[val];

        swap(&arrival[val], &arrival[i]);
        swap(&burst[val], &burst[i]);

        swap(&ct[val], &ct[i]);
        swap(&waiting[val], &waiting[i]);
        swap(&turnaround[val], &turnaround[i]);

        swap(&process[val], &process[i]);
    }
    avg();
    display(2);
}

int psort(int a[], int s)
{
    int ind=0;
    for (int i = 0; i < s; i++)
    {
        if (prio[a[i]] < prio[a[ind]])
            ind=i;
    }
    return (a[ind]);
}

int remain()
{
    int s = 0;
    for (int i = 0; i < n; i++)
        s += bt[i];
    return (s);
}

void priority()
{

    int sum = 0, time = 0, k, r = 0, j = 0, temp[20];
    for (int i = 0; i < n; i++)
    {
        sum += burst[i];
        waiting[i] = -1;
        bt[i] = burst[i];
    }
    time = 0;
    while (remain())
    {
        r = 0;
        //finding all jobs with arrival time less than current time
        for (k = 0; k < n; k++)
        {
            if (time >= arrival[k] && bt[k] > 0)
            {
                temp[r] = k;
                r++;
            }
        }
        // finding job with highest priority
        if (r > 0)
        {
            if (r == 1)
                j = temp[0];
            else
                j = psort(temp, r);

            waiting[j] = time - arrival[j];
            turnaround[j] = waiting[j] + burst[j];
            time += burst[j];
            bt[j] = 0;
        }
        else
            time++;
    }

    avg();
    display(3);
}

void push(int item)
{
    if (front == -1)
        front = 0;
    rear = rear + 1;
    readyq[rear] = item;
}

int pop()
{
    int item = readyq[front];
    front = front + 1;
    return (item);
}

void roundrobin()
{

    int time = 0, r = 0, first[20], f = 0, t = 0;
    for (int i = 0; i < n; i++)
    {
        waiting[i] = -1;
        bt[i] = burst[i];
        first[i] = -1;
    }
    while (remain() > 0)
    {
        for (int k = 0; k < n; k++)
        {
            if (time >= arrival[k] && bt[k] > 0 && first[k] == -1)
            {
                push(k);
                first[k] = 0;
                r++;
            }
        }
        if (f == 1)
            push(t);

        if (bt[readyq[front]] <= tq && bt[readyq[front]] > 0 && r > 0)
        {
            time += bt[readyq[front]];
            bt[readyq[front]] = 0;
            turnaround[readyq[front]] = time - arrival[readyq[front]];
            waiting[readyq[front]] = turnaround[readyq[front]] - burst[readyq[front]];
            t = pop();
            r--;
            f = 0;
        }
        else if (bt[readyq[front]] > 0 && r > 0)
        {
            time += tq;
            bt[readyq[front]] -= tq;
            t = pop();
            f = 1;
        }
        else
        {
            time++;
        }
    }
    avg();
    display(4);
}

void main()
{
    int ch;

    while (1)
    {
        printf("1. FCFS Scheduling \n2. SJF Scheduling \n3. Priority Scheduling \n4. Round Robin Scheduling \n5. Exit \n");
        printf("\nEnter your choice\n");
        scanf("%d", &ch);

        if (ch == 5)
            exit(0);

        printf("Enter the number of processes\n");
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
            process[i] = i + 1;

        printf("Enter the arrival time\n");
        for (int i = 0; i < n; i++)
            scanf("%d", &arrival[i]);

        printf("Enter the burst time\n");
        for (int i = 0; i < n; i++)
            scanf("%d", &burst[i]);

        switch (ch)
        {
        case 1:
            sort(1);
            fcfs();
            break;

        case 2:
            sort(2);
            sjf();
            break;

        case 3:
            printf("Enter the priorities\n");
            for (int i = 0; i < n; i++)
                scanf("%d", &prio[i]);

            sort(3);
            priority();
            break;

        case 4:
            sort(4);
            printf("Enter the time quantum\n");
            scanf("%d", &tq);
            roundrobin();
            break;

        case 5:
            exit(0);

        default:
            printf("Invalid choice\n");
        }
    }
}
