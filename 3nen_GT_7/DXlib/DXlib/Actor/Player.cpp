#include "Player.h"

Player::Player(const char* tag):
	Actor(tag),
	pos(&Vector2(0,0)),
	filename("Player.png"),
	renderer(*new Renderer()),
	input(new Input()),
	fall(true)
{
	Actor::SetPos(*pos);
	Actor::SetSize(*new Vector2(64, 64));
}

Player::Player(const Vector2& position, const char* tag):
	Actor(tag),
	pos(new Vector2(0,0)),
    filename(tag),
	renderer(*new Renderer()),
	input(new Input()),
	fall(true)
{
	pos->x = position.x;
	pos->y = position.y;
	Actor::SetPos(*pos);
	Actor::SetSize(*new Vector2(64, 64));
}

Player::~Player() = default;

void Player::Init()
{
	Width = 64;
	Height = 64;
	input->Init();

}

void Player::Update()
{
	if (fall)//�d��
	{
		pos->y += 1;
	}
	if (input->GetKey(A))
	{
		pos->x -= 10;
	}
	else if(input->GetKey(D))
	{
		pos->x += 10;
	}

	if (input->GetKey(W))
	{
		pos->y -= 10;
	}
	else if(input->GetKey(S))
	{
		pos->y += 10;
	}
	Hit();
}

void Player::Draw()
{
	//renderer.Draw(filename, *pos);
	//test�p
	int a;
	a = LoadGraph("./Assets/Texture/Player.png");
	DrawGraph(pos->x, pos->y, a, TRUE);
	DeleteGraph(a);
}

void Player::SetPosition(const Vector2& position)
{
	*pos = position;
}

Vector2 & Player::GetPosition()
{
	return *pos;
}

void Player::Hit()
{
}

