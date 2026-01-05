#ifndef BSTBUKU_H
#define BSTBUKU_H

#include <iostream>
#include <string>

using namespace std;

// Node Generik
template <typename T>
struct NodeTree {
    T data;
    NodeTree<T> *left, *right;

    NodeTree(T value) : data(value), left(NULL), right(NULL) {}
};

// Class BST Generik
template <typename T>
class BSTBuku {
public:
    NodeTree<T>* root;

    BSTBuku() : root(NULL) {}

    // 1. Insert (Berdasarkan ID)
    NodeTree<T>* insert(NodeTree<T>* node, T value) {
        if (node == NULL) return new NodeTree<T>(value);
        if (value.id_buku < node->data.id_buku)
            node->left = insert(node->left, value);
        else if (value.id_buku > node->data.id_buku)
            node->right = insert(node->right, value);
        return node;
    }

    // 2. Cari Berdasarkan ID: O(log n)
    T* searchById(NodeTree<T>* node, int id) {
        if (node == NULL) return NULL;
        if (node->data.id_buku == id) return &(node->data);

        if (id < node->data.id_buku)
            return searchById(node->left, id);
        return searchById(node->right, id);
    }

    // 3. Cari Berdasarkan Judul (Traversal)
    void searchByTitle(NodeTree<T>* node, string judul, bool &ketemu) {
        if (node == NULL) return;
        
        searchByTitle(node->left, judul, ketemu);
        
        if (node->data.nama_buku.find(judul) != string::npos) {
            cout << "[Ketemu di Tree] ID: " << node->data.id_buku 
                 << " | Judul: " << node->data.nama_buku << endl;
            ketemu = true;
        }
        
        searchByTitle(node->right, judul, ketemu);
    }
};

#endif