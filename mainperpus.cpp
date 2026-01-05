#include <iostream>
#include <string>
#include "login.h"
#include "peminjaman.h"
#include "history.h" 
#include "bukuLinklist.h"
#include "arraybuku.h"
using namespace std;

// === DEFINISI OBJEK GLOBAL ===
// Sesuai dengan deklarasi 'extern' di peminjaman.h
Queue<Peminjaman> antrianPeminjaman; 
Stack<Pengembalian> stackPengembalian;
HistoryManager hm;
Perpus db; // Database buku pusat

ArrayKTP databaseKTP;

int main() {
	muatDatabaseKTP(databaseKTP);
	
    //DoublyLinkedListBuku list;
	hm.loadFromFile();
	db.isi_data_buku(); // ISI DATABASE BUKU AWAL
	db.muat_data_buku();
    
    int pil;
    long long currentNIK = 0; // Ganti dari string ke long long
    
	//int pil;
	
    while (true) {
    	cout << "==============================================\n";
    	cout << "|					     |\n";
        cout << "|   SELAMAT DATANG DI PERPUSTAKAAN DEALPIS   |\n";
        cout << "|					     |\n";
        cout << "==============================================\n";
        cout << "|					     |\n";
        cout << "| 1. Login                                   |\n";
        cout << "| 2. Register User                           |\n";
        cout << "| 3. Lupa Password                           |\n";
        cout << "| 4. Hapus Akun                              |\n";
        cout << "| 5. Keluar                                  |\n";
        cout << "|					     |\n";
        cout << "==============================================\n";
        cout << "Masukkan pilihan anda : ";
        cin >> pil;

        system("cls");

        switch(pil) {
            case 1:{
            	// loginOtomatis sekarang menerima parameter long long &nikActive
			    int status = loginOtomatis(currentNIK); 
			    
			    if (status == 1) {
			        cout << "\nLogin sebagai ADMIN berhasil.\n";
			        system("pause"); system("cls");
			        menuAdmin();
			    }
			    else if (status == 2) {
			        cout << "\n====================================\n";
			        cout << "   LOGIN BERHASIL (SISTEM UMUM)\n";
			        cout << "====================================\n";
			        cout << "NIK Aktif    : " << currentNIK << endl;
			        
			        // OTOMATIS: Deteksi daerah dari NIK
			        cout << "Asal Daerah  : " << getDaerahByNIK(currentNIK) << endl; 
			        
			        cout << "====================================\n";
			        system("pause"); system("cls");
			        
			        // NIK dikirim ke menuUser agar tercatat di history
			        menuUser(to_string(currentNIK),db); 
			    }
			    break;
            }
                
            case 2:
                daftarUser(databaseKTP);
                system("pause");
                system("cls");
                break;

            case 3:
                lupaPassword();
                system("pause");
                system("cls");
                break;

            case 4:
            	hapusAkun();
            	system("pause");
                system("cls");
                break;

            default:
                cout << "Pilihan tidak valid!\n";
                system("pause");
                system("cls");
                break;
        }
    }
    
	

    return 0;
}