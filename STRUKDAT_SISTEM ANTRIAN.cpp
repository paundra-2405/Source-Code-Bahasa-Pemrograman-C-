#include <iostream>
#include <string>

using namespace std;

// Menyimpan data pasien berupa nomor antrian, nama, dan umur
struct Pasien {
    int nomor;
    string nama;
    int umur;
};

// Node Linked List yang digunakan oleh Queue dan Stack
struct Node {
    Pasien data;
    Node* next;
};

class QueuePasien {
private:
    Node* front;
    Node* rear;

public:

    // Constructor Queue
    // Menginisialisasi antrian dalam keadaan kosong
    QueuePasien() {
        front = rear = NULL;
    }

    // Mengecek apakah antrian kosong
    // Digunakan sebelum proses hapus atau tampil data
    bool isEmpty() {
        return front == NULL;
    }

    // Menambahkan pasien ke belakang antrian
    // Menerapkan konsep FIFO (First In First Out)
    void enqueue(Pasien p) {

        Node* baru = new Node;
        baru->data = p;
        baru->next = NULL;

        if(isEmpty()) {
            front = rear = baru;
        }
        else {
            rear->next = baru;
            rear = baru;
        }
    }

    // Mengambil dan menghapus pasien paling depan
    // Digunakan saat pasien dilayani
    Pasien dequeue() {

        Pasien kosong;
        kosong.nomor = -1;

        if(isEmpty()) {
            return kosong;
        }

        Node* hapus = front;
        Pasien p = front->data;

        front = front->next;

        if(front == NULL)
            rear = NULL;

        delete hapus;

        return p;
    }

    // Menampilkan seluruh data pasien
    // yang masih berada dalam antrian
    void display() {

        if(isEmpty()) {
            cout << "\nAntrian Kosong\n";
            return;
        }

        Node* temp = front;

        cout << "\n===== DAFTAR ANTRIAN =====\n";

        while(temp != NULL) {

            cout << "No : "
                 << temp->data.nomor
                 << " | Nama : "
                 << temp->data.nama
                 << " | Umur : "
                 << temp->data.umur
                 << endl;

            temp = temp->next;
        }
    }

    // Mencari pasien berdasarkan nomor antrian
    // Memudahkan pencarian data pasien tertentu
    void search(int nomor) {

        Node* temp = front;

        while(temp != NULL) {

            if(temp->data.nomor == nomor) {

                cout << "\nData ditemukan\n";
                cout << "Nama : "
                     << temp->data.nama
                     << endl;

                return;
            }

            temp = temp->next;
        }

        cout << "\nData tidak ditemukan\n";
    }

    // Menghitung jumlah pasien
    // yang sedang berada dalam antrian
    int count() {

        int jumlah = 0;

        Node* temp = front;

        while(temp != NULL) {

            jumlah++;
            temp = temp->next;
        }

        return jumlah;
    }

    // Mengurutkan nama pasien secara alfabetis
    // menggunakan algoritma Bubble Sort
    void bubbleSort() {

        if(front == NULL)
            return;

        bool swapped;

        do {

            swapped = false;

            Node* ptr = front;

            while(ptr->next != NULL) {

                if(ptr->data.nama >
                   ptr->next->data.nama) {

                    swap(ptr->data,
                         ptr->next->data);

                    swapped = true;
                }

                ptr = ptr->next;
            }

        } while(swapped);

        cout << "\nData berhasil diurutkan.\n";
    }
};

class StackRiwayat {
private:
    Node* top;

public:

    // Constructor Stack
    // Menginisialisasi riwayat pelayanan kosong
    StackRiwayat() {
        top = NULL;
    }

    // Menambahkan pasien yang telah dilayani
    // ke dalam riwayat pelayanan (Stack)
    void push(Pasien p) {

        Node* baru = new Node;

        baru->data = p;
        baru->next = top;

        top = baru;
    }

    // Menampilkan seluruh riwayat pasien
    // yang sudah mendapatkan pelayanan
    void display() {

        if(top == NULL) {

            cout << "\nBelum ada riwayat.\n";
            return;
        }

        Node* temp = top;

        cout << "\n===== RIWAYAT PELAYANAN =====\n";

        while(temp != NULL) {

            cout << temp->data.nomor
                 << " - "
                 << temp->data.nama
                 << endl;

            temp = temp->next;
        }
    }
};

// Fungsi utama program
// Mengatur seluruh jalannya sistem antrian pasien
int main() {

    QueuePasien antrian;
    StackRiwayat riwayat;

    int pilihan;
    int nomorOtomatis = 1;

    do {

        cout << "\n===== SISTEM ANTRIAN =====\n";
        cout << "1. Tambah Pasien\n";
        cout << "2. Layani Pasien\n";
        cout << "3. Tampilkan Antrian\n";
        cout << "4. Cari Pasien\n";
        cout << "5. Urutkan Nama\n";
        cout << "6. Riwayat Pelayanan\n";
        cout << "7. Jumlah Antrian\n";
        cout << "0. Keluar\n";

        cout << "Pilih : ";
        cin >> pilihan;

        switch(pilihan) {

        // Menambahkan pasien baru ke antrian
        case 1: {

            Pasien p;

            p.nomor = nomorOtomatis++;

            cin.ignore();

            cout << "Nama : ";
            getline(cin,p.nama);

            cout << "Umur : ";
            cin >> p.umur;

            antrian.enqueue(p);

            break;
        }

        // Melayani pasien terdepan
        // lalu menyimpannya ke riwayat
        case 2: {

            Pasien p = antrian.dequeue();

            if(p.nomor == -1)
                cout << "\nAntrian kosong\n";
            else {

                cout << "\nMelayani : "
                     << p.nama
                     << endl;

                riwayat.push(p);
            }

            break;
        }

        // Menampilkan seluruh antrian pasien
        case 3:
            antrian.display();
            break;

        // Mencari pasien berdasarkan nomor antrian
        case 4: {

            int no;

            cout << "Nomor antrian : ";
            cin >> no;

            antrian.search(no);

            break;
        }

        // Mengurutkan data pasien berdasarkan nama
        case 5:
            antrian.bubbleSort();
            break;

        // Menampilkan riwayat pelayanan pasien
        case 6:
            riwayat.display();
            break;

        // Menampilkan jumlah pasien yang menunggu
        case 7:

            cout << "\nJumlah Antrian : "
                 << antrian.count()
                 << endl;

            break;
        }

    } while(pilihan != 0);

    return 0;
}