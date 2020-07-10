/* Exercise 6-3. Write a cross-referencer that prints a list of all words in a document, and, for each word,
 *  a list of the line numbers on which line numbers it occurs. Remove noise words like "the", "and" and so on */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD  100
#define MAXWORDS 1000
#define MAXPOS   1000
#define BUFSIZE  100000 /* enough room to store the entire program */ 
#define OUT      0
#define IN       1

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
void preproccess(void);

struct tnode {
    char *word;
    int positions[MAXPOS];
    int positions_pos; /* position in the array */
    struct tnode *left;
    struct tnode *right;
};

int line = 1;

/* word frequency count */
int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    preproccess();

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0])) root = addtree(root, word);
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *strdup(char *);

/* add_local: add position onto end of array */
void add_loc(struct tnode *p) {

    /* if the word has already appeared on the line, the line number will be the last appended item */
    if (p->positions[p->positions_pos - 1] != line) {
        p->positions[p->positions_pos++] = line;
    }
}

void printstr(char *str) {
    char c;
    int i = 0, linenum = 1;

    while ((c = str[i++]) != '\0') {
        if (c == '\n') printf("| line %d", linenum++);

        printf("%c", c);
    }
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {  /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = strdup(w);
        p->positions[0] = line;
        p->positions_pos = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        add_loc(p); /* add current location for word */
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
    int i;

    if (p != NULL) {
        treeprint(p->left);
        printf("%s\n{ ", p->word);
        for (i = 0; i < p->positions_pos; i++) {
            if (i < p->positions_pos - 1)
                printf("%d, ", p->positions[i]);
            else
                printf("%d }\n", p->positions[i]);
        }
        treeprint(p->right);
    }
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
            if (k == '*' && comment) {
                comment = OUT;
                continue;
            }
            break;
        case '*':
            if (k == '/' && !comment) {
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
            else if (k != '\'')
                string = IN;
            break;
        case '\n':
            pre = OUT;
            break;
        default:
            break;
        }

        if (!comment && !string && !pre)
            *p++ = c;
        else if (c == '\n')
            *p++ = c;

        k = c;
    }

    *p = '\0';
    ungets(buf);
    printstr(buf);
}

/* getword: get next word or charactter from input */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        if (c == '\n') line++;

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
