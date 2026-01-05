#ifndef PEMINJAMAN_H
#define PEMINJAMAN_H

#include "queue_generic.h" // Memanggil Queue Generik
#include "stack_generic.h"
#include "bukuLinklist.h"
#include "perpus.h"
#include "history.h"
#include "login.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// Objek Global
extern Queue<Peminjaman> antrianPeminjaman; // Menggunakan Queue Generik
extern Stack<Pengembalian> stackPengembalian;
extern HistoryManager hm; // TAMBAHKAN INI (Asumsi nama class di history.h adalah HistoryManager)
extern ArrayKTP databaseKTP;

// =================================
// Fitur Struk Peminjaman
// =================================
void simpanStruk(Peminjaman p) {
    ofstream file("struk_peminjaman.txt", ios::app);
    if (!file.is_open()) return;

    file << "========================================\n";
    file << "        STRUK PEMINJAMAN BUKU\n";
    file << "        PERPUSTAKAAN DEALPIS\n";
    file << "========================================\n";
    file << "Tanggal Pinjam : " << p.tanggal_pinjam << "\n";
    file << "Waktu          : " << p.waktu_pinjam << "\n";
    file << "----------------------------------------\n";
    file << "Nama Anggota   : " << p.nama << "\n";
    file << "Umur (Prioritas): " << p.umur << " Tahun\n"; // <-- Tambahan
    file << "ID Buku        : " << p.id_buku << "\n";
    file << "Judul Buku     : " << p.judulBuku << "\n";
    file << "Lama Pinjam    : " << p.lamaPinjam << " Hari\n";
    file << "----------------------------------------\n";
    file << "Status         : " << p.status << "\n";
    file << "========================================\n\n";
    file.close();
}

void cetakStruk(Peminjaman p) {
    cout << "\n========================================";
    cout << "\n        STRUK PEMINJAMAN BUKU";
    cout << "\n        PERPUSTAKAAN DEALPIS";
    cout << "\n========================================";
    cout << "\nTanggal Pinjam : " << p.tanggal_pinjam;
    cout << "\nWaktu          : " << p.waktu_pinjam;
    cout << "\n----------------------------------------";
    cout << "\nNama Anggota   : " << p.nama;
    cout << "\nUmur           : " << p.umur << " Tahun"; // <-- Tambahan
    cout << "\nID Buku        : " << p.id_buku;
    cout << "\nJudul Buku     : " << p.judulBuku;
    cout << "\nLama Pinjam    : " << p.lamaPinjam << " Hari";
    cout << "\n----------------------------------------";
    cout << "\nStatus         : " << p.status;
    cout << "\n========================================\n";
}

// =================================
// Fitur Struk Pengembalian
// =================================
void cetakStrukPengembalian(Pengembalian p) {
    cout << "\n========================================";
    cout << "\n      STRUK PENGEMBALIAN BUKU";
    cout << "\n       PERPUSTAKAAN DEALPIS";
    cout << "\n========================================";
    cout << "\nNama Peminjam   : " << p.nama;
    cout << "\nJudul Buku      : " << p.judulBuku;
    cout << "\n----------------------------------------";
    cout << "\nLama Dipinjam   : " << p.lamaPinjam << " Hari";
    cout << "\nHari Terlambat  : " << p.hariTerlambat << " Hari";
    cout << "\nDenda           : Rp " << p.denda;
    cout << "\nMetode Bayar    : " << p.metodeBayar << endl;
		if (p.metodeBayar == "Transfer")
    cout << "\nBank Tujuan     : " << p.bank << endl;
    cout << "\n----------------------------------------";
    cout << "\nStatus          : DIKEMBALIKAN";
    cout << "\n========================================\n";
}

void simpanStrukPengembalian(Pengembalian p) {
    ofstream file("struk_pengembalian.txt", ios::app);
    if (!file.is_open()) return;

    file << "========================================\n";
    file << "      STRUK PENGEMBALIAN BUKU\n";
    file << "       PERPUSTAKAAN DEALPIS\n";
    file << "========================================\n";
    file << "Nama Peminjam   : " << p.nama << "\n";
    file << "Judul Buku      : " << p.judulBuku << "\n";
    file << "----------------------------------------\n";
    file << "Lama Dipinjam   : " << p.lamaPinjam << " Hari\n";
    file << "Hari Terlambat  : " << p.hariTerlambat << " Hari\n";
    file << "Denda           : Rp " << p.denda << "\n";
    file << "Metode Bayar    : " << p.metodeBayar << "\n";
		if (p.metodeBayar == "Transfer")
    file << "Bank Tujuan     : " << p.bank << "\n";
    file << "----------------------------------------\n";
    file << "Status          : DIKEMBALIKAN\n";
    file << "========================================\n\n";
    file.close();
}


