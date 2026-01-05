#ifndef STACKKTP_H
#define STACKKTP_H

#include "stack_generic.h"
#include "ktp.h"
#include <iostream>

using namespace std;

class StackKTP {
private:
    Stack<KTP> s; // Memanggil implementasi stack generik berbasis chain

public:
    bool isEmpty() {
        return s.isEmpty();
    }

    void push(KTP x) {
        s.push(x);
    }

    void pop(KTP &x) {
        if (!s.pop(x)) {
            cout << "Stack sudah kosong!\n";
        }
    }

    void display() {
        if (s.isEmpty()) {
            cout << "Data KTP di Stack kosong!\n";
            return;
        }
        cout << "\n==== DATA KTP (STACK BERBASIS CHAIN) ====\n";
        s.display();
    }
};

#endif	