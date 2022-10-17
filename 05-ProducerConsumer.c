#include <stdio.h>
#include <stdlib.h>

// Producer Consumer Problems

int full = 0, buffer = 10, itemNo = 0, n = 0;

void producer()
{
    printf ("Enter the no of items\n");
    scanf ("%d", &n);
    if(n <= buffer)
    {
        full += n;
        buffer -= n;
        itemNo += n;
        printf ("Producer produces %d items\n", n);
    }
    else
        printf ("Cannot produce %d items as item limit is reached\n", n);
}


void consumer()
{
    --full;
    ++buffer;
    printf ("Consumer consumes item %d\n", itemNo);
    itemNo--;
}

int main()
{
    int ch;

    while (1)
    {
        printf ("\n1. Producer\n2. Consumer\n3. Exit\n");
        printf("Enter your choice\n");
        scanf ("%d", &ch);

        switch (ch)
        {
            case 1:
                if (buffer != 0)
                    producer();
                else
                    printf ("Buffer is full\n");
                    break;

            case 2:
                if (full != 0)
                    consumer();
                else
                    printf ("Buffer is empty\n");
                    break;

            case 3:
                exit (0);
                break;

            default:
                printf("Invalid choice\n");
        }
    }
}

// End
