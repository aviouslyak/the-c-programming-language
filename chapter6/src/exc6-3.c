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
int not_in(char **, int, char *);

struct tnode {
    char *word;
    int positions[MAXPOS];
    int positions_pos; /* position in the array */
    struct tnode *left;
    struct tnode *right;
};

char *COMMON_WORDS[] = {"the", "a", "i"};
int length = 3;

int line = 1;

/* word frequency count */
int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && not_in(COMMON_WORDS, length, word)) root = addtree(root, word);
    treeprint(root);
    return 0;
}

char *string_to_lower(char *s) {
    int i;

    for (i = 0; (s[i] = tolower(s[i])) != '\0'; i++)
        ;

    return s;
}

/* returns true if s not in strings, false otherwise */
int not_in(char *strings[], int len, char *s) {
    int i;
    char p[MAXWORD];

    strcpy(p, s);
    string_to_lower(p);

    for (i = 0; i < len; i++)
        if (strcmp(strings[i], p) == 0) 
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

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {  /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = strdup(w);
        p->positions[0] = line;
        p->positions_pos = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, string_to_lower(p->word))) == 0)
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
