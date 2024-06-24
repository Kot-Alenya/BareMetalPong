section .text
global _idt_flush
_idt_flush:
    mov eax, [esp + 4]
    lidt [eax]
    ret