#include <iostream>
#include <iomanip>
#include <string.h>
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
        return (belakang - depan + 1);
    }

    bool cari(int indeks){
        for(unsigned int i = 0; i < sizeof(arr); i++){
            if(arr[i] == indeks);
            return true;
        }
        return false; 
    }
};

class Stack{
private:
    int top;
    int arr[5];

public:
    Stack(){
        top = -1;
        for(int i = 0; i < 5; i++){
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
        if(top == 4)
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

void updateIndeks(Node* head_ref, int &indeks){
    // cek apakah nilai indeks sudah mulai digunakan
    if(head_ref == NULL){
        return;
    }
    //mencari nilai indeks terkahir dari node
    do{
        indeks++;
        head_ref = head_ref->next; 
    }
    while(head_ref->indeks != indeks);
}

void daftarAnggota(Node* node){
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
        cout << "|" << setw(5) << node->indeks << setw(5) << "|" << setw(29) <<  node->nama << "|" << setw(39) << node->alamat<< "|" << setw(21) << node->no_ktp << "|" << endl;
        cout << "+---------+-----------------------------+---------------------------------------+---------------------+" << endl;
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
        if(daf_pem.cari(tarIdk)){
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

void inputSuara(Node** pemilih, Node** calon, Queue &daf_pem, Stack &golput){
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

        // Apabila pemilih memutuskan golput
        if(pilih == -1){
            golput.push(indeks);
        }
       
        // Masukkan indeks pemilih ke daftar orang sudah memilih
        daf_pem.enqueue(indeks);

        // Tambahkan node pemilih ke belakang node calon
        while(temp->next != NULL){
            if(temp->status == "Calon"){
                nomor++;
                if( nomor == no_calon ){
                    sisipBelakang(&temp, indeks, nama, "-", "-", "Pemilh" );
				return; 
			}
            }
            temp = temp->next; 
        }


    } else {
        cout << endl << endl; 
        cout << "MAAF ANDA TIDAK DAPAT MEMILIH" << endl;
    }
}

int hitungSuara(Node* head_ref){
	Node* temp = head_ref; 
	int number = 0;

	while(temp->next->status != "Calon"){
		temp = temp->next; 
		number++;
	}
	return number; 
}

void hasilPem(Queue suara, Stack putih, Node* calon){
    Node* temp = calon;
    Node* ptr[100];
    int jumlah = 0;
    int hasil = 0;
    
    do{
		if(temp->status == "Calon"){
			ptr[jumlah] = temp;
			jumlah++;
		}
		temp = temp->next; 
	}while(temp != NULL);

	for(int i = 0; i < jumlah; i++){
		hasil = hitungSuara(ptr[i]);
		cout << "+----------------------------+" << endl; 
        cout << "|" << " # NOMOR " << i + 1 << endl;
        cout << "|" << endl; 
        cout << "| " << calon->nama << endl;
        cout << "| " << hasil << " SUARA" << endl;  
        cout << "+----------------------------+" << endl << endl;
	}

    cout << "TOTAL PEMILIH  : " << suara.hitung() << endl;
    cout << "JUMLAH GOLPUT  : " << putih.count() << endl << endl;
}


int main(){
    int pilihan;

    Node* pemilih = NULL; // Inisiasi linked list untuk pemilih
    Node* calon = NULL; // Inisiasi linked list untuk calon terpilih
    Queue suara; //Inisiasi queue untuk menyimpan data idk_pemilih
    Stack golput; 

    sisipBelakang(&pemilih, idk_anggota, "harya", "panjang", "13", "Pemilih");
    sisipBelakang(&calon, idk_calon, "Suhartanto", "panjangjiwo", "2424", "Calon");
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
                            daftarAnggota(pemilih);
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
                            daftarAnggota(calon);
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
                hasilPem(suara, golput, calon);
                system("PAUSE");
            break;
            
            case 5:

            break;

            default:
                system("CLS");
                cout << "Mohon masukkan indeks angka (1/2/3/4/5)" << endl << endl;
                system("PAUSE");
            break;
        }

    }while(pilihan != -1);
}
