#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct lnode *lalloc(void);

struct lnode *insert(struct linkedlist *list, struct tnode *data) {
    struct lnode *p, *l, *temp;

    if (list->head != NULL) {
        p = list->head;
        while (p->next != NULL && strcmp(data->word, p->next->data->word) > 0) {
            p = p->next;
        }

        l = p->next;
        p->next = lalloc();
        p->next->data = data;
        p->next->next = l;
    } else {
        p = list->head = lalloc();
        p->data = data;
        p->next = NULL;
    }
}

void listprint(struct linkedlist *list) {
    struct lnode *p;

    p = list->head;
    while (p != NULL) {
        printf("word => %s\n", p->data->word);
        printf("count => %d\n\n", p->data->count);
        p = p->next;
    }
}

struct lnode *lalloc(void) {
    struct lnode *temp;
    temp = (struct lnode *)malloc(sizeof(struct lnode));

    return temp;
}

struct linkedlist *new_list() {
    return (struct linkedlist *)malloc(sizeof(struct linkedlist));
}
