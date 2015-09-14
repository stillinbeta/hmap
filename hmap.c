#include <stdlib.h>
#include <string.h>
#include "hmap.h"


struct Value {
    char *key;
    char *value;
    struct Value *next;
};


struct Hashmap {
    int size;
    struct Value **values;
};



#define HM_DEFAULT_BUCKET_COUNT 16

static int hash(char *key, int size) {
    int count = 0;
    for (int i = 0; i < strlen(key); i++) {
        count += (int)key[i];
    }
    return count % size;
}

static struct Value **find_value(Hashmap *h, char *key) {
    int bucket = hash(key, h->size);
    struct Value **ptr = &(h->values[bucket]);
    while ((*ptr) != NULL) {
        if (strcmp(key, (*ptr)->key) == 0) {
            return ptr;
        }
        ptr = &((*ptr)->next);
    }
    return ptr;
}
Hashmap *hm_new_size(int size) {
    struct Value **values = malloc(sizeof(struct Value *) * size);
    memset(values, 0, sizeof(struct Value *) * size);
    Hashmap *hmap = malloc(sizeof(struct Hashmap));
    hmap->values = values;
    hmap->size = size;
    return hmap;
}

Hashmap *hm_new() {
    return hm_new_size(HM_DEFAULT_BUCKET_COUNT);
}

bool hm_has_key(Hashmap * h, char * key) {
    return (hm_get(h, key) != NULL);
}

char *hm_get(Hashmap *h, char *key) {
    struct Value **ptr = find_value(h, key);
    if ((*ptr) == NULL) {
        return NULL;
    } else {
        return (*ptr)->value;
    }
}

bool hm_insert(Hashmap *h, char *key, char *value) {
    struct Value **ptr = find_value(h, key);
    if ((*ptr) == NULL) {
        struct Value *newval = malloc(sizeof(struct Value));
        newval->key = strdup(key);
        newval->value = strdup(value);
        *ptr = newval;
        return true;
    } else {
        return false;
    }
}

bool hm_delete(Hashmap *h, char *key) {
    struct Value *temp;
    struct Value **ptr = find_value(h, key);
    if ((*ptr) == NULL) {
        return false;
    } else {
        temp = (*ptr);
        (*ptr) = (*ptr) -> next;
        free(temp);
        return true;
    }
}
