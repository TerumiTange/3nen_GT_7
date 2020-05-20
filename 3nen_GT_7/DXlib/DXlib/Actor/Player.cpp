#include "Player.h"
#include "../Device/WindowSize.h"
#include "../Map/Map.h"
#include "ActorManager.h"
#include <algorithm>
#define NOMINMAX
#define max(a,b)            (((a) > (b)) ? (a) : (b))


Player::Player(const Vector2& position, const char* tag) :
	Actor(tag),
	mCollider(new ColliderComponent(this)),
	mMaxHp(4),										  //最大体力
	mHp(4),											  //現在の体力
	mInvincibleTime(4),								  //無敵時間
	mGoal(false),									  //ゴールしたかどうか
	mPos(new Vector2(0, 0)),							  //現在の位置
	mVelocity(new Vector2(0, 0)),					  //移動量
	maxSpeed(7),									  //最大スピード
	mAcceleration(0.5),								  //加速度
	mSize(new Vector2(32, 32)), 						  //自分の大きさ
    mFilename(tag),									  //画像名
	mRenderer(new Renderer(tag)),					  //描画関数
	mStaticElectricity(new Renderer("ThunderEffect")),//静電気の画像
	mHeart(new Renderer("Metal")),					  //現在HPを表示する
	mInput(new Input()),							  //キー入力関数
	mCountTimer(new CountDownTimer()),				  //無敵時間更新カウントダウンタイマー
	mFall(true),									  //落ちているかどうか
	mGravity(16),									  //重力のスピード
	mMovingFastGravity(8),							  //高速移動中の重力
	mMovingFast(false),								  //高速移動しているかどうか
	mMovingFastCount(4),							  //高速移動できる回数
	mMovingFastMaxCount(4),							  //最大高速移動の回数
	mMovingFastTime(0.5f),//0.5f					  //高速移動が回復するまでの時間
	mMovingFastTimer(new CountDownTimer()),			  //高速移動回復用カウントダウンタイマー
	mMovingFastAmount(35),							  //高速移動の移動量
	mMovingFastDifferenceX(0),						  //高速移動後の位置の差分X
	mMovingFastDifferenceY(0),						  //高速移動後の位置の差分Y
	mNowMovingFastTimer(new CountDownTimer()),        //高速移動状態のタイマー
	mNowMovingFastTime(0.2f),						  //高速移動状態の時間
	mNowMovingFast(false),							  //高速移動した瞬間
	mFallTimer(new CountDownTimer()),				  //重力軽減の時間タイマー(IsTime()がfalseなら軽減中)
	mFallTime(0.2f),								  //重力軽減の時間
	mNumber(new Renderer("Number")),
	sound(new Sound()),
	mContent(new Renderer("content")),
	mFrame(new Renderer("frame"))
{
	mPos->x = position.x;
	mPos->y = position.y;
	Actor::SetPos(*mPos);   //アクターにセット
	Actor::SetSize(*mSize);	//アクターにセット
	mInput->Init();
	sound->Init();
	sound->Load("./Assets/Sound/damage.wav");//ダメージ
	sound->Load("./Assets/Sound/pdeth.wav");//死亡
	sound->Load("./Assets/Sound/movingfast.wav");//高速移動
	sound->Load("./Assets/Sound/crash.wav");//壁との衝突
}

Player::~Player() = default;

void Player::End()//メモリの開放
{
	delete(mPos);
	delete(mVelocity);
	delete(mSize);
	delete(mRenderer);
	delete(mStaticElectricity);
	delete(mHeart);
	delete(mInput);
	delete(mCountTimer);

	delete(mMovingFastTimer);
	delete(mNowMovingFastTimer);
	delete(mNumber);
	delete(mFallTimer);
	delete(sound);
	delete(mContent);
	delete(mFrame);
}

