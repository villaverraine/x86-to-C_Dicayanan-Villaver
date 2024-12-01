section .data
; Precomputed value for 1/255.0 as a double
scale dq 0.00392156862745098      

section .text
bits 64
default rel
global imgCvtGrayIntToDouble

imgCvtGrayIntToDouble:
    ; rcx -> output (double *output)
    ; rdx -> input (int *input)
    ; r8  -> total_elements (int total_elements)

    movsd xmm1, [scale]

    ; r9: index
    xor r9, r9

loop_start:
    cmp r9, r8
    jge loop_end

    ; convert input[r9] to double
    mov eax, dword [rdx + r9*4]
    cvtsi2sd xmm0, rax

    ; input[r9] / 255.0
    mulsd xmm0, xmm1

    ; store it to output array
    movsd [rcx + r9*8], xmm0

    ; Increment index and loop
    inc r9 
    jmp loop_start

loop_end:
    ret

