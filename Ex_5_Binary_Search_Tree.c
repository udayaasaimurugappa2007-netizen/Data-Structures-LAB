#include <stdio.h>
#include <stdlib.h>

struct BST {
    int data;
    struct BST *lchild;
    struct BST *rchild;
};

typedef struct BST *NODE;

NODE create_node(int data) {
    NODE temp = (NODE)malloc(sizeof(struct BST));

    if (temp == NULL) {
        printf("\nMemory allocation failed.\n");
        exit(1);
    }

    temp->data = data;

    temp->lchild = NULL;
    temp->rchild = NULL;

    return temp;
}

void insert(NODE root, NODE newnode);
void inorder(NODE root);
void preorder(NODE root);
void postorder(NODE root);
void search(NODE root);
void free_tree(NODE root);
int read_int(const char *prompt, int *value);

void insert(NODE root, NODE newnode) {
    /* Duplicate values are skipped. */

    if (newnode->data < root->data) {
        if (root->lchild == NULL)
            root->lchild = newnode;
        else
            insert(root->lchild, newnode);
    } else if (newnode->data > root->data) {
        if (root->rchild == NULL)
            root->rchild = newnode;
        else
            insert(root->rchild, newnode);
    } else {
        free(newnode);
    }
}

void search(NODE root) {
    int key;
    NODE cur;

    if (root == NULL) {
        printf("\nBST is empty.\n");
        return;
    }

    if (!read_int("\nEnter element to be searched: ", &key))
        return;

    cur = root;

    while (cur != NULL) {
        if (cur->data == key) {
            printf("\nKey element is present in BST.\n");
            return;
        }

        if (key < cur->data)
            cur = cur->lchild;
        else
            cur = cur->rchild;
    }

    printf("\nKey element is not found in the BST.\n");
}

void inorder(NODE root) {
    if (root != NULL) {
        inorder(root->lchild);
        printf("%d ", root->data);
        inorder(root->rchild);
    }
}

void preorder(NODE root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->lchild);
        preorder(root->rchild);
    }
}

void postorder(NODE root) {
    if (root != NULL) {
        postorder(root->lchild);
        postorder(root->rchild);
        printf("%d ", root->data);
    }
}

void free_tree(NODE root) {
    if (root != NULL) {
        free_tree(root->lchild);
        free_tree(root->rchild);
        free(root);
    }
}

int read_int(const char *prompt, int *value) {
    int result;
    int character;

    printf("%s", prompt);
    result = scanf("%d", value);

    while ((character = getchar()) != '\n' && character != EOF)
        ;

    if (result != 1) {
        printf("\nInvalid input.\n");
        return 0;
    }

    return 1;
}

int main(void) {
    int ch, i, n;
    NODE root = NULL;
    NODE new_root;
    NODE newnode;

    while (1) {
        printf("\n~~~~ BST MENU ~~~~");
        printf("\n1. Create a BST");
        printf("\n2. Display");
        printf("\n3. Search");
        printf("\n4. Exit");
        if (!read_int("\nEnter your choice: ", &ch)) {
            free_tree(root);
            return EXIT_FAILURE;
        }

        switch (ch) {
            case 1:
                if (!read_int("\nEnter the number of elements: ", &n))
                    break;

                if (n < 0) {
                    printf("\nNumber of elements cannot be negative.\n");
                    break;
                }

                new_root = NULL;

                for (i = 1; i <= n; i++) {
                    int value;

                    if (!read_int("\nEnter the value: ", &value)) {
                        free_tree(new_root);
                        new_root = NULL;
                        break;
                    }

                    newnode = create_node(value);

                    if (new_root == NULL)
                        new_root = newnode;
                    else
                        insert(new_root, newnode);
                }

                if (i > n) {
                    free_tree(root);
                    root = new_root;
                    printf("\nBST created successfully.\n");
                }
                break;

            case 2:
                if (root == NULL) {
                    printf("\nTree is not created.\n");
                } else {
                    printf("\nThe Preorder display : ");
                    preorder(root);

                    printf("\nThe Inorder display  : ");
                    inorder(root);

                    printf("\nThe Postorder display : ");
                    postorder(root);

                    printf("\n");
                }
                break;

            case 3:
                search(root);
                break;

            case 4:
                free_tree(root);
                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}
