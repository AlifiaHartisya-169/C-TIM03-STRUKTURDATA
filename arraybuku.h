#include "perpus.h"
#include "array1d.h" 
#include "structku.h"
#include "bukuLinklist.h"
#include <iostream>
#include <string>
using namespace std;

Perpus::Perpus() : buku(100) { 
    jumlah_buku = 0;
    treeBuku.root = NULL; // Inisialisasi root tree agar tidak error

    // 1. Isi data Hardcoded ke Array1D
    isi_data_buku(); 
    
    // 2. Gabungkan data dari file
    gabung_data_dari_file("data_buku_dll.txt"); 
    
    // 3. Urutkan data agar Binary Search bekerja
    urut_buku_id(); 
    
    // 4. Muat Tanggal
    muat_tanggal();
}

//-------------------- ISI DATA BUKU --------------------
void Perpus::isi_data_buku() {
	
	Buku dataAwal[] = {
	    {"Laskar Pelangi", 1001, "Drama", "Andrea Hirata"},
	    {"Bumi", 1002, "Fantasi", "Tere Liye"},
	    {"Bulan", 1003, "Fantasi", "Tere Liye"},
	    {"Matahari", 1004, "Fantasi", "Tere Liye"},
	    {"Bintang", 1005, "Fantasi", "Tere Liye"},
	    {"Komet", 1006, "Fantasi", "Tere Liye"},
	    {"Komet Minor", 1007, "Fantasi", "Tere Liye"},
	    {"Matahari Minor", 1008, "Fantasi", "Tere Liye"},
	    {"Selena", 1009, "Fantasi", "Tere Liye"},
	    {"Nebula", 1010, "Fantasi", "Tere Liye"},
	    {"Si Putih", 1011, "Fantasi", "Tere Liye"},
	    {"Hingga Lumpu", 1012, "Fantasi", "Tere Liye"},
	    {"Negeri 5 Menara", 1013, "Inspirasi", "Ahmad Fuadi"},
	    {"Dilan 1990", 1014, "Romance", "Pidi Baiq"},
	    {"Perahu Kertas", 1015, "Romance", "Dee Lestari"},
	    {"Filosofi Teras", 1016, "Filsafat", "Henry Manampiring"},
	    {"Ayat-Ayat Cinta", 1017, "Romantis", "Habiburrahman El Shirazy"},
	    {"Selamat Tinggal", 1018, "Relasi", "Tere Liye"},
	    {"Critical Eleven", 1019, "Drama", "Ika Natassa"},
	    {"Dear Nathan", 1020, "Remaja", "Erisca Febriani"},
	    {"Mariposa", 1021, "Romantis", "Luluk HF"},
	    {"Imperfect", 1022, "Komedi", "Meira Anastasia"},
	    {"Galaksi", 1023, "Remaja", "Poppi Pertiwi"},
	    {"Pintu Harmonika", 1024, "Keluarga", "Clara Ng"},
	    {"Koala Kumal", 1025, "Komedi", "Raditya Dika"},
	    {"Sang Pemimpi", 1026, "Pendidikan", "Andrea Hirata"},
	    {"Hujan", 1027, "Fiksi Ilmiah", "Tere Liye"},
	    {"Rectoverso", 1028, "Cinta", "Dee Lestari"},
	    {"Tentang Kamu", 1029, "Misteri", "Tere Liye"},
	    {"Sabtu Bersama Bapak", 1030, "Keluarga", "Adhitya Mulya"},
	    {"Cinta Brontosaurus", 1031, "Komedi", "Raditya Dika"},
	    {"The Little Prince", 1032, "Anak-anak", "Antoine de Saint-Exupéry"},
	    {"The Alchemist", 1033, "Filsafat", "Paulo Coelho"},
	    {"1984", 1034, "Dystopia", "George Orwell"},
	    {"Animal Farm", 1035, "Politik", "George Orwell"},
	    {"To Kill a Mockingbird", 1036, "Sosial", "Harper Lee"},
	    {"Pride and Prejudice", 1037, "Romantis", "Jane Austen"},
	    {"Looking for Alaska", 1038, "Remaja", "John Green"},
	    {"Paper Towns", 1039, "Remaja", "John Green"},
	    {"Daun yang Jatuh Tak Pernah Membenci Angin", 1040, "Drama", "Tere Liye"},
	    {"Negeri Para Bedebah", 1041, "Politik", "Tere Liye"},
	    {"Negeri di Ujung Tanduk", 1042, "Politik", "Tere Liye"},
	    {"Berjuta Rasanya", 1043, "Cinta", "Tere Liye"},
	    {"Filosofi Kopi", 1044, "Drama", "Dee Lestari"},
	    {"Balada Si Roy", 1045, "Remaja", "Gol A Gong"},
	    {"Ronggeng Dukuh Paruk", 1046, "Sosial", "Ahmad Tohari"},
	    {"Cantik Itu Luka", 1047, "Sejarah", "Eka Kurniawan"},
	    {"Lelaki Harimau", 1048, "Mitologi", "Eka Kurniawan"},
	    {"Laut dan Langit", 1049, "Romantis", "Dwitasari"},
	    {"Sebuah Seni untuk Bersikap Bodo Amat", 1050, "Non Fiksi", "Mark Manson"},
	    {"The Psychology of Money", 1051, "Non Fiksi", "Morgan Housel"},
	    {"Mimpi-Mimpi si Patah Hati", 1052, "Romance", "Tere Liye"},
	    {"Sendiri", 1053, "Non Fiksi", "Tere Liye"},
	    {"Tikungan Tajam", 1054, "Drama", "Okky Madasari"},
	    {"Ayah", 1055, "Keluarga", "Andrea Hirata"},
	    {"Hati Suhita", 1056, "Religi", "Khila Rindani"},
	    {"Cinta dalam Gelas", 1057, "Inspiratif", "Andrea Hirata"},
	    {"Surat Kecil untuk Tuhan", 1058, "Keluarga", "Agnes Davonar"},
	    {"Catatan Najwa", 1059, "Sosial Politik", "Najwa Shihab"},
	    {"Orang-Orang Biasa", 1060, "Sosial", "Andrea Hirata"},
	    {"Bumi Manusia", 1061, "Sejarah", "Pramoedya Ananta Toer"},
	    {"Anak Semua Bangsa", 1062, "Sejarah", "Pramoedya Ananta Toer"},
	    {"Jejak Langkah", 1063, "Sejarah", "Pramoedya Ananta Toer"},
	    {"Rumah Kaca", 1064, "Sejarah", "Pramoedya Ananta Toer"},
	    {"This Earth of Mankind", 1065, "Sejarah", "Pramoedya Ananta Toer"},
	    {"Sang Penari", 1066, "Budaya", "Ahmad Tohari"},
	    {"Manusia Setengah Salmon", 1067, "Komedi", "Raditya Dika"},
	    {"Jalan Pulang", 1068, "Fiksi", "Tere Liye"},
	    {"Cinta dalam Diam", 1069, "Religi", "Felix Siauw"},
	    {"Bidadari Bermata Bening", 1070, "Religi", "Habiburrahman El Shirazy"},
	    {"Atomic Habits", 1071, "Self-Help", "James Clear"},
	    {"La Tahzan", 1072, "Religi", "'Aidh Al-Qarni"},
	    {"Struktur Data dan Algoritma", 1073, "Pendidikan", "Abdul Kadir"},
	    {"Kisah 25 Nabi dan Rasul", 1074, "Religi, Pendidikan", "Tim Edukatif"},
	    {"Sherlock Holmes", 1075, "Detektif", "Sir Arthur Conan Doyle"},
	    {"Laut Bercerita", 1076, "Historical", "Leila S.Chudori"},
	    {"Step By Step Skripsimu", 1077, "Non Fiksi", "Ira Mirawati"},
	    {"Is It Bad or Good Habits", 1078, "Motivasi", "Sabrina Ara"},
	    {"Madilog", 1079, "Filsafat", "Tan Malaka"},
	    {"Slow Living", 1080, "Mental Health", "Sabrina Ara"},
	    {"The Power of Personality", 1081, "Mental Health", "Tara Damaya"},
	    {"Seporsi Mie Ayam Sebelum Mati", 1082, "Mental Health", "Brian Khrisna"},
	    {"Cantik Itu Luka", 1083, "Romantis, sejarah", "Eka Kurniawan"},
	    {"Pulang", 1084, "Politik, Sejarah", "Leila S.Chudori"},
	    {"Sisi Gelap Surga", 1085, "Fiksi", "Brian Khrisna"},
	    {"Bandung Menjelang Pagi", 1086, "Komedi, Romantis", "Brian Khrisna"},
	    {"Malice", 1087, "Misteri, Fiksi", "Keigo Higashino"},
	    {"Dunia Sophie", 1088, "Filsafat", "Jostein Gaarder"},
	    {"Dompet Ayah Sepatu Ibu", 1089, "Keluarga", "JS Khairen"},
	    {"Ayah, Ini Arahnya Ke Mana, ya?", 1090, "Keluarga", "Khoirul Trian"},
	    {"As Long as The Lemon Trees", 1091, "Fiksi", "Zoulfa Katouh"},
	    {"Tuhan, Beri Aku Alasan Untuk Tidak Menyerah", 1092, "Religi", "Malik al Mughis, Lukman al Hakim"},
	    {"Seni Mengelola Waktu", 1093, "Motivasi", "Brian Adam"},
	    {"Seni Mengatasi Pikiran Berlebihan", 1094, "Mental Health", "Brian Adam"},
	    {"Seni Berpikir Positif", 1095, "Mental Health", "Brian Adam"},
	    {"Hujan", 1096, "Fiksi", "Tere Liye"},
	    {"Parable", 1097, "Novel", "Brian Khrisna"},
	    {"Hai Nak!", 1098, "Self-Improvement", "Reda Gaudiamo"},
	    {"Seni Memaafkan", 1099, "Mental Health", "Brian Adam"},
	    {"Menua dengan Gembira", 1100, "Esai", "Andina Dwi Fatma"},
	    {"Semua Ada Prosesnya", 1101, "Motivasi", "Rendy Ariyanto"},
	    {"Berdamai dengan Kecemasan", 1102, "Mental Health", "Sony Adams"},
	    {"Rusak Saja Buku Ini", 1103, "Mental Health", "Sony Adams"},
	    {"Dasar-Dasar Teknik Informatika", 1104, "Non Fiksi", "Novega Pratama Adiputra"},
	    {"Pengantar Teknologi Informasi", 1105, "Non Fiksi", "Buhori Muslim"},
	    {"Metode Penelitian Teknik Informatika", 1106, "Non Fiksi", "Ade Djohar Maturidi"},
	    {"Komputer Cerdas Untuk Mahasiswa Teknik Informatika", 1107, "Non Fiksi", "Nur Nafi'iyah"},
	    {"Pengantar Teknologi Informatika Dan Komunikasi Data", 1108, "Non Fiksi", "Bagaskoro"},
	    {"Aplikasi Komputer", 1109, "Non Fiksi", "Dwi Krisbiantoro"},
	    {"Aplikasi Komputer", 1110, "Non Fiksi", "Dwi Krisbiantoro"},
	    {"Psikologi Industri dan Organisasi", 1111, "Non Fiksi", "Hany Azza Umama"},
	    {"Psikologi Pendidikan", 1112, "Non Fiksi", "Yunita Septriana"},
	    {"Psikologi Belajar", 1113, "Non Fiksi", "Afi Parnawi"},
	    {"Psikologi Komunikasi", 1114, "Non Fiksi", "Markus Utomo Sukendar"},
	    {"Manusia Dalam Pandangan Psikologi", 1115, "Non Fiksi", "Supriadi"},
	    {"Berdamai dengan Rasa Malas", 1116, "Mental Health", "Munita Yeni"},
	    {"Berdamai dengan Luka Batin", 1117, "Mental Health", "Embrase"},
	    {"Semua Ada Prosesnya", 1118, "Mental Health", "Rendy Ariyanto"},
	    {"Otodidak Kuasai Bahasa Jepang", 1119, "Non Fiksi", "Mia Astuti"},
	    {"Public Speaking", 1120, "Non Fiksi", "Mulasih Tary"},
	    {"Berani Berubah Untuk Hidup yang Lebih Baik", 1121, "Motivasi", "Mulasih Tary"},
	    {"Be Happy Be Positif!", 1122, "Non Fiksi", "Irfan Suryana"},
	    {"Untuk Kamu yang Malas dan Suka Menunda", 1123, "Motivasi", "Noura"},
	    {"Filsafat Berpikir", 1124, "Filsafat", "Embrase"},
	    {"Self Love", 1125, "Mental Health", "Embrase"},
	    {"Seni Memberi", 1126, "Mental Health", "Era Findiani"},
	    {"Berdamai Dengan Emosi", 1127, "Mental Health", "Asti Musman"},
	    {"Hal Baik Berakhir Baik", 1128, "Mental Health", "Kiki Musthafa"},
	    {"Hukum Perdata", 1129, "Non Fiksi", "Ronald Saija"},
	    {"Hukum Perdata Internasional", 1130, "Non Fiksi", "Ronald Saija"},
	    {"Hukum Administrasi Negara", 1131, "Non Fiksi", "Nur Asyiah"},
	    {"Hukum Tata Negara", 1132, "Non Fiksi", "Maemunah"},
	    {"Hukum Lingkungan", 1133, "Non Fiksi", "Aditia Syapirillah"},
	    {"Aneka Masalah Masyarakat Hukum Adat Dalam Pembangunan", 1134, "Non Fiksi", "Ronald Saija"},
	    {"Kapita Selekta Neurologi", 1135, "Non Fiksi", "Harsono"},
	    {"Instrumen Bedah Jantung Pediatri", 1136, "Non Fiksi", "Yudha Krisnadia"},
	    {"Etika Kedokteran", 1137, "Non Fiksi", "Yandri Naldi"},
	    {"Manajemen Keselamatan Pasien", 1138, "Non Fiksi", "Irwan Hadi"},
	    {"Harry Potter And The Philosopher’s Stone", 1139, "Fiksi", "J.K. Rowling"},
	    {"Harry Potter And Chamber of Secrets", 1140, "Fiksi", "J.K. Rowling"},
	    {"Harry Potter And The Prisoner of Azkaban", 1141, "Fiksi", "J.K. Rowling"},
	    {"Harry Potter And The Goblet of Fire", 1142, "Fiksi", "J.K. Rowling"},
	    {"Harry Potter And The Order of The Phoenix", 1143, "Fiksi", "J.K. Rowling"},
	    {"Harry Potter And The Half-Blood Prince", 1144, "Fiksi", "J.K. Rowling"},
	    {"Harry Potter And The Deathly Hallows", 1145, "Fiksi", "J.K. Rowling"},
	    {"Kitab Omong Kosong", 1146, "Non Fiksi", "Seno Gumira Ajidarma"},
	    {"Negeri Para Bedebah", 1147, "Petualangan, drama", "Tere Liye"},
	    {"Bulan Terbelah di Langit Amerika", 1148, "Fiksi, spiritual", "Hanum Salsabiela Rais"},
	    {"Rembulan Tenggelam di Wajahmu", 1149, "Romantis", "Tere Liye"},
	    {"Kolam Berdarah", 1150, "Horor", "Abdullah Harahap"},
	    {"Gadis Kretek", 1151, "Sejarah, Fiksi", "Ratih Kumala"},
	    {"Di Bawah Lindungan Ka'bah", 1152, "Novel Klasik", "Hamka"},
	    {"Ronggeng Dukuh Paruk", 1153, "Historical", "Ahmad Tohari"},
	    {"Tenggelamnya Kapal Van der Wijck", 1154, "Romantis, Historical", "Abdul Malik Karim Amrullah"},
	    {"Sabtu Bersama Bapak", 1155, "Keluarga", "Adhitya Mulya"},
	    {"Hafalan Shalat Delisa", 1156, "Fiksi Religi", "Tere Liye"},
	    {"Edensor", 1157, "Historical", "Andrea Hirata"},
	    {"Jalan Tak Ada Ujung", 1158, "Historical", "Mochtar Lubis"},
	    {"Tentang Kamu", 1159, "Romantis", "Tere Liye"},
	    {"Sosiologi Hukum Kontemporer", 1160, "Non Fiksi", "Rio Christiawaan"},
	    {"Pertanyaan-Pertanyaan Sosiologi", 1161, "Non Fiksi", "Pierre Bourdieu"},
	    {"Secret Of Divine Love", 1162, "Spiritual", "A. Helwa"},
	    {"Metode Penerapan Hukum Islam", 1163, "Spiritual", "KH. Ahmad Dimyati"},
	    {"Kun Bil Qur'ani Najman", 1164, "Spiritual", "Sairul Basyir"},
	    {"Anti Malas", 1165, "Non Fiksi, Spiritual", "Joko Suprapmanto"},
	    {"Dasyatnya Merketing Islami", 1166, "Spiritual", "Erik Arya Tandi"},
	    {"Ulama Kritis Berjejak Manis", 1167, "Non Fiksi", "M. Anwar Djaelani"},
	    {"Fiqih Mu'amalah Kontemporer", 1168, "Non Fiksi", "Imam Mustofa"},
	    {"7 Tahap untuk Meraih Kesempurnaan Ibadah", 1169, "Non Fiksi", "Imam Al-Ghazali"},
	    {"Merindu Cahaya De Amstel", 1170, "Romantis", "Arumi E"},
	    {"Di Atas Sajadah Cinta", 1171, "Romantis", "Habiburrahman El Shirazy"},
	    {"Cinta dalam Ikhlas", 1172, "Romantis", "Abay Adhitya"},
	    {"Dear, Imamku", 1173, "Romantis", "Mellyana"},
	    {"Cinta Suci Zahrana", 1174, "Romantis", "Habiburrahman El Shirazy"},
	    {"Komik Panglima Islam Pemberani", 1175, "Perjuangan, Islami", "Fajar Istiqlal"},
	    {"Komik Oshi No Ko", 1176, "Fiksi", "Aka Akasaka & Mengo Yokoyari"},
	    {"Komik Jitu", 1177, "Thriller", "Yudha Negara Nyoman & Haryadhi"},
	    {"Komik Si Buta Dari Gua Hantu", 1178, "Petualann", "Putih Hitam"},
	    {"Manga Golden Kamuy", 1179, "Action, Adventure, Comedy", "Noda Satoru"},
	    {"Manga Jujutsu Kaisen", 1180, "Action, Demons, Fantasy", "Akutami Gege"},
	    {"Manga Komi-san wa Komyushou Desu", 1181, "Romantis, Kehidupan Sekolah", "Tomohito Oda"},
	    {"Pengantar Bioteknologi", 1182, "Non Fiksi", "Endik Deni Nugroho & Dwi Anggorowati Rahayu"},
	    {"Novel Wingit", 1183, "Horor", "Sara Wijayanto"},
	    {"Novel Gong Nyai Gandrung", 1184, "Horor", "Sekar Ayu Asmara"},
	    {"Novel Laknat", 1185, "Horor", "Lentera Langit"},
	    {"Novel Teror Liburan Sekolah", 1186, "Horor", "Risa Saraswati"},
	    {"Novel Belenggu Hitam", 1187, "Horor", "Anonymous"},
	    {"Novel Dikta & Hukum", 1188, "Romantis", "Dhia'an Farah"},
	    {"Novel Antares", 1189, "Romantis, Kehidupan Sekolah", "Rweinda"},
	    {"Novel I Remember you", 1190, "Romantis", "Stephanie Zen"},
	    {"Novel Winter in Tokyo", 1191, "Romantis", "Ilana Tan"},
	    {"Novel Putri Pelangi", 1192, "Romantis, kehidupan", "Cinkia Ewys"},
	    {"Novel Utara", 1193, "Romantis, kehidupan", "Siti Habibah"},
	    {"The Star and I", 1194, "Romantis", "Ilana Tan"},
	    {"Novel Pengantin Remaja", 1195, "Romantis, kehidupan", "Ken Terate"},
	    {"Pramoedya Ananta Toer: Dari Dekat Sekali", 1196, "Non Fiksi, Biografi", "Koesalah Soebagyo Toer"},
	    {"Buya Hamka", 1197, "Non Fiksi, Biografi", "Ahmad Fuadi"},
	    {"Mahatma Gandhi: Sebuah Autobiografi", 1198, "Non Fiksi, Biografi", "M.K. Gandhi"},
	    {"Nikola Tesla dan Ambisi Besarnya", 1199, "Non Fiksi, Biografi", "Mufiah Laeliyah"},
	    {"Nelson Mandela", 1200, "Non Fiksi, Biografi", "Peter Limb"}
	};

    jumlah_buku = sizeof(dataAwal) / sizeof(dataAwal[0]);
    buku.ReSize(jumlah_buku);

    for (int i = 0; i < jumlah_buku; i++) {
        buku[i] = dataAwal[i];
        
    // MASUKKAN JUGA KE TREE AGAR BISA DICARI CEPAT O(log n)
    treeBuku.root = treeBuku.insert(treeBuku.root, buku[i]);
    }
}

