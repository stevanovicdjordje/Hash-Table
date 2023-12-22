#include <iostream>
#include <fstream>
#include <sstream>
#include "HashTable.h"

using namespace std;


void menu() {
    cout << "**** MENU *****" << endl;
    cout << "1. Make a table" << endl;
    cout << "2. Find key" << endl;
    cout << "3. Insert new key" << endl;
    cout << "4. Delete key" << endl;
    cout << "5. Average access in successful search" << endl;
    cout << "6. Average access in unsuccessful search" << endl;
    cout << "7. Reset statistics" << endl;
    cout << "8. Clear table" << endl;
    cout << "9. Number of keys in table" << endl;
    cout << "10. Table size" << endl;
    cout << "11. Print table" << endl;
    cout << "12. Fill ratio" << endl;
    cout << "0. Exit" << endl;
}

basic_ifstream<char> open_file(const char *file_name) {
    ifstream data_file;
    data_file.open(file_name);
    return data_file;
}

HashTable::Node process_line(const string &line_to_process, char delimiter) {
    auto *key = new HashTable::Node;
    std::istringstream line(line_to_process);
    std::string token;
    std::vector<std::string> lines;

    while (getline(line, token, delimiter)) {
        lines.push_back(token);
    }
    key->key = stoll(lines[1]);
    key->value = lines[0];
    return *key;
}


HashTable make_table(int size) {
    HashTable Table(size);
    return Table;
}

void insert_keys_from_file(HashTable &Table) {
    string line_to_process, token;
    char delimiter = '\t';
    ifstream data_file;
    data_file = open_file("C://Users//jovan//CLionProjects//asp2dz3//keys.txt");
    if (!data_file.is_open()) {
        cout << "File is not open!" << endl;
        exit(0);
    }
    while (getline(data_file, line_to_process)) {
        auto *new_key = new HashTable::Node;
        *new_key = process_line(line_to_process, delimiter);
        Table.insert_key(*new_key, new_key->value);
    }
}

void insert_keys_from_si(HashTable &Table) {
    cout << "Inserting key from standard input, when you want to finish enter C" << endl;
    char delimiter = ' ';
    std::string line;

    while (getline(std::cin, line)) {
        if (line == "C") {
            break;
        }
        size_t pos = line.find(delimiter);
        if (pos != string::npos) {
            auto *new_key = new HashTable::Node;
            new_key->key = std::stoll(line.substr(0, pos));
            new_key->value = line.substr(pos + 1);
            Table.insert_key(*new_key, new_key->value);
        }
    }
}


bool insert_keys(HashTable &Table) {
    char choice;
    cout << "Insert key from file or standard input? " << endl;
    cout << "F for file, S for standard input" << endl;
    cin >> choice;
    if (choice == 'F') {
        insert_keys_from_file(Table);
    } else {
        insert_keys_from_si(Table);
    }
    return true;
}

void find_key_in_table(const HashTable &Table) {
    long long int key_to_find;
    cout << "Enter key you want to find: ";
    cin >> key_to_find;
    string found_result = Table.find_key(key_to_find);
    if (found_result != "0") {
        cout << found_result << endl;
    }
}

void delete_key_from_table(HashTable &Table) {
    long long int key_to_delete;
    cout << "Enter key you want to delete: ";
    cin >> key_to_delete;
    bool found_result = Table.delete_key(key_to_delete);
    if (found_result) {
        cout << "Key deleted." << endl;
    }
}


HashTable create_new_table(HashTable Table) {
    int size;
    cout << "Enter new size: ";
    cin >> size;
    HashTable newTable(size);
    newTable = Table.rehash(newTable);
    return newTable;
}


int main() {
    int choice, size;
    double unsuccessful_access_limit, successful_access_limit, fill_ratio_limit;
    bool limit;
    HashTable Table;
    while (true) {
        menu();
        cout << "Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Making table...." << endl;
                cout << "Enter limit for successful access: ";
                cin >> successful_access_limit;
                cout << "Enter limit for unsuccessful access: ";
                cin >> unsuccessful_access_limit;
                cout << "Enter limit for fill ratio: ";
                cin >> fill_ratio_limit;
                cout << "Enter size of table: ";
                cin >> size;
                Table = make_table(size);
                break;
            case 2:
                cout << "Finding key...." << endl;
                find_key_in_table(Table);
                break;
            case 3:
                cout << "Inserting new key...." << endl;
                insert_keys(Table);
                limit = Table.check_stats(successful_access_limit, unsuccessful_access_limit, fill_ratio_limit);
                if (limit) {
                    cout << "Creating new table...." << endl;
                    Table = create_new_table(Table);
                }
                break;
            case 4:
                cout << "Deleting key...." << endl;
                delete_key_from_table(Table);
                break;
            case 5:
                cout << "Average access in successful search: " << Table.avg_access_successful() << endl;
                break;
            case 6:
                cout << "Average access in unsuccessful search: " << HashTable::avg_access_unsuccessful() << endl;
                break;
            case 7:
                cout << "Reset statistics...." << endl;
                HashTable::reset_statistics();
                break;
            case 8:
                cout << "Clearing table...." << endl;
                Table.clear();
                break;
            case 9:
                cout << "Number keys in table: " << Table.get_key_count() << endl;
                break;
            case 10:
                cout << "Table size: " << Table.get_table_size() << endl;
                break;
            case 11:
                cout << "Printing table...." << endl;
                cout << Table;
                break;
            case 12:
                cout << "Fill ratio: " << Table.fill_ratio() << endl;
                break;
            case 0:
                cout << "Exiting...." << endl;
                Table.clear();
                exit(0);
            default:
                cout << "Wrong choice, try again" << endl;
                menu();
                std::cin >> choice;
                break;
        }
    }
}
