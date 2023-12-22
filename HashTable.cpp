#include "HashTable.h"
#include <string>
#include <iostream>

using namespace std;

string HashTable::find_key(long long int key) const {
    BLinearAddress bla(find_largest_prime(size));
    int attempts = 0, base_address;
    int address = hash_function(key);
    base_address = address;
    int max_attempts = size;
    while ((table[address].occupied || table[address].deleted) && attempts < max_attempts) {
        if (table[address].key == key) {
            return table[address].value;
        }
        attempts++;
        address = bla.get_address(key, base_address, attempts, size) % size;
        if (address < 0) {
            address *= -1;
        }
    }
    unsuccessful_steps += attempts;
    search_count++;
    cout << "Key not found!" << endl;
    return "0";
}

bool HashTable::delete_key(long long int key) {
    BLinearAddress bla(find_largest_prime(size));
    int attempts = 0, base_address;
    int address = hash_function(key);
    base_address = address;
    int max_attempts = size;

    while ((table[address].occupied || table[address].deleted) && attempts < max_attempts) {
        if (table[address].key == key && table[address].occupied) {
            table[address].deleted = true;
            key_count--;
            return true;
        }
        attempts++;
        address = bla.get_address(key, base_address, attempts, size) % size;
        if (address < 0) {
            address *= -1;
        }
    }

    cout << "Key not found!" << endl;
    return false;
}

bool HashTable::insert_key(const HashTable::Node &node, const string &value) {
    BLinearAddress bla(find_largest_prime(size));
    int attempts = 1, base_address;
    if (key_count >= size) {
        cout << "Table is full!" << endl;
        return false;
    }
    int address = hash_function(node.key);
    base_address = address;

    while (table[address].occupied) {
        if (table[address].key == node.key and table[address].value == node.value) {
            cout << "Node is already in table!" << endl;
            return false;
        }
        attempts++;
        address = bla.get_address(node.key, base_address, attempts, size) % size;
        if (address < 0) {
            address *= -1;
        }
    }
    successful_steps += attempts;
    table[address].key = node.key;
    table[address].value = value;
    table[address].occupied = true;
    key_count++;
    return true;
}

double HashTable::avg_access_successful() const {
    return (successful_steps * 1.0) / (get_key_count() * 1.0);
}

double HashTable::avg_access_unsuccessful() {
    return (unsuccessful_steps * 1.0) / (search_count * 1.0);
}

void HashTable::reset_statistics() {
    successful_steps = 0, unsuccessful_steps = 0, search_count = 0;
}

void HashTable::clear() {
    for (int i = 0; i < get_table_size(); i++) {
        table[i].key = 0;
        table[i].value = "";
        table[i].deleted = false;
        table[i].occupied = false;
    }
    key_count = 0;
}

double HashTable::fill_ratio() const {
    return (key_count * 1.0) / (size * 1.0);
}

bool HashTable::is_prime(int number) {
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int HashTable::find_largest_prime(int value) {
    for (int i = value - 1; i >= 2; --i) {
        if (is_prime(i)) {
            return i;
        }
    }
    return 0;
}


int HashTable::hash_function(long long int key) const {
    return key % find_largest_prime(size);
}

ostream &operator<<(ostream &os, const HashTable &Table) {
    for (int i = 0; i < Table.get_table_size(); i++) {
        if (!Table.table[i].occupied) {
            os << "EMPTY" << endl;
        } else {
            os << Table.table[i].value << endl;
        }
    }
    return os;
}

bool HashTable::check_stats(double successful_steps_limit, double unsuccessful_steps_limit, double fill_ratio_limit) {
    if (avg_access_successful() > successful_steps_limit || avg_access_unsuccessful() > unsuccessful_steps_limit ||
        fill_ratio() > fill_ratio_limit) {
        return true;
    }
    return false;
}


HashTable HashTable::rehash(HashTable &newTable) {
    for (int i = 0; i < this->size; i++) {
        if (this->table[i].occupied) {
            newTable.insert_key(this->table[i], this->table[i].value);
        }
    }
    return newTable;
}

