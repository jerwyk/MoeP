.set IRQ_BASE, 0x20

.data
    interruptnumber: .byte 0

.section .text

.extern _ZN4MoeP6kernel16InterruptManager15HandleInterruptEhj

.global _ZN4MoeP6kernel16InterruptManager22IgnoreInterruptRequestEv

.macro HandleInterruptException num
.global _ZN4MoeP6kernel16InterruptManager28HandleInterruptException\num\()Ev
_ZN4MoeP6kernel16InterruptManager28HandleInterruptException\num\()Ev:
    movb $\num, (interruptnumber)
    jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN4MoeP6kernel16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN4MoeP6kernel16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptnumber)
    jmp int_bottom
.endm

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x0C

int_bottom:

    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (interruptnumber)
    call _ZN4MoeP6kernel16InterruptManager15HandleInterruptEhj
    movl %eax, %esp

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

_ZN4MoeP6kernel16InterruptManager22IgnoreInterruptRequestEv:
    iret