// =================================
// USER: Tambah peminjaman (enqueue)
// Logika Transaksi
// =================================
void userPinjamBuku(const string& currentUsername, Perpus &db) {
    int idCari;
    cout << "\n=== PINJAM BUKU ===\nMasukkan ID Buku: ";
    cin >> idCari;

    //Buku* b = db.getBukuById(idCari); 
    Buku* b = db.treeBuku.searchById(db.treeBuku.root, idCari);
    if (b == NULL) {
        cout << "ID Buku tidak terdaftar di sistem Tree!\n";
        return;
    }
    
    Peminjaman baru;
    
    // AMBIL DATA UMUR DARI KTP
    long long nikUser = stoll(currentUsername);
    KTP* dataKtp = databaseKTP.cariByNIK(nikUser);
    
    if (dataKtp != NULL) {
        // Hitung umur: Tahun sekarang - Tahun lahir
        baru.umur = 2026 - dataKtp->tgl_lahir.tahun;
    } else {
        baru.umur = 0; // Default jika data tidak ada
    }
    
    baru.nama = currentUsername;
    baru.username = currentUsername;
    baru.id_buku = b->id_buku;
    baru.judulBuku = b->nama_buku;
    
    cout << "Buku ditemukan : " << b->nama_buku << endl;
    cout << "Lama Pinjam(hari): "; cin >> baru.lamaPinjam;

    // Set Waktu Otomatis
    time_t now = time(0);
    tm* ltm = localtime(&now);
    baru.tanggal_pinjam = to_string(ltm->tm_mday) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(1900 + ltm->tm_year);
    baru.waktu_pinjam = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min);
    baru.status = "DIPINJAM";

    antrianPeminjaman.enqueue(baru);

    // Simpan ke History ADT (Linked List)
    History h = {baru.username, baru.judulBuku, baru.id_buku, baru.lamaPinjam};
    hm.addHistory(h); 
	
	antrianPeminjaman.enqueue(baru);
    cetakStruk(baru);
    simpanStruk(baru);
    cout << ">> Berhasil dicatat dalam riwayat.\n";
}

// =================================
// ADMIN: Lihat data peminjaman
// =================================
void adminLihatData() {
    cout << "\n=== DATA PEMINJAMAN (QUEUE) ===\n";
    if (antrianPeminjaman.isEmpty()) {
        cout << ">> Tidak ada data peminjaman di antrian.\n";
    } else {
        antrianPeminjaman.display();
    }

    // ==============================
    // TAMBAHAN: LIHAT FILE STRUK TXT
    // ==============================
    ifstream file("struk_peminjaman.txt");
    if (!file.is_open()) {
        cout << "\n>> File struk_peminjaman.txt belum ada.\n";
        return;
    }

    cout << "\n=== RIWAYAT STRUK PEMINJAMAN (FILE TXT) ===\n";
    string baris;
    while (getline(file, baris)) {
        cout << baris << endl;
    }
    file.close();
}

// =================================
// ADMIN: Proses peminjaman (dequeue)
// =================================
void adminProsesPeminjaman() {
    if (antrianPeminjaman.isEmpty()) {
        cout << ">> Antrian peminjaman kosong.\n";
        return;
    }

    // Ambil data terdepan dari queue
    Peminjaman dataDepan = antrianPeminjaman.getFront();

    cout << "\n=== PEMINJAMAN DIPROSES (QUEUE) ===\n";
    cout << "Nama       : " << dataDepan.nama << endl;
    cout << "Judul Buku : " << dataDepan.judulBuku << endl;

    // ==============================
    // TAMPILKAN STRUK DARI FILE TXT
    // ==============================
    ifstream file("struk_peminjaman.txt");
    if (!file.is_open()) {
        cout << "\n>> File struk_peminjaman.txt tidak ditemukan.\n";
    } else {
        cout << "\n=== STRUK PEMINJAMAN (FILE TXT) ===\n";
        string baris;
        while (getline(file, baris)) {
            cout << baris << endl;
        }
        file.close();
    }

    // Hapus data dari queue
    antrianPeminjaman.dequeue();

    cout << "\n>> Peminjaman selesai diproses.\n";
}

