#include <iostream>

#define NODE_EMPTY(node) ((node) == NULL || (node) == &deleted )

int try_hash = 0;

struct Node {
    int key;
    int value;
    Node(int key, int value) {
        this->key = key;
        this->value = value;
    }
    Node() { Node(0, 0); }
};

static Node deleted;

struct HashTable {
    Node **rows;
    size_t size;
    size_t capacity;
};

HashTable *ht_create(size_t capacity) {
    HashTable *ht = new HashTable();
    ht -> rows = new Node*[capacity];
    for (int i = 0 ; i < capacity ; i++)
        ht -> rows[i] = NULL;
    ht -> size = 0;
    ht -> capacity = capacity;
}

void ht_destroy(HashTable *ht) {
    for (int i = 0 ; i < ht -> capacity ; i++) {
        if (ht -> rows[i] != NULL && ht -> rows[i] != &deleted)
            delete ht -> rows[i];
    }
    delete ht;
}

void ht_insert(HashTable *ht, int key, int value) {
    auto h = std::hash<int>();
    int key_pos = h(key) % ht -> capacity;

    while (ht -> rows[key_pos] != NULL && ht -> rows[key_pos] != &deleted) {
        if (ht -> rows[key_pos] -> key == key) {
            ht -> rows[key_pos] -> value = value;
            return;
        }
        key_pos = (key_pos + 1) % ht -> capacity;
    }

    Node *node = new Node(key, value);
    ht -> rows[key_pos] = node;
    ht -> size++;
}

ssize_t ht_cluster_count(HashTable *ht) {
    int current_cluster_size = 0;
    int cluster_count = 0;

    for (int i = 1 ; i < ht -> capacity ; i++) {
        if (NODE_EMPTY(ht -> rows[i])) {
            cluster_count += (current_cluster_size > 0 ? 1 : 0);
            current_cluster_size = 0;
        }
        else {
            current_cluster_size++;
        }
    }
    cluster_count += (current_cluster_size > 0 ? 1 : 0);

    return cluster_count;
}

int main() {
    for (int N = 1000 ; N <= 1000000 ; N *= 10) {
        HashTable *ht = ht_create(N);
        for (int i = 0 ; i < N / 2 ; i++) {
            ht_insert(ht, rand(), rand());
        }
        int cluster_count = ht_cluster_count(ht);

        std::cout << "Capacity: " << N << std::endl;
        std::cout << "Size: " << ht -> size << std::endl;
        std::cout << "Cluster count: " << cluster_count << std::endl;
        std::cout << "Average cluster size: " << (double)ht -> size / cluster_count << std::endl;
        std::cout << "----------" << std::endl;

        ht_destroy(ht);
    }
}