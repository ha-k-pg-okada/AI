#ifndef STATEBASEAI_H
#define STATEBASEAI_H

#include "Engine/Engine.h"
#include "Collision.h"

class StateBaseAi
{
public:
	StateBaseAi();
	~StateBaseAi();

public:

	void Update();
	void Draw();

public:
	//�ҋ@
	void Wait();

	//�ړ�
	void Move();

	//�A�C�e�����
	void MoveItem();

public:
	Vec2 GetStateBaseAIPos();

private:
	float Speed;
	float Angle;//�p�x
	int Counter;
	int Step;
	Vec2 Position;
	Vec2 Direction;//�ړ����Ɏg������

	int ItemNumber;//���������A�C�e���̔ԍ�

	const float FanLengh = 150.0f;
	const float FanDegree = 90.0f;

	Collision Collision;
};

#endif // !STATEBASEAI_H
