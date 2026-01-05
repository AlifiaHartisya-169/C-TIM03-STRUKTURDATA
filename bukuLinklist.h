#ifndef BUKULINKLIST_H 
#define BUKULINKLIST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "structku.h"
#include "linkedlist.h" // Panggil file linkedlist generik

using namespace std;

class DoublyLinkedListBuku {
    private:
        LinkedList<Buku> list; // Gunakan LinkedList generik untuk menyimpan data Buku

    public:
        // Constructor tidak perlu lagi mengurus head/tail secara manual kerana sudah diuruskan oleh LinkedList
        DoublyLinkedListBuku() {}

        // Mengambil head daripada LinkedList generik
        Node<Buku>* getHead() const{
            return list.getHead(); //
        }

        bool isEmpty() const{
            return list.isEmpty(); //
        }

        // Memanggil fungsi insertBack daripada linkedlist.h
        void insert(Buku x) {
            list.insertBack(x); //
        }

        // Paparkan data dengan melayari (traversing) LinkedList
        void displayForward() {
            if (list.isEmpty()) { //
                cout << "Linked List buku kosong!\n";
                return;
            }

            cout << "\n==== DATA BUKU (Forward) ====\n";
            Node<Buku>* temp = list.getHead(); //

            while (temp != NULL) {
                cout << "\nNama Buku         : " << temp->data.nama_buku
                     << "\nID Buku           : " << temp->data.id_buku
                     << "\nGenre Buku        : " << temp->data.genre_buku
                     << "\nPenulis           : " << temp->data.penulis
                     << "\n-----------------------------------";
                temp = temp->next;
            }
        }
        
        void displayBackward() {
            if (list.isEmpty()) {
                cout << "Linked List buku kosong!\n";
                return;
            }
            cout << "\n==== DATA BUKU (Backward) ====\n";
            Node<Buku>* temp = list.getTail(); // Memerlukan getTail() di linkedlist.h
            while (temp != NULL) {
                cout << "\nNama Buku         : " << temp->data.nama_buku
                     << "\nID Buku           : " << temp->data.id_buku
                     << "\nGenre Buku        : " << temp->data.genre_buku
                     << "\nPenulis           : " << temp->data.penulis
                     << "\n-----------------------------------";
                temp = temp->prev; // Berpindah ke node sebelumnya
            }
        }

        // Simpan data ke fail .txt menggunakan data daripada LinkedList
        void simpanKeFile(string databuku) {
            ofstream file(databuku.c_str(), ios::trunc); 
            
            if (!file.is_open()) {
                cerr << "Gagal membuka file: " << databuku << "\n";
                return;
            }
            
            Node<Buku>* temp = list.getHead(); // Ambil data bermula dari head
            while (temp != NULL) {
                file << temp->data.nama_buku << "|"
                     << temp->data.id_buku << "|"
                     << temp->data.genre_buku << "|"
                     << temp->data.penulis << "\n";
                temp = temp->next;
            }

            file.close();
            //cout << "\nData berhasil disimpan ke file: " << databuku << "\n";
        }

        // Baca dari fail dan masukkan ke dalam LinkedList
       	void bacaDariFile(string databuku) {
    		ifstream file(databuku.c_str());
    			if (!file.is_open()) return;

    	string baris;
    		while (getline(file, baris)) {
        		if (baris == "") continue;
                
                Buku x;
        		stringstream ss(baris);
        		string segment;

        		getline(ss, segment, ';');
        		x.id_buku = atoi(segment.c_str());

        		getline(ss, segment, ';');
        		x.nama_buku = segment;

        		getline(ss, segment, ';');
        		x.genre_buku = segment;

        		getline(ss, segment, ';');
        		x.penulis = segment;

        		list.insertBack(x);
    		}
    		file.close();
            //cout << "\nData berhasil dimuat dari file: " << databuku << ".\n";
        }
        
};

#endif