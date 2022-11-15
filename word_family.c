#include <stdio.h>
#include <stdlib.h>
#include "word_family.h"
#include "generic.h"
#include "my_string.h"

// Create Node
struct node;
typedef struct node Node;
struct node
{
    MY_STRING key;
    GENERIC_VECTOR data;
    Node *left;
    Node *right;
    int height;
};

struct word_family;
typedef struct word_family Word_family;
struct word_family {
    Node* root;
};

int height(Node* node);
int max(int a, int b);
Node *newNode(MY_STRING key);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
int getBalance(Node *node);
Node *insertWord(Node *node, MY_STRING word, MY_STRING key);
void destroy_tree(Node* node);
Node* get_largest_family(Node* node);

WORD_FAMILY word_family_init_vector(GENERIC_VECTOR pVector, MY_STRING guessed_letters) {
    Word_family* word_family = (Word_family*) malloc(sizeof(Word_family));
    word_family->root = NULL;
    MY_STRING word = NULL;
    MY_STRING key = NULL;
    for(int i = 0; i < generic_vector_get_size(pVector); i++) {
        word = *generic_vector_at(pVector, i);
        word_family_get_word_key(&key, word, guessed_letters);
        word_family->root = insertWord(word_family->root, word, key);
    }
    my_string_destroy(&key);
    return word_family;
}

GENERIC_VECTOR word_family_get_largest_family(WORD_FAMILY pWord_family) {
    Word_family* word_family = (Word_family*) pWord_family;
    return get_largest_family(word_family->root)->data;
}

MY_STRING word_family_get_largest_family_key(WORD_FAMILY pWord_family) {
    Word_family* word_family = (Word_family*) pWord_family;
    return get_largest_family(word_family->root)->key;
}

void word_family_destroy(WORD_FAMILY* pHWord_family) {
    Word_family* word_family = (Word_family*) *pHWord_family;
    if(word_family == NULL)
        return;
    destroy_tree(word_family->root);
    free(word_family);
    *pHWord_family = NULL;
}

// Calculate height
int height(Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Create a node
Node *newNode(MY_STRING key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = NULL;
    my_string_assignment((Item *)&node->key, key);
    node->data = generic_vector_init_default(my_string_assignment, my_string_destroy);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotate
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get the balance factor
int getBalance(Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Insert node
Node *insertWord(Node *node, MY_STRING word, MY_STRING key)
{
    // Find the correct position to insertWord the node and insertWord it
    if (node == NULL) {
        Node* new_node = newNode(key);
        generic_vector_push_back(new_node->data, (Item) word);
        return new_node;
    }

    int comparisson = my_string_compare(key, node->key);
    if (comparisson < 0)
        node->left = insertWord(node->left, word, key);
    else if (comparisson > 0)
        node->right = insertWord(node->right, word, key);
    else {
        generic_vector_push_back(node->data, (Item) word);
        return node;
    }

    // Update the balance factor of each node and
    // Balance the tree
    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && my_string_compare(key, node->left->key) < 0)
        return rightRotate(node);

    if (balance < -1 && my_string_compare(key, node->right->key) > 0)
        return leftRotate(node);

    if (balance > 1 && my_string_compare(key, node->left->key) > 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && my_string_compare(key, node->right->key) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void destroy_tree(Node* node) {
    if(node->left != NULL)
        destroy_tree(node->left);
    if(node->right != NULL)
        destroy_tree(node->right);
    generic_vector_destroy(&node->data);
    my_string_destroy(&node->key);
    free(node);
}

Node* get_largest_family(Node* node) {
    if(node->left == NULL && node->right == NULL)
        return node;

    Node* largest = node;
    Node* tempNode;
    int largestSize = generic_vector_get_size(largest->data);
    int tempSize;
    if(node->left != NULL) {
        tempNode = get_largest_family(node->left);
        tempSize = generic_vector_get_size(tempNode->data);
        if(tempSize > largestSize) {
            largest = tempNode;
            largestSize = tempSize;
        }
    }
    if(node->right != NULL) {
        tempNode = get_largest_family(node->right);
        tempSize = generic_vector_get_size(tempNode->data);
        if(tempSize > largestSize) {
            largest = tempNode;
            largestSize = tempSize;
        }
    }
    return largest;
}

void word_family_get_word_key(MY_STRING* pKey, MY_STRING word, MY_STRING guessedLetters) {
    my_string_assignment((Item*) pKey, (Item) word);
    char c;
    for(int i = 0; i < my_string_get_size(*pKey); i++) {
        c = *my_string_at(*pKey, i);
        if(!my_string_contains_letter(guessedLetters, c))
            *my_string_at(*pKey, i) = '-';
    }
}