// =================================
// ADMIN: Lihat Histori Peminjaman
// =================================
void adminLihatHistori() {
    string usernameCari;
    cout << "\n=== LIHAT RIWAYAT PEMINJAMAN ===\n";
    cout << "Masukkan Username Peminjam : ";
    //hapusBuffer(); 
    cin >> usernameCari;

    hm.viewHistory(usernameCari);
}

// =================================
// PILIH METODE TRANSFER PAMBAYARAN
// =================================
string pilihBankTransfer() {
    int pilih;
    cout << "\n=== PILIH BANK TRANSFER ===\n";
    cout << "1. BRI\n";
    cout << "2. BNI\n";
    cout << "3. Mandiri\n";
    cout << "4. BCA\n";
    cout << "5. BSI\n";
    cout << "Pilih bank: ";
    cin >> pilih;

    switch (pilih) {
        case 1: return "BRI";
        case 2: return "BNI";
        case 3: return "Mandiri";
        case 4: return "BCA";
        case 5: return "BSI";
        default:
            cout << "Pilihan tidak valid, default BRI.\n";
            return "BRI";
    }
}


// =================================
// PILIH METODE PAMBAYARAN
// =================================
string pilihMetodePembayaran(string &bank) {
    int pilih;
    cout << "\n=== METODE PEMBAYARAN DENDA ===\n";
    cout << "1. Tunai\n";
    cout << "2. QRIS\n";
    cout << "3. Transfer\n";
    cout << "Pilih metode pembayaran: ";
    cin >> pilih;

    bank = "-";

    switch (pilih) {
        case 1:
            return "Tunai";
        case 2:
            return "QRIS";
        case 3:
            bank = pilihBankTransfer(); // 🔥 submenu bank
            return "Transfer";
        default:
            cout << "Pilihan tidak valid, default Tunai.\n";
            return "Tunai";
    }
}


// =================================
// USER: Kembalikan buku (PUSH ke Stack Manual)
// =================================
void userKembalikanBuku(const string& currentUsername) {
    int idCari;
    cout << "\n=== PENGEMBALIAN ===\nMasukkan ID Buku yang dikembalikan: ";
    cin >> idCari;

    History* loan = hm.findLastLoan(currentUsername, idCari);
    if (loan == NULL) {
        cout << "Data peminjaman tidak ditemukan di riwayat Anda!\n";
        return;
    }

    Pengembalian baru;
    baru.nama = currentUsername;
    baru.judulBuku = loan->judulBuku;

    int hariNyata;
    cout << "Buku: " << loan->judulBuku << endl;
    cout << "Total hari Anda meminjam: ";
    cin >> hariNyata;

    baru.lamaPinjam = hariNyata;

    // =====================
    // HITUNG DENDA
    // =====================
    if (hariNyata > loan->lamaPinjam) {
        baru.hariTerlambat = hariNyata - loan->lamaPinjam;
        baru.denda = (long long)baru.hariTerlambat * 2000;
    } else {
        baru.hariTerlambat = 0;
        baru.denda = 0;
    }

    // =====================
    // PEMBAYARAN
    // =====================
    if (baru.denda > 0) {
        cout << "\nAnda terlambat " << baru.hariTerlambat << " hari\n";
        cout << "Total denda : Rp " << baru.denda << endl;
        baru.metodeBayar = pilihMetodePembayaran(baru.bank);
    } else {
        baru.metodeBayar = "Tidak Ada Denda";
        baru.bank = "-";
    }

    // =====================
    // SIMPAN & CETAK
    // =====================
    stackPengembalian.push(baru);
    cetakStrukPengembalian(baru);
    simpanStrukPengembalian(baru);

    cout << ">> Buku berhasil dikembalikan.\n";
}


// =================================
// ADMIN: Lihat data pengembalian
// =================================
void adminLihatPengembalian() {
    cout << "\n=== DATA PENGEMBALIAN (STACK GENERIK) ===\n";

    // ==========================
    // TAMPILKAN DATA DARI STACK
    // ==========================
    if (stackPengembalian.isEmpty()) {
        cout << ">> Tidak ada data pengembalian di stack.\n";
    } else {
        stackPengembalian.display();
    }

    // ==========================
    // TAMPILKAN STRUK DARI FILE
    // ==========================
    ifstream file("struk_pengembalian.txt");
    if (!file.is_open()) {
        cout << "\n>> File struk_pengembalian.txt belum tersedia.\n";
        return;
    }

    cout << "\n=== RIWAYAT STRUK PENGEMBALIAN (FILE TXT) ===\n";
    string baris;
    while (getline(file, baris)) {
        cout << baris << endl;
    }
    file.close();
}


