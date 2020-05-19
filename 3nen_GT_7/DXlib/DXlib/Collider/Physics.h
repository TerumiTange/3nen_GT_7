#pragma once

#include <vector>

class Actor;
class Collider;

class Physics
{
public:
	Physics();
	~Physics();

	void add(Collider* col);
	void remove(Collider* col);
	void clear();
	void sweepAndPrune();

private:
	std::vector<Collider*> mColliders;
};