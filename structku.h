#ifndef STRUCTKU_H
#define STRUCTKU_H

#include<iostream>
using namespace std;

// ==========================
//  STRUCT BUKU
// ==========================
struct Buku {
    string nama_buku;
    int id_buku;
    string genre_buku;
    string penulis;
};

// =================================
// Struktur node queue
// =================================
struct Peminjaman {
    string nama;
    string judulBuku;
    int id_buku;
    int lamaPinjam;
    string username;
    string tanggal_pinjam;
    string waktu_pinjam;
    string status;
    int umur;
};

// Overload operator << agar fungsi display() generik bisa mencetak data Peminjaman
inline ostream& operator<<(ostream& os, const Peminjaman& p) {
    os << p.nama << " | Buku: " << p.judulBuku << " | " << p.lamaPinjam << " hari";
    return os;
}

// =================================
// Struktur node stack pengembalian
// =================================
struct Pengembalian {
    string nama;
    string judulBuku;
    int lamaPinjam;
    int hariTerlambat;
    long long denda;
    string metodeBayar;
    string bank;
};

// Overload agar Stack::display bekerja
inline ostream& operator<<(ostream& os, const Pengembalian& p) {
    os << p.nama << " | Buku: " << p.judulBuku << " | Denda: Rp " << p.denda 
       << " (" << p.hariTerlambat << " hari)";
    return os;
}
#endif