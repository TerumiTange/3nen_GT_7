#pragma once
#include "../Device/Dx.h"

enum KeyCode//DELETE����Delete
{
	A = KEY_INPUT_A,				   //A�L�[
    B = KEY_INPUT_B,				   //B�L�[
    C = KEY_INPUT_C,				   //C�L�[
    D = KEY_INPUT_D,				   //D�L�[
    E = KEY_INPUT_E,				   //E�L�[
    F = KEY_INPUT_F,				   //F�L�[
    G = KEY_INPUT_G,				   //G�L�[
    H = KEY_INPUT_H,				   //H�L�[
    I = KEY_INPUT_I,				   //I�L�[
    J = KEY_INPUT_J,				   //J�L�[
    K = KEY_INPUT_K,				   //K�L�[
    L = KEY_INPUT_L,				   //L�L�[
    M = KEY_INPUT_M,				   //M�L�[
    N = KEY_INPUT_N,				   //N�L�[
    O = KEY_INPUT_O,				   //O�L�[
    P = KEY_INPUT_P,				   //P�L�[
    Q = KEY_INPUT_Q,				   //Q�L�[
    R = KEY_INPUT_R,				   //R�L�[
    S = KEY_INPUT_S,				   //S�L�[
    T = KEY_INPUT_T,				   //T�L�[
    U = KEY_INPUT_U,				   //U�L�[
    V = KEY_INPUT_V,				   //V�L�[
    W = KEY_INPUT_W,				   //W�L�[
    X = KEY_INPUT_X,				   //X�L�[
    Y = KEY_INPUT_Y,				   //Y�L�[
    Z = KEY_INPUT_Z,				   //Z�L�[
    BACK = KEY_INPUT_BACK,			   //�o�b�N�X�y�[�X�L�[
    TAB = KEY_INPUT_TAB,			   //�^�u�L�[
    ENTER = KEY_INPUT_RETURN,		   //�G���^�[�L�[
    LEFTSHIFT = KEY_INPUT_LSHIFT,	   //���V�t�g�L�[
    RIGHTSHIFT = KEY_INPUT_RSHIFT,	   //�E�V�t�g�L�[
    LEFTCONTROL = KEY_INPUT_LCONTROL,  //���R���g���[���L�[
    RIGHTCONTROL = KEY_INPUT_RCONTROL, //�E�R���g���[���L�[
    ESCAPE = KEY_INPUT_ESCAPE,         //�G�X�P�[�v�L�[
    SPACE = KEY_INPUT_SPACE,		   //�X�y�[�X�L�[
    PAGEUP = KEY_INPUT_PGUP,		   //PageUp�L�[
    PAGEDOWN = KEY_INPUT_PGDN,		   //PageDown�L�[
    END = KEY_INPUT_END,			   //�G���h�L�[
    HOME = KEY_INPUT_HOME,			   //�z�[���L�[
    LEFTARROW = KEY_INPUT_LEFT,		   //���A���[�L�[
    UPARROW = KEY_INPUT_UP,			   //��A���[�L�[
    RIGHTARROW = KEY_INPUT_RIGHT,	   //�E�A���[�L�[
    DOWNARROW = KEY_INPUT_DOWN,		   //���A���[�L�[
    INSERT = KEY_INPUT_INSERT,		   //�C���T�[�g�L�[
    Delete = KEY_INPUT_DELETE,		   //�f���[�g�L�[
    MINUS = KEY_INPUT_MINUS,		   //-�L�[
    YEN = KEY_INPUT_YEN,			   //\�L�[
    PREVTRACK = KEY_INPUT_PREVTRACK,   //^�L�[
    PERIOD = KEY_INPUT_PERIOD,		   //.�L�[
    SLASH = KEY_INPUT_SLASH,		   ///�L�[
    LEFTALT = KEY_INPUT_LALT,		   //��ALT�L�[
    RIGHT = KEY_INPUT_RALT,			   //�EALT�L�[
    SCROLLLOCK = KEY_INPUT_SCROLL,	   //ScrollLock�L�[
    SEMICOLON = KEY_INPUT_SEMICOLON,   //;�L�[
    COLON = KEY_INPUT_COLON,		   //:�L�[
    LEFTBRACKET = KEY_INPUT_LBRACKET,  //[�L�[
    RIGHTBRACKET = KEY_INPUT_RBRACKET, //]�L�[
    AT = KEY_INPUT_AT,				   //@�L�[
    BACKSLASH = KEY_INPUT_BACKSLASH,   //�o�b�N�X�y�[�X�L�[
    COMMA = KEY_INPUT_COMMA,		   //,�L�[
    CAPSLOCK = KEY_INPUT_CAPSLOCK,	   //CaspLock�L�[
    PAUSEBREAK = KEY_INPUT_PAUSE,	   //PauseBreak�L�[
    TEN0 = KEY_INPUT_NUMPAD0,		   //�e���L�[0�L�[
    TEN1 = KEY_INPUT_NUMPAD1,		   //�e���L�[1�L�[
    TEN2 = KEY_INPUT_NUMPAD2,		   //�e���L�[2�L�[
    TEN3 = KEY_INPUT_NUMPAD3,		   //�e���L�[3�L�[
    TEN4 = KEY_INPUT_NUMPAD4,		   //�e���L�[4�L�[
    TEN5 = KEY_INPUT_NUMPAD5,		   //�e���L�[5�L�[
    TEN6 = KEY_INPUT_NUMPAD6,		   //�e���L�[6�L�[
    TEN7 = KEY_INPUT_NUMPAD7,		   //�e���L�[7�L�[
    TEN8 = KEY_INPUT_NUMPAD8,		   //�e���L�[8�L�[
    TEN9 = KEY_INPUT_NUMPAD9,		   //�e���L�[9�L�[
    TENMULTIPLY = KEY_INPUT_MULTIPLY,  //�e���L�[*�L�[
    TENADD = KEY_INPUT_ADD,			   //�e���L�[+�L�[
    TENSUBTRACT = KEY_INPUT_SUBTRACT,  //�e���L�[-�L�[
    TENDECIMAL = KEY_INPUT_DECIMAL,	   //�e���L�[.�L�[
    TENDIVIDE = KEY_INPUT_DIVIDE,	   //�e���L�[/�L�[
    TENENTER = KEY_INPUT_NUMPADENTER,  //�e���L�[�G���^�[�L�[
    F1 = KEY_INPUT_F1,				   //F1�L�[
    F2 = KEY_INPUT_F2,				   //F2�L�[
    F3 = KEY_INPUT_F3,				   //F3�L�[
    F4 = KEY_INPUT_F4,				   //F4�L�[
    F5 = KEY_INPUT_F5,				   //F5�L�[
    F6 = KEY_INPUT_F6,				   //F6�L�[
    F7 = KEY_INPUT_F7,				   //F7�L�[
    F8 = KEY_INPUT_F8,				   //F8�L�[
    F9 = KEY_INPUT_F9,				   //F9�L�[
    F10 = KEY_INPUT_F10,			   //F10�L�[
    F11 = KEY_INPUT_F11,			   //F11�L�[
    F12 = KEY_INPUT_F12,			   //F12�L�[
    ALPHA0 = KEY_INPUT_0,			   //0�L�[
    ALPHA1 = KEY_INPUT_1,			   //1�L�[
    ALPHA2 = KEY_INPUT_2,			   //2�L�[
    ALPHA3 = KEY_INPUT_3,			   //3�L�[
    ALPHA4 = KEY_INPUT_4,			   //4�L�[
    ALPHA5 = KEY_INPUT_5,			   //5�L�[
    ALPHA6 = KEY_INPUT_6,			   //6�L�[
    ALPHA7 = KEY_INPUT_7,			   //7�L�[
    ALPHA8 = KEY_INPUT_8,			   //8�L�[
    ALPHA9 = KEY_INPUT_9,			   //9�L�[
    
    None = 512                         
};

enum JoyCode
{
	
};

class Input
{
public:
	Input();
	~Input();
	void Init();
	void Update();
	bool GetKey(KeyCode key);
	bool GetKeyUp(KeyCode key);
	bool GetKeyDown(KeyCode key);
	bool Pad();
	bool PadUp();
	bool PadDown();

private:
	int mCurrentKey;//���݉�����Ă���L�[
	int mPreviousKey;//1�t���[���O�̃L�[
};