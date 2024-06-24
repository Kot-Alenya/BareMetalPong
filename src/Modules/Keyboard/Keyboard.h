#ifndef _Keyboard_h
#define _Keyboard_h

#include <stdint.h>
#include "KeyboardScancodes.h"

typedef void (*on_change_key_status_handler_t) (keyboard_scancode_t key_code, uint32_t status);

extern void keyboard_initialize();
extern char keyboard_convert_scancode_to_ASCII(uint8_t key_code, uint32_t is_shift, uint32_t is_capslock);

extern void keyboard_register_on_change_key_status_handler(on_change_key_status_handler_t handler);
extern void keyboard_unregister_on_change_key_status_handler(on_change_key_status_handler_t handler);
extern uint32_t keyboard_is_capslock();
extern uint32_t keyboard_test_key(keyboard_scancode_t key_code);

#endif