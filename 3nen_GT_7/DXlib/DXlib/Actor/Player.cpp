#include "Player.h"

Player::Player(const char* tag):
	Actor(tag),
	pos(&Vector2(0,0)),
	filename("Player.png"),
	renderer(*new Renderer()),
	input(new Input()),
	mCSVReader(nullptr),
	mCSV(0),
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
	mCSVReader(nullptr),
	mCSV(0),
	fall(true)
{
	pos->x = position.x;
	pos->y = position.y;
	Actor::SetPos(*pos);
	Actor::SetSize(*new Vector2(64, 64));
}

Player::~Player() = default;

void Player::Init(const char* name)
{
	Width = 64;
	Height = 64;
	input->Init();
	mCSV.clear();
	mCSVReader = new CSVReader(name);
	mCSV = mCSVReader->load(name);
	mapWidth = mCSVReader->getWidth();
	mapHeight = mCSVReader->getHeight();
}

void Player::Update()
{
	if (fall)//d—Í
	{
		pos->y += 1;
	}
	fall = true;
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
	//test—p
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
	HitMap();
}

bool Player::CheckHit(int x, int y, int width, int height)
{
	int L1 = pos->x;
	int R1 = pos->x + Width;
	int L2 = x;
	int R2 = x + width;
	int U1 = pos->y;
	int D1 = pos->y + Height;
	int U2 = y;
	int D2 = y + height;
	if (R1 < L2)return false;
	if (R2 < L1)return false;
	if (D1 < U2)return false;
	if (D2 < U1)return false;
	return true;
}

void Player::HitMap()
{
	for (int j = 0; j < mapHeight; ++j)
	{
		for (int i = 0; i < mapWidth; ++i)
		{
			int no = mCSV[i + j * mapWidth];
			if (no == 1)//wall‚Æ‚Ì“–‚½‚è”»’è
			{
				if (CheckHit(i * 32, j * 32, 32, 32))//‚ ‚½‚Á‚Ä‚¢‚½‚È‚ç
				{
					fall = false;
				}
			}
		}
	}
}

