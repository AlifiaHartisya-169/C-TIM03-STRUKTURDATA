#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio> // Untuk remove dan rename
#include "arrayktp.h"

using namespace std;

// =====================================================
// 1. FUNGSI PEMBANTU (HELPERS)
// =====================================================

// Mengambil nilai setelah tanda ":" tanpa menggunakan npos
inline string pecahNilai(string line) {
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

// Validasi password maksimal 10 karakter
inline bool validPassword(const string &pass) {
    if (pass.length() > 10) {
        cout << ">> Password maksimal 10 karakter!\n";
        return false;
    }
    return true;
}

// Deteksi Daerah berdasarkan NIK
inline string getDaerahByNIK(long long nik) {
    string s_nik = to_string(nik);
    if (s_nik.length() < 6) return "Wilayah Tidak Terdeteksi";

    string provCode = s_nik.substr(0, 2);
    string kotaCode = s_nik.substr(2, 2);

    if (provCode == "34") { // DIY
        if (kotaCode == "04") return "Sleman, DIY";
        if (kotaCode == "71") return "Yogyakarta Kota, DIY";
        if (kotaCode == "02") return "Bantul, DIY";
        return "Daerah Istimewa Yogyakarta";
    } 
    else if (provCode == "31") return "DKI Jakarta";
    else if (provCode == "32") return "Jawa Barat";
    else if (provCode == "33") return "Jawa Tengah";
    else if (provCode == "35") return "Jawa Timur";

    return "Luar Daerah / Kode Provinsi: " + provCode;
}

inline void simpanKTPKeFile(KTP x) {
    ofstream file("data_ktp.txt", ios::app);
    if (file.is_open()) {
        file << "NIK           : " << x.nik << endl;
        file << "Nama          : " << x.nama << endl;
        file << "Tempat Lahir  : " << x.tempat_lahir << endl;
        // Format Tanggal: dd-mm-yyyy (Wajib 10 karakter agar substr aman)
        file << "Tgl Lahir     : " << (x.tgl_lahir.hari < 10 ? "0" : "") << x.tgl_lahir.hari << "-" 
             << (x.tgl_lahir.bulan < 10 ? "0" : "") << x.tgl_lahir.bulan << "-" << x.tgl_lahir.tahun << endl;
        file << "Jenis Kelamin : " << (x.jenis_kelamin ? "Laki-laki" : "Perempuan") << endl;
        file << "Gol. Darah    : " << x.gol_darah << endl;
        file << "Alamat        : " << x.alamat << endl;
        file << "RT            : " << x.rt << endl; // Baris RT sendiri
        file << "RW            : " << x.rw << endl; // Baris RW sendiri
        file << "Kel/Desa      : " << x.kel_desa << endl;
        file << "Kecamatan     : " << x.kecamatan << endl;
        file << "Agama         : " << teksAgama(x.agama) << endl; 
        file << "Status        : " << (x.status_perkawinan ? "Kawin" : "Belum") << endl;
        file << "Pekerjaan     : " << x.pekerjaan << endl;
        file << "Warganegara   : " << (x.kewarganegaraan ? "WNI" : "WNA") << endl;
        file << "Berlaku Hingga: " << teksBerlaku(x.berlaku_hingga) << endl;
        file << "========================================" << endl;
        file.close();
    }
}

// =====================================================
// 2. SISTEM REGISTRASI (DENGAN PENGECEKAN KTP)
// =====================================================
void daftarUser(ArrayKTP &database) {
    long long inputNIK;
    string password;
    KTP baru;

    cout << "\n===============================\n";
    cout << "      REGISTER USER BARU       \n";
    cout << "===============================\n";
    cout << "Masukkan NIK Anda : "; 
    cin >> inputNIK;

    // Cek apakah NIK sudah ada di database KTP
    KTP* existingData = database.cariByNIK(inputNIK);

    if (existingData != NULL) {
        // Jika data KTP sudah ada, cukup buat password akun
        cout << "\n>> Data KTP Ditemukan!\n";
        cout << "Nama   : " << existingData->nama << endl;
        cout << "Daerah : " << getDaerahByNIK(inputNIK) << endl;
        cout << "-------------------------------\n";
        cout << "Silakan buat password untuk akun perpustakaan Anda.\n";
        
        do {
            cout << "Buat Password (maks 10): "; cin >> password;
        } while (!validPassword(password));

        ofstream fAkun("Akun.txt", ios::app);
        fAkun << inputNIK << " " << password << endl;
        fAkun.close();
        cout << "\n>> Registrasi berhasil! Akun diaktifkan.\n";
    } 
    else {
        // Jika NIK belum ada, wajib input KTP lengkap
        cout << "\n>> NIK tidak ditemukan di database KTP.\n";
        cout << "Silakan lengkapi data KTP Anda untuk mendaftar:\n";
        baru.nik = inputNIK;
        
        cin.ignore();
        cout << "Nama Lengkap        : "; getline(cin, baru.nama);
        cout << "Tempat Lahir        : "; getline(cin, baru.tempat_lahir);
        cout << "Tgl Lahir (tgl bln thn): "; cin >> baru.tgl_lahir.hari >> baru.tgl_lahir.bulan >> baru.tgl_lahir.tahun;
        
        int jk, agm, st, wn, ber;
        cout << "Jenis Kelamin (1:L / 2:P): "; cin >> jk; baru.jenis_kelamin = (jk == 1);
        cin.ignore();
        cout << "Golongan Darah      : "; getline(cin, baru.gol_darah);
        cout << "Alamat              : "; getline(cin, baru.alamat);
        cout << "RT / RW             : "; cin >> baru.rt >> baru.rw;
        cin.ignore();
        cout << "Kelurahan/Desa      : "; getline(cin, baru.kel_desa);
        cout << "Kecamatan           : "; getline(cin, baru.kecamatan);
        cout << "Agama (1:Islam, 2:Krist, 3:Katol, 4:Hindu, 5:Budha, 6:Konghucu)        : "; cin >> agm; baru.agama = agm;
        cout << "Status (1:Belum, 2:Kawin): "; cin >> st; baru.status_perkawinan = (st == 1);
        cin.ignore();
        cout << "Pekerjaan           : "; getline(cin, baru.pekerjaan);
        cout << "Warganegara (1:WNI, 2:WNA): "; cin >> wn; baru.kewarganegaraan = (wn == 1);
        cout << "Berlaku (1:Sement, 2:5 Thn, 3:Selamanya): "; cin >> ber; baru.berlaku_hingga = ber;

        do {
            cout << "\nBuat Password Login : "; cin >> password;
        } while (!validPassword(password));

        // Simpan Akun
        ofstream fAkun("Akun.txt", ios::app);
        fAkun << baru.nik << " " << password << endl;
        fAkun.close();

        // Simpan Profil KTP Baru
        simpanKTPKeFile(baru);
        database.insert(baru); // Masukkan ke RAM

        cout << "\n>> Registrasi Akun & KTP Berhasil!\n";
    }
}

// =====================================================
// 3. LOGIN SISTEM
// =====================================================
int loginOtomatis(long long &nikActive) {
    string inputUser, password, filePass;
    long long fileNIK;

    cout << "\n===============================\n";
    cout << "          LOGIN SISTEM          \n";
    cout << "===============================\n";
    cout << "NIK / Username : "; cin >> inputUser;
    cout << "Password       : "; cin >> password;

    if (inputUser == "admin" && password == "admin123") return 1;

    ifstream baca("Akun.txt");
    if (!baca.is_open()) return 0;

    while (baca >> fileNIK >> filePass) {
        stringstream ss(inputUser);
        long long tempNIK;
        if (!(ss >> tempNIK)) continue;

        if (tempNIK == fileNIK && password == filePass) {
            nikActive = fileNIK;
            baca.close();
            return 2;
        }
    }
    baca.close();
    cout << ">> NIK atau Password salah!\n";
    return 0;
}

// =====================================================
// 4. LUPA PASSWORD & HAPUS AKUN
// =====================================================
void lupaPassword() {
    long long nikCari, fileNIK;
    string filePass, newPass;
    bool ditemukan = false;
    cout << "\n=== LUPA PASSWORD ===\nMasukkan NIK : "; cin >> nikCari;

    ifstream baca("Akun.txt");
    ofstream temp("Temp.txt");
    while (baca >> fileNIK >> filePass) {
        if (fileNIK == nikCari) {
            ditemukan = true;
            do {
                cout << "Password Baru: "; cin >> newPass;
            } while (!validPassword(newPass));
            temp << fileNIK << " " << newPass << endl;
        } else temp << fileNIK << " " << filePass << endl;
    }
    baca.close(); temp.close();
    remove("Akun.txt"); rename("Temp.txt", "Akun.txt");

    if (ditemukan) cout << ">> Password diperbarui!\n";
    else cout << ">> NIK tidak ditemukan!\n";
}

void hapusAkun() {
    long long nikHapus, fileNIK;
    string passKonf, filePass;
    bool ditemukan = false;
    cout << "\n=== HAPUS AKUN ===\nNIK: "; cin >> nikHapus;
    cout << "Password: "; cin >> passKonf;

    ifstream baca("Akun.txt");
    ofstream temp("Temp.txt");
    while (baca >> fileNIK >> filePass) {
        if (fileNIK == nikHapus && filePass == passKonf) { ditemukan = true; continue; }
        temp << fileNIK << " " << filePass << endl;
    }
    baca.close(); temp.close();
    remove("Akun.txt"); rename("Temp.txt", "Akun.txt");

    if (ditemukan) cout << ">> Akun berhasil dihapus!\n";
    else cout << ">> Gagal hapus akun. NIK/Password salah!\n";
}

inline void muatDatabaseKTP(ArrayKTP &arr) {
    ifstream file("data_ktp.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line.length() > 3 && line[0] == 'N' && line[1] == 'I' && line[2] == 'K') {
            KTP x;
            x.nik = stoll(pecahNilai(line));
            getline(file, line); x.nama = pecahNilai(line);
            getline(file, line); x.tempat_lahir = pecahNilai(line);
            
            // Baca Tanggal & Hitung Umur
            getline(file, line);
            string tglStr = pecahNilai(line);
            int d, m, y;
            sscanf(tglStr.c_str(), "%d-%d-%d", &d, &m, &y);
            x.tgl_lahir.hari = d; x.tgl_lahir.bulan = m; x.tgl_lahir.tahun = y;
            x.umur = 2026 - y; // Hitung Umur Otomatis untuk Antrean

            getline(file, line); x.jenis_kelamin = (pecahNilai(line) == "Laki-laki");
            getline(file, line); x.gol_darah = pecahNilai(line);
            getline(file, line); x.alamat = pecahNilai(line);
            
            // Baca RT dan RW (Dua baris terpisah sesuai fungsi simpan di atas)
            getline(file, line); x.rt = stoi(pecahNilai(line));
            getline(file, line); x.rw = stoi(pecahNilai(line));

            getline(file, line); x.kel_desa = pecahNilai(line);
            getline(file, line); x.kecamatan = pecahNilai(line);
            
            // Ambil Teks Agama, lalu ubah jadi Angka (Agar RAM mengenali 1-6)
            getline(file, line); string agm = pecahNilai(line);
            if(agm == "Islam") x.agama = 1; 
            else if(agm == "Kristen") x.agama = 2;
            else if(agm == "Katolik") x.agama = 3;
            else if(agm == "Hindu") x.agama = 4;
            else if(agm == "Budha") x.agama = 5;
            else if(agm == "Konghucu") x.agama = 6;
            else x.agama = 0;

            getline(file, line); x.status_perkawinan = (pecahNilai(line) == "Kawin");
            getline(file, line); x.pekerjaan = pecahNilai(line);
            getline(file, line); x.kewarganegaraan = (pecahNilai(line) == "WNI");
            
            // Ambil Teks Berlaku, lalu ubah jadi Angka
            getline(file, line); string ber = pecahNilai(line);
            if(ber == "Sementara") x.berlaku_hingga = 1;
            else if(ber == "5 Tahun") x.berlaku_hingga = 2;
            else if(ber == "Selamanya") x.berlaku_hingga = 3;
            
            arr.insert(x);
            getline(file, line); // Membaca pembatas "======"
        }
    }
    file.close();
}

