#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2526_P1_1/ListLinked.h"  // Asegúrate de modificar esta ruta si es necesario

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
        int max;
        ListLinked<TableEntry<V>>* table;

        int h(std::string key) {
            int sum = 0;
            for (char c : key) {
                sum += static_cast<int>(c);
            }
            return sum % max;
        }

    public:
        HashTable(int size) : n(0), max(size) {
            table = new ListLinked<TableEntry<V>>[size];
        }

        ~HashTable() {
            delete[] table;
        }

        void insert(std::string key, V value) override {
            int index = h(key);
            for (auto& entry : table[index]) {
                if (entry.key == key) {
                    throw std::runtime_error("Key already exists.");
                }
            }
            table[index].push_back(TableEntry<V>(key, value));
            n++;
        }

        V search(std::string key) override {
            int index = h(key);
            for (auto& entry : table[index]) {
                if (entry.key == key) {
                    return entry.value;
                }
            }
            throw std::runtime_error("Key not found.");
        }

        V remove(std::string key) override {
            int index = h(key);
            for (auto it = table[index].begin(); it != table[index].end(); ++it) {
                if (it->key == key) {
                    V value = it->value;
                    table[index].erase(it);
                    n--;
                    return value;
                }
            }
            throw std::runtime_error("Key not found.");
        }

        int entries() override {
            return n;
        }

        int capacity() {
            return max;
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &ht) {
            for (int i = 0; i < ht.max; i++) {
                out << "Bucket " << i << ": ";
                for (const auto& entry : ht.table[i]) {
                    out << entry << " ";
                }
                out << std::endl;
            }
            return out;
        }

        V operator[](std::string key) {
            return search(key);
        }
};

#endif

