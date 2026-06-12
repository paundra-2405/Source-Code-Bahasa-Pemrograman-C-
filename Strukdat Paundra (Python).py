# Class untuk menyimpan data pasien
# Berisi nomor antrian, nama, dan umur pasien
class Pasien:

    # Constructor untuk menginisialisasi data pasien
    def __init__(self, nomor, nama, umur):
        self.nomor = nomor
        self.nama = nama
        self.umur = umur


# Node Linked List
# Digunakan sebagai elemen penyusun Queue dan Stack
class Node:

    # Constructor Node
    # Menyimpan data pasien dan pointer ke node berikutnya
    def __init__(self, data):
        self.data = data
        self.next = None


# Class Queue untuk mengelola antrian pasien
# Menggunakan prinsip FIFO (First In First Out)
class QueuePasien:

    # Constructor Queue
    # Menginisialisasi antrian kosong
    def __init__(self):
        self.front = None
        self.rear = None

    # Mengecek apakah antrian kosong
    # Digunakan sebelum proses hapus atau tampil data
    def is_empty(self):
        return self.front is None

    # Menambahkan pasien ke belakang antrian
    # Pasien yang datang lebih dulu akan dilayani lebih dulu
    def enqueue(self, pasien):

        baru = Node(pasien)

        if self.is_empty():
            self.front = self.rear = baru
        else:
            self.rear.next = baru
            self.rear = baru

    # Mengambil dan menghapus pasien paling depan
    # Digunakan saat pasien dilayani
    def dequeue(self):

        if self.is_empty():
            return None

        pasien = self.front.data
        self.front = self.front.next

        if self.front is None:
            self.rear = None

        return pasien

    # Menampilkan seluruh pasien yang masih menunggu
    # dalam antrian
    def display(self):

        if self.is_empty():
            print("\nAntrian Kosong")
            return

        temp = self.front

        print("\n===== DAFTAR ANTRIAN =====")

        while temp is not None:

            print(
                f"No : {temp.data.nomor} | "
                f"Nama : {temp.data.nama} | "
                f"Umur : {temp.data.umur}"
            )

            temp = temp.next

    # Mencari pasien berdasarkan nomor antrian
    # Mempermudah pencarian data pasien tertentu
    def search(self, nomor):

        temp = self.front

        while temp is not None:

            if temp.data.nomor == nomor:

                print("\nData ditemukan")
                print("Nama :", temp.data.nama)
                print("Umur :", temp.data.umur)

                return

            temp = temp.next

        print("\nData tidak ditemukan")

    # Menghitung jumlah pasien yang sedang
    # berada dalam antrian
    def count(self):

        jumlah = 0
        temp = self.front

        while temp is not None:

            jumlah += 1
            temp = temp.next

        return jumlah

    # Mengurutkan data pasien berdasarkan nama
    # menggunakan algoritma Bubble Sort
    def bubble_sort(self):

        if self.front is None:
            return

        swapped = True

        while swapped:

            swapped = False
            ptr = self.front

            while ptr.next is not None:

                if ptr.data.nama.lower() > ptr.next.data.nama.lower():

                    ptr.data, ptr.next.data = (
                        ptr.next.data,
                        ptr.data
                    )

                    swapped = True

                ptr = ptr.next

        print("\nData berhasil diurutkan.")


# Class Stack untuk menyimpan riwayat pelayanan
# Menggunakan prinsip LIFO (Last In First Out)
class StackRiwayat:

    # Constructor Stack
    # Menginisialisasi riwayat pelayanan kosong
    def __init__(self):
        self.top = None

    # Menambahkan pasien yang telah dilayani
    # ke dalam riwayat pelayanan
    def push(self, pasien):

        baru = Node(pasien)
        baru.next = self.top
        self.top = baru

    # Menampilkan seluruh riwayat pasien
    # yang sudah mendapatkan pelayanan
    def display(self):

        if self.top is None:

            print("\nBelum ada riwayat.")
            return

        temp = self.top

        print("\n===== RIWAYAT PELAYANAN =====")

        while temp is not None:

            print(
                f"{temp.data.nomor} - "
                f"{temp.data.nama}"
            )

            temp = temp.next


# Fungsi utama program
# Mengatur seluruh jalannya sistem antrian pasien
def main():

    antrian = QueuePasien()
    riwayat = StackRiwayat()

    nomor_otomatis = 1

    while True:

        print("\n===== SISTEM ANTRIAN =====")
        print("1. Tambah Pasien")
        print("2. Layani Pasien")
        print("3. Tampilkan Antrian")
        print("4. Cari Pasien")
        print("5. Urutkan Nama")
        print("6. Riwayat Pelayanan")
        print("7. Jumlah Antrian")
        print("0. Keluar")

        try:
            pilihan = int(input("Pilih : "))

        except ValueError:

            print("Input harus berupa angka!")
            continue

        # Menambahkan pasien baru ke antrian
        if pilihan == 1:

            nama = input("Nama : ")
            umur = int(input("Umur : "))

            pasien = Pasien(
                nomor_otomatis,
                nama,
                umur
            )

            nomor_otomatis += 1

            antrian.enqueue(pasien)

            print("Pasien berhasil ditambahkan.")

        # Melayani pasien paling depan
        # kemudian menyimpan ke riwayat pelayanan
        elif pilihan == 2:

            pasien = antrian.dequeue()

            if pasien is None:

                print("\nAntrian kosong")

            else:

                print(f"\nMelayani : {pasien.nama}")
                riwayat.push(pasien)

        # Menampilkan seluruh daftar antrian
        elif pilihan == 3:

            antrian.display()

        # Mencari pasien berdasarkan nomor antrian
        elif pilihan == 4:

            nomor = int(
                input("Nomor antrian : ")
            )

            antrian.search(nomor)

        # Mengurutkan nama pasien secara alfabetis
        elif pilihan == 5:

            antrian.bubble_sort()

        # Menampilkan riwayat pelayanan pasien
        elif pilihan == 6:

            riwayat.display()

        # Menampilkan jumlah pasien yang masih menunggu
        elif pilihan == 7:

            print(
                "\nJumlah Antrian :",
                antrian.count()
            )

        # Mengakhiri program
        elif pilihan == 0:

            print("\nProgram selesai.")
            break

        # Menangani pilihan yang tidak tersedia
        else:

            print("Pilihan tidak valid!")


# Menjalankan program utama
if __name__ == "__main__":
    main()