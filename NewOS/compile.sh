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

bcc -ansi -c -o ./o/readFile.o ./libs/readFile.c

bcc -ansi -c -o ./o/writeFile.o ./libs/writeFile.c

bcc -ansi -c -o ./o/mod.o ./libs/mod.c

bcc -ansi -c -o ./o/div.o ./libs/div.c

bcc -ansi -c -o ./o/printChar.o ./libs/printChar.c

bcc -ansi -c -o ./o/printString.o ./libs/printString.c

bcc -ansi -c -o ./o/copy.o ./libs/copy.c

bcc -ansi -c -o ./o/readString.o ./libs/readString.c

bcc -ansi -c -o ./o/readSector.o ./libs/readSector.c

bcc -ansi -c -o ./o/writeSector.o ./libs/writeSector.c

bcc -ansi -c -o ./o/printline.o ./libs/printline.c

bcc -ansi -c -o ./o/getDirIndex.o ./libs/getDirIndex.c

bcc -ansi -c -o ./o/getPathIndex.o ./libs/getPathIndex.c

bcc -ansi -c -o ./o/clear.o ./libs/clear.c

bcc -ansi -c -o ./o/clearScreen.o ./libs/clearScreen.c

bcc -ansi -c -o ./o/strLen.o ./libs/strLen.c

bcc -ansi -c -o ./o/strComp.o ./libs/strComp.c

bcc -ansi -c -o ./o/strCompLimit.o ./libs/strCompLimit.c

bcc -ansi -c -o ./o/executeProgram.o ./libs/executeProgram.c

gcc loadFile.c -o ./bin/loadFile

echo installing kernel.c
nasm -f as86 kernel.asm -o kernel_asm.o
bcc -ansi -c -o kernel.o kernel.c
ld86 -o kernel -d kernel.o kernel_asm.o ./o/readFile.o ./o/writeFile.o  ./o/div.o ./o/mod.o ./o/printChar.o ./o/printString.o ./o/copy.o ./o/readString.o ./o/readSector.o ./o/writeSector.o ./o/printline.o ./o/getDirIndex.o ./o/getPathIndex.o ./o/clear.o ./o/clearScreen.o ./o/strLen.o ./o/strComp.o ./o/strCompLimit.o ./o/executeProgram.o
dd if=kernel of=system.img bs=512 seek=1 conv=notrunc

arr=(ls cls cat cd echo editor)
for program in ${arr[*]};
    do
        echo installing $program
        bcc -ansi -c -o ./o/$program.o ./programs/$program.c
        ld86 -o ./bin/$program -d ./o/$program.o lib_asm.o ./o/readFile.o ./o/writeFile.o  ./o/div.o ./o/mod.o ./o/printChar.o ./o/printString.o ./o/copy.o  ./o/readString.o ./o/readSector.o ./o/writeSector.o ./o/printline.o ./o/getDirIndex.o ./o/getPathIndex.o ./o/clear.o ./o/clearScreen.o ./o/strLen.o ./o/strComp.o ./o/strCompLimit.o ./o/executeProgram.o
    done


bcc -ansi -c -o ./o/shell.o ./programs/shell.c

ld86 -o ./bin/shell -d ./o/shell.o lib_asm.o ./o/readFile.o ./o/writeFile.o  ./o/div.o ./o/mod.o ./o/printChar.o ./o/printString.o ./o/copy.o ./o/readString.o ./o/readSector.o ./o/writeSector.o ./o/printline.o ./o/getDirIndex.o ./o/getPathIndex.o ./o/clear.o ./o/clearScreen.o ./o/strLen.o ./o/strComp.o ./o/strCompLimit.o ./o/executeProgram.o

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