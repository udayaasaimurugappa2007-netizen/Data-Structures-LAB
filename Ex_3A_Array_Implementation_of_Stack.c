/*
===============================================================================
                     DATA STRUCTURES LABORATORY
===============================================================================

Experiment : 3.A
Title      : Array Implementation of Stack
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

#define MAX_SIZE 100

typedef struct
{
    int items[MAX_SIZE];
    int top;
} Stack;

static void initialize_stack(Stack *stack);
static int is_empty(const Stack *stack);
static int is_full(const Stack *stack);
static void push(Stack *stack, int data);
static void pop(Stack *stack);
static void peek(const Stack *stack);
static void display(const Stack *stack);
static int read_int(const char *prompt, int *value);

/* ========================================================================= */

int main(void)
{
    Stack stack;
    int choice;
    int data;

    initialize_stack(&stack);

    while (1)
    {
        printf("\n========================================\n");
        printf("           STACK USING ARRAY\n");
        printf("========================================\n");
        printf("1. Push\n");
        printf("2. Pop\n");
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
                push(&stack, data);
                break;

            case 2:
                pop(&stack);
                break;

            case 3:
                peek(&stack);
                break;

            case 4:
                display(&stack);
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

static void initialize_stack(Stack *stack)
{
    stack->top = -1;
}

/* ========================================================================= */

static int is_empty(const Stack *stack)
{
    return stack->top == -1;
}

/* ========================================================================= */

static int is_full(const Stack *stack)
{
    return stack->top == MAX_SIZE - 1;
}

/* ========================================================================= */

static void push(Stack *stack, int data)
{
    if (is_full(stack))
    {
        printf("Stack Overflow.\n");
        return;
    }

    stack->items[++stack->top] = data;

    printf("Element pushed successfully.\n");
}

/* ========================================================================= */

static void pop(Stack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack Underflow.\n");
        return;
    }

    printf("Popped element: %d\n", stack->items[stack->top--]);
}

/* ========================================================================= */

static void peek(const Stack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Top element: %d\n", stack->items[stack->top]);
}

/* ========================================================================= */

static void display(const Stack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack (Top -> Bottom): ");

    for (int i = stack->top; i >= 0; --i)
        printf("%d%s", stack->items[i], i == 0 ? "\n" : " ");
}
