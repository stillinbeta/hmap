#include <stdbool.h>
typedef struct Hashmap Hashmap;

Hashmap *hm_new();
Hashmap *hm_new_size(int);
bool hm_has_key(Hashmap *,char *);
char *hm_get(Hashmap *, char *);
bool hm_insert(Hashmap *, char *, char *);
bool hm_delete(Hashmap *, char *);
