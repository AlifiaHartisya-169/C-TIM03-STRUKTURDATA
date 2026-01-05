#ifndef ARRAYKTP_H
#define ARRAYKTP_H

#include <iostream>
#include "array1d.h"
#include "ktp.h"

using namespace std;

class ArrayKTP {
private:
    Array1D<KTP> data;
    int size;
    int kapasitas;

public:
    ArrayKTP(int max = 100) : data(max) {
        kapasitas = max;
        size = 0;
    }

    bool isFull() {
        return size >= kapasitas;
    }

    bool isEmpty() {
        return size == 0;
    }

    void insert(KTP x) {
	    if (size >= kapasitas) {
	        // Jika penuh, otomatis tambah kapasitas (Resize)
	        kapasitas += 10; 
	        data.ReSize(kapasitas);
	    }
	    data[size] = x;
	    size++;
	}
    
    void display() {
	    if (isEmpty()) { cout << "Array kosong!\n"; return; }
	    cout << "\n==== DATA KTP (ARRAY) ====\n";
	    for (int i = 0; i < size; i++) {
	        cout << data[i] << endl; // Otomatis mencetak semua field!
	    }
	}
	
	// Tambahkan fungsi ini di dalam class ArrayKTP pada file arrayktp.h
	KTP* cariByNIK(long long nikCari) {
	    for (int i = 0; i < size; i++) {
	        if (data[i].nik == nikCari) {
	            return &data[i]; // Kembalikan alamat data KTP yang ketemu
	        }
	    }
	    return NULL; // Jika tidak ketemu
	}
	
	int getJumlah() { 
	    return size; 
	}
	
	KTP getKTP(int index) { 
	    return data[index]; 
	}

};

#endif