void Player::Update()
{
	mElectricTimer->Update();//敵の麻痺用

	if (mMovingFastCount > mMovingFastMaxCount)//最大回数をオーバーしたら
	{
		mMovingFastCount = mMovingFastMaxCount;//最大回数にする
	}
	//clsDx();
	//デバッグ用
	//printfDx("体力%d", mHp);
	//printfDx("無敵時間%.001f", mCountTimer->Now());
	//printfDx("瞬間移動できる回数%d", mMovingFastCount);
	//printfDx("瞬間移動できるようになるまでの時間%.01f", mMovingFastTimer->Now());

	if (mHp <= 0)return;//体力がなくなったら操作しないようにする

	

	mInput->JoyUpdate();//ジョイパッド更新
	mCountTimer->Update();//無敵時間更新

	if (!mMovingFast)//高速移動中でなければ
	{
		mMovingFastTimer->Update();//高速移動回復時間更新
	}

	if ((mMovingFastCount <= 0) && (mMovingFastTimer->IsTime()))//高速移動回数が無く、高速移動回復時間が過ぎたら
	{
		mFall = true;
		//if (mMovingFast)return;
		//mMovingFastCount = 1;//高速移動回数を1にする
	}
	
	if (mNowMovingFastTimer->IsTime())//高速移動した瞬間の処理が終了したら
	{
		mMovingFast = false;
		mFall = true;
		mFallTimer->Update();
	}

	Actor::SetPos(*mPos);//現在の位置座標をアクターにセットする
	old_x = mPos->x;//移動前に現在の座標Xを更新
	old_y = mPos->y;//移動前に現在の座標Yを更新
	
	mNowMovingFastTimer->Update();//高速移動した瞬間の処理を更新
	

	if (mInput->GetKeyDown(SPACE) || mInput->PadDown(Joy_A))//スペースまたはコントローラーのAを押したら
	{
		MovingFast();//瞬間移動
	}

	if (mInput->GetKeyDown(H))//デバッグ用
	{
		Recovery();//体力回復
	}

	Move();//移動処理
	Fall();//重力計算
	Movement();//移動計算
}
void Player::Fall()//重力
{
	if (mMovingFast || !mFallTimer->IsTime())//高速移動中または重力軽減中なら
	{
		mPos->y += mMovingFastGravity;
		return;
	}
	if (!mFall)return;//地面に着地していなければリターン
	mPos->y += mGravity;
}

void Player::Move()
{
	if (mMovingFast)return;//瞬間移動中ならリターン
	if ((mInput->Horizontal() < 0) || (mInput->GetKey(A) || mInput->GetKey(LEFTARROW)))//左移動
	{
		mVelocity->x = min(mVelocity->x - mAcceleration, -maxSpeed);
	}
	else if ((mInput->Horizontal() > 0) || (mInput->GetKey(D) || mInput->GetKey(RIGHTARROW)))//右移動
	{
		mVelocity->x = max(mVelocity->x + mAcceleration, maxSpeed);
	}
}

void Player::Movement()//移動処理
{
	mPos->y += mVelocity->y;//移動処理Y
	mPos->x += mVelocity->x;//移動処理X


	if (!mNowMovingFast)
	{
		mVelocity->y *= 0.7f;//ここで慣性性が出る
		mVelocity->x *= 0.9f;//ここで慣性性が出る
	}
	
	if (mNowMovingFast&&mNowMovingFastTimer->IsTime())//高速移動なら慣性0
	{
		mVelocity->x = 0;
		mVelocity->y = 0;

		//mMovingFastDifference->x -= mPos->x;
		//mMovingFastDifference->y -= mPos->y;
		mMovingFastDifferenceX -= mPos->x;//高速移動前との差分を計算
		mMovingFastDifferenceY -= mPos->y;//高速移動前との差分を計算
		mNowMovingFast = false;
		mNowMovingFastTimer->SetTime(mFallTime);//重力発生まで軽減
	}
	//画面外に出た場合位置修正
	if (mPos->x < 32)
	{
		mPos->x = 32;
	}
	if (mPos->x > Map::width * 32 - 32)
	{
		mPos->x = Map::width * 32 - 32;
	}
	if (mPos->y < 32)
	{
		mPos->y = 32;
	}
	if (mPos->y > Map::height * 32 - 32)
	{
		mPos->y = Map::height * 32 - 64;
	}
	
}

