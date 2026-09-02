/*
===============================================================================
                     DATA STRUCTURES LABORATORY
===============================================================================

Experiment : 4.B
Title      : Linked List Implementation of Queue
Language   : C
Standard   : C11

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

Implementation:
    A front pointer and a rear pointer are maintained so that both
    insertion and deletion can be performed in constant time.

===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct
{
    Node *front;
    Node *rear;
} Queue;

static Node *create_node(int data);
static void initialize_queue(Queue *queue);
static void enqueue(Queue *queue, int data);
static void dequeue(Queue *queue);
static void peek(const Queue *queue);
static void display(const Queue *queue);
static void free_queue(Queue *queue);
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
        printf("        QUEUE USING LINKED LIST\n");
        printf("========================================\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        if (!read_int("Enter your choice: ", &choice))
        {
            free_queue(&queue);
            return EXIT_FAILURE;
        }

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
                free_queue(&queue);
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

static Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

/* ========================================================================= */

static void initialize_queue(Queue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
}

/* ========================================================================= */

static void enqueue(Queue *queue, int data)
{
    Node *new_node = create_node(data);

    if (queue->rear == NULL)
    {
        queue->front = new_node;
        queue->rear = new_node;
    }
    else
    {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }

    printf("Element enqueued successfully.\n");
}

/* ========================================================================= */

static void dequeue(Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Queue Underflow.\n");
        return;
    }

    Node *temp = queue->front;

    printf("Dequeued element: %d\n", temp->data);

    queue->front = temp->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    free(temp);
}

/* ========================================================================= */

static void peek(const Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Front element: %d\n", queue->front->data);
}

/* ========================================================================= */

static void display(const Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue (Front -> Rear): ");

    for (const Node *current = queue->front;
         current != NULL;
         current = current->next)
    {
        printf("%d%s", current->data,
               current->next == NULL ? "\n" : " ");
    }
}

/* ========================================================================= */

static void free_queue(Queue *queue)
{
    while (queue->front != NULL)
    {
        Node *temp = queue->front;
        queue->front = temp->next;
        free(temp);
    }

    queue->rear = NULL;
}