// =================================
// ADMIN: Proses pengembalian (POP)
// =================================
void adminProsesPengembalian() {
    if (stackPengembalian.isEmpty()) {
        cout << ">> Stack pengembalian kosong.\n";
        return;
    }

    Pengembalian hapus = stackPengembalian.peek();

    cout << "\n=== PENGEMBALIAN DIPROSES ===\n";
    cout << "Nama       : " << hapus.nama << endl;
    cout << "Judul Buku : " << hapus.judulBuku << endl;

    // Tampilkan arsip struk
    ifstream file("struk_pengembalian.txt");
    if (file.is_open()) {
        string baris;
        cout << "\n=== ARSIP STRUK PENGEMBALIAN ===\n";
        while (getline(file, baris)) {
            cout << baris << endl;
        }
        file.close();
    }

    stackPengembalian.pop(hapus);
    cout << ">> Pengembalian selesai diproses.\n";
}

//==================================
//UNTUK INPUT DATA BUKU DI ADMIN
//==================================
Buku inputData() {
    Buku x;

    cout << "\n==== INPUT DATA BUKU ====\n";

    cin.ignore(); // aman jika sebelumnya ada cin >>

    cout << "Masukkan Nama Buku : ";
    getline(cin, x.nama_buku);

    cout << "Masukkan ID Buku   : ";
    cin >> x.id_buku;
    cin.ignore();

    cout << "Masukkan Genre    : ";
    getline(cin, x.genre_buku);

    cout << "Masukkan Penulis  : ";
    getline(cin, x.penulis);

    return x;
}

//==================================
//ADMIN INPUT BUKU MASUK KE TXT
//==================================
void simpanKeTxt(Buku x) {
    ofstream file("data_buku.txt", ios::app);
    if (file.is_open()) {
        file << x.id_buku << ";"
             << x.nama_buku << ";"
             << x.genre_buku << ";"
             << x.penulis << endl;
        file.close();
    }
}


void tampilMenuGenre() {
    cout << "\n=== PILIH GENRE BUKU ===\n";
    cout << "1. Fiksi\n";
    cout << "2. Romance\n";
    cout << "3. Drama\n";
    cout << "4. Komedi\n";
    cout << "5. Remaja\n";
    cout << "6. Pendidikan\n";
    cout << "7. Non Fiksi\n";
    cout << "8. Sejarah\n";
    cout << "9. Religi\n";
    cout << "10. Mental Health\n";
    cout << "11. Horor\n";
    cout << "12. Keluarga\n";
    cout << "13. Semua Buku\n";
    cout << "Pilih Genre: ";
}


void tampil_buku_berdasarkan_genre(int pilih,Perpus &p) {
    string keyword;
    bool ketemu = false;

    // Tentukan keyword berdasarkan pilihan user
    switch (pilih) {
        case 1: keyword = "Fantasi"; break;
        case 2: keyword = "Romantis"; break;
        case 3: keyword = "Drama"; break;
        case 4: keyword = "Komedi"; break;
        case 5: keyword = "Remaja"; break;
        case 6: keyword = "Pendidikan"; break;
        case 7: keyword = "Non Fiksi"; break;
        case 8: keyword = "Sejarah"; break;
        case 9: keyword = "Religi"; break;
        case 10: keyword = "Mental Health"; break;
        case 11: keyword = "Horor"; break;
        case 12: keyword = "Keluarga"; break;
        case 13: keyword = ""; break; // tampilkan semua
        default:
            cout << "Pilihan genre tidak valid!\n";
            return;
    }

    cout << "\n=============================================\n";
    cout << "        DAFTAR BUKU GENRE: " << (keyword == "" ? "SEMUA" : keyword) << "\n";
    cout << "=============================================\n";

    for (int i = 0; i < p.jumlah_buku; i++) {
        // Jika pilih semua ATAU genre mengandung keyword
        if (pilih == 13 || p.buku[i].genre_buku.find(keyword) != string::npos || 
            (pilih == 2 && p.buku[i].genre_buku.find("Romance") != string::npos)) {

            cout << "Judul   : " << p.buku[i].nama_buku << endl;
            cout << "ID      : " << p.buku[i].id_buku << endl;
            cout << "Genre   : " << p.buku[i].genre_buku << endl;
            cout << "Penulis : " << p.buku[i].penulis << endl;
            cout << "---------------------------------------------\n";

            ketemu = true;
        }
    }

    if (!ketemu) {
        cout << "Tidak ada buku pada genre ini.\n";
    }
}

