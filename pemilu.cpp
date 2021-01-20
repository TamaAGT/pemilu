#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
using namespace std;

//Variabel Global indeks anggota &  calon
int idk_anggota = 0;
int idk_calon = 0;

class Queue{
private:
    int depan; 
    int belakang;
    int arr[500];

public:
    // Konstruktor untuk queue
    Queue(){
        depan = -1; 
        belakang = -1;
        for(int i = 0; i < 100; i++){
            arr[i] = 0;
        }
    }
    // Cek apakah antrian kosong
    bool kosong(){
        if(depan == -1 && belakang == -1){
            return true; 
        } else {
        return false;
        }
    }
    // Cek apkah antrian penuh
    bool penuh(){
        if(belakang == sizeof(arr) - 1){
            return true; 
        }
        return false; 
    }
    // Input Data
    void enqueue(int val){
        if(penuh()){
            cout << "Data Penuh" << endl;
            return; 
        }
        else if(kosong()){
            depan = 0;
            belakang = 0;
            arr[belakang] = val;
        }
        else {
            belakang++;
            arr[belakang] = val; 
        }
    }
    // Mengeluarkan antrian sesuai urutan
    int dequeue(){
        int x; 
        
        if(kosong()){
            cout << "Data masih kosong" << endl; 
            return 0;
        }
        else if(depan == belakang){
            x = arr[depan];
            arr[depan] = 0;
            depan = -1; 
            belakang = -1;
        }
        else {
            x = arr[depan];
            depan++;
        }
        return x;
    }
    
    int hitung(){
        if(kosong()){
            return 0;
        }
        return (belakang - depan + 1);
    }
};

class Stack{
private:
    int top;
    int arr[500];

public:
    Stack(){
        top = -1;
        for(int i = 0; i < 500; i++){
            arr[i] = 0;
        }
    }
    bool isEmpty(){
        if(top == -1)
            return true;
        else 
            return false; 
    }
    bool isFull(){
        if(top == 500)
            return true; 
        else 
            return false; 
    }
    void push(int val){
        if(isFull()){
            cout << "Stack overflow" << endl; 
        }
        else {
            top++;
            arr[top] = val; 
        }
    }

    int pop(){
        if(isEmpty()){
            cout << "Stack underflow" << endl; 
            return 0;
        }
        else {
            int popValue = arr[top];
            arr[top] = 0;
            top--;
            return popValue; 
        }
    }

    int count(){
        return(top + 1);
    }

    void display(){
        cout << "Nilai pada stack sebagai berikut : " << endl; 
        for(int i = sizeof(arr) - 1; i >= 0; i--){
            cout << arr[i] << " ";
        }
    }

};

// Struct untuk menyimpan data buffer file
struct Anggota{
    int id;
    string nama;
    string alamat;
    string no_ktp;
    string status; 
};

// Linked list 
class Node {
public:
    int indeks;
	string nama;
	string alamat;
	string no_ktp;
    string status;
	Node* next; 
};

void sisipBelakang(Node** head_ref, int &indeks, string new_nama,string new_alamat, string no_ktp, string new_status){
    // Membuat agar indeks anggota berubah
    indeks++;

    Node* newNode = new Node();
	Node* tail = *head_ref; 

	// Mengisi data sesuai dengan parameter fungsi
    newNode->indeks = indeks; 
	newNode->nama = new_nama;
	newNode->alamat = new_alamat;
	newNode->no_ktp = no_ktp;
    newNode->status = new_status;

    // Apabila node masih kosong
	if(*head_ref == NULL){
		*head_ref = newNode; 
		return; 
	}
    // Mengiterasi node sampai belakang
	while(tail->next != NULL){
		tail = tail->next; 
	}
    //Sisip node ke paling belakang
	tail->next = newNode; 
	return;
}

void hapusNode(Node** head_ref, int id){
    Node* temp = *head_ref; 
    Node* prev = NULL; 
    // Apabila data ada pada ujung Node
    if(temp != NULL && temp->indeks == id){
        *head_ref = temp->next; 
        delete temp;
        return;
    }
    // Menelusuri linked list
    while(temp != NULL && temp->indeks != id){
        prev = temp;
        temp = temp->next; 
    }
    // Jika data tidak ditemukan
    if(temp == NULL){
        cout << "Data tidak ditemukan" << endl;
        return; 
    }
    prev->next = temp->next;
    //hapus memori
    delete temp; 
}

