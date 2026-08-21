#include <iostream>
#include "kvstore.hpp"

int main() {
    try {
        // 1. Создаем C++ хранилище с начальной емкостью 2
        KeyValueStore store(2);
        std::cout << "KeyValueStore successfully initialized!\n\n";

        // 2. Вставляем несколько значений (проверим авто-расширение realloc)
        store.put("language", "C++");
        store.put("version", "17");
        store.put("author", "Alex");

        // 3. Чтение существующих ключей
        if (auto lang = store.get("language")) {
            std::cout << "language: " << *lang << "\n";
        }

        if (auto ver = store.get("version")) {
            std::cout << "version: " << *ver << "\n";
        }

        // 4. Обновление значения
        store.put("version", "20");
        if (auto ver = store.get("version")) {
            std::cout << "updated version: " << *ver << "\n";
        }

        // 5. Запрос несуществующего ключа
        auto missing = store.get("non_existent_key");
        if (!missing.has_value()) {
            std::cout << "non_existent_key: NOT FOUND (as expected)\n";
        }

        std::cout << "\nAll operations completed successfully!\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    // При выходе из main срабатывает деструктор KeyValueStore,
    // который безопасно вызывает kv_free без утечек памяти!
    return 0;
}