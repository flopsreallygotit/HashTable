;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

section .rodata

Power: equ 53

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

section .text

global polynomialRollingHashASM

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Pollynomial Rolling Hash Function on x86-64 asm
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Entry:    RDI = Address of string
; Exit:     RAX = Hash value
; Destroys: None
; Expects:  Constant number 'Power'
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

polynomialRollingHashASM:  
        push rdi    ; Saving registers values
        push rbx
        push rcx
        push rdx
        push r8
        push r9

        mov rax, 1      ; Moving 1 to register for current power
        mov r8, Power   ; Moving power to register

        xor rbx, rbx    ; Zeroing register for current symbol
        xor rcx, rcx    ; Zeroing register for hash

.next:  mov bl, byte [rdi]  ; Loading current symbol in BL
        test bl, bl         ; Checking that current symbol != '\0'
        jz .end

        mov r9, rax         ; Saving current power

        mul rbx             ; Mulling current power and current symbol
        add rcx, rax        ; Adding that value to hash

        mov rax, r9         ; Restoring current power

        mul r8              ; Increasing power
        inc rdi             ; Going to next symbol
        jmp .next           ; Going to next iteration

.end:   mov rax, rcx    ; Saving hash value to RAX

        pop  r9         ; Restoring registers values
        pop  r8
        pop  rdx 
        pop  rcx
        pop  rbx
        pop  rdi 

        ret

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; crc32 on x86-64 asm
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Entry:    RDI = Address of string
; Exit:     RAX = Hash value
; Destroys: None
; Expects:  None
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

global crc32AVX

crc32AVX:       xor rax, rax                    ; Zero register for hash

                crc32 rax, qword [rdi + 0 * 8]  ; Counting hash
                crc32 rax, qword [rdi + 1 * 8]
                crc32 rax, qword [rdi + 2 * 8]
                crc32 rax, qword [rdi + 3 * 8]

                ret

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
