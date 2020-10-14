#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct lnode {
    struct lnode *next;
    struct tnode *data;
};

struct linkedlist {
    struct lnode *head;
};

struct lnode *insert(struct linkedlist *, struct tnode *);
void listprint(struct linkedlist *);

#endif
