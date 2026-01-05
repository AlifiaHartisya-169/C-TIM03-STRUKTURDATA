#ifndef QUEUE_GENERIC_H
#define QUEUE_GENERIC_H

#include <iostream>
using namespace std;

// ============================
// NODE GENERIC
// ============================
template <typename T>
struct QueueNode {
    T data;
    QueueNode<T>* next;
};

// ============================
// CLASS QUEUE GENERIC
// ============================
template <typename T>
class Queue {
private:
    QueueNode<T>* front;
    QueueNode<T>* rear;

public:
    // Constructor
    Queue() {
        front = rear = NULL;
    }

    // Cek kosong
    bool isEmpty() {
        return front == NULL;
    }

    // ============================
    // ENQUEUE (tambah belakang)
    // ============================
    /*void enqueue(T x) {
        QueueNode<T>* baru = new QueueNode<T>;
        baru->data = x;
        baru->next = NULL;

        if (isEmpty()) {
            front = rear = baru;
        } else {
            rear->next = baru;
            rear = baru;
        }
    }*/
    
    // =========================================================
    // ENQUEUE BERPRIORITAS (Berdasarkan Umur)
    // Data dengan umur lebih tinggi akan berada di depan
    // =========================================================
    void enqueue(T x) {
        QueueNode<T>* baru = new QueueNode<T>;
        baru->data = x;
        baru->next = NULL;

        // Kondisi 1: Antrian Kosong atau Umur baru lebih besar dari Front (Prioritas Tertinggi)
        if (isEmpty() || x.umur > front->data.umur) {
            baru->next = front;
            front = baru;
            if (rear == NULL) rear = baru;
        } 
        else {
            // Kondisi 2: Cari posisi di tengah atau di belakang
            QueueNode<T>* temp = front;
            while (temp->next != NULL && temp->next->data.umur >= x.umur) {
                temp = temp->next;
            }
            
            baru->next = temp->next;
            temp->next = baru;
            
            if (baru->next == NULL) {
                rear = baru;
            }
        }
    }

    // ============================
    // DEQUEUE (hapus depan)
    // ============================
    bool dequeue() {
        if (isEmpty()) {
            cout << "Queue kosong!\n";
            return false;
        }

        QueueNode<T>* temp = front;
        front = front->next;

        if (front == NULL)
            rear = NULL;

        delete temp;
        return true;
    }

    // ============================
    // AMBIL DATA DEPAN
    // ============================
    T getFront() {
        return front->data;
    }

    // ============================
    // TAMPILKAN QUEUE
    // ============================
    void display() {
        if (isEmpty()) {
            cout << "Queue kosong!\n";
            return;
        }

        QueueNode<T>* temp = front;
        while (temp != NULL) {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
};

#endif
