org 0x8000
bits 16

mov ah,0
mov al,13h
int 0x10

mov si,imageFile
call drawImage

jmp $

drawImage:
	pusha
	xor ax, ax
	lodsb
	mov cx, ax                      ;x-length (first byte of binary)
	lodsb
	mov dx, ax                      ;y-length (2nd byte of binary)
	.for_x:
		push dx
		.for_y:
			mov bh, 0               ;page number (0 is default)
			lodsb                   ;read byte to al (color) -> next byte
			mov ah, 0xC             ;write pixel at coordinate (cx, dx)
			int 0x10                ;draw!
		sub dx, 1                   ;decrease dx by one and set flags
		jnz .for_y                  ;repeat for y-length
		pop dx                      ;restore dx (y-length)
	sub cx, 1                       ;decrease si by one and set flags
	jnz .for_x                      ;repeat for x-length
	popa                            ;restore everything
	ret
	
imageFile : incbin "image.bin"

%assign usedMemory ($-$$)
%assign usableMemory (512*16)
%warning [usedMemory/usableMemory] Bytes used
times (512*16)-($-$$) db 0