bool konfirmasi(Node* node, int id, bool &option){
    char input;

    while( node != NULL){
        if(node->indeks == id){
            cout << "Yakin ingin menghapus anggota?" << endl;
            cout << "+---------+-----------------------------+---------------------------------------+---------------------+"<< endl;
            cout << "|" << setw(5) << "ID" << setw(5) << "|" << setw(15) << "NAMA" << setw(15) << "|" 
            << setw(20) << "ALAMAT" << setw(20) << "|" << setw(13) << "NO. KTP" << setw(9) << "|" << endl;
            cout << "+---------+-----------------------------+---------------------------------------+---------------------+" << endl;
            cout << "|" << setw(5) << node->indeks << setw(5) << "|" << setw(29) <<  node->nama << "|" << setw(39) << node->alamat<< "|" << setw(21) << node->no_ktp << "|" << endl;
            cout << "+---------+-----------------------------+---------------------------------------+---------------------+" << endl;
            cout << "Input (Y/T) : ";
            cin >> input;
            if(input == 'y' || input == 'Y'){
                option = true;
                return option; 
            }
        }
        node = node->next; 
    }
    option = false; 
    return option; 
}

//Cek apakah indeks sudah ada pada daftar orang yg memilih
bool cari(int indeks, Queue daf_pem){
        for(int i = 0; i < daf_pem.hitung(); i++){
            if(indeks == daf_pem.dequeue()){
              return true;
            }
        }
        return false; 
    }

void simpanFileIdk(int indeks, string fileName){
    //Mendeklarasikan file
    ofstream file; 

    //Membuka file untuk menyimpan data stack golput
    file.open(fileName.c_str());

    file << indeks << endl; 

    //Menutup file
    file.close();
}

void bacaQueue(Queue &suara){
    ifstream file;
    //Membuka file
    file.open("suara.txt");

    if(file.is_open()){
        int line;
        //Looping sampai ke data terakhir file
        while(!file.eof()){
            // meyimpan setiap data pada buffer
            file >> line;

            if(!file){
                break;
            }
            // Masukkan data pada queue
            suara.enqueue(line);
        }
    }
}

void bacaStack(Stack &golput){
    ifstream stack;
    //Membuka file
    stack.open("golput.txt");

    if(stack.is_open()){
        int line; 

        while(!stack.eof()){
            // Menyimpan setiap line pada file pada buffer 
            stack >> line; 

            if(!stack){
                break;
            }
            // Menginputkan nilai pada Stack golput
            golput.push(line);
        }
        //Menutup file jika sudah selesai
        stack.close();
    }
}

void bacaList(Node** node, Anggota &data, string fileName){
    ifstream outFile;

    outFile.open(fileName.c_str());

    if(outFile.is_open()){
        while(!outFile.eof()){
            //Masukkan data file pada buffer yang ada 
            outFile >> data.id;
            
            outFile.get();

            getline(outFile, data.nama);
            getline(outFile, data.alamat);
            getline(outFile, data.no_ktp);
            getline(outFile, data.status);

            if(!outFile){
                break;
            }
            data.id -= 1;
            //Sisip data node dari var buffer
            sisipBelakang(node, data.id, data.nama, data.alamat, data.no_ktp, data.status);
        }
    }
}

void updateIndeks(Node* head_ref, int &indeks){
    // cek apakah nilai indeks sudah mulai digunakan
    if(head_ref == NULL){
        return;
    }
    //mencari nilai indeks terkahir dari node
    while(head_ref != NULL){
        head_ref = head_ref->next; 
    }

    indeks = head_ref->indeks;
    indeks++;
}

void daftarAnggota(Node* node, string jenis){
    cout << "+---------+-----------------------------+---------------------------------------+---------------------+"<< endl;
    cout << "|" << setw(5) << "ID" << setw(5) << "|" << setw(15) << "NAMA" << setw(15) << "|" 
    << setw(20) << "ALAMAT" << setw(20) << "|" << setw(13) << "NO. KTP" << setw(9) << "|" << endl;
    cout << "+---------+-----------------------------+---------------------------------------+---------------------+" << endl;

    if(node == NULL){
        cout << endl; 
        cout << "!!! DATA KOSONG !!!" << endl << endl;
        return;
    }

    while(node != NULL){
        if(node->status == jenis){
            cout << "|" << setw(5) << node->indeks << setw(5) << "|" << setw(29) <<  node->nama << "|" << setw(39) << node->alamat<< "|" << setw(21) << node->no_ktp << "|" << endl;
            cout << "+---------+-----------------------------+---------------------------------------+---------------------+" << endl;
        }
        node = node->next; 
    }
}

