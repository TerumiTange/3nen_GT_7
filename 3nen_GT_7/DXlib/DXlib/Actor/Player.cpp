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
	mMaxHp(5),										  //�ő�̗�
	mHp(5),											  //���݂̗̑�
	mInvincibleTime(3),								  //���G����
	mPos(new Vector2(0, 0)),							  //���݂̈ʒu
	mVelocity(new Vector2(0, 0)),					  //�ړ���
	maxSpeed(7),									  //�ő�X�s�[�h
	mAcceleration(0.5),								  //�����x
	mSize(new Vector2(32, 32)), 						  //�����̑傫��
	mFilename(tag),									  //�摜��
	mRenderer(new Renderer(tag)),					  //�`��֐�
	mIdolRenderer(new Renderer("PlayerIDL")),
	mStaticElectricity(new Renderer("ThunderEffect")),//�Ód�C�̉摜
	mHeart(new Renderer("HP")),					  //����HP��\������
	mAttackImages(new Renderer("PlayerAttack")),
	mInput(new Input()),							  //�L�[���͊֐�
	mCountTimer(new CountDownTimer()),				  //���G���ԍX�V�J�E���g�_�E���^�C�}�[
	mFall(true),									  //�����Ă��邩�ǂ���
	mGravity(5),									  //�d�͂̃X�s�[�h
	mMovingFastGravity(0),							  //�����ړ����̏d��
	mMovingFast(false),								  //�����ړ����Ă��邩�ǂ���
	mMovingFastCount(3),							  //�����ړ��ł����
	mMovingFastMaxCount(3),							  //�ő卂���ړ��̉񐔁[
	mMovingFastAmount(13),							  //�����ړ��̈ړ���
	mNowMovingFastTimer(new CountDownTimer()),        //�����ړ���Ԃ̃^�C�}�[
	mNowMovingFastTime(0.2f),						  //�����ړ���Ԃ̎���
	mNowMovingFast(false),							  //�����ړ������u��
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
	Actor::SetPos(*mPos);   //�A�N�^�[�ɃZ�b�g
	Actor::SetSize(*mSize);	//�A�N�^�[�ɃZ�b�g
	mInput->Init();
	sound->Init();
	sound->Load("./Assets/Sound/damage.wav");//�_���[�W
	sound->Load("./Assets/Sound/pdeth.wav");//���S
	sound->Load("./Assets/Sound/movingfast.wav");//�����ړ�
	sound->Load("./Assets/Sound/crash.wav");//�ǂƂ̏Փ�
	sound->Load("./Assets/Sound/Landing.wav");//���n��
	mCountTimer->SetTime(0.0f);
	mNowMovingFastTimer->SetTime(0.0f);
}

Player::~Player() = default;

void Player::End()//�������̊J��
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
	mElectricTimer->Update();//�G�̖�თp

	if (mMovingFastCount > mMovingFastMaxCount)//�ő�񐔂��I�[�o�[������
	{
		mMovingFastCount = mMovingFastMaxCount;//�ő�񐔂ɂ���
	}
	//clsDx();
	//�f�o�b�O�p
	//printfDx("�̗�%d", mHp);
	//printfDx("���G����%.001f", mCountTimer->Now());
	//printfDx("�u�Ԉړ��ł����%d", mMovingFastCount);
	//printfDx("�u�Ԉړ��ł���悤�ɂȂ�܂ł̎���%.01f", mMovingFastTimer->Now());

	if (mHp <= 0)return;//�̗͂��Ȃ��Ȃ����瑀�삵�Ȃ��悤�ɂ���

	mInput->JoyUpdate();//�W���C�p�b�h�X�V
	mCountTimer->Update();//���G���ԍX�V

	if (mNowMovingFastTimer->IsTime())//�����ړ������u�Ԃ̏������I��������
	{
		mMovingFast = false;
		//mFall = true;
	}

	Actor::SetPos(*mPos);//���݂̈ʒu���W���A�N�^�[�ɃZ�b�g����
	old_x = mPos->x;//�ړ��O�Ɍ��݂̍��WX���X�V
	old_y = mPos->y;//�ړ��O�Ɍ��݂̍��WY���X�V
	mNowMovingFastTimer->Update();//�����ړ������u�Ԃ̏������X�V
	

	if (mInput->GetKeyDown(SPACE) || mInput->PadDown(Joy_A))//�X�y�[�X�܂��̓R���g���[���[��A����������
	{
		MovingFast();//�u�Ԉړ�
	}

	//if (mInput->GetKeyDown(H))//�f�o�b�O�p
	//{
	//	Recovery();//�̗͉�
	//}

	Move();//�ړ�����
	Fall();//�d�͌v�Z
	Movement();//�ړ��v�Z
}
void Player::Fall()//�d��
{
	if (mMovingFast)//�����ړ����Ȃ�
	{
		//mPos->y += mMovingFastGravity;//�y���d��
		mVelocity->y += mMovingFastGravity;
		return;
	}
	if (!mFall)return;//�n�ʂɒ��n���Ă��Ȃ���΃��^�[��
	//mPos->y += mGravity;
	mVelocity->y += mGravity;
}

