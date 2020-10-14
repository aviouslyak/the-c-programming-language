/* Exercise 6-4. Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurence.
 * Precede each word by its count */

#include "linkedlist.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 1000
struct tnode *addtree(struct tnode *, char *);
void fill_list(struct tnode *, struct linkedlist *);
int getword(char *, int);

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

/* word frequency count */
int main() {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    struct linkedlist l; 
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0])) root = addtree(root, word);
    fill_list(root, &l);
    listprint(&l);  
    return 0;
}

struct tnode *talloc(void);
char *strdup(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {  /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

/* fill_list: insert items from tree into list*/
void fill_list(struct tnode *p, struct linkedlist *l) {
    if (p != NULL) {
        fill_list(p->left, l);
        insert(l, p);
        fill_list(p->right, l);
    }
}

/* getword: get next word or charactter from input */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF) *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }

    *w = '\0';
    return word[0];
}

/*talloc: make a tnode */
struct tnode *talloc(void) {
    return (struct tnode *)malloc(sizeof(struct tnode));
}

/* strdup: make a duplicate of s */
char *strdup(char *s) {
    char *p;

    p = (char *)malloc(strlen(s) + 1); /* plus one for '\0' */
    if (p != NULL) strcpy(p, s);
    return p;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
