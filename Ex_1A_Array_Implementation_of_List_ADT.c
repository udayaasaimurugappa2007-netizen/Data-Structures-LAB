/*
===============================================================================
                     DATA STRUCTURES LABORATORY
===============================================================================

Experiment : 1.A
Title      : Array Implementation of List ADT
Language   : C
Standard   : C11

Description:
    Implements a List ADT using a fixed-size array.

Operations:
    1. Create List
    2. Insert Element
    3. Delete Element
    4. Search Element
    5. Display List

Complexity:
    Create  : O(n)
    Insert  : O(n) worst case
    Delete  : O(n) worst case
    Search  : O(n)
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
    int size;
} List;

/* Function Prototypes */
static void initialize_list(List *list);
static void create_list(List *list);
static void insert_element(List *list);
static void delete_element(List *list);
static void search_element(const List *list);
static void display_list(const List *list);
static int read_int(const char *prompt, int *value);

/* ========================================================================= */

int main(void)
{
    List list;
    int choice;

    initialize_list(&list);

    while (1)
    {
        printf("\n========================================\n");
        printf("        ARRAY IMPLEMENTATION OF LIST\n");
        printf("========================================\n");
        printf("1. Create List\n");
        printf("2. Insert Element\n");
        printf("3. Delete Element\n");
        printf("4. Search Element\n");
        printf("5. Display List\n");
        printf("6. Exit\n");
        printf("----------------------------------------\n");
        if (!read_int("Enter your choice: ", &choice))
        {
            return EXIT_FAILURE;
        }

        switch (choice)
        {
            case 1:
                create_list(&list);
                break;

            case 2:
                insert_element(&list);
                break;

            case 3:
                delete_element(&list);
                break;

            case 4:
                search_element(&list);
                break;

            case 5:
                display_list(&list);
                break;

            case 6:
                printf("Program terminated successfully.\n");
                return EXIT_SUCCESS;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

/* ========================================================================= */

static void initialize_list(List *list)
{
    list->size = 0;
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

static void create_list(List *list)
{
    int n;

    if (!read_int("Enter number of elements (0-100): ", &n))
        return;

    if (n < 0 || n > MAX_SIZE)
    {
        printf("Invalid size.\n");
        return;
    }

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; ++i)
    {
        if (!read_int("Enter element: ", &list->items[i]))
            return;
    }

    list->size = n;

    printf("List created successfully.\n");
}

/* ========================================================================= */

static void insert_element(List *list)
{
    int position;
    int value;

    if (list->size == MAX_SIZE)
    {
        printf("List is full. Insertion not possible.\n");
        return;
    }

    if (!read_int("Enter element: ", &value) ||
        !read_int("Enter position: ", &position))
        return;

    if (position < 0 || position > list->size)
    {
        printf("Invalid position.\n");
        return;
    }

    for (int i = list->size; i > position; --i)
        list->items[i] = list->items[i - 1];

    list->items[position] = value;
    ++list->size;

    printf("Element inserted successfully.\n");
}

/* ========================================================================= */

static void delete_element(List *list)
{
    int position;

    if (list->size == 0)
    {
        printf("List is empty.\n");
        return;
    }

    if (!read_int("Enter position to delete: ", &position))
        return;

    if (position < 0 || position >= list->size)
    {
        printf("Invalid position.\n");
        return;
    }

    for (int i = position; i < list->size - 1; ++i)
        list->items[i] = list->items[i + 1];

    --list->size;

    printf("Element deleted successfully.\n");
}

/* ========================================================================= */

static void search_element(const List *list)
{
    int value;

    if (!read_int("Enter element to search: ", &value))
        return;

    for (int i = 0; i < list->size; ++i)
    {
        if (list->items[i] == value)
        {
            printf("Element found at position %d.\n", i);
            return;
        }
    }

    printf("Element not found.\n");
}

/* ========================================================================= */

static void display_list(const List *list)
{
    if (list->size == 0)
    {
        printf("List is empty.\n");
        return;
    }

    printf("List: ");

    for (int i = 0; i < list->size; ++i)
        printf("%d%s", list->items[i], i == list->size - 1 ? "\n" : " ");
}
