#include "Player.h"

Renderer renderer;

Player::Player(const char* tag):
	pos(&Vector2(0,0)),
	filename(tag),
	mCollider(new Collider(tag))
{

}

Player::Player(const Vector2 & position, const char* tag):
	pos(&Vector2(0,0)),
    filename(tag)
{
	*pos = position;
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	mCollider->Update();
}

void Player::Draw()
{
	renderer.Draw(filename, *pos);
}

void Player::SetPosition(const Vector2 & position)
{
	*pos = position;
}

Vector2 & Player::GetPosition()
{
	return *pos;
}