//==================================
//CARI BUKU BERDASARKAN JUDUL TREE
//==================================
// Fungsi UI: Cari Berdasarkan Nama menggunakan Tree
void UI_CariBukuNama(Perpus &db) {
    string judul;
    cout << "\n=== CARI BUKU (TREE BY NAME) ===\n";
    cout << "Masukkan Judul/Keyword Buku: ";
    cin.ignore();
    getline(cin, judul);

    bool ketemu = false;
    db.treeBuku.searchByTitle(db.treeBuku.root, judul, ketemu);

    if (!ketemu) cout << "Buku tidak ditemukan.\n";
}

//==================================
//CARI BUKU BERDASARKAN ID BUKU TREE
//==================================
// Fungsi UI: Cari Berdasarkan ID menggunakan Tree
void UI_CariBukuId(Perpus &db) {
    int idCari;
    cout << "\n=== CARI BUKU (TREE BY ID) ===\n";
    cout << "Masukkan ID Buku: ";
    cin >> idCari;

    Buku* b = db.getBukuById(idCari);
    if (b != NULL) {
        cout << "Buku Ketemu: " << b->nama_buku << " | Penulis: " << b->penulis << endl;
    } else {
        cout << "ID " << idCari << " tidak ditemukan di Tree.\n";
    }
}

// =================================
// LAPORAN PEMINJAMAN + DENDA
// =================================
long long toTimestamp(string tanggal, string waktu) {
    int d, m, y, h, min;
    sscanf(tanggal.c_str(), "%d-%d-%d", &d, &m, &y);
    sscanf(waktu.c_str(), "%d:%d", &h, &min);

    return (long long)y * 100000000 +
           (long long)m * 1000000 +
           (long long)d * 10000 +
           (long long)h * 100 +
           min;
}

void adminLaporanRentangWaktu() {
    string tglAwal, jamAwal, tglAkhir, jamAkhir;

    cout << "\n=== LAPORAN RENTANG WAKTU ===\n";
    cout << "Tanggal awal (dd-mm-yyyy): ";
    cin >> tglAwal;
    cout << "Jam awal (hh:mm): ";
    cin >> jamAwal;

    cout << "Tanggal akhir (dd-mm-yyyy): ";
    cin >> tglAkhir;
    cout << "Jam akhir (hh:mm): ";
    cin >> jamAkhir;

    long long start = toTimestamp(tglAwal, jamAwal);
    long long end   = toTimestamp(tglAkhir, jamAkhir);

    ifstream pinjam("struk_peminjaman.txt");
    ifstream kembali("struk_pengembalian.txt");

    if (!pinjam.is_open() || !kembali.is_open()) {
        cout << "File data tidak ditemukan!\n";
        return;
    }

    string line, tanggal, waktu;
    int totalPeminjaman = 0;
    long long totalDenda = 0;

    // =====================
    // BACA PEMINJAMAN
    // =====================
    while (getline(pinjam, line)) {
        if (line.find("Tanggal Pinjam") != string::npos)
            tanggal = line.substr(line.find(":") + 2);

        if (line.find("Waktu") != string::npos) {
            waktu = line.substr(line.find(":") + 2);
            long long ts = toTimestamp(tanggal, waktu);
            if (ts >= start && ts <= end)
                totalPeminjaman++;
        }
    }

    // =====================
    // BACA DENDA
    // =====================
    while (getline(kembali, line)) {
        if (line.find("Denda") != string::npos) {
            long long d;
            sscanf(line.c_str(), "Denda           : Rp %lld", &d);
            totalDenda += d;
        }
    }

    pinjam.close();
    kembali.close();

    // =====================
    // OUTPUT KE LAYAR
    // =====================
    cout << "\n========================================\n";
    cout << " 	LAPORAN TRANSAKSI PERPUSTAKAAN\n";
    cout << "========================================\n";
    cout << "Periode : " << tglAwal << " " << jamAwal
         << " s/d " << tglAkhir << " " << jamAkhir << endl;
    cout << "----------------------------------------\n";
    cout << "Total Peminjaman : " << totalPeminjaman << " orang\n";
    cout << "Total Denda      : Rp " << totalDenda << endl;
    cout << "========================================\n";

    // =====================
    // SIMPAN KE FILE TXT
    // =====================
    ofstream file("laporan_admin.txt",ios::app);
    if (!file) {
        cout << "\nGAGAL membuat file laporan_admin.txt\n";
        return;
    }

	file << "\n========================================\n";
    file << " 	LAPORAN PERPUSTAKAAN\n";
    file << "========================================\n";
    file << "Periode : " << tglAwal << " " << jamAwal
            << " s/d " << tglAkhir << " " << jamAkhir << endl;
    file << "----------------------------------------\n";
    file << "Total Peminjaman : " << totalPeminjaman << endl;
    file << "Total Denda      : Rp " << totalDenda << endl;
    file << "========================================\n\n";

    file.close();
}

