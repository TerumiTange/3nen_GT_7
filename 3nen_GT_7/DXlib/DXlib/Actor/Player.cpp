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
	mMaxHp(5),										  //最大体力
	mHp(5),											  //現在の体力
	mInvincibleTime(3),								  //無敵時間
	mPos(new Vector2(0, 0)),							  //現在の位置
	mVelocity(new Vector2(0, 0)),					  //移動量
	maxSpeed(7),									  //最大スピード
	mAcceleration(0.5),								  //加速度
	mSize(new Vector2(32, 32)), 						  //自分の大きさ
	mFilename(tag),									  //画像名
	mRenderer(new Renderer(tag)),					  //描画関数
	mIdolRenderer(new Renderer("PlayerIDL")),
	mStaticElectricity(new Renderer("ThunderEffect")),//静電気の画像
	mHeart(new Renderer("HP")),					  //現在HPを表示する
	mAttackImages(new Renderer("PlayerAttack")),
	mInput(new Input()),							  //キー入力関数
	mCountTimer(new CountDownTimer()),				  //無敵時間更新カウントダウンタイマー
	mFall(true),									  //落ちているかどうか
	mGravity(5),									  //重力のスピード
	mMovingFastGravity(0),							  //高速移動中の重力
	mMovingFast(false),								  //高速移動しているかどうか
	mMovingFastCount(3),							  //高速移動できる回数
	mMovingFastMaxCount(3),							  //最大高速移動の回数ー
	mMovingFastAmount(13),							  //高速移動の移動量
	mNowMovingFastTimer(new CountDownTimer()),        //高速移動状態のタイマー
	mNowMovingFastTime(0.2f),						  //高速移動状態の時間
	mNowMovingFast(false),							  //高速移動した瞬間
	mNumber(new Renderer("Number")),
	sound(new Sound()),
	mContent(new Renderer("content")),
	mFrame(new Renderer("frame")),
	mRight(false),
	mUpTimer(new CountUpTimer()),
	mDamage(new Renderer("Damage")),
	mDamageEf1(new Renderer("DamageEffect01")),
	mDamageEf2(new Renderer("DamageEffect02"))
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
	sound->Load("./Assets/Sound/Landing.wav");//着地音
	mCountTimer->SetTime(0.0f);
	mNowMovingFastTimer->SetTime(0.0f);
}

Player::~Player() = default;

void Player::End()//メモリの開放
{
	sound->DeleteM("./Assets/Sound/damage.wav");
	sound->DeleteM("./Assets/Sound/pdeth.wav");
	sound->DeleteM("./Assets/Sound/movingfast.wav");
	sound->DeleteM("./Assets/Sound/crash.wav");
	sound->DeleteM("./Assets/Sound/Landing.wav");
	delete(mPos);
	delete(mVelocity);
	delete(mSize);
	delete(mRenderer);
	delete(mStaticElectricity);
	delete(mHeart);
	delete(mInput);
	delete(mCountTimer);
	delete(mAttackImages);
	delete(mIdolRenderer);

	delete(mNowMovingFastTimer);
	delete(mNumber);
	delete(sound);
	delete(mContent);
	delete(mFrame);
	delete(mUpTimer);
	delete(mDamage);
	delete(mDamageEf1);
	delete(mDamageEf2);
}

void Player::Update()
{
	mUpTimer->Update();
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

	if (mNowMovingFastTimer->IsTime())//高速移動した瞬間の処理が終了したら
	{
		mMovingFast = false;
		//mFall = true;
	}

	Actor::SetPos(*mPos);//現在の位置座標をアクターにセットする
	old_x = mPos->x;//移動前に現在の座標Xを更新
	old_y = mPos->y;//移動前に現在の座標Yを更新
	mNowMovingFastTimer->Update();//高速移動した瞬間の処理を更新
	

	if (mInput->GetKeyDown(SPACE) || mInput->PadDown(Joy_A))//スペースまたはコントローラーのAを押したら
	{
		MovingFast();//瞬間移動
	}

	//if (mInput->GetKeyDown(H))//デバッグ用
	//{
	//	Recovery();//体力回復
	//}

	Move();//移動処理
	Fall();//重力計算
	Movement();//移動計算
}
void Player::Fall()//重力
{
	if (mMovingFast)//高速移動中なら
	{
		//mPos->y += mMovingFastGravity;//軽減重力
		mVelocity->y += mMovingFastGravity;
		return;
	}
	if (!mFall)return;//地面に着地していなければリターン
	//mPos->y += mGravity;
	mVelocity->y += mGravity;
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
	mRight = (mVelocity->x > 0) ? true : false;
	mVelocity->x = (abs(mVelocity->x) < 15) ? mVelocity->x : ((mVelocity->x < 0) ? -14 : 14);
	mVelocity->y = (abs(mVelocity->y) < 15) ? mVelocity->y : ((mVelocity->y < 0) ? -14 : 14);



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

		mNowMovingFast = false;
	}
	//画面外に出た場合位置修正
	if (mPos->x < 32)
	{
		mPos->x = 32;
	}
	if (mPos->x > Map::width * 32 - 64)
	{
		mPos->x = Map::width * 32 - 64;
	}
	if (mPos->y < 33)
	{
		mPos->y = 33;
	}
	if (mPos->y > Map::height * 32 - 64)
	{
		mPos->y = Map::height * 32 - 64;
	}
	
}

