#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 10

char in[MAXN], post[MAXN];

typedef struct node {
    char val;
    struct node *left, *right;
} Node;

Node *create_node(char c) 
{
    Node *node = (Node *) malloc(sizeof(Node));
    if (!node) exit(1);
    node->val = c;
    node->left = node->right = NULL;
    return node;
}

Node *rebuild(int il, int ir, int pl, int pr) 
{
    if (pl > pr || il > ir) return NULL;
    char rc = post[pr];
    int pos = strchr(in, rc) - in;
    Node *root = create_node(rc);
    root->left = rebuild(il, pos - 1, pl, pos - il + pl - 1);
    root->right = rebuild(pos + 1, ir, pos - il + pl, pr - 1);
    return root;
}

void print_tree(Node *root) 
{
    if (!root) return;
    printf("%c", root->val);
    print_tree(root->left);
    print_tree(root->right);
}

int main() 
{
    scanf(" %s %s", in, post);
    int n = strlen(in);
    Node *root = rebuild(0, n - 1, 0, n - 1);
    print_tree(root);
    return 0;
}