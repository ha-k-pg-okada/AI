#ifndef RULEBASEAI_H
#define RULEBASEAI_H

#include "Engine/Engine.h"
#include "Collision.h"

enum class Rule
{
	HitFan,
	HitCircle,
	Noen,
};

class RuleBaseAi
{
public:
	RuleBaseAi();
	~RuleBaseAi();

public:
	void Update();
	void Draw();

public:
	//�ҋ@
	void Wait();
	//�ړ�
	void Move();

	//���[��(�I���E�I�t�@)
	Rule OnOff();

public:
	Vec2 GetRuleBaseAiPos();

private:
	float Speed;
	float Angle;//�p�x
	int Counter;
	int Step;

	Vec2 Direction;       //�ړ����Ɏg������
	Vec2 Position;
	Rule NowRules;        //���݂̃��[��
	int ItemNumber;       //���������A�C�e���̔ԍ�
	int FanItemNumber;    //��̔��������A�C�e���̔ԍ�
	int CircleItemNumber; //�~�̔��������A�C�e���̔ԍ�

	bool HitFan;
	bool HitCircle;
	Rule HitLastTime;

	const float FanLengh  = 200.0f;
	const float FanDegree = 30.0f;
	const float CircleRadius = 80.0f;

	Collision Collision;

	Vec2 ItemsPos[5];
};

#endif // !RULEBASEAI_H

