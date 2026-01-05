#ifndef PERPUS_H
#define PERPUS_H

#include <iostream>
#include <fstream>
#include <string>
#include "array1d.h" 
#include "bukuLinklist.h"
#include "ktp.h"
#include "bstbuku.h" 

using namespace std;

class Perpus {
public:
    BSTBuku<Buku> treeBuku; // Tree untuk pencarian O(log n)
    Array1D<Buku> buku;
    int jumlah_buku;
    Tanggal hari_ini;

    Perpus(); 
    Buku* getBukuById(int id);
    void isi_data_buku();
    void muat_data_buku();
    void tampil_buku();
    void cari_buku();
    void cari_buku_id();
    void muat_tanggal();
    void simpan_tanggal();
    void tambah_hari();
    bool is_kabisat(int tahun);
    int jumlah_hari_bulan(int bulan, int tahun);
    void tampilkan_tanggal();
    void tambah_ke_array(Buku x);
    void gabung_data_dari_file(string namaFile);
    void simpan_semua_data(string namaFile);
    void urut_buku_id();
    void tampil_buku_berdasarkan_genre();
};

#endif