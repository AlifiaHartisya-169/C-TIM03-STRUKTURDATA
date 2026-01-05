#include <iostream>
#include <string>
#include <fstream>
#include "ktp.h"
#include "arrayktp.h"
#include "linkedlistktp.h"
#include "stackktp.h"
#include "queuektp.h"

using namespace std;

// Membersihkan buffer tanpa <limits>
void bersihkanBuffer() {
    char c;
    while (cin.get(c) && c != '\n');
}

// Mengambil nilai setelah tanda ":" 
string pecahNilai(string line) {
    int pos = -1;
    for (int i = 0; i < (int)line.length(); i++) {
        if (line[i] == ':') {
            pos = i;
            break;
        }
    }
    if (pos != -1 && (pos + 2) < (int)line.length()) {
        return line.substr(pos + 2);
    }
    return "";
}

KTP inputData() {
    KTP x;
    int jk, sp, warga;

    cout << "\n==== INPUT DATA KTP ====\n";
    
    cout << "Masukkan NIK                : ";
    cin >> x.nik;
    bersihkanBuffer();
    
    cout << "Masukkan Nama               : ";
    getline(cin, x.nama);
    
    cout << "Tempat Lahir                : ";
	getline(cin, x.tempat_lahir);

	cout << "Tanggal Lahir               : ";  
    cin >> x.tgl_lahir.hari >> x.tgl_lahir.bulan >> x.tgl_lahir.tahun;
	
	cout << "Jenis Kelamin (1=L, 0=P)    : ";
	cin >> jk;
    x.jenis_kelamin = (jk == 1);
	
	cout << "Golongan Darah              : ";
	cin >> x.gol_darah;
	bersihkanBuffer();
	
	cout << "Alamat                      : ";
	getline(cin, x.alamat);
	
	cout << "RT                          : ";
	cin >> x.rt;
	bersihkanBuffer();
	
	cout << "RW                          : ";
	cin >> x.rw;
	bersihkanBuffer();
	
    cout << "Kelurahan/Desa              : ";
	getline(cin, x.kel_desa);
	
    cout << "Kecamatan                   : ";
	getline(cin, x.kecamatan);
	
    cout << "1. Islam\n2. Kristen\n3. Katolik\n4. Hindu\n5. Budha\n6. Konghucu\n"
	     << "Agama                       : ";
	cin >> x.agama;
	
	cout << "1. Sudah Kawin\n2. Belum Kawin\n"
	     << "Status Perkawinan           : ";
	cin >> sp;
	x.status_perkawinan = (sp == 1);
	bersihkanBuffer();
	
    cout << "Pekerjaan                   : ";
	getline(cin, x.pekerjaan);
	
    cout << "1. WNI\n2. WNA\n"
	     << "Kewarganegaraan             : ";
	cin >> warga;
	x.kewarganegaraan = (warga == 1);
	
    cout << "1. Sementara\n2. 5 Tahun\n3. Selamanya\n" 
	    << "Berlaku Hingga               : ";
	cin >> x.berlaku_hingga;
                 
    cout << "\n-----------------------------------";

    return x;
}

void simpanKeFile(KTP x) {
    ofstream file("data_ktp.txt", ios::app);
    if (!file.is_open()) return;

    file << "NIK               : " << x.nik << endl;
    file << "Nama              : " << x.nama << endl;
    file << "Tempat Lahir      : " << x.tempat_lahir << endl;
    file << "Tanggal Lahir     : " << (x.tgl_lahir.hari < 10 ? "0" : "") << x.tgl_lahir.hari << "-" 
         << (x.tgl_lahir.bulan < 10 ? "0" : "") << x.tgl_lahir.bulan << "-" << x.tgl_lahir.tahun << endl;
    file << "Jenis Kelamin     : " << (x.jenis_kelamin ? "Laki-laki" : "Perempuan") << endl;
    file << "Golongan Darah    : " << x.gol_darah << endl;
    file << "Alamat            : " << x.alamat << endl;
    file << "RT                : " << x.rt << endl;
    file << "RW                : " << x.rw << endl;
    file << "Kelurahan/Desa    : " << x.kel_desa << endl;
    file << "Kecamatan         : " << x.kecamatan << endl;
    
    // GUNAKAN FUNGSI BANTUAN AGAR TERSIMPAN TEKS
    file << "Agama             : " << teksAgama(x.agama) << endl;
    file << "Status Perkawinan : " << (x.status_perkawinan ? "Kawin" : "Belum") << endl;
    file << "Pekerjaan         : " << x.pekerjaan << endl;
    file << "Kewarganegaraan   : " << (x.kewarganegaraan ? "WNI" : "WNA") << endl;
    file << "Berlaku Hingga    : " << teksBerlaku(x.berlaku_hingga) << endl;
    file << "----------------------------------------" << endl;

    file.close();
}

