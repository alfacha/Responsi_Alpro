#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct Mahasiswa {
    string nim, nama;
    double nilaiTugas, nilaiUTS, nilaiUAS, nilaiAkhir;
    char grade;
};

double hitungNilaiAkhirRekursif(double tugas, double uts, double uas, int komponen) {
    if (komponen == 1) return (0.30 * tugas) + hitungNilaiAkhirRekursif(tugas, uts, uas, komponen + 1);
    if (komponen == 2) return (0.30 * uts) + hitungNilaiAkhirRekursif(tugas, uts, uas, komponen + 1);
    if (komponen == 3) return (0.40 * uas);
    return 0;
}

char tentukanGrade(double nilai) {
    if (nilai >= 85) return 'A';
    if (nilai >= 75) return 'B';
    if (nilai >= 60) return 'C';
    if (nilai >= 45) return 'D';
    return 'E';
}

void dataNilaiMahasiswa() {
    ofstream nilaiMahasiswa("data_mahasiswa.txt");
    if (nilaiMahasiswa.is_open()) {
        nilaiMahasiswa << "2500018041 Alfarina 87 89 95\n";
        nilaiMahasiswa << "2500018033 Eliana 81 77 90\n";
        nilaiMahasiswa << "2500018001 Arif 92 95 88\n";
        nilaiMahasiswa << "2500018088 Dewita 71 62 50\n";
        nilaiMahasiswa << "2400018176 Tania 41 65 75\n";
        nilaiMahasiswa.close();
    }
}

int main() {
    dataNilaiMahasiswa();

    const int MAX_MHS = 100;
    Mahasiswa daftarMhs[MAX_MHS];
    int jumlahMhs = 0;

    ifstream fileInput("data_mahasiswa.txt");
    if (!fileInput) {
        cout << "GAGAL MEMPROSES DATA!" << endl;
        return 1;
    }

    while (fileInput >> daftarMhs[jumlahMhs].nim >> daftarMhs[jumlahMhs].nama 
                     >> daftarMhs[jumlahMhs].nilaiTugas >> daftarMhs[jumlahMhs].nilaiUTS 
                     >> daftarMhs[jumlahMhs].nilaiUAS) {
        
        daftarMhs[jumlahMhs].nilaiAkhir = hitungNilaiAkhirRekursif(
            daftarMhs[jumlahMhs].nilaiTugas, daftarMhs[jumlahMhs].nilaiUTS, daftarMhs[jumlahMhs].nilaiUAS, 1
        );
        daftarMhs[jumlahMhs].grade = tentukanGrade(daftarMhs[jumlahMhs].nilaiAkhir);
        jumlahMhs++;
        if (jumlahMhs >= MAX_MHS) break;
    }
    fileInput.close();

    int pilihan;
    do {
        cout << "\n==========================================" << endl;
        cout << "        ANALISIS NILAI MAHASISWA   " << endl;
        cout << "==========================================" << endl;
        cout << "1. Tampilkan Semua Data Mahasiswa" << endl;
        cout << "2. Cari Mahasiswa Berdasarkan NIM" << endl;
        cout << "3. Cari Mahasiswa dengan Nilai Terendah" << endl;
        cout << "4. Hitung Rata-rata Nilai Akhir Kelas" << endl;
        cout << "5. Simpan Hasil Analisis ke File" << endl;
        cout << "6. Keluar" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Pilih menu (1-6): ";
        cin >> pilihan;
        
        system("cls");

        switch (pilihan) {
            case 1:
                cout << left << setw(13) << "NIM" << setw(15) << "Nama" 
                     << setw(8) << "Tugas" << setw(8) << "UTS" << setw(8) << "UAS" 
                     << setw(12) << "Nilai Akhir" << setw(12) << "Grade" << endl;
                cout << "---------------------------------------------------------------------" << endl;
                for (int i = 0; i < jumlahMhs; i++) {
                    cout << left << setw(13) << daftarMhs[i].nim << setw(15) << daftarMhs[i].nama 
                         << setw(8) << daftarMhs[i].nilaiTugas << setw(8) << daftarMhs[i].nilaiUTS << setw(8) << daftarMhs[i].nilaiUAS 
                         << setw(12) << fixed << setprecision(2) << daftarMhs[i].nilaiAkhir << setw(12) << daftarMhs[i].grade << endl;
                }
                break;
            case 2: {
                string cariNim;
                cout << "Masukkan NIM yang dicari: ";
                cin >> cariNim;
                bool ditemukan = false;
                for (int i = 0; i < jumlahMhs; i++) {
                    if (daftarMhs[i].nim == cariNim) {
                        cout << "\n=== | Data Ditemukan | ===" << endl;
                        cout << "Nama           : " << daftarMhs[i].nama << endl;
                        cout << "Nilai Akhir    : " << daftarMhs[i].nilaiAkhir << endl;
                        cout << "Grade          : " << daftarMhs[i].grade << endl;
                        ditemukan = true;
                        break;
                    }
                }
                if (!ditemukan) cout << "Mahasiswa dengan NIM " << cariNim << " tidak ditemukan." << endl;
                break;
            }
            case 3: {
                int indeksTerendah = 0;
                for (int i = 1; i < jumlahMhs; i++) {
                    if (daftarMhs[i].nilaiAkhir < daftarMhs[indeksTerendah].nilaiAkhir) indeksTerendah = i;
                }
                cout << "Mahasiswa dengan Nilai Akhir Terendah" << endl;
                cout << "-------------------------------------" << endl;
                cout << "NIM         : " << daftarMhs[indeksTerendah].nim << endl;
                cout << "Nama        : " << daftarMhs[indeksTerendah].nama << endl;
                cout << "Nilai Akhir : " << daftarMhs[indeksTerendah].nilaiAkhir << endl;
                cout << "Grade       : " << daftarMhs[indeksTerendah].grade << endl;
                break;
            }
            case 4: {
                double totalNilai = 0;
                for (int i = 0; i < jumlahMhs; i++) totalNilai += daftarMhs[i].nilaiAkhir;
                cout << "Rata-rata Nilai Akhir Seluruh Mahasiswa: " << fixed << setprecision(2) << (totalNilai / jumlahMhs) << endl;
                break;
            }
            case 5: {
                ofstream fileOutput("hasil_nilai.txt");
                if (fileOutput.is_open()) {
                    fileOutput << left << setw(13) << "NIM" << setw(15) << "Nama" << setw(12) << "Nilai Akhir" << "Grade" << endl;
                    fileOutput << "------------------------------------------------------------" << endl;
                    for (int i = 0; i < jumlahMhs; i++) {
                        fileOutput << left << setw(13) << daftarMhs[i].nim << setw(15) << daftarMhs[i].nama 
                                   << setw(12) << fixed << setprecision(2) << daftarMhs[i].nilaiAkhir << daftarMhs[i].grade << endl;
                    }
                    fileOutput.close();
                    cout << "Hasil analisis berhasil disimpan ke 'hasil_nilai.txt'!" << endl;
                }
                break;
            }
            case 6:
                cout << "Program Selesai." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 6);

    return 0;
}
