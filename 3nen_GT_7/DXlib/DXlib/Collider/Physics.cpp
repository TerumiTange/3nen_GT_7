#include "Physics.h"

#include "../Actor/Actor.h"
#include "../Actor/ActorManager.h"
#include "ColliderComponent.h"
#include "../Collider/Collider.h"
#include "ComponentManager.h"
#include "Collision.h"
#include <algorithm>

Physics::Physics() = default;
Physics::~Physics() = default;

void Physics::add(Collider* col) 
{
	mColliders.emplace_back(col);
}

void Physics::remove(Collider* col) 
{
	auto itr = std::find(mColliders.begin(), mColliders.end(), col);
	if (itr != mColliders.end()) 
	{
		std::iter_swap(itr, mColliders.end() - 1);
		mColliders.pop_back();
	}
}

void Physics::clear() 
{
	mColliders.clear();
}

void Physics::sweepAndPrune()//�������蔻��
{
	if (mColliders.empty()) 
	{
		return;
	}

	//�ʒuX�����������Ƀ\�[�g
	std::sort(mColliders.begin(), mColliders.end(), [](Collider* a, Collider*b)
	{
		auto A = dynamic_cast<ColliderComponent*>(a);
		auto B = dynamic_cast<ColliderComponent*>(b);
		return A->getQuadrangle()->position.x < B->getQuadrangle()->position.x;
	});

	for (size_t i = 0; i < mColliders.size(); ++i)
	{
		auto a = dynamic_cast<ColliderComponent*>(mColliders[i]);
		if (a->getOwner()->Tag() == "Wall")continue;
		if (!a->getEnable())
		{
			continue;
		}
		auto ac = a->getQuadrangle();
		//mQuadrangle[i]��X�l+�T�C�YX���擾
		float max = ac->position.x + ac->size.x;
		for (size_t j = i + 1; j < mColliders.size(); ++j)
		{
			auto b = dynamic_cast<ColliderComponent*>(mColliders[j]);
			if (!b->getEnable())
			{
				continue;
			}
			auto bc = b->getQuadrangle();
			//std::sqrtf(std::powf(pPos.x - mPos->x, 2) + std::powf(pPos.y - mPos->y, 2)) < 200
			//����mQuadrangle[j]��X�l���AmQuadrangle[i]��X�l+�T�C�YX���傫�����
			//mQuadrangle[i]�ƌ�������{�b�N�X�͑��݂��Ȃ�
			if (bc->position.x > max)
			{
				break;
			}
			else if (CheckHit(*ac, *bc))//�������Ă���΂̏���
			{
				a->AddHitCollider(b);
				b->AddHitCollider(a);
			}
		}
	}
}

