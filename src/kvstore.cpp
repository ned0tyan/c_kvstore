#include "kvstore.hpp"

KeyValueStore::KeyValueStore(size_t initial_capacity) {
    this->_store = kv_create(initial_capacity);

    if (this->_store == nullptr) {
        throw std::runtime_error("Failed to allocate KVStore");
    }
}

KeyValueStore::~KeyValueStore() {
    kv_free(this->_store);
}

bool KeyValueStore::put(std::string_view key, std::string_view value) {
    return kv_put(this->_store, key.data(), value.data()) == 1;
}

std::optional<std::string> KeyValueStore::get(std::string_view key) const {
    const char* result = kv_get(this->_store, key.data());
    
    if (result == nullptr) 
        return std::nullopt;
    
    return std::string(result);
}