# WindOS
Program dibuat untuk memenuhi tugas IF2230 Sistem Operasi
---
## List of Utility Applications
### cat
```cat [nama_file]``` <br>
Menuliskan isi sebuah file<br>
Parameter:
* nama_file: file yang akan ditampilkan isinya
### cd
```cd [folder_tujuan]``` <br>
Berpindah dari satu direktori ke direktori lainnya<br>
Parameter:
* folder_tujuan: path folder yang akan dituju

### cls
```cls``` <br>
Mengosongkan tampilan shell

### cp
```cp [nama_file] [folder_tujuan]``` <br>
Menyalin sebuah file ke folder lain<br>
Parameter:
* nama_file: nama file yang akan disalin
* folder_tujuan: folder tempat file akan di-paste

### help
```help``` <br>
Menampilkan list of commands yang dapat dilakukan di dalam shell

### ln 
```ln [nama_file] [nama_link]``` <br>
Membuat symbolic link dengan terhadap sebuah file<br>
Parameter:
* nama_file: nama file yang akan disalin
* nama_link: nama link yang akan menyimpan konten file

### ls
```ls``` <br>
Menampilkan daftar file dan folder yang ada pada current directory

### mkdir
```mkdir [nama_direktori]``` <br>
Membuat direktori baru pada current directory<br>
Parameter:
* nama_direktori: Nama direktori yang ingin dibuat

### mv
```mv [nama_file] [direktori_tujuan]``` <br>
Memindahkan file dari current directory ke direktori lain<br>
Parameter:
* nama_file: File pada current directory yang ingin dipindahkan
* direktori_tujuan: Direktori tujuan file ditempatkan

### rm
```rm [nama_file atau folder]``` <br>
Menghapus sebuah file atau direktori<br>
Parameter:
* nama_file atau folder: file atau folder yang akan dihapus

### wim
```wim [nama_file]``` <br>
Text editor dari shell<br>
Parameter:
* nama_file: nama file yang akan diedit isinya ***optional***

---
## Requirements
- <a href="https://ubuntu.com/download/desktop" target="_blank">Ubuntu - version 18.04 or 20.04</a>
- <a href="http://bochs.sourceforge.net/" target="_blank">bochs</a>
- <a href="https://linux.die.net/man/1/bcc" target="_blank">bcc C compiler</a>
- <a href="https://www.nasm.us/" target="_blank">nasm</a>
- <a href="https://linux.die.net/man/1/ld86" target="_blank">ld86 Linker</a>
---
## Setup
Untuk mendapatkan seluruh *requirements* pada Ubuntu, masukkan *command* berikut pada terminal:
```
sudo apt update
sudo apt install nasm bcc bin86 bochs bochs-x
```
---
## Cara run
1. Navigasi pada folder hasil clone
2. Pada terminal, ketik `chmod +x commands.sh`
3. Untuk menjalankan, ketik `./commands.sh`

---
## Author
- Daru Bagus Dananjaya (13519080)
- Shifa Salsabiila (13519106)
- Daffa Ananda Pratama Resyaly (13519107)


