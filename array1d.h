#ifndef ARRAY1D_H
#define ARRAY1D_H

#include <iostream>
using namespace std;

// CLASS TEMPLATE ARRAY 1D DINAMIS

template<class T>
class Array1D {
private:
    T* element;    // pointer ke array dinamis
    int size;      // ukuran array

public:

    // Konstruktor default
    Array1D(int sz = 0) {
        size = sz;
        if (size > 0)
            element = new T[size];
        else
            element = nullptr;
    }

    // Copy constructor
    Array1D(const Array1D<T>& other) {
        size = other.size;
        element = new T[size];
        for (int i = 0; i < size; i++)
            element[i] = other.element[i];
    }

    // Destructor
    ~Array1D() {
        delete[] element;
    }

    // Operator indeks
    T& operator[](int i) {
        return element[i];  // tanpa boundary check
    }

    // Mendapat ukuran array
    int Size() const {
        return size;
    }

    // Assignment operator
    Array1D<T>& operator=(const Array1D<T>& other) {
        if (this != &other) {
            delete[] element;

            size = other.size;
            element = new T[size];
            for (int i = 0; i < size; i++)
                element[i] = other.element[i];
        }
        return *this;
    }

    // Resize array
    void ReSize(int newSize) {
        delete[] element;      // hapus memori lama
        size = newSize;
        element = new T[size]; // alokasi baru
    }
};

#endif
