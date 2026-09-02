/*
===============================================================================
                     DATA STRUCTURES LABORATORY
===============================================================================

Experiment : 3.B
Title      : Array Implementation of Queue
Language   : C
Standard   : C11

Implementation:
    Circular Queue using a fixed-size array.

Operations:
    1. Enqueue
    2. Dequeue
    3. Peek
    4. Display

Complexity:
    Enqueue : O(1)
    Dequeue : O(1)
    Peek    : O(1)
    Display : O(n)
    Space   : O(n)

Note:
    A circular queue is used instead of a simple linear queue so that
    positions released by dequeue can be reused.

===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct
{
    int items[MAX_SIZE];
    int front;
    int rear;
    int count;
} Queue;

static void initialize_queue(Queue *queue);
static int is_empty(const Queue *queue);
static int is_full(const Queue *queue);
static void enqueue(Queue *queue, int data);
static void dequeue(Queue *queue);
static void peek(const Queue *queue);
static void display(const Queue *queue);
static int read_int(const char *prompt, int *value);

/* ========================================================================= */

int main(void)
{
    Queue queue;
    int choice;
    int data;

    initialize_queue(&queue);

    while (1)
    {
        printf("\n========================================\n");
        printf("           QUEUE USING ARRAY\n");
        printf("========================================\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        if (!read_int("Enter your choice: ", &choice))
            return EXIT_FAILURE;

        switch (choice)
        {
            case 1:
                if (!read_int("Enter data: ", &data))
                    break;
                enqueue(&queue, data);
                break;

            case 2:
                dequeue(&queue);
                break;

            case 3:
                peek(&queue);
                break;

            case 4:
                display(&queue);
                break;

            case 5:
                printf("Program terminated successfully.\n");
                return EXIT_SUCCESS;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

static int read_int(const char *prompt, int *value)
{
    int result;
    int character;

    printf("%s", prompt);
    result = scanf("%d", value);

    while ((character = getchar()) != '\n' && character != EOF)
        ;

    if (result != 1)
    {
        printf("Invalid input.\n");
        return 0;
    }

    return 1;
}

/* ========================================================================= */

static void initialize_queue(Queue *queue)
{
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
}

/* ========================================================================= */

static int is_empty(const Queue *queue)
{
    return queue->count == 0;
}

/* ========================================================================= */

static int is_full(const Queue *queue)
{
    return queue->count == MAX_SIZE;
}

/* ========================================================================= */

static void enqueue(Queue *queue, int data)
{
    if (is_full(queue))
    {
        printf("Queue Overflow.\n");
        return;
    }

    queue->items[queue->rear] = data;
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    ++queue->count;

    printf("Element enqueued successfully.\n");
}

/* ========================================================================= */

static void dequeue(Queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue Underflow.\n");
        return;
    }

    printf("Dequeued element: %d\n", queue->items[queue->front]);

    queue->front = (queue->front + 1) % MAX_SIZE;
    --queue->count;
}

/* ========================================================================= */

static void peek(const Queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Front element: %d\n", queue->items[queue->front]);
}

/* ========================================================================= */

static void display(const Queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue (Front -> Rear): ");

    for (int i = 0; i < queue->count; ++i)
    {
        int index = (queue->front + i) % MAX_SIZE;
        printf("%d%s", queue->items[index],
               i == queue->count - 1 ? "\n" : " ");
    }
}
