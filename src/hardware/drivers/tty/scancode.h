#pragma once

#include <MoeP/keycode.h>
#include <hardware/keyboard.h>

using namespace MoeP;

#define SCAN_RELEASE 0x80
#define SCAN_EXTEND1 0xE0

//https://wiki.osdev.org/Keyboard
//look up table for set2 scan code
static const uint8 scancodeSet1LUT[] = 
{
    0,
    KEY_ESC,
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
    KEY_DASH,
    KEY_EQUAL,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_Q,
    KEY_W,
    KEY_E,
    KEY_R,
    KEY_T,
    KEY_Y,
    KEY_U,
    KEY_I,
    KEY_O,
    KEY_P,
    KEY_OPEN_BRACKET,
    KEY_CLOSE_BRACKET,
    KEY_ENTER,
    KEY_LCTRL,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_SEMICOLON,
    KEY_QUOTE,
    KEY_BACK_TICK,
    KEY_LSHIFT,
    KEY_BACKSLASH,
    KEY_Z,
    KEY_X,
    KEY_C,
    KEY_V,
    KEY_B,
    KEY_N,
    KEY_M,
    KEY_COMMA,
    KEY_PERIOD,
    KEY_SLASH,
    KEY_RSHIFT,
    KEY_NUM_STAR,
    KEY_LALT,
    KEY_SPACE,
    KEY_CAPS_LOCK,
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
    KEY_NUM_LOCK,
    KEY_SCROLL_LOCK,
    KEY_NUM_7,
    KEY_NUM_8,
    KEY_NUM_9,
    KEY_NUM_DASH,
    KEY_NUM_4,
    KEY_NUM_5,
    KEY_NUM_PLUS,
    KEY_NUM_1,
    KEY_NUM_2,
    KEY_NUM_3,
    KEY_NUM_DOT,
    0,
    0,
    0,
    KEY_F11,
    KEY_F12,
};

static const uint8 scancodeSet1EscapeLUT[] = 
{
    0,                  //0x0
    0,                  //0x1
    0,                  //0x2
    0,                  //0x3
    0,                  //0x4
    0,                  //0x5
    0,                  //0x6
    0,                  //0x7
    0,                  //0x8
    0,                  //0x9
    0,                  //0xa
    0,                  //0xb
    0,                  //0xc
    0,                  //0xd
    0,                  //0xe
    0,                  //0xf
    KEY_MEDIA_PREV,     //0x10
    0,                  //0x11
    0,                  //0x12
    0,                  //0x13
    0,                  //0x14
    0,                  //0x15
    0,                  //0x16
    0,                  //0x17
    0,                  //0x18
    KEY_MEDIA_NEXT,     //0x19
    0,                  //0x1a
    0,                  //0x1b
    KEY_NUM_ENTER,      //0x1c
    KEY_RCTRL,          //0x1d
    0,                  //0x1e
    0,                  //0x1f
    KEY_VOLUMN_MUTE,    //0x20
    0,                  //0x21
    KEY_MEDIA_PLAY,     //0x22
    0,                  //0x23
    KEY_MEDIA_STOP,     //0x24
    0,                  //0x25
    0,                  //0x26
    0,                  //0x27
    0,                  //0x28
    0,                  //0x29
    0,                  //0x2a
    0,                  //0x2b
    0,                  //0x2c
    0,                  //0x2d
    KEY_VOLUMN_DOWN,    //0x2e
    0,                  //0x2f
    KEY_VOLUMN_UP,      //0x30
    0,                  //0x31
    0,                  //0x32
    0,                  //0x33
    0,                  //0x34
    KEY_NUM_SLASH,      //0x35
    0,                  //0x36
    0,                  //0x37
    KEY_RALT,           //0x38
    0,    //0x39
    0,    //0x3a
    0,    //0x3b
    0,    //0x3c
    0,    //0x3d
    0,    //0x3e
    0,    //0x3f
    0,    //0x40
    0,    //0x41
    0,    //0x42
    0,    //0x43
    0,    //0x44
    0,    //0x45
    0,    //0x46
    KEY_HOME,           //0x47
    0,    //0x48
    KEY_PAGE_UP,        //0x49
    0,    //0x4a
    0,    //0x4b
    0,    //0x4c
    0,    //0x4d
    0,    //0x4e
    KEY_PAGE_DOWN,      //0x4f
    0,    //0x50
    KEY_PAGE_DOWN,      //0x51
    KEY_INSERT,         //0x52
    KEY_DELETE,         //0x53
    0,                  //0x54
    0,                  //0x55
    0,    //0x56
    0,    //0x57
    0,    //0x58
    0,    //0x59
    0,    //0x5a
    KEY_LGUI,           //0x5b
    KEY_RGUI,           //0x5c
    KEY_APPS,           //0x5d
    0,    //0x5e
};