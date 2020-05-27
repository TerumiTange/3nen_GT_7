#pragma once
#include "Actor.h"
#include "../Utility/Vector2.h"
#include "../Device/Renderer.h"
#include "../System/CountDownTimer.h"
#include "../Device/Sound.h"
#include "../Collider/ColliderComponent.h"
#include "../Collider/Component.h"

#include <memory>

class TitleEnemy : public Actor
{
public:
	TitleEnemy(const Vector2& pos, const char* tag = "TitleEnemy");
	~TitleEnemy();
	virtual void End()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Hit() override;
	void ToPlayer();
};