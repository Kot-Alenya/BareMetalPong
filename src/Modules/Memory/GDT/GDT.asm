section .data
extern GDT_DATA_SELECTOR

section .text
global _gdt_flush
_gdt_flush:
    ; Устанавливаем запись gdt
    mov eax, [esp + 4]
    lgdt [eax]

    ; Настраиваем сегментные регистры
    mov ax, word [GDT_DATA_SELECTOR]
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Переход по длинному прыжку для установки кода сегмента
    jmp 0x08:.flush ;GDT_CODE_SELECTOR = 0x08
.flush:
    ret