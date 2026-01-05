#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template <class T>
struct Node {
    T data;
    Node* next;
    Node* prev;
};

template <class T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() {
        head = tail = NULL;
    }

    ~LinkedList() {
        Node<T>* current = head;
        while (current != NULL) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = tail = NULL;
    }

    bool isEmpty() const{
        return head == NULL;
    }

    // TAMBAH DEPAN
    void insertFront(T x) {
        Node<T>* baru = new Node<T>;
        baru->data = x;
        baru->next = head;
        baru->prev = NULL;

        if (isEmpty()) {
            head = tail = baru;
        } else {
            head->prev = baru;
            head = baru;
        }
    }

    // TAMBAH BELAKANG
    void insertBack(T x) {
        Node<T>* baru = new Node<T>;
        baru->data = x;
        baru->next = NULL;
        baru->prev = tail;

        if (isEmpty()) {
            head = tail = baru;
        } else {
            tail->next = baru;
            tail = baru;
        }
    }

    // TAMBAH TENGAH (Berdasarkan Indeks)
    void insertAt(int index, T x) {
        if (index <= 0) {
            insertFront(x);
            return;
        }

        Node<T>* temp = head;
        for (int i = 0; i < index - 1 && temp != NULL; i++) {
            temp = temp->next;
        }

        if (temp == NULL || temp == tail) {
            insertBack(x);
        } else {
            Node<T>* baru = new Node<T>;
            baru->data = x;
            baru->next = temp->next;
            baru->prev = temp;
            temp->next->prev = baru;
            temp->next = baru;
        }
    }

    // Gunakan const agar bisa dipanggil dari fungsi const lain
    Node<T>* getHead() const { return head; }
    Node<T>* getTail() const { return tail; } // Tambahkan ini
};

#endif