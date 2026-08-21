#ifndef KVSTORE_HPP
#define KVSTORE_HPP

#include <string>
#include <string_view>
#include <optional>

extern "C" {
    #include "kvstore.h"
}

class KeyValueStore {
public:
    explicit KeyValueStore(size_t initial_capacity = 4);
    ~KeyValueStore();

    KeyValueStore(const KeyValueStore&) = delete;
    KeyValueStore& operator=(const KeyValueStore&) = delete;

    bool put(std::string_view key, std::string_view value);

    std::optional<std::string> get(std::string_view key) const;

private:
    KVStore* _store { nullptr };
};

#endif //KVSTORE_HPP