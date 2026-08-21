#include <kvstore.h>
#include <stdlib.h>
#include <string.h>

KVStore* kv_create(size_t initial_capacity) {
    KVStore *store = (KVStore*) malloc(sizeof(KVStore));
    if (store == NULL){
        return NULL;
    }

    store->pairs = (KVPair*) malloc(initial_capacity * sizeof(KVPair));

    if (store->pairs == NULL){
        free(store);
        return NULL;
    }

    store->capacity = initial_capacity;
    store->count = 0;

    return store;
}

const char* kv_get(KVStore *store, const char *key) {
    if (store == NULL || key == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < store->count; i++) {
        if (strcmp(store->pairs[i].key, key) == 0) {
            return store->pairs[i].value;
        }
    }

    return NULL;
}

int kv_put(KVStore *store, const char *key, const char *value){
    if (store == NULL || key == NULL || value == NULL){
        return 0;
    }

    for(size_t i = 0; i < store->count; i++){
        if (strcmp(store->pairs[i].key, key) == 0){
            char *new_value = strdup(value);
            if (new_value == NULL){
                return 0;
            }

            free(store->pairs[i].value);
            store->pairs[i].value = new_value;
            return 1;
        }
    }

    if (store->count == store->capacity){
        size_t new_capacity = store->capacity * 2;
        KVPair *new_pairs = (KVPair*) realloc(store->pairs, sizeof(KVPair) * new_capacity);

        if (new_pairs == NULL){
            return 0;
        }

        store->pairs = new_pairs;
        store->capacity = new_capacity;
    }

    char *new_key = strdup(key);
    char *new_value = strdup(value);

    if (new_key == NULL || new_value == NULL) {
        free(new_key); // В Си free(NULL) безопасен
        free(new_value);
        return 0;
    }

    store->pairs[store->count].key = new_key;
    store->pairs[store->count].value = new_value;
    store->count++;

    return 1;
}

void kv_free(KVStore *store) {
    if (store == NULL) {
        return;
    }

    for (size_t i = 0; i < store->count; i++) {
        free(store->pairs[i].key);
        free(store->pairs[i].value);
    }

    free(store->pairs);
    free(store);
}