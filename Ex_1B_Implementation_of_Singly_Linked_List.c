/*
===============================================================================
                     DATA STRUCTURES LABORATORY
===============================================================================

Experiment : 1.B
Title      : Implementation of Singly Linked List
Language   : C
Standard   : C11

Operations:
    1. Insert at Beginning
    2. Insert at End
    3. Delete by Position
    4. Search Element
    5. Display List

Complexity:
    Insert at Beginning : O(1)
    Insert at End       : O(n)
    Delete by Position  : O(n)
    Search              : O(n)
    Display             : O(n)
    Space               : O(n)

===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

/* Function Prototypes */
static Node *create_node(int data);
static void insert_beginning(Node **head, int data);
static void insert_end(Node **head, int data);
static void delete_position(Node **head, int position);
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
    int position;

    while (1)
    {
        printf("\n========================================\n");
        printf("        SINGLY LINKED LIST\n");
        printf("========================================\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Delete by Position\n");
        printf("4. Search Element\n");
        printf("5. Display List\n");
        printf("6. Exit\n");
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
                insert_beginning(&head, data);
                break;

            case 2:
                if (!read_int("Enter data: ", &data))
                    break;
                insert_end(&head, data);
                break;

            case 3:
                if (!read_int("Enter position (0-based): ", &position))
                    break;
                delete_position(&head, position);
                break;

            case 4:
                if (!read_int("Enter element to search: ", &data))
                    break;
                search_element(head, data);
                break;

            case 5:
                display_list(head);
                break;

            case 6:
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

static void insert_beginning(Node **head, int data)
{
    Node *new_node = create_node(data);

    new_node->next = *head;
    *head = new_node;

    printf("Element inserted successfully.\n");
}

/* ========================================================================= */

static void insert_end(Node **head, int data)
{
    Node *new_node = create_node(data);

    if (*head == NULL)
    {
        *head = new_node;
        printf("Element inserted successfully.\n");
        return;
    }

    Node *current = *head;

    while (current->next != NULL)
        current = current->next;

    current->next = new_node;

    printf("Element inserted successfully.\n");
}

/* ========================================================================= */

static void delete_position(Node **head, int position)
{
    if (*head == NULL || position < 0)
    {
        printf("Invalid position or empty list.\n");
        return;
    }

    if (position == 0)
    {
        Node *temp = *head;
        *head = temp->next;
        free(temp);

        printf("Element deleted successfully.\n");
        return;
    }

    Node *current = *head;

    for (int i = 0; current != NULL && i < position - 1; ++i)
        current = current->next;

    if (current == NULL || current->next == NULL)
    {
        printf("Invalid position.\n");
        return;
    }

    Node *temp = current->next;
    current->next = temp->next;
    free(temp);

    printf("Element deleted successfully.\n");
}

/* ========================================================================= */

static void search_element(const Node *head, int data)
{
    int position = 0;

    for (const Node *current = head; current != NULL; current = current->next)
    {
        if (current->data == data)
        {
            printf("Element found at position %d.\n", position);
            return;
        }

        ++position;
    }

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

    printf("List: ");

    for (const Node *current = head; current != NULL; current = current->next)
        printf("%d -> ", current->data);

    printf("NULL\n");
}

/* ========================================================================= */

static void free_list(Node **head)
{
    while (*head != NULL)
    {
        Node *temp = *head;
        *head = temp->next;
        free(temp);
    }
}
