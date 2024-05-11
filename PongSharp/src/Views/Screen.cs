using System.Numerics;
using System.Runtime.InteropServices;
using PongSharp.Data;

namespace PongSharp.Views;

internal class Screen(Int2 size, Vector2 scale)
{
    private const int MF_BYCOMMAND = 0x00000000;
    private const int SC_MAXIMIZE = 0xF030;
    private const int SC_SIZE = 0xF000;

    private readonly char[] _buffer = new char[size.X * size.Y];

    [DllImport("user32.dll")]
    private static extern int DeleteMenu(IntPtr hMenu, int nPosition, int wFlags);

    [DllImport("user32.dll")]
    private static extern IntPtr GetSystemMenu(IntPtr hWnd, bool bRevert);

    [DllImport("kernel32.dll", ExactSpelling = true)]
    private static extern IntPtr GetConsoleWindow();

    public void Initialize()
    {
        SetConstantWindowSize();
        Console.CursorVisible = false;
    }

    public void Update()
    {
        Console.SetCursorPosition(0, 0);
        Console.Write(_buffer);

        for (var i = 0; i < _buffer.Length; i++)
            _buffer[i] = ' ';
    }

    public void DrawRectangle(Rectangle rect, PixelColor color)
    {
        var position = Int2.FromVector2(rect.LeftUpCornerPosition * scale);
        var rectSize = Int2.FromVector2(rect.Size * scale);

        for (var x = 0; x < rectSize.X; x++)
        for (var y = 0; y < rectSize.Y; y++)
            SetChar(new Int2(position.X + x, position.Y + y), (char)color);
    }

    public void DrawNumber(Int2 position, int number)
    {
        var str = number.ToString();

        for (var i = 0; i < str.Length; i++)
            SetChar(new Int2(position.X + i, position.Y), str[i]);
    }

    private void SetConstantWindowSize()
    {
        var handle = GetConsoleWindow();
        var sysMenu = GetSystemMenu(handle, false);
        var screenYSize = size.Y + 1;
        
        if (handle != IntPtr.Zero)
        {
            DeleteMenu(sysMenu, SC_MAXIMIZE, MF_BYCOMMAND);
            DeleteMenu(sysMenu, SC_SIZE, MF_BYCOMMAND);
        }

        Console.SetWindowSize(size.X, screenYSize);
        Console.SetBufferSize(size.X, screenYSize);
        Console.SetWindowSize(size.X, screenYSize);
    }

    private void SetChar(Int2 position, char c) => _buffer[position.Y * size.X + position.X] = c;
}