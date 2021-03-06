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
	//待機
	void Wait();

	//移動
	void Move();

	//アイテム回収
	void MoveItem();

public:
	Vec2 GetStateBaseAIPos();

private:
	float Speed;
	float Angle;//角度
	int Counter;
	int Step;
	Vec2 Position;
	Vec2 Direction;//移動時に使う向き

	int ItemNumber;//発見したアイテムの番号

	const float FanLengh = 150.0f;
	const float FanDegree = 90.0f;

	Collision Collision;
};

#endif // !STATEBASEAI_H
