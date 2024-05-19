#include <stdio.h>
#include <stdlib.h>


typedef struct node node;
struct node {
    int q;
    node* left;
    node * right;
};

node* newNode(int s){
    node* n = malloc(sizeof(node ));
    n->q = s; n->left = n->right = NULL;
    return n;
}
node* insert(node *n, int s){
    if(!n)
        return NULL;
    if (n->q> s)
    {
        if(!insert(n->left,s))
        {
            node *ne= newNode(s);
            n->left = ne;
        }
    }
    else {
        if(!insert(n->right, s))
        {
            node *ne= newNode(s);
            n->right = ne;
        }
    }
    return n;
}
node* successor(node* n, int o)
{
    if(!n)
        return NULL;
    if(n->q == o)
    {
        if (n->right) {
            n = n->right;
            while (n->left){
                n = n->left;
            }
            return n;
        }
        return NULL;
    }
    if(n->q>o)
    {
        node *t = successor(n->left, o);
        if (!t)
            return n;
        return t;
    }
    else
        return successor(n->right, o);
}
node* predecessor(node* n, int o)
{
    if(!n)
        return NULL;
    if(n->q == o)
    {
        if (n->left) {
            n = n->left;
            while (n->right){
                n = n->right;
            }
            return n;
        }
        return NULL;
    }
    if(n->q<o)
    {
        node *t = predecessor(n->right, o);
        if (!t)
            return n;
        return t;
    }
    else
        return predecessor(n->left, o);
}
void printTree(node* N)
{
    if(!N)
        return;
    printTree(N->left);
    printf("%d ", N->q);
    printTree(N->right);
}
int main(void){
    int a[] = {7,6,8,4,12,9,2};
    node *n = newNode(a[0]);
    for(int i = 1;i<7;i++)
    {
        insert(n, a[i]);
    }
    printTree(n);
    printf("\n%d", predecessor(n, 12)->q);
}