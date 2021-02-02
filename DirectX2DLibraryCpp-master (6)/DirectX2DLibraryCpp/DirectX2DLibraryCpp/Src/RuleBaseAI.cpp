#include"RuleBaseAI.h"
#include"ItemManager.h"
#include <time.h>
#include <math.h>

RuleBaseAi::RuleBaseAi()
{
	Position = Vec2(350.0f, 200.0f);

	Speed = 1.0f;
	Angle = 0.0f;
	Counter = 0;
	Step = 0;

	Direction = Vec2(0.0f, 0.0f);

	NowRules = Rule::Noen;
	ItemNumber = 0;
	FanItemNumber = 0;
	CircleItemNumber = 0;

	HitFan = false;
	HitCircle = false;
	HitLastTime = Rule::Noen;

	srand((unsigned int)time(NULL));
}
RuleBaseAi::~RuleBaseAi()
{

}

Vec2 RuleBaseAi::GetRuleBaseAiPos()
{
	return Position;
}

void RuleBaseAi::Update()
{
	switch (Step)
	{
	case 0:
		Wait();
		break;
	case 1:
		Move();
		break;
	default:
		break;
	}
}
void RuleBaseAi::Draw()
{
	Vec2 CenterPos = Vec2(Position.X + Collision.AiSize.X / 2, Position.Y + Collision.AiSize.Y / 2);

	//円
	Engine::DrawFan(CenterPos, 360.0f, CircleRadius, Angle, 0x900000ff);

	//扇
	Engine::DrawFan(CenterPos, FanDegree, FanLengh, Angle, 0x90ff0000);

	Engine::DrawTexture(Position.X, Position.Y, "Enemy", 255, 0.0f, 1.0f, 1.0f);
}

//待機
void RuleBaseAi::Wait()
{
	Counter++;
	if (Counter >= 120)
	{
		NowRules = Rule::Noen;
		HitFan = false;
		HitCircle = false;
		Counter = 298;
		Step = 1;
	}
}
//移動
void RuleBaseAi::Move()
{
	if (NowRules == Rule::Noen)
	{
		NowRules = OnOff();

		Counter++;

		if (Counter >= 300)
		{
			//角度
			Angle = rand() % 360;

			//ラジアン変換
			float rad = Angle * 3.14 / 180;

			Direction = Vec2(cosf(rad), sinf(rad));

			Counter = 0;
		}
		//移動
		Position.X += Direction.X * Speed;
		Position.Y += Direction.Y * Speed;

		//画面外にいかなくする
		if (Position.X < 0.0f)   Position.X = 0.0f;
		if (Position.X > 592.0f) Position.X = 592.0f;
		if (Position.Y < 0.0f)   Position.Y = 0.0f;
		if (Position.Y > 432.0f) Position.Y = 432.0f;
	}
	else if (NowRules == Rule::HitFan || NowRules == Rule::HitCircle)
	{
		//ベクトル算出
		Vec2 Vector =
			Vec2((ItemManager::Instance()->Items[ItemNumber].Position.X + Collision.ItemSize.X / 2.0f) - (Position.X + Collision.AiSize.X / 2.0f),
				 (ItemManager::Instance()->Items[ItemNumber].Position.Y + Collision.ItemSize.Y / 2.0f) - (Position.Y + Collision.AiSize.Y / 2.0f));
		//単位ベクトル算出
		float Length = sqrtf(Vector.X * Vector.X + Vector.Y * Vector.Y);
		Vec2 Normal = Vec2(Vector.X / Length, Vector.Y / Length);
	
		//移動
		Position.X += Normal.X * Speed;
		Position.Y += Normal.Y * Speed;

		//移動終了
		if (ItemManager::Instance()->Items[ItemNumber].IsActive == false)
		{
			Counter = 0;
			Step = 0;
		}

		//向いている角度
		Angle = atan(Vector.Y / Vector.X) * (180.0f / 3.14);
		if (Vector.X < 0)
		{
			Angle += 180;
		}
	}
}

//ルール(オン・オフ法)
Rule RuleBaseAi::OnOff()
{
	Vec2 CenterPos = Vec2(Position.X + Collision.AiSize.X / 2, Position.Y + Collision.AiSize.Y / 2);

	Vec2 CirclePos = Vec2(Position.X + Collision.AiSize.X / 2.0f - CircleRadius, Position.Y + Collision.AiSize.Y / 2.0f - CircleRadius);
	Vec2 CircleSize = Vec2(CircleRadius * 2, CircleRadius * 2);
	
	//扇の探索判定
	for (int i = 0; i < 5; i++)
	{
		if (Collision.OnCollisionArcAndPoint(CenterPos,ItemManager::Instance()->Items[i].Position,FanDegree,Angle,FanLengh,Collision.ItemSize) == true)
		{
			FanItemNumber = i;
			HitFan = true;
			break;
		}
	}
	
	//円の探索判定
	for (int i = 0; i < 5; i++)
	{
		if (Collision.OnCollisionCircleAndCircle(ItemManager::Instance()->Items[i].Position,Collision.ItemSize,CirclePos,CircleSize) == true)
		{
			CircleItemNumber = i;
			HitCircle = true;
			break;
		}
	}

	//OnOffで返す
	if (HitFan == true && HitCircle == true)
	{
		if (HitLastTime != Rule::HitFan)
		{
			ItemNumber = FanItemNumber;
			HitLastTime = Rule::HitFan;
			return Rule::HitFan;
		}
		else
		{
			ItemNumber = CircleItemNumber;
			HitLastTime = Rule::HitCircle;
			return Rule::HitCircle;
		}
	}
	else if (HitFan == true)
	{
		ItemNumber = FanItemNumber;
		return Rule::HitFan;
	}
	else if (HitCircle == true)
	{
		ItemNumber = CircleItemNumber;
		return Rule::HitCircle;
	}
	
	return Rule::Noen;
}