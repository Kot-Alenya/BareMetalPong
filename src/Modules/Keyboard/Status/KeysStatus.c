#include <stdint.h>
#include "Bitmap.h"
#include "KeyboardScancodes.h"
#include "Keyboard.h"

static const uint32_t MAX_KEY_SCANCODE = 0x53;

static uint32_t _keys_status_bitmap[3];
static uint32_t _is_e0;
static uint32_t _is_capslock;

static on_change_key_status_handler_t _on_change_key_status_handlers[2];
static uint32_t on_change_key_status_handlers_count = 0;

static void clear(uint32_t key_code)
{
    bitmap_clear((uint32_t*)&_keys_status_bitmap, (uint32_t)key_code);

	for(uint32_t i = 0; i < on_change_key_status_handlers_count; i++)
		_on_change_key_status_handlers[i](key_code, 0);
}

static void set(uint32_t key_code)
{
    bitmap_set((uint32_t*)&_keys_status_bitmap, (uint32_t)key_code);

	for(uint32_t i = 0; i < on_change_key_status_handlers_count; i++)
		_on_change_key_status_handlers[i](key_code, 1);
}

static uint32_t test(uint32_t key_code)
{
    return bitmap_test((uint32_t*)&_keys_status_bitmap, (uint32_t)key_code) != 0;
}

static uint32_t is_valide_key(uint32_t key_code)
{
	if(key_code > 0x80) 
	{
		if(key_code > MAX_KEY_SCANCODE + 0x80)
			return 0;
	}	
	else if(key_code > MAX_KEY_SCANCODE)
		return 0;
	
	return 1;
}

static uint32_t clear_or_set(uint32_t key_code_set, uint32_t key_code_clear, uint32_t is_set, uint32_t is_clear)
{
	if(is_clear)
	{
    	clear(key_code_clear);
		return 1;
	}
	else if(is_set)
	{
		set(key_code_set);
		return 1;
	}

	return 0;
}

static uint32_t is_update_capslock(uint32_t key_code)
{
	if(key_code != CAPSLOCK && key_code != CAPSLOCK + 0x80)
		return 0;
	
	if(!test(CAPSLOCK))
		_is_capslock = !_is_capslock;

	clear_or_set(CAPSLOCK, CAPSLOCK, key_code == CAPSLOCK, key_code == CAPSLOCK + 0x80);

	return 1;
}

static uint32_t is_update_arrows(uint32_t key_code)
{
	if(clear_or_set(UP_ARROW, UP_ARROW, key_code == UP_ARROW, key_code == UP_ARROW + 0x80))
		return 1;
	if(clear_or_set(LEFT_ARROW, LEFT_ARROW, key_code == LEFT_ARROW, key_code == LEFT_ARROW + 0x80))
		return 1;
	if(clear_or_set(RIGHT_ARROW, RIGHT_ARROW, key_code == RIGHT_ARROW, key_code == RIGHT_ARROW + 0x80))
		return 1;
	if(clear_or_set(DOWN_ARROW, DOWN_ARROW, key_code == DOWN_ARROW, key_code == DOWN_ARROW + 0x80))
		return 1;
	return 0;
}

static uint32_t is_update_delete(uint32_t key_code)
{
	return clear_or_set(DELETE, DELETE, key_code == DELETE, key_code == DELETE + 0x80);
}

void keys_status_update(uint32_t key_code)
{
	if(key_code == 0xE1)
		return;
	
    if(key_code == 0xE0)
    {
        _is_e0 = 1;
        return;
    }

	if(_is_e0)
	{
        _is_e0 = 0;

		if(is_update_arrows(key_code))
			return;
		if(is_update_delete(key_code))
			return;
		return;
	}
	
	if(!is_valide_key(key_code)) 
		return;
		
	if(is_update_capslock(key_code))
		return;

	clear_or_set(key_code, key_code - 0x80, 1, key_code > 0x80);
}

void keyboard_register_on_change_key_status_handler(on_change_key_status_handler_t handler)
{
	_on_change_key_status_handlers[on_change_key_status_handlers_count] = handler;
	on_change_key_status_handlers_count++;
}

void keyboard_unregister_on_change_key_status_handler(on_change_key_status_handler_t handler)
{
	for(uint32_t i = 0; i < on_change_key_status_handlers_count; i++)
	{
		if(_on_change_key_status_handlers[i] != handler)
			continue;
	
		for(uint32_t j = i; j < on_change_key_status_handlers_count - 1; j++)
			_on_change_key_status_handlers[j] = _on_change_key_status_handlers[j + 1];

		on_change_key_status_handlers_count--;	
		break;
	}
}

uint32_t keyboard_is_capslock()
{
	return _is_capslock;
}
uint32_t keyboard_test_key(keyboard_scancode_t key_code)
{
	return test(key_code);
}