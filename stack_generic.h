#ifndef STACK_GENERIC_H
#define STACK_GENERIC_H

#include <iostream>

// Node untuk menyimpan data dalam rantai (chain)
template <typename T>
struct StackNode {
    T data;
    StackNode<T>* next;
};

template <typename T>
class Stack {
private:
    StackNode<T>* topNode; // Pointer ke elemen teratas

public:
    Stack() {
        topNode = NULL;
    }

    // Cek apakah stack kosong
    bool isEmpty() const {
        return topNode == NULL;
    }

    // PUSH: Menambah elemen ke puncak stack (Chain: insert front)
    void push(T x) {
        StackNode<T>* baru = new StackNode<T>;
        baru->data = x;
        baru->next = topNode;
        topNode = baru;
    }

    // POP: Menghapus elemen dari puncak stack
    bool pop(T &x) {
        if (isEmpty()) {
            return false;
        }
        StackNode<T>* temp = topNode;
        x = topNode->data;      // Ambil datanya sebelum dihapus
        topNode = topNode->next;
        delete temp;
        return true;
    }

    // PEEK: Melihat data teratas tanpa menghapus
    T peek() const {
        if (!isEmpty()) {
            return topNode->data;
        }
        return T(); // Mengembalikan objek default jika kosong
    }

    // Menampilkan isi stack dari atas ke bawah
    void display() const {
        StackNode<T>* temp = topNode;
        while (temp != NULL) {
            std::cout << temp->data << std::endl;
            temp = temp->next;
        }
    }

    // Destructor untuk membersihkan memori
    ~Stack() {
        T temp;
        while (pop(temp));
    }
};

#endif