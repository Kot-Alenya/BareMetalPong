#include <stdint.h>
#include "IOAccess.h"

//https://wiki.osdev.org/Reboot

/* keyboard interface IO port: data and control
   READ:   status port
   WRITE:  control register */
#define KBRD_INTRFC 0x64

// keyboard interface bits 
#define KBRD_BIT_KDATA 0 // keyboard data is in buffer (output buffer is empty) (bit 0)
#define KBRD_BIT_UDATA 1 // user data is in buffer (command buffer is empty) (bit 1) 

#define KBRD_IO 0x60 // keyboard IO port 
#define KBRD_RESET 0xFE // reset CPU command 

#define bit(n) (1<<(n)) // Set bit n to 1 

#define check_flag(flags, n) ((flags) & bit(n)) // Check if bit n in flags is set 

void machine_control_reboot()
{
    uint8_t temp = io_in_byte(KBRD_INTRFC); // empty user data 
    
    while (check_flag(temp, KBRD_BIT_UDATA) != 0) 
    {
        if (check_flag(temp, KBRD_BIT_KDATA) != 0) 
        {
            io_in_byte(KBRD_IO); // empty keyboard data 
        }
        temp = io_in_byte(KBRD_INTRFC); // empty user data 
    }

    io_out_byte(KBRD_INTRFC, KBRD_RESET); // pulse CPU reset line 

    asm volatile ("hlt");
    while (1) {}    
}
