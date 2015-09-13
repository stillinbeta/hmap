#include <stdlib.h>
#include "hmap.h"

#define HM_DEFAULT_BUCKET_COUNT 16

Hashmap *hm_new_size(int size) {
    return (Hashmap *)malloc(sizeof(Hashmap));
}

Hashmap *hm_new() {
    return hm_new_size(HM_DEFAULT_BUCKET_COUNT);
}

bool hm_has_key(Hashmap * h, char * key) {
    return (hm_get(h, key) != NULL);
}
char *hm_get(Hashmap *h, char *key) {
    return NULL;
}
bool hm_insert(Hashmap *h, char *key, char *value) {
    return false;
}
bool hm_delete(Hashmap *h, char *key) {
    return false;
}
