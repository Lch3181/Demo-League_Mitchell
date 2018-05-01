#pragma once
#include "Car.h"
#include <random>

class Loot
{
public:

	GPU_Image * AmmoBoxImage = GPU_LoadImage("energyRefillCube.png");
	GPU_Image * PowerUpImage = GPU_LoadImage("PowerUp.png");
	GPU_Image * RePairKitImage = GPU_LoadImage("repairKit.png");
	int type;//(1=AmmoBox, 2=PowerUp, 3=RepairKit)
	GPU_Image* image;
	Vec2 Position;


	Loot()
	{
		image = nullptr;
		type = 0;
	}

	bool Drop()
	{
		random_device seed;
		mt19937 mt;
		mt.seed(seed());

		uniform_int<int> rand(1, 100);
		int rd = rand(mt);
		if (rd <= 20)
		{
			image = AmmoBoxImage;
			type = 1;
			return true;
		}
		if (rd > 20 && rd <= 35)
		{
			image = RePairKitImage;
			type = 3;
			return true;
		}
		if (rd > 35 && rd <= 50)
		{
			image = PowerUpImage;
			type = 2;
			return true;
		}


		return false;
	}

	void Update(Car* playerCar)
	{
		Position -= playerCar->velocity;
	}

	void Draw(GPU_Target* screen)
	{
		GPU_BlitRotate(image, nullptr, screen, Position.x, Position.y, 0.0f);
	}

};