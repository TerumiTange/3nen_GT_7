#include "Player.h"

Player::Player(const char* tag):
	Actor(tag),
	mPos(&Vector2(0,0)),
	mFilename("Player.png"),
	mRenderer(new Renderer()),
	mInput(new Input()),
	mCSVReader(nullptr),
	mCSV(0),
	mFall(true)
{
	Actor::SetPos(*mPos);
	Actor::SetSize(*new Vector2(64, 64));
}

Player::Player(const Vector2& position, const char* tag):
	Actor(tag),
	mPos(new Vector2(0,0)),
    mFilename(tag),
	mRenderer(new Renderer()),
	mInput(new Input()),
	mCSVReader(nullptr),
	mCSV(0),
	mFall(true)
{
	mPos->x = position.x;
	mPos->y = position.y;
	Actor::SetPos(*mPos);
	Actor::SetSize(*new Vector2(64, 64));
}

Player::~Player() = default;

void Player::Init(const char* name)
{
	mWidth = 64;
	mHeight = 64;
	mInput->Init();
	mCSV.clear();
	mCSVReader = new CSVReader(name);
	mCSV = mCSVReader->load(name);
	mapWidth = mCSVReader->getWidth();
	mapHeight = mCSVReader->getHeight();
}

void Player::Update()
{
	if (mFall)//d—Í
	{
		mPos->y += 20;
	}
	mFall = true;
	old_x = mPos->x;
	old_y = mPos->y;
	if (mInput->GetKey(A)||mInput->GetKey(LEFTARROW))
	{
		mPos->x -= 10;
	}
	else if(mInput->GetKey(D) || mInput->GetKey(RIGHTARROW))
	{
		mPos->x += 10;
	}

	Hit();
}

void Player::Draw()
{
	//renderer.Draw(filename, *pos);
	//test—p
	int a;
	a = LoadGraph("./Assets/Texture/Player.png");
	DrawGraph(mPos->x, mPos->y, a, TRUE);
	DeleteGraph(a);
}

void Player::SetPosition(const Vector2& position)
{
	*mPos = position;
}

Vector2 & Player::GetPosition()
{
	return *mPos;
}

void Player::Hit()
{
	HitMap();
}

bool Player::CheckHit(int x, int y, int width, int height)
{
	int L1 = mPos->x;
	int R1 = mPos->x + mWidth;
	int L2 = x;
	int R2 = x + width;
	int U1 = mPos->y;
	int D1 = mPos->y + mHeight;
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
					mPos->x = old_x;
					//mPos->y = old_y;
				}
			}
			if (no == 2)//Floor‚Æ‚Ì“–‚½‚è”»’è
			{
				if (CheckHit(i * 32, j * 32, 32, 32))
				{
					mFall = false;
				}
			}
		}
	}
}

