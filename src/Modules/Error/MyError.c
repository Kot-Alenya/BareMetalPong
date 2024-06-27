#include <stdint.h>
#include <stddef.h>
#include "Monitor.h"
#include "MyString.h"

void print_stack_trace()
{
    uint32_t max_frames_count = 10;
    uint32_t l = 0;
    uint32_t* ebp_value; //ebp содержит адресс начала кадра

    asm volatile("mov %%ebp, %0" : "=r" (ebp_value));

    l += string_build(monitor_get_common_buffer(), 0, "\nStackTrace:\n");

    for(uint32_t frameIndex = 0; frameIndex < max_frames_count; frameIndex++)
    {
        if(ebp_value == NULL)
            break;
        
        uint32_t ret_addr = *(ebp_value + 1); //адресс возврата храниться в стеке как второе значение кадра, *(ebp_value) получаем первое значение кадра, *(ebp_value + 1) получаем второе значение
        ebp_value = (uint32_t*)*ebp_value; //в кадре первое значение - старое значение регистра ebp_value, т.е. адресс указывающий на начало кадра предыдущей функции
        
        l += string_build(monitor_get_common_buffer() + l, 0, "Frame %d: 0x%h\n", frameIndex, ret_addr);
    }

    *(monitor_get_common_buffer() + l) = '\0';
    monitor_push_string(monitor_get_common_buffer());
}

void error_throw(char* mess)
{
    monitor_push_string("\n\0");
    monitor_push_string(mess);
    print_stack_trace();
    
    while(1) {}
}
