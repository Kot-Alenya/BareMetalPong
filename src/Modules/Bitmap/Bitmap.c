#include <stdint.h>

static const uint32_t INT_BIT_COUNT = (8 * sizeof(uint32_t));

inline static uint32_t get_index(uint32_t value)
{
	return (value / INT_BIT_COUNT);
}

inline static uint32_t get_offset(uint32_t value)
{
	return (value % INT_BIT_COUNT);
}

uint32_t bitmap_get_index(uint32_t value)
{
	return get_index(value);
}

uint32_t bitmap_get_offset(uint32_t value)
{
	return get_offset(value);
}

void bitmap_set(uint32_t* bitmap, uint32_t number)
{
	uint32_t index = get_index(number);
	uint32_t offset = get_offset(number);
	bitmap[index] |= (0x1 << offset);
}

void bitmap_clear(uint32_t* bitmap, uint32_t number)
{
	uint32_t index = get_index(number);
	uint32_t offset = get_offset(number);
	bitmap[index] &= ~(0x1 << offset);
}

uint32_t bitmap_test(uint32_t* bitmap, uint32_t number)
{
	uint32_t index = get_index(number);
	uint32_t offset = get_offset(number);
	return (bitmap[index] & (0x1 << offset));
}

uint32_t calculate_byte_size(uint32_t elements_count)
{
	uint32_t frame_bit_map_int_size = bitmap_get_index(elements_count) + (bitmap_get_offset(elements_count) ? 1 : 0);
	return frame_bit_map_int_size * sizeof(uint32_t);
}