// =====================================================
// 9. TAMPILAN PROFIL (USER & ADMIN)
// =====================================================

// Fungsi untuk User melihat datanya sendiri
void tampilkanProfilPribadi(long long nik, ArrayKTP &database) {
    KTP* data = database.cariByNIK(nik);
    
    if (data != NULL) {
        // Hitung umur secara real-time jika belum dihitung saat muat file
        data->umur = 2026 - data->tgl_lahir.tahun;

        cout << "\n========================================";
        cout << "\n           PROFIL KTP ANGGOTA           ";
        cout << "\n========================================";
        cout << "\nNIK               : " << data->nik;
        cout << "\nNama              : " << data->nama;
        cout << "\nUmur              : " << data->umur << " Tahun"; // Menampilkan umur untuk prioritas
        cout << "\nTempat/Tgl Lahir  : " << data->tempat_lahir << ", " 
             << data->tgl_lahir.hari << "-" << data->tgl_lahir.bulan << "-" << data->tgl_lahir.tahun;
        cout << "\nJenis Kelamin     : " << (data->jenis_kelamin ? "Laki-laki" : "Perempuan");
        cout << "\nGolongan Darah    : " << data->gol_darah;
        cout << "\nAlamat            : " << data->alamat;
        cout << "\nRT/RW             : " << data->rt << "/" << data->rw;
        cout << "\nKelurahan/Desa    : " << data->kel_desa;
        cout << "\nKecamatan         : " << data->kecamatan;
        cout << "\nWilayah (NIK)     : " << getDaerahByNIK(data->nik);
        cout << "\nAgama             : " << teksAgama(data->agama);
        cout << "\nStatus Perkawinan : " << (data->status_perkawinan ? "Belum Kawin" : "Sudah Kawin");
        cout << "\nPekerjaan         : " << data->pekerjaan;
        cout << "\nKewarganegaraan   : " << (data->kewarganegaraan ? "WNI" : "WNA");
        cout << "\nBerlaku Hingga    : " << teksBerlaku(data->berlaku_hingga);
        cout << "\n========================================\n";
    } else {
        cout << "\n>> Data profil tidak ditemukan di database KTP!\n";
    }
}

