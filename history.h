#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "linkedlist.h" // Memanggil linked list generik

using namespace std;

struct History {
    string username;
    string judulBuku;
    int idBuku;
    int lamaPinjam;
};

class HistoryManager {
private:
    LinkedList<History> list; // Menggunakan ADT Linked List

public:
	
	void addHistory(History h) {
        list.insertBack(h);
        ofstream file("history.txt", ios::app);
        file << h.username << "," << h.judulBuku << "," << h.idBuku << "," << h.lamaPinjam << endl;
        file.close();
    }

    // Fungsi KUNCI: Mencari data peminjaman terakhir user untuk otomatisasi return
    History* findLastLoan(string user, int idBuku) {
        Node<History>* temp = list.getHead();
        History* found = NULL;
        while (temp != NULL) {
            if (temp->data.username == user && temp->data.idBuku == idBuku) {
                found = &temp->data;
            }
            temp = temp->next;
        }
        return found;
    }

    void loadFromFile() {
	    ifstream file("history.txt");
	    if (!file.is_open()) {
	        cout << "[DEBUG] File history.txt tidak ditemukan.\n";
	        return;
	    }
	
	    string line;
	    int count = 0;
	    while (getline(file, line)) {
	        if (line.empty()) continue;
	        stringstream ss(line);
	        string u, j, id, l;
	        if (getline(ss, u, ',') && getline(ss, j, ',') && getline(ss, id, ',') && getline(ss, l, ',')) {
	            History h = {u, j, stoi(id), stoi(l)};
	            list.insertBack(h);
	            count++;
	        }
	    }
	    //cout << "Berhasil memuat " << count << " data riwayat dari file.\n";
	    file.close();
	}
	
    // Menambah riwayat ke memori dan file
    /*void addHistory(const string &user, const string &judul, int lama) {
        History h = {user, judul, lama};
        list.insertBack(h); // Masukkan ke list

        // Tetap simpan ke file agar permanen
        ofstream simpan("history.txt", ios::app);
        if (simpan.is_open()) {
            simpan << user << "," << judul << "," << lama << endl;
            simpan.close();
        }
    }

    // Memuat data dari file ke Linked List saat program mulai
    void loadFromFile() {
        ifstream baca("history.txt");
        if (!baca.is_open()) return;

        string line;
        while (getline(baca, line)) {
            stringstream ss(line);
            string u, j, l;
            if (getline(ss, u, ',') && getline(ss, j, ',') && getline(ss, l, ',')) {
                History h = {u, j, stoi(l)};
                list.insertBack(h); // Masukkan ke memori
            }
        }
        baca.close();
    }*/

    // Menampilkan riwayat dari memori (jauh lebih cepat)
    void viewHistory(const string &username) {
        if (list.isEmpty()) { // Cek kondisi kosong
            cout << "Belum ada riwayat.\n";
            return;
        }

        Node<History>* temp = list.getHead(); // Traversal list
        bool ditemukan = false;
        int counter = 1;

        /*cout << "\n=== RIWAYAT PEMINJAMAN " << username << " ===\n";
        while (temp != NULL) {
            if (temp->data.username == username) {
                ditemukan = true;
                cout << counter++ << ". " << temp->data.judulBuku 
                     << " (" << temp->data.lamaPinjam << " hari)\n";
            }
            temp = temp->next;
        }*/
        
        cout << "\n=== RIWAYAT PEMINJAMAN USER: " << username << " ===\n";
        cout << "---------------------------------------------------------\n";
        cout << left << setw(4) << "No" << " | " << setw(10) << "ID Buku" << " | " << setw(25) << "Judul Buku" << " | " << "Lama\n";
        cout << "---------------------------------------------------------\n";

        while (temp != NULL) {
            if (temp->data.username == username) {
                ditemukan = true;
                cout << left << setw(4) << counter++ << " | " 
                     << setw(10) << temp->data.idBuku << " | " 
                     << setw(25) << temp->data.judulBuku << " | " 
                     << temp->data.lamaPinjam << " hari" << endl;
            }
            temp = temp->next;
        }

        if (!ditemukan) cout << "Riwayat tidak ditemukan.\n";
    }
};

#endif