void Player::MovingFast()//瞬間移動
{
	if (mMovingFastCount <= 0)return;//0以下ならリターン
	if (mMovingFast)return;//瞬間移動中ならリターン
	if (!mNowMovingFastTimer->IsTime())return;//一定時間たつまで無効
	sound->PlaySE("./Assets/Sound/movingfast.wav");
	mMovingFast = true;
	mFall = false;
	mNowMovingFast = true;
	mMovingFastCount--;
	//mMovingFastDifference = mPos;
	mMovingFastDifferenceX = mPos->x;//高速移動前の座標X
	mMovingFastDifferenceY = mPos->y;//高速移動前の座標Y

	mVelocity->x = mInput->Horizontal()*mMovingFastAmount;//コントローラでの移動
	mVelocity->y = mInput->Vertical()*mMovingFastAmount;  //コントローラでの移動

	//キーボードでの移動
	if (mInput->GetKeyDown(LEFTARROW) || mInput->GetKeyDown(A))
	{
		mVelocity->x = -mMovingFastAmount;
	}
	else if (mInput->GetKeyDown(D) || mInput->GetKeyDown(RIGHTARROW))
	{
		mVelocity->x = mMovingFastAmount;
	}

	if (mInput->GetKeyDown(W) || mInput->GetKeyDown(UPARROW))
	{
		mVelocity->y = -mMovingFastAmount;
	}
	else if (mInput->GetKeyDown(S) || mInput->GetKeyDown(DOWNARROW))
	{
		mVelocity->y = mMovingFastAmount;
	}


	if (mVelocity->x == 0 && mVelocity->y == 0)//もし入力がなければ右に移動
	{
		mVelocity->x = mMovingFastAmount;
	}

	mMovingFastTimer->SetTime(mMovingFastTime);//回数を回復させるまでの時間
	mNowMovingFastTimer->SetTime(mNowMovingFastTime);//処理に必要な時間
}

void Player::Damage()//ダメージ
{
	if (mMovingFast)return;//瞬間移動中なら
	if (mCountTimer->IsTime())//無敵時間でないなら
	{
		mHp--;//1ダメージ受ける
		sound->PlaySE("./Assets/Sound/damage.wav");
		mCountTimer->SetTime(mInvincibleTime);//無敵時間をセット
	}

	if (mHp <= 0)//体力がなくなったら
	{
		sound->PlaySEF("./Assets/Sound/pdeth.wav");
		Destroy(this, 3.f);//3秒後に死亡
	}
}

void Player::Recovery()//体力回復
{
	mHp++;
	if (mMaxHp < mHp)//最大体力を超えたら
	{
		mHp = mMaxHp;//最大体力にする
	}
}


void Player::Draw()//描画
{
	mRenderer->Draw(*mPos);
	//mRenderer->DrawE(*mPos, 64);
	if (mNowMovingFast)
	{
		mStaticElectricity->Draw(mPos->x - 16, mPos->y + 32);
	}
	for (size_t i = 0; i < mHp; ++i)
	{
		mHeart->Drawb(10 + i * 36, 36);
	}
    //DrawString(0, 0, "", mMovingFastCount);
	//DrawFormatString(10, 0, GetColor(255, 0, 0), "瞬間移動できる回数%d", mMovingFastCount);
	//SetFontSize(32);
	//DrawString(0, 0, "瞬間移動できる回数:", GetColor(255, 0, 0));
	//mNumber->DrawIntegerNumber(Vector2(350, 0), mMovingFastCount);

	for (int i = 0; i < mMovingFastMaxCount; ++i)
	{
		mFrame->Drawb(i * 32, 0);
	}
	for (int i = 0; i < mMovingFastCount; ++i)
	{
		mContent->Drawb(i * 32, 0);
	}
}

void Player::SetPosition(const Vector2& position)
{
	*mPos = position;
}

Vector2& Player::GetPosition()
{
	return *mPos;
}

