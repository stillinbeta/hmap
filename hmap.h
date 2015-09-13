#include <stdbool.h>
/*typedef struct {
    *char key;
    *char value;
} Value;

typedef bucket {
    Value[] values;
}


typedef struct {
    int size;
    char[][][] map;
} Hashmap */

typedef struct {
} Hashmap;

Hashmap *hm_new();
Hashmap *hm_new_size(int);
bool hm_has_key(Hashmap *,char *);
char *hm_get(Hashmap *, char *);
bool hm_insert(Hashmap *, char *, char *);
bool hm_delete(Hashmap *, char *);
