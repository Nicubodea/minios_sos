segment .text
[BITS 32]

;;
;; import / export entries between .nasm and .c parts
;;
%ifidn __OUTPUT_FORMAT__, win32
extern _SosEntryPoint                  ; import C entry point from main.c
SosEntryPoint equ _SosEntryPoint          ; win32 builds from Visual C decorate C names using _
%else
extern SosEntryPoint                   ; import C entry point from main.c
%endif

global gMultiBootHeader         ; export multiboot structures to .c
global gMultiBootStruct


;;
;; we use hardcoded address space / map for our data structures, the multiboot header and the entry point
;; the plain binary image is loaded to 0x00200000 (2MB)
;;
KERNEL_BASE_VIRTUAL_32      equ 0x40000000			    ; magic 1G VA for x86 builds
KERNEL_BASE_VIRTUAL_64      equ 0x0000000200000000	    ; magic 8G VA for x64 builds
KERNEL_BASE_PHYSICAL        equ 0x200000                ; physical address where this file will be loaded (2 MB PA)

MULTIBOOT_HEADER_BASE       equ KERNEL_BASE_PHYSICAL + 0x400 ; take into account the MZ/PE header + 0x400 allignment
                                                        ; the multiboot header begins in the .text section
MULTIBOOT_HEADER_SIZE       equ 48                      ; check out '3.1.1 The layout of Multiboot header'
MULTIBOOT_HEADER_MAGIC      equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS      equ 0x00010003              ; 0x1 ==> loading of modules must pe 4K alligned, 0x2 ==> OS needs memory map
                                                        ; 0x10000 ==> OS image has valid header_addr, load_addr, ..., entry_addr

MULTIBOOT_INFO_STRUCT_BASE  equ MULTIBOOT_HEADER_BASE + MULTIBOOT_HEADER_SIZE
MULTIBOOT_INFO_STRUCT_SIZE  equ 90

MULTIBOOT_ENTRY_POINT       equ (gMultiBootEntryPoint - gMultiBootHeader) + KERNEL_BASE_PHYSICAL + 0x400

IA32_EFER                   equ 0xC0000080
CR4_PAE                     equ 0x00000020
IA23_EFER_LME               equ 0x100


TOP_OF_STACK_VIRTUAL        equ KERNEL_BASE_VIRTUAL_64 + 0x10000



;;
;; KERNEL_BASE_PHYSICAL + 0x400
;;
;; *** IMPORTANT: __init.nasm MUST be the first object to be linked into the code segment ***
;;

