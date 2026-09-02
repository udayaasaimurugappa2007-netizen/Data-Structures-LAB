/*
===============================================================================
                     DATA STRUCTURES LABORATORY
===============================================================================

Experiment : 4.A
Title      : Linked List Implementation of Stack
Language   : C
Standard   : C11

Operations:
    1. Push
    2. Pop
    3. Peek
    4. Display

Complexity:
    Push    : O(1)
    Pop     : O(1)
    Peek    : O(1)
    Display : O(n)
    Space   : O(n)

===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

static Node *create_node(int data);
static void push(Node **top, int data);
static void pop(Node **top);
static void peek(const Node *top);
static void display(const Node *top);
static void free_stack(Node **top);
static int read_int(const char *prompt, int *value);

/* ========================================================================= */

int main(void)
{
    Node *top = NULL;
    int choice;
    int data;

    while (1)
    {
        printf("\n========================================\n");
        printf("        STACK USING LINKED LIST\n");
        printf("========================================\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        if (!read_int("Enter your choice: ", &choice))
        {
            free_stack(&top);
            return EXIT_FAILURE;
        }

        switch (choice)
        {
            case 1:
                if (!read_int("Enter data: ", &data))
                    break;
                push(&top, data);
                break;

            case 2:
                pop(&top);
                break;

            case 3:
                peek(top);
                break;

            case 4:
                display(top);
                break;

            case 5:
                free_stack(&top);
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

static void push(Node **top, int data)
{
    Node *new_node = create_node(data);

    new_node->next = *top;
    *top = new_node;

    printf("Element pushed successfully.\n");
}

/* ========================================================================= */

static void pop(Node **top)
{
    if (*top == NULL)
    {
        printf("Stack Underflow.\n");
        return;
    }

    Node *temp = *top;

    printf("Popped element: %d\n", temp->data);

    *top = temp->next;
    free(temp);
}

/* ========================================================================= */

static void peek(const Node *top)
{
    if (top == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Top element: %d\n", top->data);
}

/* ========================================================================= */

static void display(const Node *top)
{
    if (top == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack (Top -> Bottom): ");

    for (const Node *current = top; current != NULL; current = current->next)
        printf("%d%s", current->data,
               current->next == NULL ? "\n" : " ");
}

/* ========================================================================= */

static void free_stack(Node **top)
{
    while (*top != NULL)
    {
        Node *temp = *top;
        *top = temp->next;
        free(temp);
    }
}
