#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::Init()
{

}

void Input::Update()
{
}

bool Input::GetKey(KeyCode key)
{
	return CheckHitKey(key);
}

bool Input::GetKeyUp(KeyCode key)
{
	return !CheckHitKey(key);
}

bool Input::GetKeyDown(KeyCode key)
{
	return CheckHitKey(key);
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
