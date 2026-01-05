#ifndef QUEUEKTP_H
#define QUEUEKTP_H

#include "queue_generic.h"
#include "ktp.h"
#include <iostream>
using namespace std;

class QueueKTP {
private:
    Queue<KTP> q;   // ?? pakai queue generic

public:
    bool isEmpty() {
        return q.isEmpty();
    }

    void enqueue(KTP x) {
        q.enqueue(x);
    }

    void dequeue() {
        if (q.dequeue()) {
            cout << "Data KTP terdepan berhasil dihapus.\n";
        }
    }

    void display() {
        if (q.isEmpty()) {
            cout << "Queue KTP kosong!\n";
            return;
        }

        cout << "\n==== DATA KTP (QUEUE) ====\n";
        q.display(); // tampilkan via generic
    }
};

#endif