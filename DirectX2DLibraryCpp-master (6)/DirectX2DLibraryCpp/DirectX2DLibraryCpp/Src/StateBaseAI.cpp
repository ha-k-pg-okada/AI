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
	//��
	Engine::DrawFan(CenterPos, FanDegree, FanLengh, Angle, 0x9000ff00);

	Engine::DrawTexture(Position.X, Position.Y, "Enemy", 255, 0.0f, 1.0f, 1.0f);
	
}

//�ҋ@
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
		//��̒T������
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
//�ړ�
void StateBaseAi::Move()
{
	Counter++;

	if (Counter == 0)
	{
		//�p�x
		Angle = rand() % 360 + 1;

		//���W�A���ϊ�
		float radian = Angle * 3.14 / 180;

		Direction = Vec2(cosf(radian), sinf(radian));
	}
	//�ړ�
	Position.X += Direction.X * Speed;
	Position.Y += Direction.Y * Speed;

	//��ʊO�ɂ����Ȃ�����
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

	//��̒T������
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
	
		//�x�N�g���Z�o
		Vec2 Vector = Vec2((ItemManager::Instance()->Items[ItemNumber].Position.X + Collision.ItemSize.X / 2.0f) - (Position.X + Collision.AiSize.X / 2.0f),
				          (ItemManager::Instance()->Items[ItemNumber].Position.Y + Collision.ItemSize.Y / 2.0f) - (Position.Y + Collision.AiSize.Y / 2.0f));

		//�P�ʃx�N�g���Z�o
		float Length = sqrtf(Vector.X * Vector.X + Vector.Y * Vector.Y);
		Vec2 Normal = Vec2(Vector.X / Length, Vector.Y / Length);

		//�ړ�
		Position.X += Normal.X * Speed;
		Position.Y += Normal.Y * Speed;

		//����
		Vec2 Distance = Vec2(ItemManager::Instance()->Items[ItemNumber].Position.X - Position.X,
			ItemManager::Instance()->Items[ItemNumber].Position.Y - Position.Y);

		//�����Ă���p�x
		Angle = atan(Vector.Y / Vector.X) * (180.0f / 3.14);
		if (Vector.X < 0)
		{
			Angle += 180;
		}
	
        //�ړ��I��
		if (ItemManager::Instance()->Items[ItemNumber].IsActive == false)
	    {
			Counter = -1;
		    Step = 0;
	    }
}