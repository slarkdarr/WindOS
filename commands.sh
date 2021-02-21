bcc -ansi -c -o kernel.o kernel.c -lrt
nasm -f as86 kernel.asm -o kernel_asm.o
ld86 -o kernel -d kernel.o kernel_asm.o
dd if=kernel of=system.img bs=512 conv=notrunc seek=1
bochs -f if2230.config