/*
===============================================================================
                     DATA STRUCTURES LABORATORY
===============================================================================

Experiment : 2
Title      : Implementation of Circular Linked List
Language   : C
Standard   : C11

Operations:
    1. Insert at End
    2. Delete by Value
    3. Search Element
    4. Display List

Complexity:
    Insert at End : O(n)
    Delete        : O(n)
    Search        : O(n)
    Display       : O(n)
    Space         : O(n)

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
static void insert_end(Node **head, int data);
static void delete_value(Node **head, int data);
static void search_element(const Node *head, int data);
static void display_list(const Node *head);
static void free_list(Node **head);
static int read_int(const char *prompt, int *value);

/* ========================================================================= */

int main(void)
{
    Node *head = NULL;
    int choice;
    int data;

    while (1)
    {
        printf("\n========================================\n");
        printf("        CIRCULAR LINKED LIST\n");
        printf("========================================\n");
        printf("1. Insert at End\n");
        printf("2. Delete by Value\n");
        printf("3. Search Element\n");
        printf("4. Display List\n");
        printf("5. Exit\n");
        printf("----------------------------------------\n");
        if (!read_int("Enter your choice: ", &choice))
        {
            free_list(&head);
            return EXIT_FAILURE;
        }

        switch (choice)
        {
            case 1:
                if (!read_int("Enter data: ", &data))
                    break;
                insert_end(&head, data);
                break;

            case 2:
                if (!read_int("Enter value to delete: ", &data))
                    break;
                delete_value(&head, data);
                break;

            case 3:
                if (!read_int("Enter element to search: ", &data))
                    break;
                search_element(head, data);
                break;

            case 4:
                display_list(head);
                break;

            case 5:
                free_list(&head);
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

static void insert_end(Node **head, int data)
{
    Node *new_node = create_node(data);

    if (*head == NULL)
    {
        *head = new_node;
        new_node->next = new_node;

        printf("Element inserted successfully.\n");
        return;
    }

    Node *tail = *head;

    while (tail->next != *head)
        tail = tail->next;

    new_node->next = *head;
    tail->next = new_node;

    printf("Element inserted successfully.\n");
}

/* ========================================================================= */

static void delete_value(Node **head, int data)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    Node *current = *head;
    Node *previous = NULL;

    do
    {
        if (current->data == data)
        {
            if (current == *head)
            {
                if (current->next == current)
                {
                    *head = NULL;
                }
                else
                {
                    Node *tail = current;

                    while (tail->next != *head)
                        tail = tail->next;

                    *head = current->next;
                    tail->next = *head;
                }
            }
            else
            {
                previous->next = current->next;
            }

            free(current);
            printf("Element deleted successfully.\n");
            return;
        }

        previous = current;
        current = current->next;

    } while (current != *head);

    printf("Element not found.\n");
}

/* ========================================================================= */

static void search_element(const Node *head, int data)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    int position = 0;
    const Node *current = head;

    do
    {
        if (current->data == data)
        {
            printf("Element found at position %d.\n", position);
            return;
        }

        ++position;
        current = current->next;

    } while (current != head);

    printf("Element not found.\n");
}

/* ========================================================================= */

static void display_list(const Node *head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    printf("Circular List: ");

    const Node *current = head;

    do
    {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != head);

    printf("(HEAD)\n");
}

/* ========================================================================= */

static void free_list(Node **head)
{
    if (*head == NULL)
        return;

    Node *current = (*head)->next;

    while (current != *head)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }

    free(*head);
    *head = NULL;
}
