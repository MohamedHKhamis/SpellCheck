#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct Node Node;
struct Node{
    int h;
    int b;
    char* word;
    Node* left;
    Node* right;
};
Node* newNode(char* s){
    Node* n = malloc(sizeof(Node ));
    char* st = malloc(strlen(s)+1);
    strcpy(st, s);
    n->word = st; n->left = n->right = NULL;
    n->h =n->b = 0;
    return n;
}
Node* insert(Node *n, char *s){
    if(!n)
        return NULL;
    if (strcasecmp(n->word, s) > 0)
    {
        if(!insert(n->left,s))
        {
            Node *ne= newNode(s);
            n->left = ne;
        }
    }
    else {
        if(!insert(n->right, s))
        {
            Node *ne= newNode(s);
            n->right = ne;
        }
    }
    if(n->right && !n->left) {
        n->h = n->right->h + 1;
        n->b = -n->right->h;
    }
    else if (!n->right && n->left) {
        n->h = n->left->h + 1;
        n->b = n->left->h;
    }
    else {
        n->h = (n->left->h > n->right->h?n->left->h:n->right->h)+1;
        n->b = n->left->h - n->right->h;
    }
    return n;
}
void printTree(Node* N)
{
    if(!N)
        return;
    printTree(N->left);
    printf("%s\n", N->word);
    printTree(N->right);
}
Node* search(Node* n, char*s){
    if (!n)
        return NULL;
    if (!strcasecmp(n->word, s))
        return n;
    if (strcasecmp(n->word, s)>0)
    {
        if(!n->left)
            return n;
        return search(n->left, s);
    }
    else
    {
        if(!n->right)
            return n;
        return search(n->right, s);
    }
}
Node* successor(Node* n, char*s)
{
    if(!n)
        return NULL;
    if(!strcasecmp(n->word, s))
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
    if(strcasecmp(n->word, s)>0)
    {
        Node *t = successor(n->left, s);
        if (!t)
            return n;
        return t;
    }
    else
        return successor(n->right, s);
}
Node* predecessor(Node* n, char*s)
{
    if(!n)
        return NULL;
    if(!strcasecmp(n->word, s))
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
    if(strcasecmp(n->word, s)<0)
    {
        Node *t = predecessor(n->right, s);
        if (!t)
            return n;
        return t;
    }
    else
        return predecessor(n->left, s);
}


int main() {
    int i;
    char*d = "boars";
    char s[101];
    FILE *f = fopen("../words.txt", "r");
    fgets(s, 100, f);
    s[strlen(s)-1] = '\0';
    Node *n = newNode(s);
    for(i = 1;fgets(s, 100, f); i++){
        s[strlen(s)-1] = '\0';
        //printf("%s", s);
        insert(n, s);
    }
    //printf("%s, %s, %s\n", search(n, d)->word, successor(n, d)->word, predecessor(n, d)->word);
    //printTree(n);
    printf("%d, %d", n->h, n->b);
    fclose(f);


    return 0;
}
