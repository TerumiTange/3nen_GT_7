#pragma once

class Actor;

class Component
{
protected:
	Component(Actor* owner, int updateOrder = 100);
public:
	virtual ~Component();
	virtual void start() = 0;
	virtual void update() = 0;

	virtual void onUpdate() {};
	//�I�[�i�[�̈ʒu���X�V���ꂽ��
	int getUpdateOrder() const;
	Actor* getOwner() const;

protected:
	Actor* mOwner;
	int mUpdateOrder;
};