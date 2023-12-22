#ifndef ASP2DZ3_HASHTABLE_H
#define ASP2DZ3_HASHTABLE_H

#include <vector>
#include <string>
#include "AddressFunction.h"
#include "BidirectionalLinearAddressing.h"

using namespace std;
static int successful_steps, unsuccessful_steps, search_count;


class HashTable {

public:
    struct Node {
        long long int key;
        string value;
        bool occupied, deleted;

        Node() : key(0), value(""), occupied(false), deleted(false) {}

        Node(long long int key, const string value) : key(key), value(value) {}
    };

private:
    vector<Node> table;
    int size, key_count = 0;
public:

    HashTable() {};

    HashTable(int size) : size(size) {
        table.resize(size);
    }

    ~HashTable() { clear(); };

    string find_key(long long int key) const;

    int hash_function(long long int key) const;

    bool insert_key(const Node &node, const string &value);

    static bool is_prime(int number);

    static int find_largest_prime(int value);

    bool delete_key(long long int key);

    double avg_access_successful() const;

    static double avg_access_unsuccessful();

    static void reset_statistics();

    void clear();

    int get_key_count() const {
        return key_count;
    }

    int get_table_size() const {
        return size;
    }

    friend ostream &operator<<(ostream &os, const HashTable &table);

    double fill_ratio() const;

    bool check_stats(double successful_steps, double unsuccessful_steps, double fill_ratio);

    HashTable rehash(HashTable& newTable);

};

#endif //ASP2DZ3_HASHTABLE_H