Buku* Perpus::getBukuById(int id) {
    // Menggunakan Tree agar pencarian O(log n), bukan linear lagi!
    return treeBuku.searchById(treeBuku.root, id);
}

bool Perpus::is_kabisat(int tahun) {
	
    return (tahun % 4 == 0 && tahun % 100 != 0) || (tahun % 400 == 0);
    
}

int Perpus::jumlah_hari_bulan(int bulan, int tahun) {
	
    switch (bulan) {
        case 1: return 31;
        case 2: return is_kabisat(tahun) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
    
}

void Perpus::tambah_hari() {
	
    hari_ini.hari++;
    int hariMax = jumlah_hari_bulan(hari_ini.bulan, hari_ini.tahun);

    if (hari_ini.hari > hariMax) {
        hari_ini.hari = 1;
        hari_ini.bulan++;
        if (hari_ini.bulan > 12) {
            hari_ini.bulan = 1;
            hari_ini.tahun++;
        }
    }
}

void Perpus::muat_tanggal() {
	
    ifstream fin("tanggal.txt");
    if (fin.is_open()) {
        fin >> hari_ini.hari >> hari_ini.bulan >> hari_ini.tahun;
        fin.close();
    } else {
        hari_ini = {6, 7, 2025}; // default awal
    }
    tambah_hari();
    
}

void Perpus::muat_data_buku() {
    ifstream fin("data_buku.txt");
    if (!fin.is_open()) return;

    // Reset data sebelum muat ulang
    jumlah_buku = 0;
    treeBuku.root = NULL; // Pastikan Tree dimulai dari kosong

    string line;
    // Jika file menggunakan baris pertama sebagai jumlah buku
    int total;
    if (!(fin >> total)) return;
    fin.ignore();

    for (int i = 0; i < total; i++) {
        Buku temp;
        getline(fin, temp.nama_buku);
        fin >> temp.id_buku;
        fin.ignore();
        getline(fin, temp.genre_buku);
        getline(fin, temp.penulis);
        fin.ignore();

        // 1. Masukkan ke Tree (Pencarian Cepat O(log n))
        treeBuku.root = treeBuku.insert(treeBuku.root, temp);

        // 2. Masukkan ke Array (Penyimpanan Linear)
        tambah_ke_array(temp);
    }

    fin.close();
    //cout << "[INFO] Data buku berhasil dimuat ke Tree dan Array.\n";
}

// Helper: Menambahkan Buku ke Array Dinamis (Array1D)
void Perpus::tambah_ke_array(Buku x) {
    // Array1D harus diubah ukurannya agar bisa menampung 1 elemen baru
    buku.ReSize(jumlah_buku + 1); 
    
    // Masukkan data baru di indeks terakhir (yang baru)
    buku[jumlah_buku] = x;        
    
    // Perbarui jumlah buku
    jumlah_buku++;                
}

//Buat nambahin
void Perpus::gabung_data_dari_file(string namaFile) {
    // 1. Buat objek Linked List sementara untuk menampung data dari file
    DoublyLinkedListBuku temp_list; 

    // 2. Muat data dari file ke Linked List sementara (menggunakan fungsi di bukuLinklist.h)
    temp_list.bacaDariFile(namaFile); 

    Node<Buku>* current = temp_list.getHead();
    while (current != NULL) {
        // Panggil helper untuk memasukkan data ke array
        tambah_ke_array(current->data);
        current = current->next;
    }
    
    // Setelah selesai, temp_list akan dihancurkan secara otomatis
    //cout << "Data buku dari file telah digabungkan ke Array Dinamis.\n";
}

//buat nyimpen data semuah
void Perpus::simpan_semua_data(string namaFile) {
    // 1. Buat objek Linked List sementara
    DoublyLinkedListBuku temp_list;

    // 2. Salin seluruh isi Array1D ke Linked List sementara
    for (int i = 0; i < jumlah_buku; i++) {
        temp_list.insert(buku[i]);
    }

    // 3. Panggil fungsi simpan ke file dari Linked List
    temp_list.simpanKeFile(namaFile);
    
    // Linked List sementara akan dihancurkan, tapi file sudah tersimpan
}



//Perpus::Perpus() {
//	
//    isi_data_buku();
//    muat_data_buku();
//    muat_tanggal();
//    
//}


void Perpus::simpan_tanggal() {
	
    ofstream fout("tanggal.txt");
    fout << hari_ini.hari << " " << hari_ini.bulan << " " << hari_ini.tahun;
    fout.close();
    
}

void Perpus::tampilkan_tanggal() {
	
    cout << hari_ini.hari << " / " 
         << hari_ini.bulan << " / " 
         << hari_ini.tahun;
         
}

void Perpus::tampil_buku() {
	
    cout << "\n+=============================================+" << endl;
    cout << "|                DAFTAR BUKU                  |" << endl;
    cout << "+=============================================+" << endl;

    if (jumlah_buku == 0) {
        cout << "|         Tidak ada data buku tersedia        |" << endl;
    }

    for (int i = 0; i < jumlah_buku; i++) {
        cout << "| " << i + 1 << ". Judul   : " << buku[i].nama_buku << endl;
        cout << "|    ID        : " << buku[i].id_buku << endl;
        cout << "|    Genre     : " << buku[i].genre_buku << endl;
        cout << "|    Penulis   : " << buku[i].penulis << endl;
        cout << "+---------------------------------------------+" << endl;
    }
    
}

// ==== IMPLEMENTASI PENGURUTAN (Bubble Sort) ====
// Diperlukan agar Binary Search (cari_buku_id) bekerja
void Perpus::urut_buku_id() {
    for (int i = 0; i < jumlah_buku - 1; i++) {
        for (int j = 0; j < jumlah_buku - i - 1; j++) {
            if (buku[j].id_buku > buku[j + 1].id_buku) {
                // Swap/Tukar data buku
                Buku temp = buku[j];
                buku[j] = buku[j + 1];
                buku[j + 1] = temp;
            }
        }
    }
    //cout << "[INFO] Data buku berhasil diurutkan berdasarkan ID.\n";
}
