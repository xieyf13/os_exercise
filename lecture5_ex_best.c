#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#define MAX_PAGE (10000)

char mem[MAX_PAGE];

struct Page {
    int property;
    int head;
    struct Page *prev;
    struct Page *next;
};

struct Page *full_list;
struct Page *free_list;

void list_add(struct Page* p, struct Page *n) {
    n->next = p->next;
    n->prev = p;
    p->next->prev = n;
    p->next = n;
    return ;
}

struct Page *list_del(struct Page* n) {
    assert (n->next->prev == n);
    assert (n->prev->next == n);
    n->next->prev = n->prev;
    n->prev->next = n->next;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

int list_merge(struct Page *h, struct Page *p) {
    struct Page *iter = h->next;
    struct Page *be_delete = NULL;
    int is_merge = 0;
    while (iter != h) {
        if (p->head + p->property == iter->head) {
            be_delete = iter;
            p->property += iter->property;
            iter = iter->next;
            list_del(be_delete);
            free(be_delete);
            is_merge = 1;
        } else if (p->head == iter->head + iter->property) {
            be_delete = iter;
            p->head = iter->head;
            p->property += iter->property;
            iter = iter->next;
            list_del(be_delete);
            free(be_delete);
            is_merge = 1;
        } else {
            iter = iter->next;
        }
    }
    return is_merge;
}

int my_malloc(int n) {
    struct Page *p = free_list->next;
    assert (p != NULL);
    struct Page *res = NULL;
    while (p != free_list) {
        if ((res == NULL || p->property < res->property) && p->property >= n) {
            res = p;
        }
        p = p->next;
    }
    if (res) {
        int addr = res->head;
        struct Page *p2 = (struct Page*)malloc(sizeof(struct Page*));
        p2->head = res->head;
        p2->property = n;
        list_add(full_list, p2);
        if (res->property > n) {
            res->head += n;
            res->property -= n;
            // list_merge(full_list, p2);
        } else {
            list_del(res);
            free(res);
        }
        return addr;
    } else {
        // printf("not enough space for request\n");
        return -1;
    }
}

int my_free(int addr) {
    assert(addr >= 0 && addr < MAX_PAGE);
    struct Page* iter = full_list->next;
    while (iter != full_list) {
        // printf("iter's head is %d addr is %d\n", iter->head, addr);
        if (iter->head == addr) {
            list_add(free_list, list_del(iter));
            list_merge(free_list, iter);
            return 1;
        }
        iter = iter->next;
    }
    return 0;
}

void page_init(){
    free_list->prev = free_list;
    free_list->next = free_list;
    full_list->next = full_list;
    full_list->prev = full_list;
    struct Page *p = (struct Page *)malloc(sizeof(struct Page*));
    p->property = MAX_PAGE;
    p->head = 0;
    list_add(free_list, p);
}


void check() {
    int p1 = my_malloc(1000);
    assert(p1 == 0);
    int p2 = my_malloc(3000);
    assert(p2 == 1000);
    int p3 = my_malloc(1000);
    assert(p3 == 4000);
    int p4 = my_malloc(5000);
    assert(p4 == 5000);
    int p5 = my_malloc(1);
    assert(p5 == -1);
    assert(my_free(p2));
    assert(my_free(p4));
    int p6 = my_malloc(1000);
    assert(p6 == p2);
    assert(my_free(p3));
    assert(my_free(p6));
    int p7 = my_malloc(9000);
    assert(p7 == 1000);
    return ;
}

int main() {
    free_list = (struct Page*)malloc(sizeof(struct Page*));
    full_list = (struct Page*)malloc(sizeof(struct Page*));
    memset(mem, 0, sizeof(mem));
    page_init();
    check();
    printf("OK\n");
    free(free_list);
    free(full_list);
    return 0;
}