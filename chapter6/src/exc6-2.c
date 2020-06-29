/* Exercise 6-2. Write a program that reads a C program and prints
 * in alphabetical order each group of variable names that are identical
 * in the first 6 characters, but diffrent somewhere after. Don;t count
 * words within strings and comments. Make 6 a parameteter that can be set
 * from the command line */

/* Exercise 6-1. Our version of getword does not properly handle underscores,
 * string constants, comments, or preprocessor control lines. Write a better version */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD  100
#define MAXWORDS 1000
#define BUFSIZE  100000 /* enough room to store the entire program */
#define OUT      0
#define IN       1

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
void preproccess(void);

struct tnode {
    char *words[MAXWORDS];
    int count;
    struct tnode *left;
    struct tnode *right;
};

int n = 6; /* characters to be identical */

/* word frequency count */
int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];

    if (argc > 1) n = atoi(*(++argv));

    root = NULL;
    preproccess();

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) root = addtree(root, word);
    }
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *strdup(char *);
void add_word(struct tnode *, char *);
void print_words(char **, int);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {  /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->words[0] = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strncmp(w, p->words[0], n)) == 0)
        add_word(p, w);
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

/* add_word: adds word to end of word array if not already present */
void add_word(struct tnode *p, char *s) {
    int i;

    for (i = 0; i < p->count; i++)
        if (strcmp(p->words[i], s) == 0) return;

    p->words[p->count++] = strdup(s);
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
    char *s;

    if (p != NULL) {
        treeprint(p->left);
        s = malloc(n + 1);
        strncpy(s, p->words[0], n);
        printf("root = %s{\n", s);
        print_words(p->words, p->count); 
        printf("}\n"); 
        treeprint(p->right);
    }
}

/* compare: wraps strcmp for use with qsort */ 
int compare(const void *s, const void *s2) { return strcmp(*(char *const *)s, *(char *const *)s2); }

/* print_words: print the contents of words alphabetically */
void print_words(char **words, int count) {
    int i;

    qsort(words, count, sizeof(words), compare); 
    for (i = 0; i < count; i++) printf("%s\n", words[i]);
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

void ungetch(int);
int getch(void);
void ungets(char[]);

/* val_word_char: returns 1 if character is valid for a word, 0 if not */
int val_word_char(char c) { return (c == '_' || isalnum(c)); }

/* preproccess: filter the input stream, pushing each char back onto buf */
void preproccess(void) {
    int c, k, comment, string, pre;
    char buf[BUFSIZE];
    char *p = buf;

    k = 0;
    comment = string = pre = OUT;
    while ((c = getch()) != EOF) {
        switch (c) {
        case '/':
            if (k == '*') {
                comment = OUT;
                continue;
            }
            break;
        case '*':
            if (k == '/') {
                comment = IN;
                p--;
            }
            break;
        case '#':
            pre = IN;
            break;
        case '"':
            if (string)
                string = OUT;
            else
                string = IN;
        case '\n':
            string = OUT;
            pre = OUT;
            break;
        default:
            break;
        }

        if (!comment && !string && !pre) *(p++) = c;
        k = c;
    }

    *p = '\0';
    ungets(buf);
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
        if (!val_word_char(*w = getch())) {
            ungetch(*w);
            break;
        }

    *w = '\0';
    return word[0];
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

/* pushes an entire string back onto input */
void ungets(char s[]) {
    int i;

    i = strlen(s);
    while (i-- >= 0) ungetch(s[i]);
}
