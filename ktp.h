#ifndef KTP_H
#define KTP_H

#include <iostream>
#include <string>
using namespace std;

struct Tanggal {
    int hari, bulan, tahun;
};

struct KTP {
    long long nik;
    string nama;
    string tempat_lahir;
    Tanggal tgl_lahir;
    bool jenis_kelamin;        // true = laki-laki
    string gol_darah;
    string alamat;
    int rt, rw;
    string kel_desa;
    string kecamatan;
    int agama;
    bool status_perkawinan;    // true = sudah kawin
    string pekerjaan;
    bool kewarganegaraan;      // true = WNI
    int berlaku_hingga;
    int umur;
};

// Fungsi bantuan untuk mengubah angka Agama menjadi Teks
inline string teksAgama(int a) {
    switch(a) {
        case 1: return "Islam";
        case 2: return "Kristen";
        case 3: return "Katolik";
        case 4: return "Hindu";
        case 5: return "Budha";
        case 6: return "Konghucu";
        default: return "Tidak Diketahui";
    }
}

// Fungsi bantuan untuk mengubah angka Berlaku menjadi Teks
inline string teksBerlaku(int b) {
    switch(b) {
        case 1: return "Sementara";
        case 2: return "5 Tahun";
        case 3: return "Selamanya";
        default: return "Tidak Diketahui";
    }
}

// Overload operator agar "cout << ktp" menampilkan SEMUA data
inline ostream& operator<<(ostream& os, const KTP& k) {
    os << "\nNIK               : " << k.nik
       << "\nNama              : " << k.nama
       << "\nTempat Lahir      : " << k.tempat_lahir
       << "\nTanggal Lahir     : " << k.tgl_lahir.hari << "-" << k.tgl_lahir.bulan << "-" << k.tgl_lahir.tahun
       << "\nJenis Kelamin     : " << (k.jenis_kelamin ? "Laki-laki" : "Perempuan")
       << "\nGolongan Darah    : " << k.gol_darah
       << "\nAlamat            : " << k.alamat
       << "\nRT/RW             : " << k.rt << "/" << k.rw
       << "\nKelurahan/Desa    : " << k.kel_desa
       << "\nKecamatan         : " << k.kecamatan
       << "\nAgama             : " << teksAgama(k.agama)
       << "\nStatus Perkawinan : " << (k.status_perkawinan ? "Belum Kawin" : "Sudah Kawin")
       << "\nPekerjaan         : " << k.pekerjaan
       << "\nKewarganegaraan   : " << (k.kewarganegaraan ? "WNI" : "WNA")
       << "\nBerlaku Hingga    : " << teksBerlaku(k.berlaku_hingga)
       << "\n-----------------------------------";
    return os;
}
#endif