gMultiBootHeader:                                       ; check out '3.1.1 The layout of Multiboot header'
.magic          dd MULTIBOOT_HEADER_MAGIC
.flags          dd MULTIBOOT_HEADER_FLAGS
.checksum       dd 0-(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
.header_addr    dd MULTIBOOT_HEADER_BASE
.load_addr      dd KERNEL_BASE_PHYSICAL
.load_end_addr  dd 0
.bss_end_addr   dd 0
.entry_addr     dd MULTIBOOT_ENTRY_POINT
.mode_type      dd 0
.width          dd 0
.height         dd 0
.depth          dd 0

gMultiBootStruct:                                       ; reserve space for the multiboot info structure (will copy here)
times MULTIBOOT_INFO_STRUCT_SIZE db 0                   ; check out '3.3 Boot information format'


;; leave 0x40 bytes for GDT stuff
times (0x100 - MULTIBOOT_HEADER_SIZE - MULTIBOOT_INFO_STRUCT_SIZE - 0x40) db 0


;;
;; N.B. here we have plenty of space (over 60KB to be used to define various data structures needed, e.g. page tables)
;;

;;
;; KERNEL_BASE_PHYSICAL + 0x4C0
;;

GDTR_BASE_PHYSICAL equ KERNEL_BASE_PHYSICAL + 0x4C0

gGdtr:
	dw 0x38
	dd GDTR_BASE_PHYSICAL + 0x6

gGdt:
dq 0000000000000000000000000000000000000000000000000000000000000000b	;; null descriptor
;; base		flg lim	access	base	base			lim
dq 0000000001001111100110100000000000000000000000001111111111111111b	;; code 32
dq 0000000001001111100100100000000000000000000000001111111111111111b	;; data 32
dq 0000000000101111100110100000000000000000000000001111111111111111b	;; code 64 ring 0
dq 0000000000101111100100100000000000000000000000001111111111111111b	;; data 64 ring 0
dq 0000000000101111111110100000000000000000000000001111111111111111b	;; code 64 ring 3
dq 0000000000101111111100100000000000000000000000001111111111111111b	;; data 64 ring 3


;; much alignment such lol
times 0x1000 - 0x38 - 0x6 - 0x4C0 db 0

;; KERNEL_BASE_PHYSICAL + 0x1000 - PML4 ; each entry = 512 GB
dq 0x00202001
times 512 - 1 dq 0

;; KERNEL_BASE_PHYSICAL + 0x2000 - PDPT ; each entry = 1 GB
dq 0x00203001	; 0-1 gb
dq 0			; 1-2 gb
dq 0			; 2-3 gb
dq 0			; 3-4 gb
dq 0			; 4-5 gb
dq 0			; 5-6 gb
dq 0			; 6-7 gb
dq 0			; 7-8 gb
dq 0x00204001	; 8-10 gb
times 512 - 9 dq 0

;; KERNEL_BASE_PHYSICAL + 0x3000 - PD ; each entry = 2 MB
dq 0x00000081
dq 0x00200081
dq 0x00400081
times 512 - 3 dq 0

;; KERNEL_BASE_PHYSICAL + 0x4000 - PD for virtual addresses
dq 0x00000081
dq 0x00200081
dq 0x00400081
dq 0x00600081
times 512 - 4 dq 0

;;
;; TOP-OF-STACK is KERNEL_BASE_PHYSICAL + 0x10000
;;


;;
;; N.B. multiboot starts in 32 bit PROTECTED MODE, without paging beeing enabled (FLAT); check out '3.2 Machine state' from docs
;; we explicitly allign the entry point to +64 KB (0x10000)
;;

times 0x10000-0x400-$+gMultiBootHeader db 'G'           ; allignment


;;
;; KERNEL_BASE_PHYSICAL + 0x10000
;;
[BITS 32]
gMultiBootEntryPoint:
    cli

    MOV     DWORD [0x000B8000], 'O1S1'
%ifidn __OUTPUT_FORMAT__, win32
    MOV     DWORD [0x000B8004], '3121'                  ; 32 bit build marker
%else
    MOV     DWORD [0x000B8004], '6141'                  ; 64 bit build marker
%endif

	LGDT	[GDTR_BASE_PHYSICAL]

    ;; enable SSE instructions (CR4.OSFXSR = 1)
    MOV     EAX, CR4
    OR      EAX, 0x00000200
    MOV     CR4, EAX

	;; put the root PML4
	MOV		EAX, KERNEL_BASE_PHYSICAL + 0x1000
	MOV		CR3, EAX

	;; enable PAE & PSE
	MOV		EAX, CR4
	OR		EAX, 0x30
	MOV		CR4, EAX

	;; enable LME
	MOV		ECX, 0xC0000080
	RDMSR
	OR		EAX, 0x100
	WRMSR

	;; enable paging
	MOV		EAX, CR0
	OR		EAX, 0x80000000
	MOV		CR0, EAX


	;; now we are in 64 bits compatibility mode (i think)

	;; Put the 64 bit data selector in our segments
	mov EAX, 0x20
	MOV DS, EAX
	MOV ES, EAX
	MOV SS, EAX
	MOV GS, EAX
	MOV FS, EAX

	;; We'll do a little trick here: get the current RIP (from POP ECX)
	;; Then add to this rip the number of bytes until the 64bit stub
	;; Then push the 64 bit code selector on the stack
	;; and finally perform a retf to change the CS
	CALL	$ + 5
	POP		ECX
	ADD		ECX, 0x8
	PUSH	0x18
	PUSH	ECX
	RETF	


[BITS 64]
.64BitStub:
	
	;; We should enter C with virtual RIP and virtual RSP

	CALL $ + 5
	POP RCX
	MOV RBX, KERNEL_BASE_VIRTUAL_64
	ADD RCX, RBX
	ADD RCX, 0x14
	PUSH RCX
	RET

	MOV RSP, KERNEL_BASE_VIRTUAL_64
	ADD RSP, 0x400000 ; 2 MB stack will do 

    CALL SosEntryPoint
    
    CLI
    HLT

;;--------------------------------------------------------
;; EXPORT TO C FUNCTIONS
;;--------------------------------------------------------

;%ifidn __OUTPUT_FORMAT__, win32 ; win32 builds from Visual C decorate C names using _ 
;global ___cli
;___cli equ __cli
;%else
;global __cli
;%endif

%macro EXPORT2C 1-*
%rep  %0
    %ifidn __OUTPUT_FORMAT__, win32 ; win32 builds from Visual C decorate C names using _ 
    global _%1
    _%1 equ %1
    %else
    global %1
    %endif
%rotate 1 
%endrep
%endmacro

EXPORT2C __cli, __sti, __magic

__cli:
    CLI
    RET

__sti:
    STI
    RET

__magic:
    XCHG    BX,BX
    RET

    
extern SosGenericInterruptHandler
global AsmHandler


GenericAsmHandler:

cmp qword [rsp], 8
je _put_error_code
cmp qword [rsp], 10
jnae _skip_error_code
cmp qword [rsp], 14
jnbe _skip_error_code

_put_error_code:
	push rcx
	push rdx
	mov rcx, [rsp+0x18]
	mov rdx, [rsp+0x10]
	mov [rsp+0x18], rdx
	mov [rsp+0x10], rcx
	pop rdx
	pop rcx
jmp _continue
_skip_error_code:
	push 0		;; dummy error code
_continue:
push r15
push r14
push r13
push r12
push r11
push r10
push r9
push r8
push rbp
push rdi
push rsi
push rdx
push rcx
push rbx
push rax

mov rcx, [rsp+0x80]
mov rdx, rsp

sub rsp, 0x20

call SosGenericInterruptHandler

add rsp, 0x20

pop rax
pop rbx
pop rcx
pop rdx
pop rsi
pop rdi
pop rbp
pop r8
pop r9
pop r10
pop r11
pop r12
pop r13
pop r14
pop r15

;; Pop the error code + interrupt number
add rsp, 16 
iretq

;; We need to keep a padding so that we are sure that instructions of the form `e9 xx xx xx xx` are generated at jumps
times 0x100 db 'G'

AsmHandler:
push 0x0
jmp GenericAsmHandler

push 0x1
jmp GenericAsmHandler

push 0x2
jmp GenericAsmHandler

push 0x3
jmp GenericAsmHandler

push 0x4
jmp GenericAsmHandler

push 0x5
jmp GenericAsmHandler

push 0x6
jmp GenericAsmHandler

push 0x7
jmp GenericAsmHandler

push 0x8
jmp GenericAsmHandler

push 0x9
jmp GenericAsmHandler

push 0xa
jmp GenericAsmHandler

push 0xb
jmp GenericAsmHandler

push 0xc
jmp GenericAsmHandler

push 0xd
jmp GenericAsmHandler

push 0xe
jmp GenericAsmHandler

push 0xf
jmp GenericAsmHandler

push 0x10
jmp GenericAsmHandler

push 0x11
jmp GenericAsmHandler

push 0x12
jmp GenericAsmHandler

push 0x13
jmp GenericAsmHandler

push 0x14
jmp GenericAsmHandler

push 0x15
jmp GenericAsmHandler

push 0x16
jmp GenericAsmHandler

push 0x17
jmp GenericAsmHandler

push 0x18
jmp GenericAsmHandler

push 0x19
jmp GenericAsmHandler

push 0x1a
jmp GenericAsmHandler

push 0x1b
jmp GenericAsmHandler

push 0x1c
jmp GenericAsmHandler

push 0x1d
jmp GenericAsmHandler

push 0x1e
jmp GenericAsmHandler

push 0x1f
jmp GenericAsmHandler

push 0x20
jmp GenericAsmHandler

push 0x21
jmp GenericAsmHandler

push 0x22
jmp GenericAsmHandler

push 0x23
jmp GenericAsmHandler

push 0x24
jmp GenericAsmHandler

push 0x25
jmp GenericAsmHandler

push 0x26
jmp GenericAsmHandler

push 0x27
jmp GenericAsmHandler

push 0x28
jmp GenericAsmHandler

push 0x29
jmp GenericAsmHandler

push 0x2a
jmp GenericAsmHandler

push 0x2b
jmp GenericAsmHandler

push 0x2c
jmp GenericAsmHandler

push 0x2d
jmp GenericAsmHandler

push 0x2e
jmp GenericAsmHandler

push 0x2f
jmp GenericAsmHandler
