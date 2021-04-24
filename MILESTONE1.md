# WindOS

## Cara Kerja Interrupt
Ketika CPU menerima sinyal interrupt, hal pertama yang akan dilakukannya adalah menyimpan konteks atau keadaan proses yang sedang berjalan, umumnya pada sebuah stack. Penyimpanan konteks diperlukan agar proses yang akan diinterupsi dapat dikembalikan pada keadaan yang sama persis seperti sebelumnya. Semua jenis interrupt yang dapat ditangani oleh suatu sistem operasi memiliki kode/nomor interrupt tertentu. Setiap nomor interrupt memiliki perilaku masing-masing yang akan dijalankannya ketika dipanggil, ini disebut dengan *Interrupt Service Handler / Interrupt Service Routine (ISR)*.

Nomor interrupt beserta address ISR-nya disimpan pada sebuah tabel, yang disebut *Interrupt Vector*. Setelah menyimpan konteks, CPU akan menelusuri Interrupt Vector dan mengambil address ISR interrupt terkait. Selanjutnya, CPU akan melakukan jump ke address ISR dan akan dilakukan *context switch* oleh sistem operasi dari konteks yang sedang berjalan ke ISR. Perlu diperhatikan bahwa pada saat context switch sedang berjalan, flag yang memperbolehkan interrupt lain akan dimatikan, sehingga selama keberjalanan context switch, tidak bisa dilakukan interrupt lain. 

Setelah ISR sudah berjalan, pemanggilan interrupt lain akan kembali diperbolehkan, sehingga memungkinkan terjadinya *nested interrupt*. Selanjutnya, ISR akan dieksekusi hingga selesai pada *kernel mode*. Setelah ISR selesai dieksekusi, keadaan sebelum adanya interrupt akan direstorasi dan proses sebelumnya akan kembalil dilanjutkan. 

## Cara Kerja Kode di Kernel.asm

### putInMemory

Fungsi putInMemory dideklarasikan di dalam `kernel.asm` dan dapat dipanggil melalui `kernel.c`. Fungsi ini berguna untuk menuliskan sesuatu ke dalam segmen memori tertentu
Fungsi ini menerima 3 buah parameter, yaitu :
- Digit Hexadecimal pertama dari address dikalikan dengan 0x1000 (biasa disebut segment)
- 4 digit hexadecimal terakhir dari address
- Character yang akan dimasukkan ke memori

*Contoh :*
```
putInMemory(0xB000, 0x8000, 'H');

putInMemory(0xB000, 0x8001, 0xD);
```
instruksi di atas akan memasukkan character 'H' ke dalam segmen memory 0xB000 yaitu segmen video service dengan offset 8000 dan memasukkan warna ungu ke dalam address berikutnya
yang menunjukkan warna ungu muda. Akhir dari kedua instruksi tersebut adalah dituliskannya huruf 'H' dengan warna ungu muda di tempat cursor berada.

### Interrupt

Interrupt merupakan sinyal yang dikirimkan oleh external entities kepada CPU, umumnya I/O devices. Terdapat 3 macam interrupt di dalam operating system, yaitu :
- **Hardware Interrupt** merupakan interrupt yang digenerate oleh perangkat keras ketika dia membutuhkan "perhatian" dari operating system. Contohnya adalah keystroke dari keyboard;
- **Software Interrupt** merupakan interrupt yang digenerate oleh perangkat lunak saat dia ingin request system call untuk dilakukan oleh operating system;
- **Traps** merupakan interrupt yang digenerate oleh CPU sendiri untuk mengindikasikan adanya error yang membutuhkan bantuan dari operating system.

Berikut ini merupakan beberapa jenis interrupt yang kami gunakan dalam pengerjaan milestone ini :
- interrupt 0x10 -  Video service, mencetak sesuatu ke layar
- interrupt 0x16 - membaca input dari keyboard
- interrupt handler 0x21 - interrupt yang dapat dicustom sesuai dengan kebutuhan kita

Fungsi interrupt pada `kernel.asm` menerima 5 buah parameter, yaitu :
- Interrupt number, seperti yang sudah disebutkan di atas
- AX, address register
- BX, address register
- CX, address register
- DX, addresss register

#### Interrupt 0x10 : *Print to Screen*

Dalam penggunaannya, selain dari parameter pertama yang merupakan jenis interrupt, fungsi ini akan melakukan passing parameter ke register AX, BX, CX, DX yang kemudian mereturn value dari interrupt ke register AL.

**Contoh :**
Kita akan menggunakan interrupt 0x10 untuk mencetak huruf 'A' ke layar. Untuk itu, kita harus melakukan :
```
1. Untuk menuliskan karakter 'A', register AH harus bernilai 0xE dan register AL harus berisi karakter 'A' (0x41)
2. AX = AH*256 + AL
3. Panggil interrupt. Dan karena parameter BX, CX, DX tidak digunakan, maka isi saja dengan 0

```

#### Interrupt 0x16 : Read Input

Dalam penggunaannya, ketika kita menggunakan interrupt 0x16 untuk menerima input dari keyboard, register AH harus bernilai 0. Interrupt ini akan mengembalikan ASCII code when the key pressed. Biasanya penggunaan interrupt ini dibarengi dengan penggunaan interrupt 0x13 karena yakali ngetik tapi gabisa liat apa yang diketik.

**Syntax untuk interrupt 0x16 :**
```
interrupt(0x16, 0, 0, 0, 0);
```

### makeInterrupt21

makeInterrupt21 merupakan fungsi yang melakukan inisialisasi terhadap tabel interrupt 21 vector pada awal mula operating system dijalankan. Fungsi ini akan me-return tabel interrupt vector 21 tersebut. Fungsi ini ditulis dalam bahasa assembly dan terdapat pada file kernel.asm. Ketika interrupt 21 yang di-return oleh fungsi ini dipanggil kembali nantinya, maka fungsi interrupt21ServiceRoutine akan dijalankan.

Sebuah service untuk membuat fungsi yang menempatkan address dari fungsi tersebut ke interrupt vector table. Interrupt vector table ini terletak di bottom of memory dan mengandung 4 byte address untuk setiap interrupt number. Untuk membuat service routine interrupt 0x21, makeInterrupt akan membuat sebuah fungsi yang akan dipanggil ketika interrupt 0x21 terjadi dan menempatkan addressnya di 0x00084 (karena 21x4 = 84).

### interrupt21ServiceRoutine

interrupt21ServiceRoutine dipanggil saat interrupt 21 dipanggil. Fungsi ini kemudian akan memanggil method handleInterrupt21 yang dapat melakukan beberapa aksi, yaitu memanggil fungsi printString dan readString, tergantung input yang diterimanya. Fungsi interrupt21ServiceRoutine berada pada file kernel.asm dan menerima empat buah parameter input bertipe integer untuk diberikan kepada handleInterrupt21, yaitu AX (jenis aksi yang akan dilakukan), BX (parameter input dari fungsi printString atau readString yang akan dipanggil oleh fungsi handleInterrupt21 nantinya), CX (baris tempat kursor berada), dan DX (kolom tempat kursor berada).

Fungsi interrupt21ServiceRoutine ini akan dipanggil ketika interrupt 0x21 terjadi. Ketika service ini dipanggil, sevice ini akan memanggil fungsi handleInterrupt21(int AX, int BX, int CX, int DX) yang ada di `kernel.c`.
