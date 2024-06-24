#include <stdint.h>
#include "MyMemory.h"
#include "Bitmap.h"

static uint32_t *_frames_status_bitmap;
static uint32_t _frames_count;

void paging_create_frame_bitmap(uint32_t frames_count)
{
	uint32_t size = calculate_byte_size(frames_count);
	
	_frames_status_bitmap = (uint32_t*)memory_allocate(size);
	memory_set((void*)_frames_status_bitmap, 0, size);

	_frames_count = frames_count;
}

void paging_set_frame(uint32_t frame_number)
{
	bitmap_set(_frames_status_bitmap, frame_number);
}

void paging_clear_frame(uint32_t frame_number)
{
	bitmap_clear(_frames_status_bitmap, frame_number);
}

uint32_t paging_get_frames_count()
{
	return _frames_count;
}

uint32_t paging_test_frame(uint32_t frame_number)
{
	return bitmap_test(_frames_status_bitmap, frame_number);
}
