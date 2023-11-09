#include <iostream>
// Digunakan untuk program dasar

#include <conio.h>
// Digunakan untuk menahan output suatu program

#include <stdio.h>
// Digunakan untuk input_string dan output pada program

#include <sstream>
// Digunakan untuk mengkonversi variabel string

#include <string.h>
// Digunakan untuk mengedit string di program

#include <iomanip>
// Digunakan untuk perhitungan di program pada tampilan output

#include <vector>
// Digunakan untuk perhitungan di program pada tampilan output

#include <cmath>
// Digunakan untuk perhitungan di program

#include <ctype.h>
// untuk mengecek tipe inputan

#include <ctime>
// Untuk memasukan waktu pada program

#include <fstream>
// Digunakan untuk mengakses file dan menyimpan data

using namespace std;


// Variabel pilihan menu //
string pilihan_masuk;     // Variabel yang berisi pilihan menu masuk awal
string pilihan_admin;     // Variabel yang berisi pilihan menu admin
string pilihan_user;      // Variabel yang berisi pilihan menu user
string pilihan_tambah;    // Variabel yang berisi pilihan menu tambah pada admin
string pilihan_lihat;     // Variabel yang berisi pilihan menu lihat
string pilihan_ubah;      // Variabel yang berisi pilihan menu ubah pada admin
string pilihan_hapus;     // Variabel yang berisi pilihan menu hapus pada admin
string pilihan_pemesanan; // Variabel yang berisi pilihan pemesanan
string pilihan_disorting; // Variabel yang berisi pilihan dari data apa yang sorting


// Array Menu //
string menu_awal      [3] = {"Register", "Login", "Logout"};
string menu_admin     [5] = {"Menu Menambah(create)", "Menu Melihat(read)", "Menu Mengubah(update)", "Menu Menghapus(delete)", "Back to Login"};
string menu_user      [2] = {"Melihat daftar harga e-book", "Back to Login"};
string menu_tambah    [4] = {"Tambah data e-book di awal", "Tambah data e-book di tengah", "Tambah data e-book di akhir", "Exit"};
string menu_lihat     [6] = {"Lihat semua data e-book dari Head", "Lihat semua data e-book dari Tail", "Lihat salah satu data e-book", "Lihat berdasarkan sorting", "Lihat Histori Masuk User", "Exit"};
string menu_lihat_user[6] = {"Lihat semua data e-book dari Head", "Lihat semua data e-book dari Tail", "Lihat salah satu data e-book", "Lihat berdasarkan sorting", "Pemesanan", "Exit"};
string menu_ubah      [2] = {"Ubah salah satu data e-book", "Exit"};
string menu_hapus     [4] = {"Hapus salah satu data e-book dengan pencarian", "Hapus data e-book di awal", "Hapus data e-book di akhir", "Exit"};
string menu_pemesanan [2] = {"Ya", "Tidak"};
string menu_disorting [5] = {"Ascending Berdasarkan Jumlah halaman", "Descending Berdasarkan Jumlah halaman", "Ascending Berdasarkan Harga", "Descending Berdasarkan Harga", "Exit"};


// Variabel Akun Pengguna //
string user;       // Memasukan username pada proses login
string pass;       // Memasukan password pada proses login
string nama;       // Variabel untuk menyimpan data nama sementara
string kata_sandi; // Variabel untuk menyimpan data kata sandi sementara
string noHp;       // Variabel untuk menyimpan data nomor hp sementara
string gmail;      // Variabel untuk menyimpan data gmail sementara


// Struct akun pengguna //
struct akun_pengguna {
    string username; // Memasukan username pada proses registrasi
    string password; // Memasukan password pada proses registrasi
    string nomor_hp; // variabel nomor hp pembeli
    string gmail;    // variabel gmail pembeli
};


// Struct akun pengguna untuk histori masuk(Queue) //
struct node_histori {
    string username;                // Username histori
    string password;                // Password histori
    time_t waktu_masuk;             // Waktu histori masuk
    node_histori *next;             // Alamat node selanjutnya
};

int jum_user = 0;                       // Jumlah user histori
node_histori * front = nullptr;         // Node depan
node_histori * rear = nullptr;          // Node belakang

// Struct data e-book //
struct data_Ebook {
    string judul_Ebook;     // variabel judul Ebook
    string nama_penulis;    // variabel nama penulis
    int jmlhalaman_Ebook;   // variabel jumlah halaman Ebook
    string deskripsi_Ebook; // variabel yang berisi deskripsi Ebook
    int harga;              // variabel jumlah halaman Ebook            
};


// Double Linked List //
struct node {
    data_Ebook data_Ebook;  // struct ebook
    node *next = nullptr;      // alamat node setelahnya
    node *prev = nullptr;      // alamat node sebelumnya
};

node *Head = nullptr;              // alamat node awal
node *Tail = nullptr;              // alamat node akhir
node *alamat_sementara = nullptr;  // alamat node sementara


// Variabel tambahan //
int index;              // Variabel penanda index
int jum_char;           // Variabel untuk menyimpan jumlah char suatu string
string cek_data;        // Variabel untuk mengecek data
string judul_Ebook;     // Variabel judul Ebook sementara
string nama_penulis;    // Variabel nama penulis sementara
string deskripsi_Ebook; // variabel deskripsi_Ebook sementara
int harga;              // variabel harga sementara
int halaman;            // variabel halaman sementara


// Nama File Pengguna
string namaFile = "akunPengguna_C1_Kelompok4.csv";

// Digunakan untuk dapat mengakses file //
fstream file;




//___________________________________________________________________________________________________________________________________________________//
//                                               *FUNGSI DAN PROSEDUR TAMBAHAN DAN ERROR HANDLING*                                                   //
//___________________________________________________________________________________________________________________________________________________//

//  [1] Membersihkan layar output
    void cls(){
        cout << "\n";
        system("pause"); // Untuk menghentikan output sementara
        system("cls");   // Untuk membersihkan output program sebelumnya
    }
//___________________________________________________________________________________________________________________________________________________//

