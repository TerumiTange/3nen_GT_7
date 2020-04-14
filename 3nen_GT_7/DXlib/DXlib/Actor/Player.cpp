
#include "Player.h"

Player::Player(const char* tag):
	Actor(tag),
	pos(&Vector2(0,0)),
	filename("Player.png"),
	renderer(*new Renderer()),
	input(new Input()),
	mCollider(new Collider(this))
{
	Actor::SetPos(*pos);
}

Player::Player(const Vector2& position, const char* tag):
	Actor(tag),
	pos(new Vector2(0,0)),
    filename(tag),
	renderer(*new Renderer()),
	input(new Input()),
	mCollider(new Collider(this))
{
	pos->x = position.x;
	pos->y = position.y;
	Actor::SetPos(*pos);
}

Player::~Player() = default;

void Player::Init()
{
	input->Init();
}

void Player::Update()
{
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
	for (auto&& c : mCollider->onCollisionEnter())
	{
		if (c->GetOwner()->Tag() == "")
		{
			//����
		}
	}
}

