In C (e in informatica in generale), un **binary tree** (albero binario) è una **struttura dati gerarchica** in cui **ogni nodo ha al massimo due figli**, chiamati tipicamente:

* **figlio sinistro** (*left child*)
* **figlio destro** (*right child*)

È una struttura molto usata per rappresentare dati in modo ordinato o per facilitare ricerche, inserimenti e cancellazioni efficienti (es. negli **alberi binari di ricerca**, o *binary search trees*).

---

## 1. Struttura di base in C

In C, un nodo di un binary tree si definisce generalmente così:

```c
struct Node {
    int data;                 // Dato memorizzato nel nodo
    struct Node* left;       // Puntatore al figlio sinistro
    struct Node* right;      // Puntatore al figlio destro
};
```

Ecco un esempio per creare un nuovo nodo:

```c
#include <stdlib.h>

struct Node* newNode(int value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}
```

---

## 2. Esempio di albero binario

Supponiamo di voler costruire questo albero:

```
       10
      /  \
     5    20
```

In C lo costruiresti così:

```c
struct Node* root = newNode(10);
root->left = newNode(5);
root->right = newNode(20);
```

---

## 3. Tipi comuni di binary tree

* **Albero binario completo** (*complete binary tree*): ogni livello è pieno tranne forse l’ultimo, che è riempito da sinistra a destra.
* **Albero binario perfetto**: tutti i nodi hanno due figli e tutte le foglie sono allo stesso livello.
* **Albero binario di ricerca (BST)**: per ogni nodo, i valori nel sottoalbero sinistro sono minori, quelli nel destro sono maggiori.
* **Albero bilanciato** (come AVL o Red-Black): garantisce che la profondità dell'albero resti bassa.

---

## 4. Operazioni base sugli alberi binari

* **Inserimento di un nodo**
* **Ricerca di un valore**
* **Cancellazione di un nodo**
* **Attraversamenti** (visite):

  * *In-order* (sinistra → nodo → destra)
  * *Pre-order* (nodo → sinistra → destra)
  * *Post-order* (sinistra → destra → nodo)

Esempio di inserimento:

```c
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

void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    root = insert(root, 10);
    insert(root, 5);
    insert(root, 15);

    printf("In-order: ");
    inOrder(root);  // Output: 5 10 15
    printf("\n");

    return 0;
}
```

Esempio di ricerca:

```c
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

struct Node* search(struct Node* root, int value) {
    if (root == NULL || root->data == value)
        return root;

    if (value < root->data)
        return search(root->left, value);
    else
        return search(root->right, value);
}

int main() {
    struct Node* root = NULL;
    root = insert(root, 20);
    insert(root, 10);
    insert(root, 30);

    int target = 10;
    struct Node* result = search(root, target);

    if (result)
        printf("Valore %d trovato.\n", target);
    else
        printf("Valore %d non trovato.\n", target);

    return 0;
}

```
Esempio di rimozione:

```c
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

void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    root = insert(root, 10);
    insert(root, 5);
    insert(root, 20);

    printf("Prima della cancellazione: ");
    inOrder(root);
    printf("\n");

    root = delete(root, 10);

    printf("Dopo la cancellazione: ");
    inOrder(root);
    printf("\n");

    return 0;
}
```
Esempio di attraversamentoi:

```c
// traversals_bst.c
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

void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(struct Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    struct Node* root = NULL;
    root = insert(root, 10);
    insert(root, 5);
    insert(root, 20);

    printf("In-order: ");
    inOrder(root);    // Output: 5 10 20
    printf("\n");

    printf("Pre-order: ");
    preOrder(root);   // Output: 10 5 20
    printf("\n");

    printf("Post-order: ");
    postOrder(root);  // Output: 5 20 10
    printf("\n");

    return 0;
}

```