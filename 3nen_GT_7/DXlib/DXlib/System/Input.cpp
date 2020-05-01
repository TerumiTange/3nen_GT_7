#include "Input.h"

Input::Input():
	mCurrentKey(0),
	mPreviousKey(0),
	mFlame(0)
{
}

Input::~Input()
{
}

void Input::Init()
{
	mCurrentKey = KeyCode::None;
	mFlame = 0;
}

void Input::JoyInit()
{
	//mPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

void Input::Update()
{
	if (mFlame >= 2)
	{
		Init();
	}
	mPreviousKey = mCurrentKey;
	mFlame++;
}

void Input::JoyUpdate()
{
	//GetJoypadXInputState(DX_INPUT_PAD1, &mPad);
	mPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	GetJoypadAnalogInput(&AX, &AY, DX_INPUT_PAD1);//左スティック
	//GetJoypadAnalogInputRight(&ARX, &ARY, DX_INPUT_PAD1);//右スティック
}

bool Input::GetKey(KeyCode key)
{
	mFlame = 0;
	mCurrentKey = CheckHitKey(key);
	return CheckHitKey(key);
}

bool Input::GetKeyUp(KeyCode key)
{
	return !CheckHitKey(key);
}

bool Input::GetKeyDown(KeyCode key)
{
	mFlame = 0;
	mCurrentKey = CheckHitKey(key);
	return mCurrentKey && !mPreviousKey;
}

bool Input::Pad(JoyCode joy)
{
	return (mPad & joy);
}

bool Input::PadUp(JoyCode joy)
{
	return !(mPad & joy);
}

bool Input::PadDown(JoyCode joy)
{
	return (mPad & joy);
}

float Input::Horizontal()
{
	return AX / 1000.0f;//0.0～1.0で返す
}

float Input::Vertical()
{
	return AY / 1000.f;// 1000.0f;//0.0～1.0で返す
}

