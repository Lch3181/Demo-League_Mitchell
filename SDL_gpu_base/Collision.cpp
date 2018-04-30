#pragma once
#include "Car.h"
#include"PlayerController.h"
#include "Gun.h"
#include "Projectiles.h"
#include "Loot.h"

//(enemy, player)
bool isColliding(Car*  rec1, PlayerController rec2)
{
	Vec2 separation = rec1->position - rec2.car->position;
	return (separation.Magnitude() < rec1->position.w);
}

//(enemy, enemy)
bool isColliding(Car* rec1, Car* rec2)
{
	Vec2 separation = rec1->position - rec2->position;
	return (separation.Magnitude() < rec1->position.w);
}

//(player, loot)
bool isColliding(Car* rec1, Loot* rec2)
{
	Vec2 separation = rec1->position - rec2->Position;
	return (separation.Magnitude() < rec1->position.w);
}

//Fire if InRange(enemy, screen)
bool InRange(Car* rec1)
{
	Vec2 ScreenSize = { 800,600 };
	Vec2 separation = rec1->position - ScreenSize;
	return (separation.Magnitude() < ScreenSize.x);
}