// Memuat data dari file berlabel ke dalam struktur data
void loadDataKeMemori(ArrayKTP &arr, LinkedListKTP &list, StackKTP &stack, QueueKTP &queue) {
    ifstream file("data_ktp.txt");
    if (!file.is_open()) return;

    string s;
    KTP x;
    while (getline(file, s)) {
        if (s.length() < 2) continue;

        // Cek label menggunakan substr di awal baris (Menghindari npos)
        if (s.substr(0, 3) == "NIK") x.nik = stoll(pecahNilai(s));
        else if (s.substr(0, 4) == "Nama") x.nama = pecahNilai(s);
        else if (s.substr(0, 12) == "Tempat Lahir") x.tempat_lahir = pecahNilai(s);
        else if (s.substr(0, 13) == "Tanggal Lahir") {
            sscanf(pecahNilai(s).c_str(), "%d-%d-%d", &x.tgl_lahir.hari, &x.tgl_lahir.bulan, &x.tgl_lahir.tahun);
        }
        else if (s.substr(0, 13) == "Jenis Kelamin") x.jenis_kelamin = (pecahNilai(s) == "Laki-laki");
        else if (s.substr(0, 14) == "Golongan Darah") x.gol_darah = pecahNilai(s);
        else if (s.substr(0, 6) == "Alamat") x.alamat = pecahNilai(s);
        else if (s.substr(0, 2) == "RT") x.rt = stoi(pecahNilai(s));
        else if (s.substr(0, 2) == "RW") x.rw = stoi(pecahNilai(s));
        else if (s.substr(0, 14) == "Kelurahan/Desa") x.kel_desa = pecahNilai(s);
        else if (s.substr(0, 9) == "Kecamatan") x.kecamatan = pecahNilai(s);
        else if (s.substr(0, 5) == "Agama"){
        	string agm = pecahNilai(s);
		    if(agm == "Islam") x.agama = 1; 
		    else if(agm == "Kristen") x.agama = 2;
		    else if(agm == "Katolik") x.agama = 3;
		    else if(agm == "Hindu") x.agama = 4;
		    else if(agm == "Budha") x.agama = 5;
		    else if(agm == "Konghucu") x.agama = 6;
		}
        else if (s.substr(0, 17) == "Status Perkawinan") x.status_perkawinan = (pecahNilai(s) == "Belum Kawin");
        else if (s.substr(0, 9) == "Pekerjaan") x.pekerjaan = pecahNilai(s);
        else if (s.substr(0, 15) == "Kewarganegaraan") x.kewarganegaraan = (pecahNilai(s) == "WNI");
        else if (s.substr(0, 14) == "Berlaku Hingga") {
        	string ber = pecahNilai(s);
		    if(ber == "Sementara") x.berlaku_hingga = 1;
		    else if(ber == "5 Tahun") x.berlaku_hingga = 2;
		    else if(ber == "Selamanya") x.berlaku_hingga = 3;
		}
        else if (s[0] == '-') { 
            // Satu blok KTP selesai, masukkan ke semua struktur data
            arr.insert(x); 
            list.insertBelakang(x); 
            stack.push(x); 
            queue.enqueue(x); 
        }
    }
    file.close();
}

int main() {
    ArrayKTP arr;
    LinkedListKTP list;
    StackKTP stack;
    QueueKTP queue;
    KTP temp;
    
    //OTOMATIS LOAD SAAT PROGRAM DIMULAI
    loadDataKeMemori(arr, list, stack, queue);

    int pilih;

    do {
        cout << "\n===== MENU KTP =====\n";
        cout << "1. Input Data KTP\n";
        cout << "2. Tampilkan Array 1D\n";
        cout << "3. Tampilkan Linked List\n";
        cout << "4. Tampilkan Stack KTP\n";
        cout << "5. Tampilkan Queue KTP\n";
        cout << "6. Hapus Data Stack\n";
        cout << "7. Hapus Data Queue\n";
        cout << "8. Keluar\n";
        cout << "Pilih menu : ";
        cin >> pilih;

        switch (pilih) {
            case 1: {
			    int jumlah;
			    cout << "\nMau input berapa data KTP? : ";
			    cin >> jumlah;
			
			    for (int i = 1; i <= jumlah; i++) {
			        cout << "\n--- Data ke-" << i << " ---";
			        KTP x = inputData();
			
			        // Menu pilihan posisi khusus untuk Linked List
			        int posisi;
			        cout << "\nSimpan di Linked List bagian mana?\n";
			        cout << "1. Depan\n2. Belakang\n3. Tengah (Indeks)\nPilih: ";
			        cin >> posisi;
			
			        if (posisi == 1) {
			            list.insertDepan(x); // Fungsi baru di linkedlistktp.h
			        } else if (posisi == 3) {
			            int idx;
			            cout << "Masukkan Indeks: ";
			            cin >> idx;
			            list.insertTengah(idx, x); // Fungsi baru di linkedlistktp.h
			        } else {
			            list.insertBelakang(x); // Default tambah belakang
			        }
			
			        // Struktur data lainnya tetap menggunakan metode standar agar sinkron
			        arr.insert(x);      
			        stack.push(x);      
			        queue.enqueue(x);    
			
			        simpanKeFile(x);    
			    }
			
			    cout << "\nSemua data KTP berhasil disimpan dan disinkronkan!\n";
			    break;
			}
            case 2:
                arr.display();
                break;

            case 3:
                list.display();
                break;
                
            case 4:
                stack.display();
                break;

            case 5:
                queue.display();
                break;

            case 6:{
            	stack.pop(temp);
            	cout << "\nData berhasil Dihapus Metode pop!\n";
            	break;
			}
            	
            case 7:{
            	queue.dequeue();
            	cout << "\nData berhasil Dihapus Metode dequeue!\n";
            	break;
			}

            case 8:
                cout << "Terima kasih!\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 8);


    return 0;
}
