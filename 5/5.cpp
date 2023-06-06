#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>

using namespace std;

struct Node {
    int value;
    Node* next;
};

class HashTable {
private:
    Node** table;
    int size;
    int hashFunction(int value);
public:
    HashTable(int size);
    void addElement(int value);
    bool searchElement(int value);
    void printTable();
};

HashTable::HashTable(int size) {
    this->size = size;
    table = new Node * [size];
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
}

int HashTable::hashFunction(int value) {
    return value % size;
}

void HashTable::addElement(int value) {
    int index = hashFunction(value);
    if (table[index] == NULL) {
        table[index] = new Node;
        table[index]->value = value;
        table[index]->next = NULL;
    }
    else {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = table[index];
        table[index] = newNode;
    }
}

bool HashTable::searchElement(int value) {
    int index = hashFunction(value);
    Node* current = table[index];
    while (current != NULL) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void HashTable::printTable() {
    for (int i = 0; i < size; i++) {
        cout << i << ": ";
        Node* current = table[i];
        while (current != NULL) {
            cout << current->value << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Ru");
    srand(time(NULL));
    int array[12];
    for (int i = 0; i < 12; i++) {
        array[i] = rand() % (54000 - 24000 + 1) + 24000;
    }
    HashTable table(10);
    for (int i = 0; i < 12; i++) {
        table.addElement(array[i]);
    }
    cout << "Массив: ";
    for (int i = 0; i < 12; i++) {
        cout << array[i] << " ";
    }
    cout << endl << "Хеш таблица:" << endl;
    table.printTable();
    int searchValue;
    cout << "Введите значение для поиска: ";
    cin >> searchValue;
    if (table.searchElement(searchValue)) {
        cout << searchValue << " найдено." << endl;
    }
    else {
        cout << searchValue << " не найдено." << endl;
    }
    return 0;
}