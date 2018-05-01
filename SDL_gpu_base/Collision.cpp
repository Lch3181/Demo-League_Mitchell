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

//counter element(player projectile, enemy)
bool isCounter(int player, int enemy)
{
	if (player == 1 && enemy == 2)
	{
		return true;
	}
	else if (player == 2 && enemy == 3)
	{
		return true;
	}
	else if (player == 3 && enemy == 1)
	{
		return true;
	}
	else if (player == 4 && enemy == 5)
	{
		return true;
	}
	else if (player == 5 && enemy == 4)
	{
		return true;
	}
	else
	{
		return false;
	}
}