// Fungsi untuk Admin melihat SEMUA anggota
void tampilkanSemuaAnggota(ArrayKTP &database) {
    // PERBAIKAN: Ganti database.size menjadi database.getJumlah()
    if (database.getJumlah() == 0) { 
        cout << "\n>> Belum ada anggota yang terdaftar di database KTP.\n";
        return;
    }

    cout << "\n======================================================\n";
    cout << "                DAFTAR SELURUH ANGGOTA                \n";
    cout << "======================================================\n";
    cout << "No | NIK              | Nama                | Wilayah \n";
    cout << "------------------------------------------------------\n";
    
    // Perulangan menggunakan fungsi getJumlah()
    for (int i = 0; i < database.getJumlah(); i++) {
        // Mengambil data melalui fungsi getKTP()
        KTP x = database.getKTP(i); 
        
        cout << (i + 1) << "  | " 
             << x.nik << " | " 
             << (x.nama.length() > 15 ? x.nama.substr(0, 12) + "..." : x.nama);
             
        // Tabulasi manual agar tampilan rapi
        for(int s=0; s < (int)(18 - x.nama.length()); s++) cout << " ";
        
        cout << "| " << getDaerahByNIK(x.nik) << endl;
    }
    cout << "------------------------------------------------------\n";
    cout << "Total: " << database.getJumlah() << " Orang\n";
}

#endif