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

void Physics::sweepAndPrune()//ëçìñÇΩÇËîªíË
{
	if (mColliders.empty()) 
	{
		return;
	}

	for (size_t i = 0; i < mColliders.size(); ++i)
	{
		auto a = dynamic_cast<ColliderComponent*>(mColliders[i]);
		if (!a->getEnable())
		{
			continue;
		}
		auto ac = a->getQuadrangle();
		for (size_t j = i + 1; j < mColliders.size(); ++j)
		{
			auto b = dynamic_cast<ColliderComponent*>(mColliders[j]);
			if (!b->getEnable())
			{
				continue;
			}
			auto bc = b->getQuadrangle();
			if (CheckHit(*ac, *bc))//Ç†ÇΩÇ¡ÇƒÇ¢ÇÍÇŒÇÃèàóù
			{
				a->AddHitCollider(b);
				b->AddHitCollider(a);
			}
		}
	}
}

