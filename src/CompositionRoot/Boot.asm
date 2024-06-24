%define ALIGN     (1 << 0) ; выравнивать загруженные модули по границам страницы
%define MEMINFO   (1 << 1) ; предоставлять карту памяти (memory map)
%define MAGIC     0x1BADB002 ; "волшебное" число, позволяющее загрузчику найти заголовок
%define FLAGS     (ALIGN | MEMINFO) ; это поле "флаги" заголовка
%define CHECKSUM  -(MAGIC + FLAGS) ; контрольная сумма

section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

section .bss
align 4
stack_bottom:
resb 8 * 1024
stack_top:

section .text
extern program_main
global _start
_start:
    mov esp, stack_top ; Устанавливаем стек
    push ebx ; Кидаем данные от grub в стек
    call program_main