void Player::Move()
{
	if (mMovingFast)return;//�u�Ԉړ����Ȃ烊�^�[��
	if ((mInput->Horizontal() < 0) || (mInput->GetKey(A) || mInput->GetKey(LEFTARROW)))//���ړ�
	{
		mVelocity->x = min(mVelocity->x - mAcceleration, -maxSpeed);
	}
	else if ((mInput->Horizontal() > 0) || (mInput->GetKey(D) || mInput->GetKey(RIGHTARROW)))//�E�ړ�
	{
		mVelocity->x = max(mVelocity->x + mAcceleration, maxSpeed);
	}
}

void Player::Movement()//�ړ�����
{
	mRight = (mVelocity->x > 0) ? true : false;
	mVelocity->x = (abs(mVelocity->x) < 15) ? mVelocity->x : ((mVelocity->x < 0) ? -14 : 14);
	mVelocity->y = (abs(mVelocity->y) < 15) ? mVelocity->y : ((mVelocity->y < 0) ? -14 : 14);



	mPos->y += mVelocity->y;//�ړ�����Y
	mPos->x += mVelocity->x;//�ړ�����X


	if (!mNowMovingFast)
	{
		mVelocity->y *= 0.7f;//�����Ŋ��������o��
		mVelocity->x *= 0.9f;//�����Ŋ��������o��
	}
	
	if (mNowMovingFast&&mNowMovingFastTimer->IsTime())//�����ړ��Ȃ犵��0
	{
		mVelocity->x = 0;
		mVelocity->y = 0;

		mNowMovingFast = false;
	}
	//��ʊO�ɏo���ꍇ�ʒu�C��
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

void Player::MovingFast()//�u�Ԉړ�
{
	if (mMovingFastCount <= 0)return;//�񐔂�0�ȉ��Ȃ烊�^�[��
	//if (mMovingFast)return;//�u�Ԉړ����Ȃ烊�^�[��
	if (!mNowMovingFastTimer->IsTime())return;//��莞�Ԃ��܂Ŗ���
	sound->PlaySE("./Assets/Sound/movingfast.wav");
	mMovingFast = true;
	mFall = false;
	mNowMovingFast = true;
	mMovingFastCount--;

	mVelocity->x = mInput->Horizontal()*mMovingFastAmount;//�R���g���[���ł̈ړ�
	mVelocity->y = mInput->Vertical()*mMovingFastAmount;  //�R���g���[���ł̈ړ�

	/*
	//�L�[�{�[�h�ł̈ړ�
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

	if (mVelocity->x == 0 && mVelocity->y == 0)//�������͂��Ȃ���ΉE�Ɉړ�
	{
		mVelocity->x = mMovingFastAmount;
	}


	mNowMovingFastTimer->SetTime(mNowMovingFastTime);//�����ɕK�v�Ȏ���
}

void Player::Damage()//�_���[�W
{
	if (mMovingFast)return;//�u�Ԉړ����Ȃ�
	if (mCountTimer->IsTime())//���G���ԂłȂ��Ȃ�
	{
		mHp--;//1�_���[�W�󂯂�
		sound->PlaySE("./Assets/Sound/damage.wav");
		mCountTimer->SetTime(mInvincibleTime);//���G���Ԃ��Z�b�g
		SceneManager::score -= 100;//�X�R�A����100�_����
	}

	if (mHp <= 0)//�̗͂��Ȃ��Ȃ�����
	{
		sound->PlaySEF("./Assets/Sound/pdeth.wav");
		Destroy(this, 1.f);//3�b��Ɏ��S
	}
}

void Player::Recovery()//�̗͉�
{
	mHp++;
	if (mMaxHp < mHp)//�ő�̗͂𒴂�����
	{
		mHp = mMaxHp;//�ő�̗͂ɂ���
	}
}


void Player::Draw()//�`��
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
			int t = fmod(mUpTimer->Now() * 3, 3);//�����̊|���Ă��鐔���ŃX�s�[�h���ς��

			//�A�C�h���̉摜
			mIdolRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), t, *mSize, FALSE);
		}
		else if (mRight)
		{
			//�E�����̉摜
			int r = fmod(mUpTimer->Now() * 3, 4);
			mRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), r, *mSize, FALSE);
		}
		else
		{
			//�������̉摜
			int l = fmod(mUpTimer->Now() * 3, 4);
			mRenderer->DrawSerialNumber(*mPos, Vector2(0, 0), l, *mSize, TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�A���t�@�l�ő�

	//mRenderer->DrawE(*mPos, 64);
	if (mNowMovingFast)
	{
		//mStaticElectricity->Draw(mPos->x - 32, mPos->y);
		mStaticElectricity->DrawAlternating(mPos->x + 8, mPos->y + 5, 3);
	}
	
	//mCountTimer->Now(); mInvincibleTime
	if (mInvincibleTime - mCountTimer->Now() < 0.3f)//�_���[�W���󂯂���
	{
		//DrawString(mPos->x - 10, mPos->y - 32, "�_���[�W", GetColor(255, 0, 0));
		SetDrawBright(200, 100, 100);
		mDamage->Draw(mPos->x, mPos->y - 32);
		mDamageEf1->Drawb(0, 0);//�O�g
		mDamageEf2->Drawb(0, 0);//��ʑS�̂̐�
		SetDrawBright(255, 255, 255);
	}

	
	for (size_t i = 0; i < mHp; ++i)//HP�\��
	{
		mHeart->Drawb(10 + i * 32, 32);
	}
    //DrawString(0, 0, "", mMovingFastCount);
	//DrawFormatString(10, 0, GetColor(255, 0, 0), "�u�Ԉړ��ł����%d", mMovingFastCount);
	//SetFontSize(32);
	//DrawString(0, 0, "�u�Ԉړ��ł����:", GetColor(255, 0, 0));
	//mNumber->DrawIntegerNumber(Vector2(350, 0), mMovingFastCount);

	for (int i = 0; i < mMovingFastMaxCount; ++i)//�����ړ��񐔕\��
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
	if (mCollider->onCollisionStay().empty() && mCollider->onCollisionEnter().empty())//���Ƃ��������Ă��Ȃ����
	{
		mFall = true;
		return;
	}

	for (auto && hit : mCollider->onCollisionStay())//�A���œ������Ă���Ƃ�
	{
		if (hit->getOwner()->Tag() == "Wall")
		{
			auto cPosX = hit->getOwner()->Position()->x;
			auto cPosY = hit->getOwner()->Position()->y;
			auto cSizeX = hit->getOwner()->Size()->x;
			auto cSizeY = hit->getOwner()->Size()->y;


			auto sx = cPosX + (cSizeX / 2);//�^��
			auto sy = cPosY + (cSizeY / 2);//�^��

			Vector2 dir = Vector2(old_x + (mSize->x / 2), mPos->y + (mSize->y / 2)) - Vector2(sx, sy);


			if (abs(dir.x) > abs(dir.y))
			{
				if (dir.x > 0)//����̉E�ɓ���������
				{
					sound->PlaySEF("./Assets/Sound/crash.wav");
					mPos->x = cPosX + mSize->x+1;
				}
				else//���ɓ���������
				{
					sound->PlaySEF("./Assets/Sound/crash.wav");
					mPos->x = cPosX - mSize->x-1;
				}
			}
			else
			{
				if (dir.y < 0)//����̉��ɓ���������
				{
					//mMovingFastCount = mMovingFastMaxCount;
					mFall = false;
					if (mVelocity->y > 0)
					{
						mPos->y = cPosY - mSize->y;
						mVelocity->y = 0;
					}
				}
				else//��ɓ���������
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
			if (mMovingFast)//�����ړ���ԂȂ��
			{
				hit->getOwner()->SetElectricShock(true);
			}
			if (mNowMovingFast)//�����ړ���ԏ���������ԂȂ��
			{
				hit->getOwner()->SetElectricShock(true);
			}

			if (!hit->getOwner()->GetElectricShock())
			{
				Damage();
			}
		}
	}

	for (auto && hit : mCollider->onCollisionEnter())//���������u��
	{
		auto cPosX = hit->getOwner()->Position()->x;
		auto cPosY = hit->getOwner()->Position()->y;
		auto cSizeX = hit->getOwner()->Size()->x;
		auto cSizeY = hit->getOwner()->Size()->y;
		auto sx = cPosX + (cSizeX / 2);//�^��
		auto sy = cPosY + (cSizeY / 2);//�^��
		Vector2 dir = Vector2(mPos->x + (mSize->x / 2), mPos->y + (mSize->y / 2)) - Vector2(sx, sy);

		if (hit->getOwner()->Tag() == "Wall")
		{
			if (abs(dir.x) > abs(dir.y))
			{
				if (dir.x > 0)//����̉E�ɓ���������
				{
					mPos->x = cPosX + mSize->x;
					if (mVelocity->x < 0)
					{
						mVelocity->x = 0;
					}
				}
				else//���ɓ���������
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
				if (dir.y < 0)//����̉��ɓ���������
				{
					sound->PlaySEF("./Assets/Sound/Landing.wav");//���n��
					mMovingFastCount = mMovingFastMaxCount;
					mFall = false;
					if (mVelocity->y > 0)
					{
						mPos->y = cPosY - mSize->y;
					}
				}
				else//��ɓ���������
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
			if (mMovingFast)//�����ړ���ԂȂ��
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
			if (mNowMovingFast)//�����ړ���ԏ���������ԂȂ��
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


