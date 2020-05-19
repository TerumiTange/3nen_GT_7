#include "ComponentManager.h"
#include "Component.h"

ComponentManager::ComponentManager() = default;

ComponentManager::~ComponentManager()
{
	mStartComponents.clear();
	mComponents.clear();
}

void ComponentManager::start()
{
	if (mStartComponents.empty())
	{
		return;
	}
	for (auto&& c : mStartComponents)
	{
		c->start();

		int myOrder = c->getUpdateOrder();
		auto itr = mComponents.begin();
		for (; itr != mComponents.end(); ++itr)
		{
			if (myOrder < (*itr)->getUpdateOrder())
			{
				break;
			}
		}
		mComponents.insert(itr, c);
	}
	mStartComponents.clear();
}

void ComponentManager::update()
{
	for (auto&& c : mComponents)
	{
		c->update();
	}
}

void ComponentManager::addComponent(Component * component)
{
	mStartComponents.emplace_back(component);
}

void ComponentManager::onUpdate()
{
	for (auto&& c : mComponents)
	{
		c->onUpdate();
	}
}