void Player::MovingFast()//瞬間移動
{
	if (mMovingFastCount <= 0)return;//回数が0以下ならリターン
	//if (mMovingFast)return;//瞬間移動中ならリターン
	if (!mNowMovingFastTimer->IsTime())return;//一定時間たつまで無効
	sound->PlaySE("./Assets/Sound/movingfast.wav");
	mMovingFast = true;
	mFall = false;
	mNowMovingFast = true;
	mMovingFastCount--;

	mVelocity->x = mInput->Horizontal()*mMovingFastAmount;//コントローラでの移動
	mVelocity->y = mInput->Vertical()*mMovingFastAmount;  //コントローラでの移動

	/*
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
	*/

	if (mVelocity->x == 0 && mVelocity->y == 0)//もし入力がなければ右に移動
	{
		mVelocity->x = mMovingFastAmount;
	}


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
		SceneManager::score -= 100;//スコアから100点引く
	}

	if (mHp <= 0)//体力がなくなったら
	{
		sound->PlaySEF("./Assets/Sound/pdeth.wav");
		Destroy(this, 1.f);//3秒後に死亡
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
	//mRenderer->Draw(*mPos);
	if (!mCountTimer->IsTime())
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
	}
	if (mMovingFast)
	{
		mAttackImages->Draw(*mPos);
	}
	else
	{
		if (std::abs(mVelocity->x) <= 1)
		{
			int t = fmod(mUpTimer->Now() * 3, 3);//ここの掛けている数字でスピードが変わる

			//アイドルの画像
			mIdolRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), t, *mSize, FALSE);
		}
		else if (mRight)
		{
			//右向きの画像
			int r = fmod(mUpTimer->Now() * 3, 4);
			mRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), r, *mSize, FALSE);
		}
		else
		{
			//左向きの画像
			int l = fmod(mUpTimer->Now() * 3, 4);
			mRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), l, *mSize, TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//アルファ値最大

	//mRenderer->DrawE(*mPos, 64);
	if (mNowMovingFast)
	{
		//mStaticElectricity->Draw(mPos->x - 32, mPos->y);
		mStaticElectricity->DrawAlternating(mPos->x + 8, mPos->y + 5, 3);
	}
	
	//mCountTimer->Now(); mInvincibleTime
	if (mInvincibleTime - mCountTimer->Now() < 0.3f)//ダメージを受けたら
	{
		//DrawString(mPos->x - 10, mPos->y - 32, "ダメージ", GetColor(255, 0, 0));
		SetDrawBright(200, 100, 100);
		mDamage->Draw(mPos->x, mPos->y - 32);
		mDamageEf1->Drawb(0, 0);//外枠
		mDamageEf2->Drawb(0, 0);//画面全体の赤
		SetDrawBright(255, 255, 255);
	}

	
	for (size_t i = 0; i < mHp; ++i)//HP表示
	{
		mHeart->Drawb(10 + i * 32, 32);
	}
    //DrawString(0, 0, "", mMovingFastCount);
	//DrawFormatString(10, 0, GetColor(255, 0, 0), "瞬間移動できる回数%d", mMovingFastCount);
	//SetFontSize(32);
	//DrawString(0, 0, "瞬間移動できる回数:", GetColor(255, 0, 0));
	//mNumber->DrawIntegerNumber(Vector2(350, 0), mMovingFastCount);

	for (int i = 0; i < mMovingFastMaxCount; ++i)//高速移動回数表示
	{
		mFrame->Drawb(10 + i * 32, 0);
	}
	for (int i = 0; i < mMovingFastCount; ++i)
	{
		mContent->Drawb(10 + i * 32, 0);
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
	if (mCollider->onCollisionStay().empty() && mCollider->onCollisionEnter().empty())//何とも当たっていなければ
	{
		mFall = true;
		return;
	}

	for (auto && hit : mCollider->onCollisionStay())//連続で当たっているとき
	{
		if (hit->getOwner()->Tag() == "Wall")
		{
			auto cPosX = hit->getOwner()->Position()->x;
			auto cPosY = hit->getOwner()->Position()->y;
			auto cSizeX = hit->getOwner()->Size()->x;
			auto cSizeY = hit->getOwner()->Size()->y;


			auto sx = cPosX + (cSizeX / 2);//真ん中
			auto sy = cPosY + (cSizeY / 2);//真ん中

			Vector2 dir = Vector2(old_x + (mSize->x / 2), mPos->y + (mSize->y / 2)) - Vector2(sx, sy);


			if (abs(dir.x) > abs(dir.y))
			{
				if (dir.x > 0)//相手の右に当たったら
				{
					sound->PlaySEF("./Assets/Sound/crash.wav");
					mPos->x = cPosX + mSize->x+1;
				}
				else//左に当たったら
				{
					sound->PlaySEF("./Assets/Sound/crash.wav");
					mPos->x = cPosX - mSize->x-1;
				}
			}
			else
			{
				if (dir.y < 0)//相手の下に当たったら
				{
					//mMovingFastCount = mMovingFastMaxCount;
					mFall = false;
					if (mVelocity->y > 0)
					{
						mPos->y = cPosY - mSize->y;
						mVelocity->y = 0;
					}
				}
				else//上に当たったら
				{
					
					sound->PlaySEF("./Assets/Sound/crash.wav");
					mPos->y = cPosY + cSizeY + 1;
					if (mVelocity->y < 0)
					{
						mVelocity->y = 0;
					}
				}
			}
		}

		if (hit->getOwner()->Tag() == "FlyEnemy" || hit->getOwner()->Tag() == "RushEnemy" || hit->getOwner()->Tag() == "PatrolEnemy")
		{
			if (mMovingFast)//高速移動状態ならば
			{
				hit->getOwner()->SetElectricShock(true);
			}
			if (mNowMovingFast)//高速移動状態初期処理状態ならば
			{
				hit->getOwner()->SetElectricShock(true);
			}

			if (!hit->getOwner()->GetElectricShock())
			{
				Damage();
			}
		}
	}

	for (auto && hit : mCollider->onCollisionEnter())//あたった瞬間
	{
		auto cPosX = hit->getOwner()->Position()->x;
		auto cPosY = hit->getOwner()->Position()->y;
		auto cSizeX = hit->getOwner()->Size()->x;
		auto cSizeY = hit->getOwner()->Size()->y;
		auto sx = cPosX + (cSizeX / 2);//真ん中
		auto sy = cPosY + (cSizeY / 2);//真ん中
		Vector2 dir = Vector2(mPos->x + (mSize->x / 2), mPos->y + (mSize->y / 2)) - Vector2(sx, sy);

		if (hit->getOwner()->Tag() == "Wall")
		{
			if (abs(dir.x) > abs(dir.y))
			{
				if (dir.x > 0)//相手の右に当たったら
				{
					mPos->x = cPosX + mSize->x;
					if (mVelocity->x < 0)
					{
						mVelocity->x = 0;
					}
				}
				else//左に当たったら
				{
					mPos->x = cPosX - mSize->x;
					if (mVelocity->x < 0)
					{
						mVelocity->x = 0;
					}
				}
			}
			else
			{
				if (dir.y < 0)//相手の下に当たったら
				{
					sound->PlaySEF("./Assets/Sound/Landing.wav");//着地音
					mMovingFastCount = mMovingFastMaxCount;
					mFall = false;
					if (mVelocity->y > 0)
					{
						mPos->y = cPosY - mSize->y;
					}
				}
				else//上に当たったら
				{
					mPos->y = cPosY + cSizeY + 1;
					if (mVelocity->y < 0)
					{
						mVelocity->y = 0;
					}
				}
			}
		}
		
		if (hit->getOwner()->Tag() == "FlyEnemy" || hit->getOwner()->Tag() == "RushEnemy" || hit->getOwner()->Tag() == "PatrolEnemy")
		{
			if (mMovingFast)//高速移動状態ならば
			{
				if (hit->getOwner()->GetElectricShock())
				{
					float count = 0.1f;
					Destroy(hit->getOwner(), count);
					for (auto && ac : GetActorManager()->getActorList())
					{
						if (ac->GetElectricShock())
						{
							count += 0.15f;
							SceneManager::score += (count * 100);
							Destroy(ac, count);
						}
					}
				}
				hit->getOwner()->SetElectricShock(true);
			}
			if (mNowMovingFast)//高速移動状態初期処理状態ならば
			{
				hit->getOwner()->SetElectricShock(true);
			}

			if (!hit->getOwner()->GetElectricShock())
			{
				Damage();
			}
		}
		
	}
}

bool Player::GetMovingFast()
{
	return mMovingFast;
}


