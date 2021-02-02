#include"Run.h"
#include <time.h>
#include "ItemManager.h"

Run::Run()
{
	ItemManager::Instance()->Initialize();
	timer = 0;
	srand((unsigned int)time(NULL));
}
Run::~Run()
{

}

void Run::Update()
{
	timer++;
	if (timer >= 300)
	{
		ItemManager::Instance()->CreateItem(rand() % 590, rand() % 430);
		timer = 0;
	}

	//�A�C�e����RuleBaseAI�̓����蔻��
	for (int i = 0; i < 5; i++)
	{
		if (Collision.OnCollisionCircleAndCircle(ItemManager::Instance()->Items[i].Position,Collision.ItemSize,RuleBaseAI.GetRuleBaseAiPos(), Collision.AiSize) == true)
		{
			ItemManager::Instance()->Items[i].IsActive = false;
		}
	}

	//�A�C�e����StateBaseAI�̓����蔻��
	for (int i = 0; i < 5; i++)
	{
		if (Collision.OnCollisionCircleAndCircle(ItemManager::Instance()->Items[i].Position, Collision.ItemSize, StateBaseAI.GetStateBaseAIPos(), Collision.AiSize) == true)
		{
			ItemManager::Instance()->Items[i].IsActive = false;
		}
	}
	
	RuleBaseAI.Update();
	StateBaseAI.Update();

}
void Run::Draw()
{
	//�`��
	Engine::StartDrawing(0);
	RuleBaseAI.Draw();
	StateBaseAI.Draw();
	ItemManager::Instance()->Draw();
	Engine::FinishDrawing();
}