//  [2] Menghitung char atau huruf  yang ada dalam string
    int jml_char(string kalimat){
        int jum_karakter = 0; // Variabel yang memuat jumlah char

        // Menghitung char dengan perulangan for
        for (int i = 0; kalimat[i]; i++)
            jum_karakter++;

        // Mengembalikan nilai jumlah char
        return jum_karakter;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [3] Menampilkan kata di antara garis
    void sambutan(string kalimat){
        jum_char = jml_char(kalimat);

        // Digunakan perhitungan untuk meletakan kalimat ditengah garis
        int garis = trunc((120 - jum_char) / 2);         //(trunc digunakan untuk pembulatan bilangan desimal)
        cout << setfill('-') << setw(garis) << " "; //(setfill artinya Memasukan karakter di dalam kurung sebanyak setw(garis))
        cout << kalimat;
        cout << setfill('-') << left << setw(garis) << " " << endl;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [4] Memasukan inputan string pada program
    string input_string(string pernyataan, string variabel){

        // Menampilkan pernyataan apa yang akan menjadi inputan
        cout << pernyataan;

        // Fungsi fflush stdin adalah agar input string setelah integer tidak terlewat atau terskip
        fflush(stdin);

        // getline untuk mengizinkan spasi
        getline(cin, variabel);

        // Mengembalikan nilai variabelnya
        return variabel;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [5] Memasukan inputan string pada program tapi tidak mengizinkan pengguna hanya memasukan enter
    string input_string_khusus(string pernyataan, string variabel){

        while (true){

            // Memanggil fungsi input string untuk cek isi inputan
            variabel = input_string(pernyataan, variabel);

            // Menghitung jumlah char dari inputan string
            jum_char = jml_char(variabel);

            // Proses agar inputan tidak kosong atau tidak berisi enter saja
            if (jum_char != 0){
                break;
            }

            // Jika terdapat enter atau inputan kosong
            else{
                cls();
                sambutan("\n |  Error! Inputan Tidak Boleh Kosong |\n");
                cls();
            }
        }

        // Mengembalikan nilai
        return variabel;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [6] Memasukan harus inputan yang bukan angka pada program
    string bukan_angka(string pernyataan, string variabel){

        while (true){

            // Memanggil fungsi input string untuk cek isi inputan
            variabel = input_string_khusus(pernyataan, variabel);

            // Variabel c akan merepresentasikan karakter saat ini dalam setiap iterasi.
            for (char c : variabel){

                // Jika ada angka di dalamnya
                if (isdigit(c)){
                    cek_data = "tidak";
                    break;
                }

                // Jika tidak ada angka di dalamnya
                else{
                    cek_data = "ada";
                }
            }

            if (cek_data == "ada"){
                break;
            }

            // Jika terdapat enter atau inputan kosong
            cls();
            sambutan("\n |Error! Inputan Tidak Boleh Berisi Angka|\n");
            cls();
        }

        return variabel;
    }
//___________________________________________________________________________________________________________________________________________________//
//  [7] Fungsi agar pengguna hanya bisa memasukan angka dan mengeluarkan output berupa string
    string harus_angka(string pernyataan){
        string huruf; // variabel bertipe string perbandingan untuk angka
        int angka;    // variabel angka

        // Mengecek apakah input_string_khusus yang dimasukan pengguna adalah angka atau bukan
        while (true){
            huruf = input_string_khusus(pernyataan, huruf);

            // Memasukan inputan string ke integer
            stringstream ss(huruf);
            ss >> angka;

            // Jika tidak ditemukan error maka break
            if (ss.eof()){
                break;
            }

            // Jika terdapat enter atau inputan kosong
                cls();
                sambutan("\n |  Error! Inputan Tidak Boleh Huruf  |\n");
                cls();
        }

        // Mengembalikan nilai huruf untuk dimasukan di dalam data
        return huruf;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [8] Fungsi agar pengguna hanya bisa memasukan angka dan mengeluarkan output berupa integer
    int harus_angka_int(string pernyataan){
        string huruf; // variabel bertipe string perbandingan untuk angka
        int angka;    // variabel angka

        // Mengecek inputan integer
        huruf = harus_angka(pernyataan);
        stringstream ss(huruf);

        // mengubah string menjadi integer
        ss >> angka;

        // Mengembalikan nilai
        return angka;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [9] Membatasi suatu nilai variabel pada integer agar tidak terlalu kecil atau besar
    int error_batas(string pernyataan, int data, int batas_awal, int batas_akhir){
        while (true){

            // Mengecek apakah data terlalu kecil dari batas yang sudah diberikan
            if (data <= batas_awal){
                cout << "+------------------------------------------------------------+\n Data yang di masukan terlalu kecil, min: " << batas_awal << " \n+------------------------------------------------------------+\n";
                data = harus_angka_int(pernyataan);
                cls();
            }

            // Mengecek apakah data terlalu besar dari batas yang sudah diberikan
            else if (data >= batas_akhir){
                cout << "+------------------------------------------------------------+\n Data yang di masukan terlalu besar, max: " << batas_akhir << " \n+------------------------------------------------------------+\n";
                data = harus_angka_int(pernyataan);
                cls();
            }

            // Saat data memenuhi syarat batas maka perulangan akan berhenti
            else if (data >= batas_awal && data <= batas_akhir){
                break;
            }
        }

        // Mengembalikan nilai data
        return data;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [10] Penetapan batas char pada sebuah inputan nomor ponsel
    string batas_char_Nomor_hp(string pernyataan, string variabel){
        while (true){

            // Memeriksa inputan nomor ponsel
            variabel = harus_angka(pernyataan);

            // Mengecek apakah data char sesuai yang diinginkan
            jum_char = jml_char(variabel);
            if ((jum_char >= 11 && jum_char <= 13 && variabel[0] == *"0" && variabel[1] == *"8") || 
                (jum_char >= 11 && jum_char <= 13 && variabel[0] == *"+" && variabel[1] == *"6" && variabel[2] == *"2" && variabel[3] == *"8")){
                break;
            }

            else{
                cout << "\n+-------------------------------------------------------------------------------------------------------------------+" << endl;
                cout <<   "|      Nomor ponsel tidak memenuhi syarat, harap masukan nomor yang benar dengan format 08/+628xx xxxx xxxx         |";
                cout << "\n+-------------------------------------------------------------------------------------------------------------------+" << endl;
                cls();
            }
        }

        // Mengembalikan nilai
        return variabel;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [11] Penetapan batas char pada sebuah inputan gmail
    string batas_char_gmail(string pernyataan, string variabel){
        while (true){

            variabel = input_string_khusus(pernyataan, variabel);

            // Mengecek apakah data char sesuai yang diinginkan
            jum_char = jml_char(variabel);

            // Jika nama gmail terlalu panjang
            if (jum_char > 320){
                cout << "Nama gmail melebihi batas panjang yang di tetapkan sistem";
                cls();
            }

            else {
                jum_char = jum_char - 10;

                // Pengecekan alamat email
                if (variabel[jum_char] == *"@" && variabel[jum_char + 1] == *"g" && 
                    variabel[jum_char + 2] == *"m" && variabel[jum_char + 3] == *"a" && 
                    variabel[jum_char + 4] == *"i" && variabel[jum_char + 5] == *"l" && 
                    variabel[jum_char + 6] == *"." && variabel[jum_char + 7] == *"c" && 
                    variabel[jum_char + 8] == *"o" && variabel[jum_char + 9] == *"m"){
                    break;
                }

                else {
                    cout << "\n+-------------------------------------------------------------+" << endl;
                    cout <<   "|  Harap masukan alamat yang sesuai formatnya ....@gmail.com  |";
                    cout << "\n+-------------------------------------------------------------+" << endl;
                    cls();
                
                }
            }
        }

        // Mengembalikan nilai
        return variabel;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [12] Prosedur agar data tidak sama
    void data_tidak_sama(){

        // Menyimpan alamat Head sementara
        alamat_sementara = Head;
        while (true){

            // Memasukan nama dan judul
            judul_Ebook = input_string_khusus("Masukan judul Ebook         >> ", judul_Ebook);
            nama_penulis = bukan_angka       ("Masukan nama penulis        >> ", nama_penulis);

            // Membandingkan judul dan nama
            if (alamat_sementara != nullptr){
                
                // Jika ditemukan kesamaan judul Ebook dan nama penulis
                if (alamat_sementara->data_Ebook.judul_Ebook == judul_Ebook && 
                    alamat_sementara->data_Ebook.nama_penulis == nama_penulis){
                    
                    // Pemberitahuan data sudah ada
                    cout << "\n+-------------------------------------------------------------------------------------------------------------------+" << endl;
                    cout << "\n|  Judul Ebook & nama penulis sudah ada, pastikan Memasukan judul lengkap atau huruf tambahan untuk membedakan...   |\n";
                    cout << "\n+-------------------------------------------------------------------------------------------------------------------+" << endl;
                    cls();
                    cek_data = "ada";
                    alamat_sementara = alamat_sementara->next;
                }

                // Jika tidak ditemukan kesamaan judul Ebook dan nama penulis
                else{
                    cek_data = "tidak";
                    alamat_sementara = nullptr;
                    return;
                }
            }

            // Jika data kosong
            else {
                return;
            }
        }
    }
//___________________________________________________________________________________________________________________________________________________//





//___________________________________________________________________________________________________________________________________________________//
//                                          *FUNGSI DAN PROSEDUR TAMBAHAN UNTUK TAMPILAN OUTPUT PROGRAM*                                             //
//___________________________________________________________________________________________________________________________________________________//

//  [1] Menampilkan garis untuk hiasan pada output
    void garis(){
        cout << "\n+------------------------------------------------------------------------------------------------------------------+" << endl;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [2] Membuat tampilan menu dan memberikan keluaran pilihan input
    string menu(string arr_pilihan[], string kalimat, int jum_pilihan, string variabel){
        garis();

        // Menghitung jumlah huruf pernyataan utama menu
        int jum_karakter = jml_char(kalimat);

        // Menaruh pernyataan menu tepat di antara garis '='
        int garis_hitung = trunc((120 - jum_karakter) / 2);
        cout << setfill(' ') << setw(garis_hitung) << " ";
        cout << kalimat << endl;
        garis();

        // Menampilkan daftar pilihan menu yang sudah di nyatakan di dalam array
        for (int i = 0; i < jum_pilihan; i++)
        {
            cout << "   " << i + 1 << ". " << arr_pilihan[i] << endl;
        }
        garis();

        // Membuat inputan pilihan yang dipilih
        string pilihan = input_string("\nMasukan nomor dari tindakan yang ingin anda lakukan >> ", variabel);
        system("cls");

        return pilihan;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [3] Prosedur output saat salah Memasukan inputan
    void inputan_salah(){
        garis();
        cout << "|             Maaf inputan yang anda masukan tidak sesuai, silahkan masukan inputan yang benar...                  |";
        garis();
        cls();
    }
//___________________________________________________________________________________________________________________________________________________//

//  [4] Prosedur output saat data kosong
    void data_kosong(){
        cout << "+--------------------------------------------------------------+\n";
        cout << " Maaf, data kosong. Silahkan tambahkan data terlebih dahulu....\n";
        cout << "+--------------------------------------------------------------+\n\n";
        cls();
    }





//___________________________________________________________________________________________________________________________________________________//
//                                               *FUNGSI DAN PROSEDUR UTAMA UNTUK PROSES MASUK*                                                      //
//___________________________________________________________________________________________________________________________________________________//

//  [1] Fungsi untuk membaca data akun pengguna dari file CSV
    vector<akun_pengguna> file_akun_pengguna_read(const string &namaFile){

        // Membuat vektor untuk menyimpan data akun_pengguna
        vector<akun_pengguna> dataAkun; 

        // Membuka file dengan nama yang diberikan
        ifstream file(namaFile); 

        // Memeriksa apakah file berhasil dibuka
        if (!file.is_open()) { 

            // Jika gagal, Mengembalikan vektor kosong karena tidak dapat membaca file
            cerr << "Gagal membuka file " << namaFile << endl; 
            return dataAkun;
        }

        string baris;                   // Variabel untuk menyimpan setiap baris dalam file
        while (getline(file, baris)) {  // Membaca file baris per baris
            istringstream ss(baris);    // Membuat objek stringstream untuk memproses setiap baris
            string token;
            akun_pengguna akun;

            getline(ss, token, ',');    // Memisahkan baris menjadi token berdasarkan koma
            akun.username = token;      // Mengisi atribut username dari struktur akun_pengguna
            getline(ss, token, ',');    // Melanjutkan dengan token berikutnya
            akun.password = token;      // Mengisi atribut password
            getline(ss, token, ',');
            akun.nomor_hp = token;      // Mengisi atribut nomor_hp
            getline(ss, token, ',');
            akun.gmail = token;         // Mengisi atribut gmail

            dataAkun.push_back(akun);   // Menambahkan struktur akun_pengguna ke dalam vektor dataAkun
        }

        file.close();                   // Menutup file setelah selesai membacanya
        return dataAkun;                // Mengembalikan vektor dataAkun yang berisi data dari file CSV
    }

    // Membaca data dari file CSV
    vector<akun_pengguna> dataAkun = file_akun_pengguna_read(namaFile);
//___________________________________________________________________________________________________________________________________________________//

//  [2] Fungsi untuk menambahkan data akun pengguna ke dalam file CSV
    void file_akun_pengguna_change(const string &namaFile, const akun_pengguna &akun){
        
        ofstream file(namaFile, ios::app);
        if (!file.is_open()){
            cerr << "Gagal membuka file " << namaFile << endl;
            return;
        }

        file << akun.username << "," << akun.password << "," << akun.nomor_hp << "," << akun.gmail << "\n";
        file.close();
    }
//___________________________________________________________________________________________________________________________________________________//

//  [3] Fungsi untuk menambahkan akun ke dalam queue histori
    void enqueue(string username, string password) {
        node_histori* newNode = new node_histori;   // Membuat node baru untuk data histori
        newNode->username = username;               // Mengisi atribut username di node baru
        newNode->password = password;               // Mengisi atribut password di node baru
        newNode->waktu_masuk = time(nullptr);       // Mengambil waktu saat ini
        newNode->next = nullptr;                    // Mengatur pointer next di node baru menjadi nullptr

        // Memeriksa apakah antrian kosong
        if (rear == nullptr || front == nullptr) { 
            front = rear = newNode;                 // Jika antrian kosong, node baru adalah elemen pertama (front dan rear menunjuk ke node baru)
        } 
        
        else {
            rear->next = newNode;                   // Jika antrian tidak kosong, menghubungkan node baru ke belakang antrian
            rear = newNode;                         // Menggeser rear ke node baru
        }
    }
//___________________________________________________________________________________________________________________________________________________//

//  [4] Fungsi untuk menghapus akun dari depan histori
    void dequeue(){
        if (front == nullptr) {
            return;                     // Jika antrian kosong, keluar dari fungsi
        }

        node_histori* temp = front;     // Menyimpan alamat elemen depan antrian
        front = front->next;            // Menggeser front ke elemen berikutnya
        delete temp;                    // Menghapus elemen depan yang disimpan dalam 'temp'
    }
//___________________________________________________________________________________________________________________________________________________//

//  [5] Fungsi untuk menampilkan histori akun
    void displayHistory(){
        // Menginisialisasi pointer "alamat_sementara" dengan node pertama dalam daftar histori
        node_histori* alamat_sementara = front;         

        // Menampilkan pesan sambutan
        sambutan(" Data Histori Pengguna Masuk ");     

        // Mulai loop selama "alamat_sementara" tidak nullptr, artinya masih ada data histori yang harus ditampilkan
        while (alamat_sementara != nullptr) {   

            // Menghitung panjang (jumlah karakter) password saat ini
            int sandi = jml_char(alamat_sementara->password);   

            // Menampilkan username
            cout << "Username: " << alamat_sementara->username << "\nPassword: "; 

            // Menampilkan karakter '*' sebanyak (sandi + 1) kali untuk menyembunyikan password
            cout << setfill('*') << setw(sandi + 1) << " " << endl;

            // Konversi waktu menjadi string dan mencetaknya
            cout << "Waktu Masuk: " << ctime(&alamat_sementara->waktu_masuk); 

            // Pindah ke node berikutnya dalam daftar histori
            alamat_sementara = alamat_sementara->next; 
            garis(); // Menampilkan garis pemisah antar entri histori
        }

        cls(); 
    }
//___________________________________________________________________________________________________________________________________________________//

//  [6] Prosedur registrasi
    void registrasi(){

    // Membuat username dan password
    nama        = input_string_khusus("Buat username anda                >> ", nama);
    kata_sandi  = input_string_khusus("Buat Password anda                >> ", kata_sandi);

    // Agar pengguna tidak bisa memasukan nama dan kata sandi yang sama dengan admin
    if (nama == "xuensun" && kata_sandi == "09596"){
        cout << "Maaf, nama dan password tidak boleh digunakan";
        return;
    }
    noHp        = batas_char_Nomor_hp("Masukan nomor ponsel anda[08....] >> ", noHp);
    gmail       = batas_char_gmail   ("Masukan gmail anda                >> ", gmail);

    // Menambahkan data baru ke dalam file CSV
    akun_pengguna akunBaru = {nama, kata_sandi, noHp, gmail};
    file_akun_pengguna_change(namaFile, akunBaru);

    }
//___________________________________________________________________________________________________________________________________________________//

//  [7] Prosedur login
    void proses_login(){
        int i = 0; // Variabel untuk perulangan

        // Membaca data dari file CSV
        vector<akun_pengguna> dataAkun = file_akun_pengguna_read(namaFile);

        // Mengulang input username dan password sebanyak 3 kali
        while (i < 4){

            // Pengguna Username dan password
            user = input_string_khusus("Masukkan Username(admin   : xuensun)     : ", user);
            pass = input_string_khusus("Masukkan Password(admin pw: 09596  )     : ", pass);

            // Perulangan untuk melihat akun pengguna
            for (const auto &akun : dataAkun){

                // Jika username dan password benar(untuk user)
                if (user == akun.username && pass == akun.password){
                    cout << "\n\n +----------------+\n";
                    cout <<     " | Login Berhasil |" << endl;
                    cout <<     " +----------------+\n\n";
                    cek_data = "ada";

                    enqueue(user, pass);
                    jum_user++;

                    if (jum_user > 5){
                        dequeue();
                    }

                    break;
                }

                // Jika username dan password benar(untuk admin)
                else if (user == "xuensun" && pass == "09596"){
                    cout << "\n\n +----------------------+\n";
                    cout <<     " | Login admin Berhasil |" << endl;
                    cout <<     " +----------------------+\n\n";
                    cek_data = "ada";
                    break;
                }

                // Jika username dan password salah
                else{
                    cek_data = "tidak";
                }
            }

            // Jika akun ditemukan atau login berhasil
            if (cek_data == "ada"){
                break;
            }

            // Jika akun tidak ditemukan atau login gagal
            else if (cek_data == "tidak"){
                i = i + 1;
                cout << "\n+--------------------------------------+\n";
                cout <<   "| Username / password Salah! (" << i << "x)\n";
                cout <<   "+--------------------------------------+\n\n";

                // Jika pengguna salah Username dan password lebih dari 3x, maka pengguna akan dikeluarkan dari program
                if (i == 3){
                    cout << "\n+--------------------------------------+\n";
                    cout <<   "|    Anda dikeluarkan dari program     |\n";
                    cout <<   "+--------------------------------------+\n\n";
                    cls();

                    // Menggunakan fungsi exit untuk keluar
                    exit(0);
                }
            }
        }
    }
//___________________________________________________________________________________________________________________________________________________//





//___________________________________________________________________________________________________________________________________________________//
//                                                  *FUNGSI DAN PROSEDUR UTAMA UNTUK LINKED LIST*                                                    //
//___________________________________________________________________________________________________________________________________________________//

//  [1] Fungsi untuk membaca data dari file CSV dan memasukkannya ke dalam double linked list
    void file_data_ebook_read(){
        ifstream file("dataEbook_C1_Kelompok4.csv"); // Membuka file "data_ebook.csv" untuk dibaca
        if (!file.is_open()){
            cout << "File tidak dapat dibuka!" << endl; // Mencetak pesan kesalahan jika file tidak dapat dibuka
            return;
        }

        string line;
        while (getline(file, line)){
            data_Ebook data; // Membuat objek data_Ebook untuk menyimpan data ebook
            char judul[255];
            char penulis[255];
            char deskripsi[255];
            int jmlhalaman;
            int harga;

            // Menguraikan data dari baris ke variabel yang sesuai
            sscanf(line.c_str(), "%[^,],%[^,],%d,%[^,],%d", judul, penulis, &jmlhalaman, deskripsi, &harga);

            data.judul_Ebook = judul; // Mengisi atribut judul_Ebook
            data.nama_penulis = penulis; // Mengisi atribut nama_penulis
            data.jmlhalaman_Ebook = jmlhalaman; // Mengisi atribut jmlhalaman_Ebook
            data.deskripsi_Ebook = deskripsi; // Mengisi atribut deskripsi_Ebook
            data.harga = harga; // Mengisi atribut harga

            node *nodeBaru = new node; // Membuat node baru
            nodeBaru->data_Ebook = data; // Menyimpan data ebook ke dalam node

            if (Head == nullptr){
                // Jika data kosong, node baru menjadi Head dan Tail
                Head = nodeBaru;
                Tail = nodeBaru;
                nodeBaru->next = nullptr;
                nodeBaru->prev = nullptr;
            }
            else{
                // Jika data tidak kosong, tambahkan node baru ke belakang dan perbarui Tail
                Tail->next = nodeBaru;
                nodeBaru->prev = Tail;
                nodeBaru->next = nullptr;
                Tail = nodeBaru;
            }
        }

        file.close(); // Menutup file setelah selesai membaca
    }
//___________________________________________________________________________________________________________________________________________________//

//  [2] Fungsi untuk menggaanti isi data di dalam file
    void file_data_ebook_change(){
        ofstream file("dataEbook_C1_Kelompok4.csv"); // Membuka file "data_ebook.csv" untuk ditulis
        if (!file.is_open()){
            cout << "File tidak dapat dibuka!" << endl; // Mencetak pesan kesalahan jika file tidak dapat dibuka
            return;
        }

        node *alamat_sementara = Head;
        while (alamat_sementara != nullptr){
            data_Ebook data = alamat_sementara->data_Ebook;
            // Menulis data ebook ke dalam file CSV dalam format yang sesuai
            file << data.judul_Ebook << "," << data.nama_penulis << "," << data.jmlhalaman_Ebook << ","
                << data.deskripsi_Ebook << "," << data.harga << endl;
            alamat_sementara = alamat_sementara->next;
        }

        // Menambahkan penjelajahan dari belakang ke depan (tapi tidak melakukan apa-apa)
        alamat_sementara = Tail;
        while (alamat_sementara != nullptr){
            data_Ebook data = alamat_sementara->data_Ebook;
            // Lakukan apa yang perlu Anda lakukan dengan data di sini jika diperlukan
            alamat_sementara = alamat_sementara->prev;
        }

        file.close(); // Menutup file setelah selesai menulis
    }
//___________________________________________________________________________________________________________________________________________________//

//  [3] Menghitung panjang data e-book
    int lenght(){
        int jumlah = 0;
        alamat_sementara = Head;
        while (alamat_sementara != nullptr){
            jumlah++;
            alamat_sementara = alamat_sementara->next;
        }

        return jumlah;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [4] Mencari data
    void jumpSearch(string targetPenulis, string targetJudul){
        if (Head == nullptr){
            // Jika daftar kosong, tampilkan pesan dan keluar dari fungsi
            cout << "+-------------------------------------+\n";
            cout << "| Data tidak ditemukan, Daftar kosong |\n";
            cout << "+-------------------------------------+\n\n";
            return;
        }

        int n = lenght();   // Menaruh jumlah buku
        index = 0;          // Menaruh urutan buku

        int step = sqrt(n); // Hitung ukuran langkah (jump step)

        // Pengecekan apakah nama penulis ada dalam daftar
        bool penulisDitemukan = false;
        node *penulisCek = Head;
        while (penulisCek != nullptr) {
            if (penulisCek->data_Ebook.nama_penulis == targetPenulis) {
                penulisDitemukan = true;
                break;
            }
            penulisCek = penulisCek->next;
            
        }

        if (!penulisDitemukan) {
            alamat_sementara = nullptr;
            cek_data = "tidak";
            return;
        }

        // Kembali ke awal daftar
        alamat_sementara = Head;

        // Mencari node yang lebih dekat dengan target berdasarkan nama penulis
        while (alamat_sementara->data_Ebook.nama_penulis < targetPenulis){
            int jump = min(step, n - 1);

            // Melompati sejumlah node sesuai dengan langkah
            for (int i = 0; i < jump; i++){
                alamat_sementara = alamat_sementara->next;
            }

            n -= jump;
        }

        // Melakukan pencarian linier dalam blok saat ini
        while (alamat_sementara != nullptr){
            if (alamat_sementara->data_Ebook.nama_penulis == targetPenulis && 
                alamat_sementara->data_Ebook.judul_Ebook == targetJudul){

                // Jika data cocok, atur alamat_sementara dan cek_data, lalu keluar dari fungsi
                alamat_sementara = alamat_sementara; // Temukan data yang sesuai
                cek_data = "ada";
                return;
            }

            else if (alamat_sementara->next == nullptr &&
                    alamat_sementara->data_Ebook.nama_penulis == targetPenulis &&
                    alamat_sementara->data_Ebook.judul_Ebook == targetJudul){

                // Kondisi khusus jika data yang dicari berada di node terakhir
                alamat_sementara = alamat_sementara; // Temukan data yang sesuai
                cek_data = "ada";
                return;
            }
            index++;
            alamat_sementara = alamat_sementara->next;
        }

        // Jika data tidak ditemukan
        alamat_sementara = nullptr;
        cek_data = "tidak";
        return;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [5] Proses Pencarian data e-book
    string proses_search(){

        // Masukan judul Ebook dan nama penulis yang ingin dicari
        judul_Ebook = input_string_khusus("Masukan judul Ebook yang ingin di cari  >> ", judul_Ebook);
        nama_penulis = input_string_khusus("Masukan nama penulis yang ingin di cari >> ", nama_penulis);
        
        cls();
        jumpSearch(nama_penulis, judul_Ebook);

        if (alamat_sementara == nullptr){
            cout << "+-------------------------------------+\n";
            cout << "|    Data yang di cari tidak ada...   |\n";
            cout << "+-------------------------------------+\n\n";
            return cek_data;
        }

        if (cek_data == "ada"){
            judul_Ebook = judul_Ebook;
            nama_penulis = nama_penulis;
            deskripsi_Ebook = alamat_sementara->data_Ebook.deskripsi_Ebook;
            halaman = alamat_sementara->data_Ebook.jmlhalaman_Ebook;
            harga = alamat_sementara->data_Ebook.harga;
            return cek_data;
        }

        else if (cek_data == "tidak"){
            cout << "+-------------------------------------+\n";
            cout << "|    Data yang di cari tidak ada...   |\n";
            cout << "+-------------------------------------+\n\n";
        }

        return cek_data;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [6] Untuk Memasukan data dari node baru
    node *newnode(){
        node *nodebaru = new node;
        data_tidak_sama();
        nodebaru->data_Ebook.judul_Ebook = judul_Ebook;
        nodebaru->data_Ebook.nama_penulis = nama_penulis;
        halaman = harus_angka_int("Masukan jumlah halaman      >> ");
        nodebaru->data_Ebook.jmlhalaman_Ebook = error_batas("Masukan jumlah halaman      >> ", halaman, 20, 700);
        nodebaru->data_Ebook.deskripsi_Ebook = input_string_khusus("Masukan deskripsi cerita    >> ", nodebaru->data_Ebook.deskripsi_Ebook);
        harga = harus_angka_int("Masukan harga               >> ");
        nodebaru->data_Ebook.harga = error_batas("Masukan harga               >> ", harga, 10000, 2147483647);
        return nodebaru;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [7] Memasukan data di depan
    void addfirst() {
        // Membuat node baru
        node *nodebaru = newnode();
        nodebaru->prev = nullptr;
        nodebaru->next = nullptr;

        // Cek apakah linked list kosong
        if (Head == nullptr && Tail == nullptr) {
            // Jika kosong, atur Head dan Tail ke node baru
            Head = nodebaru;
            Tail = nodebaru;
        } 
        
        else {
            // Jika tidak kosong, atur nodebaru sebagai node pertama (Head)
            // dan perbarui referensi prev Head ke nodebaru
            nodebaru->prev = nullptr;
            nodebaru->next = Head;
            Head->prev = nodebaru;
            Head = nodebaru;
        }

        // Mencetak pesan sambutan bahwa data e-book berhasil dibuat
        sambutan("\n Data e-book Berhasil Dibuat\n");

        // Memanggil fungsi file_data_ebook_change untuk mengubah data file e-book
        file_data_ebook_change();

        return;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [8] Memasukan data di akhir
    void addlast() {
        node *nodebaru = newnode();  // Membuat node baru dan menetapkan alamatnya ke nodebaru
        nodebaru->prev = Tail;       // Mengatur nodebaru sebagai node sebelumnya dari Tail
        nodebaru->next = nullptr;    // Mengatur nodebaru sebagai node selanjutnya (tail), karena ini akan menjadi node terakhir.

        if (Head == nullptr && Tail == nullptr) {
            // Jika data kosong (linked list kosong), node baru menjadi Head dan Tail.
            Head = nodebaru;
            Tail = nodebaru;
        } else {
            // Jika data tidak kosong, menghubungkan nodebaru ke Tail dan menjadikan nodebaru sebagai Tail yang baru.
            (Tail)->next = nodebaru;  // Menghubungkan node lama (Tail) ke node baru.
            Tail = nodebaru;         // Menjadikan nodebaru sebagai Tail yang baru.
        }
        
        sambutan("\n Data e-book Berhasil Dibuat\n");  // Memberikan pesan bahwa data e-book berhasil ditambahkan.
        file_data_ebook_change();  // Kemungkinan melakukan operasi terkait penyimpanan data e-book ke file (tergantung pada logika program lainnya).
    }
//___________________________________________________________________________________________________________________________________________________//

//  [9] Memasukan data di tengah
    void addmid() {
        int posisi = 0; // Posisi index yang ingin di ganti
        posisi = harus_angka_int("Ingin Meletakan data pada urutan ke berapa?   >> ");
        int jumlah = lenght(); // Jumlah data

        if (posisi == jumlah) {
            // Jika data kosong maka akan di tambah di awal
            if (Head == nullptr && Tail == nullptr) {
                addfirst(); // Menambahkan di awal jika tidak ada data
            }
            // Jika ada berarti di tambah di atas akhir
            else {
                node *nodeBaru      = newnode();           // Membuat node baru
                nodeBaru->next      = Tail;             // Menambah alamat node baru next sama dengan Tail
                nodeBaru->prev      = Tail->prev;       // Node prev dari nodebaru adalah node sebelum Tail
                Tail->prev->next    = nodeBaru;         // Alamat node prev yang nextnya adalah node baru
                Tail->prev          = nodeBaru;         // Tail prev adalah node baru
            }
            sambutan("\n Data e-book Berhasil Dibuat\n");  // Memberikan pesan bahwa data e-book berhasil ditambahkan.
            file_data_ebook_change(); // Mengganti data di file
            return;
        }

        // Jika meletakkan di posisi pertama
        else if (posisi == 1) {
            addfirst(); // Menambahkan di awal
        }

        // Jika posisi urutan yang ingin dimasukkan lebih besar dari data yang ada
        else if (posisi > jumlah || posisi < 1) {
            cout << "_________________________________________________________" << endl;
            cout << "   ERROR, nomor urutan yang anda masukkan tidak sesuai"    << endl;
            cout << "_________________________________________________________" << endl;
            return;
        }

        // Jika urutan posisi memenuhi kondisi
        else if (posisi < jumlah) {
            // Membuat node baru
            node *nodeBaru = newnode(); // Membuat node baru
            node *alamat_sementara = Head; // Pointer sementara untuk menjelajah linked list
            for (int i = 1; i < posisi - 1; i++) {
                if (alamat_sementara->next != nullptr) {
                    alamat_sementara = alamat_sementara->next; // Menggeser pointer ke posisi yang diinginkan
                }
            }
            nodeBaru->next = alamat_sementara->next;
            nodeBaru->prev = alamat_sementara;
            alamat_sementara->next->prev = nodeBaru;
            alamat_sementara->next = nodeBaru; // Menyisipkan node baru di posisi yang diinginkan
        }

        else {
            sambutan(" Posisi salah, silahkan masukkan minimal dua data ");
            return;
        }

        sambutan("\n Data e-book Berhasil Dibuat\n");
        file_data_ebook_change(); // Mengganti data di file
        return;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [10] Melihat semua data
    void lihat_data_Ebook(){
        int i = 0;
        alamat_sementara = Head;
        while (alamat_sementara != nullptr) {
            cout << "\n[" << i + 1 << "]  ";
            cout << "Judul              : "        << alamat_sementara->data_Ebook.judul_Ebook;
            cout << "\n     Jumlah halaman     : " << alamat_sementara->data_Ebook.jmlhalaman_Ebook;
            cout << "\n     Nama Penulis       : " << alamat_sementara->data_Ebook.nama_penulis;
            cout << "\n     deskripsi          : " << alamat_sementara->data_Ebook.deskripsi_Ebook;
            cout << "\n     Harga              : " << alamat_sementara->data_Ebook.harga;
            alamat_sementara = alamat_sementara->next;
            i++;
            garis();
        }
        return;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [11] Proses melihat salah satu data e-book
    void lihat_data_satu_Ebook(){

        // Mencari data e-book dengan search
        cek_data = proses_search();

        if (cek_data == "ada"){
            sambutan(" Data ebook yang di cari ");
            // Jika data ditemukan
            cout << "\n[" << index + 1 << "]  ";
            cout << "Judul              : " << judul_Ebook;
            cout << "\n     Jumlah halaman     : " << halaman;
            cout << "\n     Nama Penulis       : " << nama_penulis;
            cout << "\n     deskripsi          : " << deskripsi_Ebook;
            cout << "\n     Harga              : " << harga;
            garis();
        }

        else if (cek_data == "tidak"){
            return;
        }
    }
//___________________________________________________________________________________________________________________________________________________//

//  [12] Proses mengubah data e-book
    void mengubah_ebook(){

        // Masukan judul Ebook dan nama penulis yang ingin dicari
        judul_Ebook = input_string_khusus("Masukan judul Ebook yang ingin di cari  >> ", judul_Ebook);
        nama_penulis = bukan_angka       ("Masukan nama penulis yang ingin di cari >> ", nama_penulis);
        cls();

        alamat_sementara = Head;
        index = 0;

        // Membandingkan judul dan nama
        while (true){   

            // Jika ditemukan kesamaan judul Ebook dan nama penulis
            if (alamat_sementara->data_Ebook.judul_Ebook == judul_Ebook && alamat_sementara->data_Ebook.nama_penulis == nama_penulis){

                nama_penulis = input_string_khusus("Masukan nama penulis baru        >> ", nama_penulis);
                alamat_sementara->data_Ebook.judul_Ebook  = judul_Ebook;
                alamat_sementara->data_Ebook.nama_penulis = nama_penulis;
                halaman      = harus_angka_int("Masukan jumlah halaman baru      >> ");
                alamat_sementara->data_Ebook.jmlhalaman_Ebook = error_batas("Masukan jumlah halaman baru      >> ", halaman, 20, 700);
                alamat_sementara->data_Ebook.deskripsi_Ebook  = input_string_khusus("Masukan deskripsi cerita baru    >> ", alamat_sementara->data_Ebook.deskripsi_Ebook);
                harga        = harus_angka_int("Masukan harga baru               >> ");
                alamat_sementara->data_Ebook.harga            = error_batas("Masukan harga baru               >> ", harga, 10000, 2147483647);

                // Jika tidak ditemukan kesamaan judul Ebook dan nama penulis
                cout << "+-------------------------------------+\n";
                cout << "|      Data berhasil di ubah...       |\n";
                cout << "+-------------------------------------+\n\n";
                cls();

                lihat_data_Ebook();
                break;
            }

            // Jika sudah sampai data akhir dan tidak di temukan
            else if (alamat_sementara->next == nullptr){
                // Jika tidak ditemukan kesamaan judul Ebook dan nama penulis
                cout << "+-------------------------------------+\n";
                cout << "|    Data yang di cari tidak ada...   |\n";
                cout << "+-------------------------------------+\n\n";
                break;
            }

            else{
                alamat_sementara = alamat_sementara->next;
                index++;
            }
        }

        file_data_ebook_change();
    }
//___________________________________________________________________________________________________________________________________________________//

//  [13] Proses hapus data e-book dari depan
    void deletefirst(){

        // Jika datanya hanya ada satu
        if ((Head)->next == nullptr){
            Head = nullptr;
            return;
        }

        alamat_sementara = Head;                    // Menyimpan alamat node awal (Head) dalam pointer sementara alamat_sementara.
        Head             = Head->next;              // Memindahkan Head ke node selanjutnya (next node) dalam linked list.
        alamat_sementara->next->prev = nullptr;     // Menyatakan bahwa prev dari node setelah head tidak memiliki node sebelumnnya.
        delete alamat_sementara;                    // Menghapus node yang sebelumnya adalah Head (node terakhir) dari memori.

        sambutan(" Data e-book Berhasil Dihapus");
        file_data_ebook_change();
        return;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [14] Proses hapus data e-book dari tengah
    void deletemid(){
        // Mencari data e-book dengan search
        cek_data = proses_search();

        // Hapus data e-book yang sudah ditemukan
        if (cek_data == "ada"){

            // Menghubungkan node sebelum dan sesudahnya secara langsung
            alamat_sementara->prev->next = alamat_sementara->next;
            alamat_sementara->next->prev = alamat_sementara->prev;

            // Menghapus node saat ini
            delete alamat_sementara;

            sambutan(" Data e-book Berhasil Dihapus ");
            index = 0;
        }

        else if (cek_data == "tidak"){
            return;
        }

        else if (lenght() < 3){
            garis();
            cout << "Harus memiliki minimal 3 data untuk menggunakan fitur hapus di tengah";
            garis();
            return;
        }

        file_data_ebook_change();
    }
//___________________________________________________________________________________________________________________________________________________//

//  [15] Proses hapus data e-book dari belakang
    void deletelast(){

        // Jika datanya hanya ada satu
        if ((Head)->next == nullptr){
            Head = nullptr;
            return;
        }

        alamat_sementara = Tail;        // Menyimpan alamat node terakhir (tail) dalam pointer sementara alamat_sementara.
        Tail             = Tail->prev;  // Memindahkan tail ke node sebelumnya (previous node) dalam linked list.
        Tail->next       = nullptr;     // Menyatakan bahwa node yang sebelumnya adalah tail sekarang tidak memiliki node berikutnya (next) karena menjadi ujung akhir.
        delete alamat_sementara;        // Menghapus node yang sebelumnya adalah tail (node terakhir) dari memori.

        sambutan(" Data e-book Berhasil Dihapus");
        file_data_ebook_change();
        return;
    }
//___________________________________________________________________________________________________________________________________________________//

//  [16] Fungsi Sorting
    node* merge(node* left, node* right, bool ascending, string pilihan_sort) {
        node dummy;
        node* current = &dummy;

        while (left && right) {
            bool condition;
            if (pilihan_sort == "harga") {
                condition = (ascending && left->data_Ebook.harga <= right->data_Ebook.harga) ||
                            (!ascending && left->data_Ebook.harga >= right->data_Ebook.harga);
            } else if (pilihan_sort == "halaman") {
                condition = (ascending && left->data_Ebook.jmlhalaman_Ebook <= right->data_Ebook.jmlhalaman_Ebook) ||
                            (!ascending && left->data_Ebook.jmlhalaman_Ebook >= right->data_Ebook.jmlhalaman_Ebook);
            } else {
                // Handle other cases if needed
            }

            if (condition) {
                current->next = left;
                left->prev = current;
                left = left->next;
            } else {
                current->next = right;
                right->prev = current;
                right = right->next;
            }
            current = current->next;
        }

        if (left) {
            current->next = left;
            left->prev = current;
        } else {
            current->next = right;
            right->prev = current;
        }

        return dummy.next;
    }

    node* mergeSort(node* head, bool ascending, string pilihan_sort) {
        if (!head || !head->next) {
            return head;
        }

        node* middle = head;
        node* fast = head->next;

        while (fast) {
            fast = fast->next;
            if (fast) {
                fast = fast->next;
                middle = middle->next;
            }
        }

        node* left = head;
        node* right = middle->next;
        left->prev = nullptr;
        middle->next = nullptr;

        left = mergeSort(left, ascending, pilihan_sort);
        right = mergeSort(right, ascending, pilihan_sort);

        return merge(left, right, ascending, pilihan_sort);
    }




//___________________________________________________________________________________________________________________________________________________//
//                                                                *FUNGSI UNTUK MENU*                                                                //
//___________________________________________________________________________________________________________________________________________________//

//  [1] Untuk menu pilihan sorting    
    void menuSort(string pernyataan){
        while (true){

            pilihan_disorting = menu(menu_disorting, pernyataan, 5, pilihan_disorting);

            // Jika pilihan melihat berdasarkan jumlah halaman descending
            if (pilihan_disorting == "1"){
                sambutan(" Urutan berdasarkan Jumlah halaman Ascending ");
                alamat_sementara = mergeSort(Head, true, "halaman");

                int i = 0; // Untuk menghitung perulangan

                while (alamat_sementara != nullptr){
                    cout << "\n[" << i + 1 << "]  ";
                    cout << "Judul              : " << alamat_sementara->data_Ebook.judul_Ebook;
                    cout << "\n     Jumlah halaman     : " << alamat_sementara->data_Ebook.jmlhalaman_Ebook;
                    cout << "\n     Nama Penulis       : " << alamat_sementara->data_Ebook.nama_penulis;
                    cout << "\n     deskripsi          : " << alamat_sementara->data_Ebook.deskripsi_Ebook;
                    cout << "\n     Harga              : " << alamat_sementara->data_Ebook.harga;
                    alamat_sementara = alamat_sementara->next;
                    i++;
                    garis();
                }
                cls();
            }

            // Jika pilihan melihat berdasarkan jumlah halaman descending
            else if (pilihan_disorting == "2"){
                sambutan(" Urutan berdasarkan Jumlah halaman Descending ");
                alamat_sementara = mergeSort(Head, false, "halaman");

                int i = 0; // Untuk menghitung perulangan

                while (alamat_sementara != nullptr){
                    cout << "\n[" << i + 1 << "]  ";
                    cout << "Judul              : " << alamat_sementara->data_Ebook.judul_Ebook;
                    cout << "\n     Jumlah halaman     : " << alamat_sementara->data_Ebook.jmlhalaman_Ebook;
                    cout << "\n     Nama Penulis       : " << alamat_sementara->data_Ebook.nama_penulis;
                    cout << "\n     deskripsi          : " << alamat_sementara->data_Ebook.deskripsi_Ebook;
                    cout << "\n     Harga              : " << alamat_sementara->data_Ebook.harga;
                    alamat_sementara = alamat_sementara->next;
                    i++;
                    garis();
                }

                while (Head != nullptr){
                    node *alamat_sementara = Head; // Simpan alamat node yang akan dihapus
                    Head = Head->next;             // Geser pointer kepala ke node berikutnya
                    delete alamat_sementara;       // Bebaskan memori node yang dihapus
                }
                file_data_ebook_read();
                cls();
            }

            // Jika pilihan melihat berdasarkan harga ascending
            else if (pilihan_disorting == "3"){
                sambutan(" Urutan berdasarkan Harga Ascending ");
                alamat_sementara = mergeSort(Head, true, "harga");

                int i = 0; // Untuk menghitung perulangan

                while (alamat_sementara != nullptr){
                    cout << "\n[" << i + 1 << "]  ";
                    cout << "Judul              : " << alamat_sementara->data_Ebook.judul_Ebook;
                    cout << "\n     Jumlah halaman     : " << alamat_sementara->data_Ebook.jmlhalaman_Ebook;
                    cout << "\n     Nama Penulis       : " << alamat_sementara->data_Ebook.nama_penulis;
                    cout << "\n     deskripsi          : " << alamat_sementara->data_Ebook.deskripsi_Ebook;
                    cout << "\n     Harga              : " << alamat_sementara->data_Ebook.harga;
                    alamat_sementara = alamat_sementara->next;
                    i++;
                    garis();
                }
                Head = nullptr;
                Tail = nullptr;
                file_data_ebook_read();
                
                cls();
            }

            // Jika pilihan melihat berdasarkan harga descending
            else if (pilihan_disorting == "4"){
                sambutan(" Urutan berdasarkan Harga Descending ");
                alamat_sementara = mergeSort(Head, false, "harga");

                int i = 0; // Untuk menghitung perulangan

                while (alamat_sementara != nullptr){
                    cout << "\n[" << i + 1 << "]  ";
                    cout << "Judul              : " << alamat_sementara->data_Ebook.judul_Ebook;
                    cout << "\n     Jumlah halaman     : " << alamat_sementara->data_Ebook.jmlhalaman_Ebook;
                    cout << "\n     Nama Penulis       : " << alamat_sementara->data_Ebook.nama_penulis;
                    cout << "\n     deskripsi          : " << alamat_sementara->data_Ebook.deskripsi_Ebook;
                    cout << "\n     Harga              : " << alamat_sementara->data_Ebook.harga;
                    alamat_sementara = alamat_sementara->next;
                    i++;
                    garis();
                }

                while (Head != nullptr){
                    node *alamat_sementara = Head; // Simpan alamat node yang akan dihapus
                    Head = Head->next;             // Geser pointer kepala ke node berikutnya
                    delete alamat_sementara;       // Bebaskan memori node yang dihapus
                }
                file_data_ebook_read();
                cls();
            }

            // Keluar dari menu
            else if (pilihan_disorting == "5"){
                break;
            }

            // Inputan yang di masukan salah atau tidak sesuai
            else{
                inputan_salah();
            }
        }
    }
//___________________________________________________________________________________________________________________________________________________//

//  [2] Untuk menu create
    void menuTambah(){
        while (true){
            pilihan_tambah = menu(menu_tambah, "Menu Tambah (E-Book)", 4, pilihan_tambah);

            if (pilihan_tambah == "1"){
                addfirst();
                cls();
            }

            else if (pilihan_tambah == "2"){
                addmid();
                cls();
            }

            else if (pilihan_tambah == "3"){
                addlast();
                cls();
            }

            // Pilihan Keluar
            else if (pilihan_tambah == "4"){
                break;
            }

            // Inputan yang di masukan salah atau tidak sesuai
            else{
                inputan_salah();
            }
        }
    }
//___________________________________________________________________________________________________________________________________________________//

//  [3] Untuk menu read
    void menuLihat(){
        // Mengecek apakah data ada atau tidak
        if (Head == nullptr){
            data_kosong();
            return;
        }
        while (true){
            pilihan_lihat = menu(menu_lihat, "Menu Lihat (E-Book)", 6, pilihan_lihat);

            // Melihat semua data e-book dari Head
            if (pilihan_lihat == "1"){
                lihat_data_Ebook();
                cls();
            }

            // Melihat semua data e-book dari Tail
            else if (pilihan_lihat == "2") {

                int i = lenght() + 1;
                alamat_sementara = Tail;
                while (alamat_sementara != nullptr){
                    cout << "\n[" << i - 1 << "]  ";
                    cout << "Judul              : " << alamat_sementara->data_Ebook.judul_Ebook;
                    cout << "\n     Jumlah halaman     : " << alamat_sementara->data_Ebook.jmlhalaman_Ebook;
                    cout << "\n     Nama Penulis       : " << alamat_sementara->data_Ebook.nama_penulis;
                    cout << "\n     deskripsi          : " << alamat_sementara->data_Ebook.deskripsi_Ebook;
                    cout << "\n     Harga              : " << alamat_sementara->data_Ebook.harga;
                    alamat_sementara = alamat_sementara->prev;
                    i--;
                    garis();
                }
                cls();
            }

            // Melihat salah satu data e-book
            else if (pilihan_lihat == "3"){

                lihat_data_satu_Ebook();
                cls();
            }

            // Melihat data e-book dengan sorting
            else if (pilihan_lihat == "4"){
                menuSort(" Menu Sorting ");
            }

            // Melihat data histori user masuk
            else if (pilihan_lihat == "5"){
                // Mengecek apakah data ada atau tidak
                if (front == nullptr || rear == nullptr){
                    cout << "+--------------------------------------------------------------+\n";
                    cout << "| Untuk sesi ini belum ada pengguna yang terdeteksi masuk...   |\n";
                    cout << "+--------------------------------------------------------------+\n\n";
                    cls();
                    return;
                }
                displayHistory();
            }

            // Keluar dari menu
            else if (pilihan_lihat == "6"){
                break;
            }

            // Inputan yang di masukan salah atau tidak sesuai
            else {
                inputan_salah();
            }
        }
    }
//___________________________________________________________________________________________________________________________________________________//

//  [4] Untuk menu update
    void menuUbah(){
        // Mengecek apakah data ada atau tidak
        if (Head == nullptr){
            data_kosong();
            return;
        }
        while (true){
            pilihan_ubah = menu(menu_ubah, "Menu Ubah (E-Book)", 2, pilihan_ubah);

            // Mengubah salah satu data e-book
            if (pilihan_ubah == "1"){
                mengubah_ebook();
                cls();
            }

            // Keluar menu
            else if (pilihan_ubah == "2"){
                break;
            }

            // Inputan yang di masukan salah atau tidak sesuai
            else{
                inputan_salah();
            }
        }
    }
//___________________________________________________________________________________________________________________________________________________//

//  [5] Untuk menu delete
    void menuHapus(){
        // Mengecek apakah data ada atau tidak
        if (Head == nullptr){
            data_kosong();
            return;
        }
        while (true){
            pilihan_hapus = menu(menu_hapus, "Menu Hapus (E-Book)", 4, pilihan_hapus);

            // Menghapus data tengah
            if (pilihan_hapus == "1"){
                deletemid();
                cls();
            }

            // Menghapus data awal
            else if (pilihan_hapus == "2"){
                deletefirst();
                cls();
            }

            // Menghapus data akhir
            else if (pilihan_hapus == "3"){

                deletelast();
                cls();
            }

            // Keluar Menu
            else if (pilihan_hapus == "4"){
                break;
            }

            // Inputan yang di masukan salah atau tidak sesuai
            else{
                inputan_salah();
            }
        }
    }
//___________________________________________________________________________________________________________________________________________________//

//  [6] Menu utama admin
    void menu_admin_utama(){
        // Menu CRUD Admin
        while (true){
            pilihan_admin = menu(menu_admin, "Menu Admin (E-Book)", 5, pilihan_admin);

            // Menu Tambah
            if (pilihan_admin == "1"){
                menuTambah();
            }

            // Menu Lihat
            else if (pilihan_admin == "2"){
                menuLihat();
            }

            // Menu Ubah
            else if (pilihan_admin == "3"){
                menuUbah();
            }

            // Menu Hapus
            else if (pilihan_admin == "4"){
                menuHapus();
            }

            // Pilihan Keluar Menu
            else if (pilihan_admin == "5"){
                break;
            }

            // Inputan yang di masukan salah atau tidak sesuai
            else{
                inputan_salah();
            }
        }
    }
//___________________________________________________________________________________________________________________________________________________//

//  [7] Untuk menu read
    void menuLihatUser(){
        // Mengecek apakah data ada atau tidak
        if (Head == nullptr){
            data_kosong();
            return;
        }
        while (true){
            pilihan_lihat = menu(menu_lihat_user, "Menu Lihat (E-Book)", 6, pilihan_lihat);

            // Melihat semua data e-book dari Head
            if (pilihan_lihat == "1"){
                lihat_data_Ebook();
                cls();
            }

            // Melihat semua data e-book dari Tail
            else if (pilihan_lihat == "2") {

                int i = lenght() + 1;
                alamat_sementara = Tail;
                while (alamat_sementara != nullptr){
                    cout << "\n[" << i - 1 << "]  ";
                    cout << "Judul              : " << alamat_sementara->data_Ebook.judul_Ebook;
                    cout << "\n     Jumlah halaman     : " << alamat_sementara->data_Ebook.jmlhalaman_Ebook;
                    cout << "\n     Nama Penulis       : " << alamat_sementara->data_Ebook.nama_penulis;
                    cout << "\n     deskripsi          : " << alamat_sementara->data_Ebook.deskripsi_Ebook;
                    cout << "\n     Harga              : " << alamat_sementara->data_Ebook.harga;
                    alamat_sementara = alamat_sementara->prev;
                    i--;
                    garis();
                }
                cls();
            }

            // Melihat salah satu data e-book
            else if (pilihan_lihat == "3"){

                lihat_data_satu_Ebook();
                cls();
            }

            // Melihat data e-book dengan sorting
            else if (pilihan_lihat == "4"){
                menuSort(" Menu Sorting ");
            }

            // Melakukan Pemesanan
            else if (pilihan_lihat == "5"){
                sambutan(" DAFTAR BUKU ");
                lihat_data_Ebook();
                garis();

                // Memilih pesanan
                lihat_data_satu_Ebook();
                if (cek_data == "tidak"){
                    cls();
                    break;
                }

                cout << "\nTotal pembelian : Rp" << harga << "\nPembayaran di lakukan via pulsa, pastikan pulsa anda mencukupi saat pembelian...\n\n";
                cls();
                garis();
                cout << " Pembelian berhasil, silahkan cek gmail anda untuk mengakses e-book";
                garis();
                cls();
                    
            }

            // Keluar dari menu
            else if (pilihan_lihat == "6"){
                break;
            }

            // Inputan yang di masukan salah atau tidak sesuai
            else {
                inputan_salah();
            }
        }
    }
//___________________________________________________________________________________________________________________________________________________//

//  [8] Menu utama user
    void menu_user_utama(){
        // Menu user
        while (true){
            pilihan_user = menu(menu_user, "Menu Pengguna (E-Book)", 2, pilihan_user);

            // Melihat daftar harga
            if (pilihan_user == "1"){
                menuLihatUser();
            }

            // Pilihan Keluar Menu
            else if (pilihan_user == "2"){
                break;
            }

            // Inputan yang di masukan salah atau tidak sesuai
            else{
                inputan_salah();
            }
        }
    }
//___________________________________________________________________________________________________________________________________________________//






//___________________________________________________________________________________________________________________________________________________//
//                                                          ***  TAMPILAN UTAMA PROGRAM  ***                                                         //
//___________________________________________________________________________________________________________________________________________________//

int main(){

    // Membersihkan layar
    system("cls");

    // Membaca data dari file dan memasukkannya ke dalam linked list
    file_data_ebook_read();

    // Masuk ke menu utama
    while (true){
        pilihan_masuk = menu(menu_awal, "Selamat datang di Pemesanan E-Book", 3, pilihan_masuk);

        // Jika ingin registrasi
        if (pilihan_masuk == "1"){
            sambutan(" M E N U  R E G I S T R A S I ");
            registrasi();
            cls();
        }

        // Jika ingin login
        else if (pilihan_masuk == "2"){
            sambutan(" M E N U  L O G I N ");
            proses_login();
            cls();

            // Jika Login sebagai admin
            if (user == "xuensun" && pass == "09596"){
                menu_admin_utama();
            }

            // Jika Login sebagai user
            else if (user != "dinda" || pass != "095"){
                menu_user_utama();
            }
        }

        // Jika ingin logout
        else if (pilihan_masuk == "3"){
            garis();
            cout << "Terima kasih sudah menggunakan program ini";
            garis();
            cls();
            break;
        }

        // Inputan yang di masukan salah atau tidak sesuai
        else{
            inputan_salah();
        }
    }
}