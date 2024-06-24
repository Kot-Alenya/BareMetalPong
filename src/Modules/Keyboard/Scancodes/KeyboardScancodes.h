#ifndef _KeyboardScanCodes_h
#define _KeyboardScanCodes_h

//http://www.techhelpmanual.com/57-keyboard_scan_codes.html

typedef enum keyboard_scancode
{
    ESC = 0x01,
    KEY_1 = 0x02, // 1 !
    KEY_2 = 0x03, // 2 @
    KEY_3 = 0x04, // 3 #
    KEY_4 = 0x05, // 4 $
    KEY_5 = 0x06, // 5 %
    KEY_6 = 0x07, // 6 ^
    KEY_7 = 0x08, // 7 &
    KEY_8 = 0x09, // 8 *
    KEY_9 = 0x0A, // 9 (
    KEY_0 = 0x0B, // 0 )
    MINUS = 0x0C, // - _
    EQUAL = 0x0D, // = +
    BACKSPACE = 0x0E,
    TAB = 0x0F,
    Q = 0x10,
    W = 0x11,
    E = 0x12,
    R = 0x13,
    T = 0x14,
    Y = 0x15,
    U = 0x16,
    I = 0x17,
    O = 0x18,
    P = 0x19,
    LEFT_BRACKET = 0x1A, // [ {
    RIGHT_BRACKET = 0x1B, // ] }
    ENTER = 0x1C,
    LEFT_CTRL = 0x1D,
    A = 0x1E,
    S = 0x1F,
    D = 0x20,
    F = 0x21,
    G = 0x22,
    H = 0x23,
    J = 0x24,
    K = 0x25,
    L = 0x26,
    SEMICOLON = 0x27, // ; :
    APOSTROPHE = 0x28, // ' "
    GRAVE = 0x29, // ` ~
    LEFT_SHIFT = 0x2A,
    BACK_SLASH = 0x2B, // \ |
    Z = 0x2C,
    X = 0x2D,
    C = 0x2E,
    V = 0x2F,
    B = 0x30,
    N = 0x31,
    M = 0x32,
    COMMA = 0x33, // , <
    PERIOD = 0x34, // . >
    FORWARD_SLASH = 0x35, // / ?
    //...
    LEFT_ALT = 0x38,
    SPACE = 0x39,
    CAPSLOCK = 0x3A,
    //...
    UP_ARROW = 0x48,
    //...
    LEFT_ARROW = 0x4B,
    RIGHT_ARROW = 0x4D,
    //...
    DOWN_ARROW = 0x50,
    //...
    DELETE = 0x53
    //...
} keyboard_scancode_t;

#endif