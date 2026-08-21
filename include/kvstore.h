#ifndef KVSTORE_H
#define KVSTORE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* key;
    char* value;
} KVPair;

typedef struct {
    KVPair* pairs;
    size_t count;
    size_t capacity;
} KVStore;

KVStore* kv_create(size_t initial_capacity); 

const char* kv_get(KVStore *store, const char *key);

int kv_put(KVStore *store, const char *key, const char *value);

void kv_free(KVStore *store);

#ifdef __cplusplus
}
#endif

#endif // KVSTORE_H