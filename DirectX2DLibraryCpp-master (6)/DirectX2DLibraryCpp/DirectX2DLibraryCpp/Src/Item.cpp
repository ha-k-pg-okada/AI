#include"Item.h"

void Item::Initialize(float x, float y)
{
	Position = Vec2(x, y);
	IsActive = false;
}
void Item::Draw()
{
	Engine::DrawTexture(Position.X, Position.Y, "Item", 255, 0.0f, 5.0f, 5.0f);
	Engine::DrawRect(Position.X + 22.5f, Position.Y + 22.5f, 3.0f, 3.0f, 0x0000ff);
}