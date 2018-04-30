#pragma once
#include "SDL_gpu.h"
#include <cmath>
#include "Car.h"

class Car;

class Projectile
{
public:
	Vec2 position;
	Vec2 velocity;
	Vec2 facingVector;
	GPU_Image* ProjectilesImage;
	int damage;
	float initialSpeed;
	float facingDegree;
	float removetimer;


	Projectile()
	{
		damage = 0;
		initialSpeed = 0;
		facingDegree = 0.0f;
		removetimer=0.0f;
	}

	Projectile(Vec2 pos, float facingD,int Dmg, float Sp, GPU_Image* image)
	{
		damage = Dmg;
		initialSpeed = Sp;
		removetimer = 0.0f;
		position = pos;
		facingDegree = facingD;
		ProjectilesImage = image;

	}

	Projectile(Vec2 pos, float facingD, float Sp)
	{
		position = pos;
		facingDegree = facingD;
		initialSpeed = Sp;
	}

	void Update(float dt)
	{
		float radiansPerDegree = (float)M_PI / 180.0f;
		facingVector.x = cos(radiansPerDegree * facingDegree);
		facingVector.y = sin(radiansPerDegree * facingDegree);
		//get new size after rotating
		position.w = fabs(50 * facingVector.x) + fabs(30 * facingVector.y);
		position.h = fabs(50 * facingVector.y) + fabs(30 * facingVector.x);



		Vec2 acceleration = facingVector*initialSpeed;
		velocity = acceleration;

		position += velocity;

		//removetimer
		removetimer += dt;
	}

	void Draw(GPU_Target* screen)
	{
		GPU_BlitRotate(ProjectilesImage, nullptr, screen, position.x, position.y, facingDegree);

	}

	bool IsColliding(Car* car);
};
