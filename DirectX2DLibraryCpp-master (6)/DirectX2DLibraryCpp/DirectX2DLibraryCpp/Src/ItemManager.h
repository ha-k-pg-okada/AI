#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include "Engine/Engine.h"
#include "Item.h"

class ItemManager
{
public:
	// �C���X�^���X���擾���邽�߂̃Q�b�^�[
	static ItemManager* Instance()
	{
		// ���̕ϐ������̃N���X�̗B��̃C���X�^���X
		static ItemManager instance;

		return &instance;
	}

public:
	void Initialize();
	void Draw();
	Item* CreateItem(float x, float y);

public:
	Item Items[5];

private:
	ItemManager(){}
};

#endif // !ITEM_MANAGER_H
