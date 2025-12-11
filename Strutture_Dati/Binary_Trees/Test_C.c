#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node* insert(struct Node* root, int value) {
    if (root == NULL)
        return newNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

struct Node* findMin(struct Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

struct Node* delete(struct Node* root, int value) {
    if (root == NULL)
        return NULL;

    if (value < root->data)
        root->left = delete(root->left, value);
    else if (value > root->data)
        root->right = delete(root->right, value);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

void inOrder(struct Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void preOrder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(struct Node *root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}
void printTree (struct Node *root) {
    printf("\nInOrder: ");
    inOrder(root);
    printf("\nPreOrder: ");
    preOrder(root);
    printf("\nPostOrder: ");
    postOrder(root);
    printf("\n");
}
int main() {
    struct Node* root = NULL;

    // Inserimento di più nodi per creare un albero più grande
    int values[] = {15, 10, 20, 8, 12, 17, 25, 6, 11, 16, 27};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }

    printTree(root);

    // Inserimento di un nuovo nodo
    printf("\nInserisco 13:\n");
    root = insert(root, 13);
    printTree(root);

    // Cancellazione di un nodo foglia
    printf("\nCancello 6 (foglia):\n");
    root = delete(root, 6);
    printTree(root);

    // Cancellazione di un nodo con un solo figlio
    printf("\nCancello 25 (un solo figlio):\n");
    root = delete(root, 25);
    printTree(root);

    // Cancellazione di un nodo con due figli
    printf("\nCancello 10 (due figli):\n");
    root = delete(root, 10);
    printTree(root);
    return 0;
}