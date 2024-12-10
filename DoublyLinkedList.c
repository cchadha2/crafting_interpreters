#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char *data;
    struct node *next;
    struct node *prev;
};

// Find a node in the list
struct node *findNode(struct node **head, char *data)
{
    if (!(*head))
        return NULL;
    else if (strcmp((*head)->data, data) == 0)
        return *head;

    struct node *next = (*head)->next;
    return findNode(&next, data);
};

// Insert a new node at the front of the list
void insertFront(struct node **newNode, struct node **head)
{
    (*newNode)->next = (*head);
    (*newNode)->prev = NULL;

    if ((*head) != NULL)
        (*head)->prev = *newNode;

    (*head) = *newNode;
};

// Insert a new node at the end of the list
void insertEnd(struct node **newNode, struct node **tail)
{
    (*newNode)->prev = (*tail);
    (*newNode)->next = NULL;

    if ((*tail) != NULL)
        (*tail)->next = *newNode;

    (*tail) = *newNode;
};

// Insert a new node anywhere in the list
void insert(struct node **newNode, struct node **head, struct node **tail, char *data)
{
    struct node *prevNode = findNode(head, data);
    if (prevNode == NULL)
        return;
    else if (prevNode->next == NULL)
    {
        insertEnd(newNode, tail);
        return;
    }
    else if (prevNode->prev == NULL)
    {
        insertFront(newNode, head);
        return;
    }

    (*newNode)->next = prevNode->next;
    (*newNode)->prev = prevNode;

    prevNode->next->prev = *newNode;

    prevNode->next = *newNode;
};

// Delete a node in the list
void deleteNode(struct node **head, struct node **tail, struct node **nodeToDelete)
{
    if ((*nodeToDelete)->prev == NULL)
    {
        (*head) = (*nodeToDelete)->next;
    }
    else
        (*nodeToDelete)->prev->next = (*nodeToDelete)->next;

    if ((*nodeToDelete)->next == NULL)
    {
        (*tail) = (*nodeToDelete)->prev;
    }
    else
        (*nodeToDelete)->next->prev = (*nodeToDelete)->prev;

    free((*nodeToDelete)->data); // Free the string data first
    free(*nodeToDelete);         // Then free the node structure itself
    *nodeToDelete = NULL;        // Set pointer to NULL to avoid dangling reference
};

void printLinkedList(struct node *current)
{
    struct node *next = current->next;
    if (next != NULL)
    {
        printf("%s", current->data);
        printf(" -> ");
        printLinkedList(next);
    }
    else
    {
        printf("%s", current->data);
        printf("\n");
    }
};

int main()
{
    struct node *head;
    struct node *tail;
    struct node *one = NULL;
    struct node *two = NULL;
    struct node *three = NULL;

    one = malloc(sizeof(struct node));
    two = malloc(sizeof(struct node));
    three = malloc(sizeof(struct node));

    one->data = malloc(strlen("hello") + 1);
    strcpy((char *)(one->data), "hello");

    two->data = malloc(strlen("how's") + 1);
    strcpy((char *)(two->data), "how's");

    three->data = malloc(strlen("things?") + 1);
    strcpy((char *)(three->data), "things?");

    one->next = two;
    two->next = three;
    three->next = NULL;

    three->prev = two;
    two->prev = one;
    one->prev = NULL;

    head = one;
    tail = three;

    struct node *newHead = NULL;
    newHead = malloc(sizeof(struct node));
    newHead->data = malloc(strlen("hey") + 1);
    strcpy((char *)(newHead->data), "hey");
    insertFront(&newHead, &head);

    printLinkedList(head);

    char *dataToFind = malloc(strlen("how's") + 1);
    strcpy(dataToFind, "how's");
    struct node *foundNode = findNode(&head, dataToFind);
    printLinkedList(foundNode);

    struct node *newTail = NULL;
    newTail = malloc(sizeof(struct node));
    newTail->data = malloc(strlen("wazzaaa") + 1);
    strcpy((char *)(newTail->data), "wazzaaa");
    insertEnd(&newTail, &tail);

    printLinkedList(head);

    struct node *newNode = NULL;
    newNode = malloc(sizeof(struct node));
    newNode->data = malloc(strlen("my man") + 1);
    strcpy((char *)(newNode->data), "my man");
    // Can be used to insert in the middle, front, or end of the list.
    // insert(&newNode, &head, two->data);
    // insert(&newNode, &head, newHead->data);
    insert(&newNode, &head, &tail, tail->data);

    printLinkedList(head);

    deleteNode(&head, &tail, &two);
    struct node *nodeToDelete = tail;
    deleteNode(&head, &tail, &nodeToDelete);
    nodeToDelete = head;
    deleteNode(&head, &tail, &nodeToDelete);

    printLinkedList(head);
};