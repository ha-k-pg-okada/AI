#ifndef ITEM_H
#define ITEM_H

#include "Engine/Engine.h"

class Item
{
public:
	void Initialize(float x, float y);

	void Draw();

public:
	Vec2 Position;
	bool IsActive;
};

#endif // !ITEM_H
