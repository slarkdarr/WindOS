echo installing system.img
dd if=/dev/zero of=system.img bs=512 count=2880

echo installing bootloader
nasm bootloader.asm -o bootloader
dd if=bootloader of=system.img bs=512 count=1 conv=notrunc

echo preparing lib
nasm -f as86 lib.asm -o lib_asm.o

echo installing sectors
dd if=map.img of=system.img bs=512 count=1 seek=256 conv=notrunc
dd if=files.img of=system.img bs=512 count=2 seek=257 conv=notrunc
dd if=sectors.img of=system.img bs=512 count=1 seek=259 conv=notrunc

bcc -ansi -c -o ./o/handleInterrupt21.o ./lib/handleInterrupt21.c

bcc -ansi -c -o ./o/_executeProgram.o ./lib/_executeProgram.c

bcc -ansi -c -o ./o/printScreen.o ./lib/printScreen.c

bcc -ansi -c -o ./o/defaultDir.o ./lib/defaultDir.c

bcc -ansi -c -o ./o/printBootScreen.o ./lib/printBootScreen.c

bcc -ansi -c -o ./o/teks.o ./lib/teks.c

bcc -ansi -c -o ./o/fileIO.o ./lib/fileIO.c

bcc -ansi -c -o ./o/folderIO.o ./lib/folderIO.c

bcc -ansi -c -o ./o/matematika.o ./lib/matematika.c

bcc -ansi -c -o ./o/utility.o ./lib/utility.c

gcc loadFile.c -o ./bin/loadFile

echo installing kernel.c
nasm -f as86 kernel.asm -o kernel_asm.o
bcc -ansi -c -o kernel.o kernel.c
ld86 -o kernel -d kernel.o kernel_asm.o ./o/handleInterrupt21.o ./o/_executeProgram.o ./o/printScreen.o ./o/defaultDir.o ./o/printBootScreen.o ./o/teks.o ./o/fileIO.o  ./o/folderIO.o ./o/matematika.o ./o/utility.o
dd if=kernel of=system.img bs=512 seek=1 conv=notrunc

arr=(help ls mkdir cp mv rm ln cls cat cd wim)
for program in ${arr[*]};
    do
        echo installing $program
        bcc -ansi -c -o ./o/$program.o ./src/$program.c
        ld86 -o ./bin/$program -d ./o/$program.o lib_asm.o ./o/handleInterrupt21.o ./o/_executeProgram.o ./o/printScreen.o ./o/defaultDir.o ./o/printBootScreen.o ./o/teks.o ./o/fileIO.o  ./o/folderIO.o ./o/matematika.o ./o/utility.o
    done


bcc -ansi -c -o ./o/shell.o ./src/shell.c

ld86 -o ./bin/shell -d ./o/shell.o lib_asm.o ./o/handleInterrupt21.o ./o/_executeProgram.o ./o/printScreen.o ./o/defaultDir.o ./o/printBootScreen.o ./o/teks.o ./o/fileIO.o  ./o/folderIO.o ./o/matematika.o ./o/utility.o

cd bin

cp ../system.img system.img

for program in ${arr[*]};
    do
        ./loadFile $program
    done

./loadFile shell

cp system.img ../system.img

cd ..

bochs -f if2230.config