void inputAnggota(Node** head_ref, int &indeks, string status){
    string nama, alamat, ktp;
    int temp = indeks; 

    cout << "Nama    : ";
    getline(cin, nama);
    cout << "Alamat  : ";
    getline(cin, alamat);
    cout << "NO. KTP : ";
    getline(cin, ktp);
    //Proses input ke node 
    sisipBelakang(head_ref, indeks, nama, alamat, ktp, status);

    cout << endl << endl;
    if(temp != indeks){
        cout << "INPUT BERHASIL" << endl;
    } else{
        cout << "INPUT GAGAL" << endl; 
    }
}

void hapusAnggota(Node** pemilih){
    bool lanjut = false;
    int id; 

    cout << "Masukkan ID  : ";
    cin >> id;
    // Mengonfirmasi apakah id yang dipilih telah sesuai
    konfirmasi(*pemilih, id,lanjut);

    if(lanjut == true){
    // mengahapuse node apabila konfirmasi dinyatakan benar
    hapusNode(pemilih, id);
    cout << endl << endl;
    cout << "---- Data telah berhasil dihapus -----" << endl << endl; 
    } else {
    cout << "---- Maaf Data tidak ditemukan -----" << endl << endl; 
    }
}

void cetakCalon(Node* calon){
    int urut = 0;

    system("cls");
    if(calon == NULL){
        cout << endl << endl;
		cout << "!!! DATA CALON MASIH KOSONG !!!" << endl; 
		return; 
	}
    
    cout << "----------- DAFTAR CALON -----------" << endl << endl;
    while(calon != NULL){
        if(calon->status == "Calon"){
            urut++;
            cout << "+----------------------------+" << endl; 
            cout << "|" << " # NOMOR " << urut << endl;
            cout << "|" << endl; 
            cout << "| " << calon->nama << endl; 
            cout << "+----------------------------+" << endl << endl;
        }
        calon = calon->next; 
    }
    cout << "!!! GOLPUT PILIH NOMOR : -1 !!!" << endl; 
}

bool validasi(Node* temp, Queue daf_pem, int tarIdk, string tarNama, string tarNomor){    
    // Cek apakah orang sudah pernah memilih
    if(daf_pem.kosong() == false){
        // Apabila indeks pemilih sudah ada di queue maka gagal
        if(cari(tarIdk, daf_pem) == true){
            cout << endl;
            cout << "ANDA SUDAH PERNAH MEMILIH" << endl << endl;
            return false;
        }
    }
    // validasi data pemilih
	while( temp != NULL){
		if((temp->indeks == tarIdk) && (temp->nama == tarNama) && (temp->no_ktp == tarNomor)){
			return true;
		}
		temp = temp->next; 
	}
    return false; 
}

void inputSuara(Node** pemilih, Node** calon, Queue &daf_pem, Stack &putih){
    Node* temp = *calon; 
    string nama, no_ktp;
    int indeks, no_calon;
    char pilih; 
    int nomor = 0;

    cout << "ID       : ";
    cin >> indeks;
    cin.ignore();
    cout << "Nama     : ";
    getline(cin, nama);
    cout << "NO. KTP  : ";
    getline(cin, no_ktp);

    // Cek apakah peserta boleh memilih 
    if(validasi(*pemilih, daf_pem, indeks, nama, no_ktp)){
        cout << endl;
        cout << "!!! ANDA TERDAFTAR DAN SELAMAT MEMILIH !!!" << endl << endl; 
        system("PAUSE");
        cout << endl;
        // Menampilkan daftar calon terpilih
        cetakCalon(*calon);

        while(true){
            cout << endl << endl; 
            cout << "PILIH NOMOR CALON : "; 
            cin >> no_calon;
            cout << endl; 
            cout << "Yakin dengan pilihan anda? (Y/T) : ";
            cin >> pilih; 

            if(pilih != 'y' || pilih != 'Y'){
                break;
            }
        }

         // Masukkan indeks pemilih ke daftar orang sudah memilih
        daf_pem.enqueue(indeks);
        // Menyimpan daftar orang yang sudah memilih
        simpanFileIdk(indeks, "suara.txt");

        // Apabila pemilih memutuskan golput masukkan ke stack golput
        if(no_calon == -1){
            putih.push(indeks);
            // Menyimpan data golput ke dalam file
            simpanFileIdk(indeks, "golput.txt");
        }
        else {
            // Tambahkan node pemilih ke belakang node calon
            while(temp != NULL){
                if(temp->status == "Calon"){
                    nomor++;
                    if( nomor == no_calon ){
                        sisipBelakang(&temp, indeks, nama, "-", "-", "Pemilh" );
                    return; 
                }
                }
                temp = temp->next; 
            }
        }
    } else {
        cout << endl << endl; 
        cout << "MAAF ANDA TIDAK DAPAT MEMILIH" << endl;
    }
}

