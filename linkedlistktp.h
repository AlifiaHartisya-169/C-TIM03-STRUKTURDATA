#ifndef LINKEDLISTKTP_H
#define LINKEDLISTKTP_H

#include <iostream>
#include "linkedlist.h"
#include "ktp.h"

using namespace std;

class LinkedListKTP {
private:
    LinkedList<KTP> list;

public:
    // Tambah depan
    void insertDepan(KTP x) {
        list.insertFront(x);
    }

    // Tambah belakang
    void insertBelakang(KTP x) {
        list.insertBack(x);
    }

    // Tambah tengah/indeks tertentu
    void insertTengah(int posisi, KTP x) {
        list.insertAt(posisi, x);
    }

    void display() {
        if (list.isEmpty()) {
            cout << "Data KTP kosong!\n";
            return;
        }

        Node<KTP>* temp = list.getHead();
        cout << "\n==== DATA KTP (Linked List) ====\n";

        while (temp != NULL) {
            // Menggunakan operator<< dari ktp.h agar otomatis rapi dan teks muncul
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
};

#endif