#include "Input.h"

Input::Input():
	mCurrentKey(0),
	mPreviousKey(0)
{
}

Input::~Input()
{
}

void Input::Init()
{
	mCurrentKey = KeyCode::None;
}

void Input::Update()
{
	mPreviousKey = mCurrentKey;
}

bool Input::GetKey(KeyCode key)
{
	mCurrentKey = CheckHitKey(key);
	return CheckHitKey(key);
}

bool Input::GetKeyUp(KeyCode key)
{
	return !CheckHitKey(key);
}

bool Input::GetKeyDown(KeyCode key)
{
	mCurrentKey = CheckHitKey(key);
	return mCurrentKey && !mPreviousKey;
}

bool Input::Pad()
{
	return 0;
}

bool Input::PadUp()
{
	return 0;
}

bool Input::PadDown()
{
	return 0;
}
