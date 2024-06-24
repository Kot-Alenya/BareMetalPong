section .text
extern _system_interrupts_common_handler
systemInteruptHandlerStart:
    pusha
    call _system_interrupts_common_handler
    popa
    add esp, 8 ; Очищаем стек от номера прерывания и кода ошибки
    sti
    iret

%macro SysIntNoErrorCode 1
global _sys_int%1
_sys_int%1:
    cli
    push dword 0
    push dword %1
    jmp systemInteruptHandlerStart
%endmacro

%macro SysIntErrorCode 1
global _sys_int%1
_sys_int%1:
    cli
    push dword %1
    jmp systemInteruptHandlerStart
%endmacro

SysIntNoErrorCode 0
SysIntNoErrorCode 1
SysIntNoErrorCode 2
SysIntNoErrorCode 3
SysIntNoErrorCode 4
SysIntNoErrorCode 5
SysIntNoErrorCode 6
SysIntNoErrorCode 7
SysIntErrorCode 8
SysIntNoErrorCode 9
SysIntErrorCode 10
SysIntErrorCode 11
SysIntErrorCode 12
SysIntErrorCode 13
SysIntErrorCode 14
SysIntNoErrorCode 15
SysIntNoErrorCode 16
SysIntErrorCode 17
SysIntNoErrorCode 18
SysIntNoErrorCode 19
SysIntNoErrorCode 20
SysIntErrorCode 21
SysIntNoErrorCode 22
SysIntNoErrorCode 23
SysIntNoErrorCode 24
SysIntNoErrorCode 25
SysIntNoErrorCode 26
SysIntNoErrorCode 27
SysIntNoErrorCode 28
SysIntNoErrorCode 29
SysIntNoErrorCode 30
SysIntNoErrorCode 31