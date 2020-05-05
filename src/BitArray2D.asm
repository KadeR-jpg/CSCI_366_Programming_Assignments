
        global  set_bit_elem
        global  get_bit_elem
        section .text

set_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ;add your code here
        ;rdx - contains row
        ;rcx - contains col
        mov rax, rdx
        imul rax, rsi
        add rax, rcx
        mov rcx, rax
        sar rcx, 3
        imul rdx, -1
        add rdx, rax
        mov rcx, 8
        sub rcx, rdx
        sub rcx, 1
        mov rdx, 1
        .LOOP:
            sal rdx, 1
            dec rcx
            cmp rcx, 0
            jg  .LOOP
        or rdi, rdx
        mov rax, rdi
        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret



get_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

       mov rax, rdx
       imul rax, rsi
       add rax, rcx
       mov rcx, rax
       sar rcx, 3
       imul rdx, -1
       add rdx, rax
       mov rcx, 8
       sub rcx, rdx
       sub rcx, 1
       mov rdx, 1
       .loop1:
           sal rdx, 1
           dec rcx
           cmp rcx, 0
           jg  .loop1
           and rdx, rdi
           mov rax, rdx
           cmp rax, 1
           setl al
           movzx rax, al
        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax
