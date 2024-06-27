#ifndef _Monitor_h
#define _Monitor_h

#include <stdint.h>

extern const uint8_t MONITOR_HEIGHT;
extern const uint8_t MONITOR_WIDTH;

typedef enum 
{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15
} VgaColor;

extern void monitor_initialize();
extern char* monitor_get_common_buffer();
extern void monitor_clean();

extern uint32_t monitor_get_cursor_position();
extern void monitor_set_cursor_position(uint32_t position);
extern void monitor_set_cursor_blinking(uint32_t is_blinking);

extern void monitor_push_char(char c);
extern void monitor_push_string(char* c);
extern void monitor_push_uint32(uint32_t value);
extern void monitor_push_uint32_hex(uint32_t value);
extern void monitor_push_uint32_bin(uint32_t value);
extern void monitor_push_int32(int32_t value);
extern void monitor_push_float(float value);

extern void monitor_set_char(char c, uint32_t position);
#endif