#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Int2.h"
#include "Float2.h"
#include "PixelColor.h"
#include "RectangleF.h"
#include "GameData.h"

Int2 _size;
Float2 _scale;
HANDLE _consoleHandle;
char *_buffer;

void SetSize(COORD size, HANDLE consoleHandle)
{
    HWND handle = GetConsoleWindow();
    HMENU sysMenu = GetSystemMenu(handle, FALSE);
    SMALL_RECT screenRect = {0, 0, size.X - 1, size.Y};
    COORD bufferSize = {_size.X, _size.Y + 1};

    if (handle != NULL)
    {
        DeleteMenu(sysMenu, SC_MAXIMIZE, MF_BYCOMMAND);
        DeleteMenu(sysMenu, SC_SIZE, MF_BYCOMMAND);
    }

    SetConsoleWindowInfo(consoleHandle, TRUE, &screenRect);
    SetConsoleScreenBufferSize(consoleHandle, bufferSize);
    SetConsoleWindowInfo(consoleHandle, TRUE, &screenRect);
}

void SetCursorVisible(HANDLE consoleHandle)
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);

    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void ClearBuffer()
{
    for (int i = 0; i < _size.X * _size.Y; i++)
        _buffer[i] = ' ';
}

void Screen_Initialize()
{
    _size = GameStaticData.ScreenSize;
    _scale = Float2_DivFloat2(Int2_ToFloat2(GameStaticData.ScreenSize), GameStaticData.MapSize);
    _consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    _buffer = malloc(_size.X * _size.Y * sizeof(char));

    COORD size = {_size.X, _size.Y};

    SetSize(size, _consoleHandle);
    SetCursorVisible(_consoleHandle);
    ClearBuffer();
}

void Screen_Update()
{
    COORD cursorPosition = {0, 0};
    
    SetConsoleCursorPosition(_consoleHandle, cursorPosition);
    fwrite(_buffer, sizeof(char), _size.X * _size.Y, stdout);
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
    char str[12];
    snprintf(str, sizeof(str), "%d", number);
    int length = strlen(str);

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
    free(_buffer);
}