// =================================
// Menu USER
// =================================
void menuUser(const string& currentUsername, Perpus &db) {
	Perpus uad;
	long long nikUser = stoll(currentUsername);
    int pilih;
    do {
        cout << "\n===================================\n";
        cout << "             MENU USER              \n";
        cout << "=====================================\n";
        cout << "1. Tampilkan Semua Buku        \n";
        cout << "2. Cari Buku Berdasarkan Nama  \n";
        cout << "3. Cari Buku Berdasarkan ID    \n";
		cout << "4. Pinjam Buku  \n";
		cout << "5. Kembalikan Buku    \n";
        cout << "6. Lihat Profil Saya\n";
        cout << "7. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
        	case 1:
        		int genre;
    			tampilMenuGenre();      // panggil langsung
    			cin >> genre;
    			tampil_buku_berdasarkan_genre(genre,uad);
    			break;
        	case 2:
        		//uad.cari_buku();
				UI_CariBukuNama(db);
				break;
			case 3:
				UI_CariBukuId(db);
				break;
			case 4:
				userPinjamBuku(currentUsername, uad);
        		break;
			case 5:
				userKembalikanBuku(currentUsername);
				break;
			case 6:
				tampilkanProfilPribadi(nikUser, databaseKTP); // Memanggil fungsi profil
			    system("pause");
			    break;
			case 7:
				cout << "\nTerimakasih telah menggunakan sistem perpustakaan\n";
				break;
			default:
				cout << "tidakk valid";
				break;
		}
				
    } while (pilih != 7);
}

// =================================
// Menu ADMIN
// =================================
void menuAdmin() {
    int pilih;
    DoublyLinkedListBuku list;
    list.bacaDariFile("data_buku.txt");
    do {
        cout << "\n====================================\n";
        cout << "             MENU ADMIN\n";
        cout << "====================================\n";
        cout << "1.  Lihat Data Peminjaman\n";
        cout << "2.  Proses Peminjaman\n";
        cout << "3.  Lihat Histori (berdasarkan Username)\n"; 
        cout << "4.  Lihat Pengembalian\n";
        cout << "5.  Proses Pengembalian\n";
        cout << "6.  Input Data Buku Baru\n";
        cout << "7.  Tampilkan Buku Linked List Depan\n";
        cout << "8.  Tampilkan Buku Linked List Belakang\n";
        cout << "9.  Lihat Semua Anggota\n";
        cout << "10. Laporan Denda dan Peminjaman\n";
        cout << "11. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                adminLihatData();
                break;
            case 2:
                adminProsesPeminjaman();
                break;
            case 3:
            	adminLihatHistori();
            	break;
            case 4:
            	adminLihatPengembalian();
            	break;
            case 5:
            	adminProsesPengembalian();
            	break;
            case 6:{
            	Buku x = inputData();   // input
                list.insert(x);         // masuk Linked List
                list.simpanKeFile("data_buku.txt"); // simpan ulang
                cout << "\nData berhasil disimpan!\n";
                break;
			}
			case 7:
				list.displayForward();
				break;
			case 8:
				list.displayBackward();
				break;
			case 9:
				tampilkanSemuaAnggota(databaseKTP); // Memanggil fungsi dari login.h
			    system("pause");
			    break;
			case 10:
				adminLaporanRentangWaktu();
				break;
			case 11:
				cout << "\nTerimakasih telah menggunakan sistem perpustakaan\n";
				break;
			default:
				cout << "tidakk valid";
				break;
        }
        
    } while (pilih != 11);
}

#endif