int hitungSuara(Node* temp){
	int number = 0;

    temp = temp->next;
    // Menelusuri node selama node selanjutnya bukan Calon
	while(temp != NULL){
        if(temp->status == "Calon"){
            break;
        }
        if(temp->status == "Pemilih"){
            number++;
        }
        number++;
        temp = temp->next; 
	}
    return number;   
}

void hasilPem(Queue suara, Node* calon, Stack golput){
    Node* temp = calon;
    Node* ptr[100];
    int jumlah = 0;
    int hasil = 0;

    // Mengambil data calon dari node kemudian simpan pada array
    do{
		if(temp->status == "Calon"){
			ptr[jumlah] = temp;
			jumlah++;
		}
		temp = temp->next; 
	}while(temp != NULL);

    // Outputkan perolehan suara berdasarkan array yang sudah terimpan
	for(int i = 0; i < jumlah; i++){
		hasil = hitungSuara(ptr[i]);
		cout << "+----------------------------+" << endl; 
        cout << "|" << " # NOMOR " << i + 1 << endl;
        cout << "|" << endl; 
        cout << "| " << ptr[i]->nama << endl;
        cout << "| " << hasil << " SUARA" << endl;  
        cout << "+----------------------------+" << endl << endl;
	}
    cout << "TOTAL PEMILIH  : " << suara.hitung() << endl;
    cout << "JUMLAH GOLPUT  : " << golput.count() << endl << endl;
}

void print(Node* n){
    while(n != NULL){
        cout << n->indeks << endl;
        cout << n->nama << endl;
        cout << n->alamat << endl; 
        cout << n->no_ktp << endl;
        cout << n->status << endl;
        n = n->next; 
    }
}