void Player::Hit()
{
	for (auto && hit : mCollider->onCollisionEnter())
	{
		auto cPosX = hit->getOwner()->Position()->x;
		auto cPosY = hit->getOwner()->Position()->y;
		auto cSizeX = hit->getOwner()->Size()->x;
		auto cSizeY = hit->getOwner()->Size()->y;
		if (hit->getOwner()->Tag() == "Wall")
		{
			mFall = false;
			mMovingFastCount = 4;
			if (mPos->y + mSize->y >= cPosY || old_y + mSize->y <= cPosY)//自分の下に当たったとき
			{
				mPos->y = cPosY - cSizeY;
				mFall = false;
			}
			else if (old_y < cPosY + cSizeY)//自分の上に当たったとき
			{
				sound->PlaySEF("./Assets/Sound/crash.wav");
				mPos->y = cPosY + cSizeY;
				if (mVelocity->y < 0)
				{
					mVelocity->y = 0;
				}
			}
			else if (old_x >= cPosX + cSizeX)//自分の左に当たったとき
			{
				sound->PlaySEF("./Assets/Sound/crash.wav");
				mPos->x = cPosX + cSizeX + 1;
				if (mVelocity->x < 0)
				{
					mVelocity->x = 0;
				}
		
			}
			else if (old_x + mSize->x <= cPosX)//自分の右に当たったとき
			{
				sound->PlaySEF("./Assets/Sound/crash.wav");
				mPos->x = cPosX - mSize->x - 1;
				if (mVelocity->x > 0)
				{
					mVelocity->x = 0;
				}
			}
		
		}

		if (hit->getOwner()->Tag() == "Goa")
		{
			mGoal = true;
		}

		if (hit->getOwner()->Tag() == "FlyEnemy")
		{
			if (mMovingFast)//高速移動状態ならば
			{
				if (hit->getOwner()->GetElectricShock())Destroy(hit->getOwner());
				hit->getOwner()->SetElectricShock(true);
				mMovingFastCount++;
			}
			if (mNowMovingFast)//高速移動状態初期処理状態ならば
			{
				hit->getOwner()->SetElectricShock(true);
				mMovingFastCount = 4;
			}

			if (!hit->getOwner()->GetElectricShock())
			{
				Damage();
			}
		}
	}
	//if (mCollider->onCollisionEnter().empty())//なぜか空のときがあるから
	//{
	
		for (auto && a : GetActorManager()->GetActors())
		{
			if (a->Tag() == "Wall")
			{
				mFall = false;
				auto cPosX = a->Position()->x;
				auto cPosY = a->Position()->y;
				auto cSizeX = a->Size()->x;
				auto cSizeY = a->Size()->y;
				if (CheckHit(mPos->x, mPos->y, mSize->x, mSize->y, cPosX, cPosY, cSizeX, cSizeY))
				{
					if (old_y + mSize->y <= cPosY)
					{
						mPos->y = cPosY - mSize->y;
						
						mMovingFastCount = 4;
						if (mVelocity->y > 0)
						{
							mVelocity->y = 0;
						}
					}
					else if (old_y < cPosY + cSizeY)//自分の上に当たったとき
					{
						sound->PlaySEF("./Assets/Sound/crash.wav");
						mPos->y = cPosY + cSizeY;
						if (mVelocity->y < 0)
						{
							mVelocity->y = 0;
						}
					}
					else if (mPos->x >= cPosX + cSizeX)//自分の左に当たったとき
					{
						sound->PlaySEF("./Assets/Sound/crash.wav");
						mPos->x = cPosX + cSizeX + 1;
						if (mVelocity->x < 0)
						{
							mVelocity->x = 0;
						}
					}
					else if (mPos->x + mSize->x <= cPosX)//自分の右に当たったとき
					{
						sound->PlaySEF("./Assets/Sound/crash.wav");
						mPos->x = cPosX - mSize->x - 1;
						if (mVelocity->x > 0)
						{
							mVelocity->x = 0;
						}
					}

				}
				
			}
			
		}
	//}
}

bool Player::RGoal()
{
	return mGoal;
}

bool Player::GetMovingFast()
{
	return mMovingFast;
}


