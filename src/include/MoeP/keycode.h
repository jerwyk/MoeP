#pragma once

#include <MoeP/types.h>

//represents a 8 bit keycode
//the lower 7 bit represents the actual keycode, where as the highest bit will be 1 if it is an hey release
typedef uint8 keycode_t;
#define KEY_RELEASE 0x80

//all the keycode corresponding to keys on the keyboard
//keycode ranges from 0x01 to 0x7F for key press
//0x80 to 0xFF is for the corresponding key release
namespace MoeP
{
    enum 
    {
        //letters
        KEY_A = 0x01,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,
        //numbers
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        KEY_0,
        //space related
        KEY_ENTER,
        KEY_TAB,
        KEY_SPACE,
        KEY_BACKSPACE,
        KEY_ESC,
        //other characters
        KEY_COMMA,
        KEY_PERIOD,
        KEY_SLASH,
        KEY_SEMICOLON,
        KEY_QUOTE,
        KEY_OPEN_BRACKET,
        KEY_CLOSE_BRACKET,
        KEY_BACKSLASH,
        KEY_DASH,
        KEY_PLUS,
        KEY_EQUAL,
        KEY_BACK_TICK,
        KEY_CAPS_LOCK,
        //arrow keys
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        //utility
        KEY_PTRSCN,
        KEY_PAUSE,
        KEY_SCROLL_LOCK,
        KEY_INSERT,
        KEY_HOME,
        KEY_PAGE_UP,
        KEY_DELETE,
        KEY_END,
        KEY_PAGE_DOWN,
        //functions keys
        KEY_F1,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12,
        //number pad
        KEY_NUM_LOCK,
        KEY_NUM_1,
        KEY_NUM_2,
        KEY_NUM_3,
        KEY_NUM_4,
        KEY_NUM_5,
        KEY_NUM_6,
        KEY_NUM_7,
        KEY_NUM_8,
        KEY_NUM_9,
        KEY_NUM_0,
        KEY_NUM_DOT,
        KEY_NUM_SLASH,
        KEY_NUM_STAR,
        KEY_NUM_DASH,
        KEY_NUM_PLUS,
        KEY_NUM_ENTER,

        KEY_LCTRL,
        KEY_RCTRL,
        KEY_LALT,
        KEY_RALT,
        KEY_LSHIFT,
        KEY_RSHIFT,
        KEY_LGUI,//basically the windows key on most keyboards
        KEY_RGUI,
        KEY_APPS,

        KEY_VOLUMN_UP,
        KEY_VOLUMN_DOWN,
        KEY_VOLUMN_MUTE,
        KEY_MEDIA_PLAY,
        KEY_MEDIA_STOP,
        KEY_MEDIA_PREV,
        KEY_MEDIA_NEXT,
    };
}