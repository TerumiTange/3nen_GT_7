#pragma once
#include "../Device/Dx.h"

enum KeyCode//DELETEだけDelete
{
	A = KEY_INPUT_A,				   //Aキー
    B = KEY_INPUT_B,				   //Bキー
    C = KEY_INPUT_C,				   //Cキー
    D = KEY_INPUT_D,				   //Dキー
    E = KEY_INPUT_E,				   //Eキー
    F = KEY_INPUT_F,				   //Fキー
    G = KEY_INPUT_G,				   //Gキー
    H = KEY_INPUT_H,				   //Hキー
    I = KEY_INPUT_I,				   //Iキー
    J = KEY_INPUT_J,				   //Jキー
    K = KEY_INPUT_K,				   //Kキー
    L = KEY_INPUT_L,				   //Lキー
    M = KEY_INPUT_M,				   //Mキー
    N = KEY_INPUT_N,				   //Nキー
    O = KEY_INPUT_O,				   //Oキー
    P = KEY_INPUT_P,				   //Pキー
    Q = KEY_INPUT_Q,				   //Qキー
    R = KEY_INPUT_R,				   //Rキー
    S = KEY_INPUT_S,				   //Sキー
    T = KEY_INPUT_T,				   //Tキー
    U = KEY_INPUT_U,				   //Uキー
    V = KEY_INPUT_V,				   //Vキー
    W = KEY_INPUT_W,				   //Wキー
    X = KEY_INPUT_X,				   //Xキー
    Y = KEY_INPUT_Y,				   //Yキー
    Z = KEY_INPUT_Z,				   //Zキー
    BACK = KEY_INPUT_BACK,			   //バックスペースキー
    TAB = KEY_INPUT_TAB,			   //タブキー
    ENTER = KEY_INPUT_RETURN,		   //エンターキー
    LEFTSHIFT = KEY_INPUT_LSHIFT,	   //左シフトキー
    RIGHTSHIFT = KEY_INPUT_RSHIFT,	   //右シフトキー
    LEFTCONTROL = KEY_INPUT_LCONTROL,  //左コントロールキー
    RIGHTCONTROL = KEY_INPUT_RCONTROL, //右コントロールキー
    ESCAPE = KEY_INPUT_ESCAPE,         //エスケープキー
    SPACE = KEY_INPUT_SPACE,		   //スペースキー
    PAGEUP = KEY_INPUT_PGUP,		   //PageUpキー
    PAGEDOWN = KEY_INPUT_PGDN,		   //PageDownキー
    END = KEY_INPUT_END,			   //エンドキー
    HOME = KEY_INPUT_HOME,			   //ホームキー
    LEFTARROW = KEY_INPUT_LEFT,		   //左アローキー
    UPARROW = KEY_INPUT_UP,			   //上アローキー
    RIGHTARROW = KEY_INPUT_RIGHT,	   //右アローキー
    DOWNARROW = KEY_INPUT_DOWN,		   //下アローキー
    INSERT = KEY_INPUT_INSERT,		   //インサートキー
    Delete = KEY_INPUT_DELETE,		   //デリートキー
    MINUS = KEY_INPUT_MINUS,		   //-キー
    YEN = KEY_INPUT_YEN,			   //\キー
    PREVTRACK = KEY_INPUT_PREVTRACK,   //^キー
    PERIOD = KEY_INPUT_PERIOD,		   //.キー
    SLASH = KEY_INPUT_SLASH,		   ///キー
    LEFTALT = KEY_INPUT_LALT,		   //左ALTキー
    RIGHT = KEY_INPUT_RALT,			   //右ALTキー
    SCROLLLOCK = KEY_INPUT_SCROLL,	   //ScrollLockキー
    SEMICOLON = KEY_INPUT_SEMICOLON,   //;キー
    COLON = KEY_INPUT_COLON,		   //:キー
    LEFTBRACKET = KEY_INPUT_LBRACKET,  //[キー
    RIGHTBRACKET = KEY_INPUT_RBRACKET, //]キー
    AT = KEY_INPUT_AT,				   //@キー
    BACKSLASH = KEY_INPUT_BACKSLASH,   //バックスペースキー
    COMMA = KEY_INPUT_COMMA,		   //,キー
    CAPSLOCK = KEY_INPUT_CAPSLOCK,	   //CaspLockキー
    PAUSEBREAK = KEY_INPUT_PAUSE,	   //PauseBreakキー
    TEN0 = KEY_INPUT_NUMPAD0,		   //テンキー0キー
    TEN1 = KEY_INPUT_NUMPAD1,		   //テンキー1キー
    TEN2 = KEY_INPUT_NUMPAD2,		   //テンキー2キー
    TEN3 = KEY_INPUT_NUMPAD3,		   //テンキー3キー
    TEN4 = KEY_INPUT_NUMPAD4,		   //テンキー4キー
    TEN5 = KEY_INPUT_NUMPAD5,		   //テンキー5キー
    TEN6 = KEY_INPUT_NUMPAD6,		   //テンキー6キー
    TEN7 = KEY_INPUT_NUMPAD7,		   //テンキー7キー
    TEN8 = KEY_INPUT_NUMPAD8,		   //テンキー8キー
    TEN9 = KEY_INPUT_NUMPAD9,		   //テンキー9キー
    TENMULTIPLY = KEY_INPUT_MULTIPLY,  //テンキー*キー
    TENADD = KEY_INPUT_ADD,			   //テンキー+キー
    TENSUBTRACT = KEY_INPUT_SUBTRACT,  //テンキー-キー
    TENDECIMAL = KEY_INPUT_DECIMAL,	   //テンキー.キー
    TENDIVIDE = KEY_INPUT_DIVIDE,	   //テンキー/キー
    TENENTER = KEY_INPUT_NUMPADENTER,  //テンキーエンターキー
    F1 = KEY_INPUT_F1,				   //F1キー
    F2 = KEY_INPUT_F2,				   //F2キー
    F3 = KEY_INPUT_F3,				   //F3キー
    F4 = KEY_INPUT_F4,				   //F4キー
    F5 = KEY_INPUT_F5,				   //F5キー
    F6 = KEY_INPUT_F6,				   //F6キー
    F7 = KEY_INPUT_F7,				   //F7キー
    F8 = KEY_INPUT_F8,				   //F8キー
    F9 = KEY_INPUT_F9,				   //F9キー
    F10 = KEY_INPUT_F10,			   //F10キー
    F11 = KEY_INPUT_F11,			   //F11キー
    F12 = KEY_INPUT_F12,			   //F12キー
    ALPHA0 = KEY_INPUT_0,			   //0キー
    ALPHA1 = KEY_INPUT_1,			   //1キー
    ALPHA2 = KEY_INPUT_2,			   //2キー
    ALPHA3 = KEY_INPUT_3,			   //3キー
    ALPHA4 = KEY_INPUT_4,			   //4キー
    ALPHA5 = KEY_INPUT_5,			   //5キー
    ALPHA6 = KEY_INPUT_6,			   //6キー
    ALPHA7 = KEY_INPUT_7,			   //7キー
    ALPHA8 = KEY_INPUT_8,			   //8キー
    ALPHA9 = KEY_INPUT_9,			   //9キー
    
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
	int mCurrentKey;//現在押されているキー
	int mPreviousKey;//1フレーム前のキー
};