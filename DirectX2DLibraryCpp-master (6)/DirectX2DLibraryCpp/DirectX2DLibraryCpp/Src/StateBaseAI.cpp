#include"StateBaseAI.h"
#include"ItemManager.h"
#include <time.h>
#include <math.h>

StateBaseAi::StateBaseAi()

{
	Position = Vec2(250.0f, 200.0f);
	Speed = 1.0f;
	Angle = 180.0f;
	Counter = 0;
	Step = 0;
	Direction = Vec2(0.0f, 0.0f);
	ItemNumber = 0;

	srand((unsigned int)time(NULL));
}
StateBaseAi::~StateBaseAi()
{

}

Vec2 StateBaseAi::GetStateBaseAIPos()
{
	return Position;
}

void StateBaseAi::Update()
{
	switch (Step)
	{
	case 0:
		Wait();
		break;
	case 1:
		Move();
		break;
	case 2:
		MoveItem();
		break;
	default:
		break;
	}
}
void StateBaseAi::Draw()
{
	Vec2 CenterPos = Vec2(Position.X + 25.0f, Position.Y + 25.0f);
	//扇
	Engine::DrawFan(CenterPos, FanDegree, FanLengh, Angle, 0x9000ff00);

	Engine::DrawTexture(Position.X, Position.Y, "Enemy", 255, 0.0f, 1.0f, 1.0f);
	
}

//待機
void StateBaseAi::Wait()
{
	Counter++;
	if (Counter >= 120)
	{
		Step = 1;
		Counter = -1;
	}
	Vec2 CenterPos = Vec2(Position.X + Collision.AiSize.X / 2, Position.Y + Collision.AiSize.Y / 2);
	if (ItemManager::Instance()->Items[ItemNumber].IsActive == true)
	{
		//扇の探索判定
		for (int i = 0; i < 5; i++)
		{
			if (Collision.OnCollisionArcAndPoint(CenterPos,ItemManager::Instance()->Items[i].Position,FanDegree,Angle,FanLengh,Collision.ItemSize) == true)
			{
				ItemNumber = i;
				Step = 2;
				break;
			}
		}
	}
}
//移動
void StateBaseAi::Move()
{
	Counter++;

	if (Counter == 0)
	{
		//角度
		Angle = rand() % 360 + 1;

		//ラジアン変換
		float radian = Angle * 3.14 / 180;

		Direction = Vec2(cosf(radian), sinf(radian));
	}
	//移動
	Position.X += Direction.X * Speed;
	Position.Y += Direction.Y * Speed;

	//画面外にいかなくする
	if (Position.X < 0.0f)   Position.X = 0.0f;
	if (Position.X > 592.0f) Position.X = 592.0f;
	if (Position.Y < 0.0f)   Position.Y = 0.0f;
	if (Position.Y > 432.0f) Position.Y = 432.0f;

	if (Counter >= 180)
	{
		Counter = 0;
		Step = 0;
	}

	Vec2 CenterPos = Vec2(Position.X + Collision.AiSize.X / 2, Position.Y + Collision.AiSize.Y / 2);

	//扇の探索判定
	for (int i = 0; i < 5; i++)
	{
		if (Collision.OnCollisionArcAndPoint(CenterPos,ItemManager::Instance()->Items[i].Position, FanDegree,Angle,FanLengh,Collision.ItemSize) == true)
		{
			ItemNumber = i;
			Step = 2;
			break;
		}
	}
}

void StateBaseAi::MoveItem()
{
	
		//ベクトル算出
		Vec2 Vector = Vec2((ItemManager::Instance()->Items[ItemNumber].Position.X + Collision.ItemSize.X / 2.0f) - (Position.X + Collision.AiSize.X / 2.0f),
				          (ItemManager::Instance()->Items[ItemNumber].Position.Y + Collision.ItemSize.Y / 2.0f) - (Position.Y + Collision.AiSize.Y / 2.0f));

		//単位ベクトル算出
		float Length = sqrtf(Vector.X * Vector.X + Vector.Y * Vector.Y);
		Vec2 Normal = Vec2(Vector.X / Length, Vector.Y / Length);

		//移動
		Position.X += Normal.X * Speed;
		Position.Y += Normal.Y * Speed;

		//距離
		Vec2 Distance = Vec2(ItemManager::Instance()->Items[ItemNumber].Position.X - Position.X,
			ItemManager::Instance()->Items[ItemNumber].Position.Y - Position.Y);

		//向いている角度
		Angle = atan(Vector.Y / Vector.X) * (180.0f / 3.14);
		if (Vector.X < 0)
		{
			Angle += 180;
		}
	
        //移動終了
		if (ItemManager::Instance()->Items[ItemNumber].IsActive == false)
	    {
			Counter = -1;
		    Step = 0;
	    }
}