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

bcc -ansi -c -o ./o/fileIO.o ./libs/fileIO.c

bcc -ansi -c -o ./o/folderIO.o ./libs/folderIO.c

bcc -ansi -c -o ./o/textIO.o ./libs/textIO.c

bcc -ansi -c -o ./o/math.o ./libs/math.c

bcc -ansi -c -o ./o/tools.o ./libs/tools.c

gcc loadFile.c -o ./bin/loadFile

echo installing kernel.c
nasm -f as86 kernel.asm -o kernel_asm.o
bcc -ansi -c -o kernel.o kernel.c
ld86 -o kernel -d kernel.o kernel_asm.o ./o/fileIO.o ./o/folderIO.o ./o/textIO.o ./o/math.o ./o/tools.o
dd if=kernel of=system.img bs=512 seek=1 conv=notrunc

arr=(ls cls cat cd echo editor)
for program in ${arr[*]};
    do
        echo installing $program
        bcc -ansi -c -o ./o/$program.o ./programs/$program.c
        ld86 -o ./bin/$program -d ./o/$program.o lib_asm.o ./o/fileIO.o ./o/folderIO.o ./o/textIO.o ./o/math.o ./o/tools.o
    done


bcc -ansi -c -o ./o/shell.o ./programs/shellmain.c

ld86 -o ./bin/shell -d ./o/shell.o lib_asm.o ./o/fileIO.o ./o/folderIO.o ./o/textIO.o ./o/math.o ./o/tools.o

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