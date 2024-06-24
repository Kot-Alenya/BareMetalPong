section .text
extern _program_interrupts_common_handler

%macro ProgIntMacro 1
global _prog_int%1
_prog_int%1:
    cli
    push dword %1
    pusha
    call _program_interrupts_common_handler
    popa
    add esp, 4
    sti
    iret
%endmacro

ProgIntMacro 0
ProgIntMacro 1
ProgIntMacro 2
ProgIntMacro 3
ProgIntMacro 4
ProgIntMacro 5
ProgIntMacro 6
ProgIntMacro 7
ProgIntMacro 8
ProgIntMacro 9
ProgIntMacro 10
ProgIntMacro 11
ProgIntMacro 12
ProgIntMacro 13
ProgIntMacro 14
ProgIntMacro 15