int main(){
    int pilihan;

    Node* pemilih = NULL; // Inisiasi linked list untuk pemilih
    Node* calon = NULL; // Inisiasi linked list untuk calon terpilih
    Queue suara; //Inisiasi queue untuk menyimpan data idk_pemilih
    Stack golput;
    Anggota buffer;

    //Membaca indeks orang yang sudah pernah memilih
    bacaQueue(suara);
    // Membaca dari database file daftar orang golput sebelumnya
    bacaStack(golput);

    // Membaca data anggota pemilih dari file
    bacaList(&pemilih, buffer, "pemilih.txt");
    // Membaca data anggota calon dari file
    bacaList(&calon, buffer, "calon.txt");
    
    do{
        system("cls");
        cout << "+-----------------------------------------+" << endl; 
        cout << "|         PROGRAM PEMILIHAN SUARA         |" << endl;
        cout << "+-----------------------------------------+" << endl << endl;
        cout << "[1] Daftar Pemilih" << endl; 
        cout << "[2] Daftar Calon Terpilih" << endl; 
        cout << "[3] Input Suara" << endl; 
        cout << "[4] Hasil Pemilihan" << endl;
        cout << "[5] Keluar" << endl << endl;
        cout << "Pilih : ";
        cin >> pilihan;
        
        switch(pilihan){
            case 1:
               do{
                    system("cls");
                    cout << "+----------------------------------+" << endl; 
                    cout << "|          DAFTAR PEMILIH          |" << endl; 
                    cout << "+----------------------------------+" << endl << endl; 
                    cout << "[1] Lihat Daftar Pemilih" << endl;
                    cout << "[2] Tambah Daftar Pemilih" << endl;
                    cout << "[3] Hapus Daftar Pemilih" << endl;
                    cout << "[4] Kembali" << endl << endl;
                    cout << "Pilih: ";
                    cin >> pilihan;
                    
                    switch(pilihan){
                        case 1:
                            system("cls");
                            cout << setw(70) << "+---------------------------------------+" << endl; 
                            cout << setw(70) << "|          LIST DAFTAR PEMILIH          |" << endl; 
                            cout << setw(70) << "+---------------------------------------+" << endl << endl << endl; 
                            daftarAnggota(pemilih, "Pemilih");
                            cout << endl << endl; 
                            system("PAUSE");
                        break;

                        case 2:
                            system("CLS");
                            cout << "+----------------------------------------+" << endl; 
                            cout << "|          INPUT DAFTAR PEMILIH          |" << endl; 
                            cout << "+----------------------------------------+" << endl << endl;
                            cin.ignore();
                            inputAnggota(&pemilih, idk_anggota, "Pemilih");
                            cout << endl << endl;
                            system("PAUSE");
                        break;

                        case 3:
                            system("CLS");
                            cout << "+----------------------------------------+" << endl; 
                            cout << "|          HAPUS DAFTAR PEMILIH          |" << endl; 
                            cout << "+----------------------------------------+" << endl << endl;
                            hapusAnggota(&pemilih);
                            system("PAUSE");
                        break;
                    }
                } while(pilihan != 4);
            break;

            case 2:
                do{
                system("CLS");
                cout << "+-----------------------------------------+" << endl; 
                cout << "|          DAFTAR CALON TERPILIH          |" << endl; 
                cout << "+-----------------------------------------+" << endl << endl; 
                cout << "[1] Lihat Daftar Calon" << endl;
                cout << "[2] Tambah Daftar Calon" << endl;
                cout << "[3] Hapus Daftar Calon" << endl;
                cout << "[4] Kembali" << endl << endl;
                cout << "Pilih: ";
                cin >> pilihan;

                switch(pilihan){
                        case 1:
                            system("CLS");
                            cout << setw(70) << "+------------------------------------+" << endl; 
                            cout << setw(70) << "|          LIST DAFTAR CALON         |" << endl; 
                            cout << setw(70) << "+------------------------------------+" << endl << endl << endl; 
                            daftarAnggota(calon, "Calon");
                            cout << endl << endl; 
                            system("PAUSE");
                        break;

                        case 2:
                            system("CLS");
                            cout << "+--------------------------------------+" << endl; 
                            cout << "|          INPUT DAFTAR CALON          |" << endl; 
                            cout << "+--------------------------------------+" << endl << endl;
                            cin.ignore();
                            inputAnggota(&calon, idk_calon, "Calon");
                            cout << endl << endl;
                            system("PAUSE");
                        break;

                        case 3:
                            system("CLS");
                            cout << "+----------------------------------------+" << endl; 
                            cout << "|          HAPUS DAFTAR PEMILIH          |" << endl; 
                            cout << "+----------------------------------------+" << endl << endl;
                            hapusAnggota(&calon);
                            system("PAUSE");
                        break;
                    }
                }while(pilihan != 4);
            break;
            
            case 3:
                system("CLS");
                cout << "+------------------------------------------+" << endl; 
                cout << "|       !!!   PEMUNGUTAN SUARA   !!!       |" << endl; 
                cout << "+------------------------------------------+" << endl << endl; 
                inputSuara(&pemilih, &calon, suara, golput);
                system("PAUSE");
            break;
            
            case 4:
                system("CLS");
                cout << "+-----------------------------------------+" << endl; 
                cout << "|          HASIL PEMILIHAN SUARA          |" << endl; 
                cout << "+-----------------------------------------+" << endl << endl;
                hasilPem(suara, calon, golput);
                system("PAUSE");
            break;
            
            case 5:
            system("CLS");
            cout << "+----------------------------------+" << endl; 
            cout << "|          KELUAR PROGRAM          |" << endl; 
            cout << "+----------------------------------+" << endl << endl;
            system("PAUSE");
            exit(1);
            break;

            default:
                system("CLS");
                cout << "Mohon masukkan indeks angka (1/2/3/4/5)" << endl << endl;
                system("PAUSE");
            break;
        }

    }while(pilihan != -1);
}
