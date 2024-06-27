#include "Int2.h"
#include "Float2.h"
#include "PixelColor.h"
#include "RectangleF.h"
#include "GameData.h"
#include "Monitor.h"
#include "MyMemory.h"
#include "MyString.h"
#include "MyMath.h"

static Int2 _size = {.X = 80, .Y = 25};
static Float2 _scale = {.X= 1, .Y = 1};
static char *_buffer;

static void ClearBuffer()
{
    //for(int i = 0; i < _size.X * _size.Y; i++)
    //    _buffer[i] = ' ';
}

void Screen_Initialize()
{
    _buffer = memory_allocate(_size.X * _size.Y * sizeof(char));
    ClearBuffer();
    monitor_set_cursor_blinking(0);
}

void Screen_Update()
{
    for(int i = 0; i < _size.X * _size.Y; i++)
        monitor_set_char(_buffer[i], i);

    ClearBuffer();
}

void SetChar(Int2 position, char c)
{
    _buffer[position.Y * _size.X + position.X] = c;
}

void Screen_DrawRectangle(RectangleF rect, PixelColor color)
{
    Int2 position = Int2_FromFloat2(Float2_MulFloat2(rect.LeftUpCornerPosition, _scale));
    Int2 rectSize = Int2_FromFloat2(Float2_MulFloat2(rect.Size, _scale));

    for (int x = 0; x < rectSize.X; x++)
    for (int y = 0; y < rectSize.Y; y++)
    {
        Int2 currentPosition = 
        {
            position.X + x,
            position.Y + y
        };

        SetChar(currentPosition, color);
    }
}

void Screen_DrawNumber(Int2 position, int number)
{
    int length = math_get_digits_count(number);
    char str[length];
    string_from_uint32(str, number, 0);

    for(int i = 0; i < length; i++)
    {
        Int2 currentPosition = 
        {
            position.X + i,
            position.Y
        };

        SetChar(currentPosition, str[i]);
    }
}

void Screen_Dispose()
{
    memory_free(_buffer);
    monitor_clean();
    monitor_set_cursor_blinking(1);
}