#pragma once
#include "SDL_gpu.h"
#include "Vec2.h"
#include <cmath>
#include "Projectiles.h"
#include "Vector.h"
class Car
{
public:
	Vec2 position;
	Vec2 velocity;
	Vec2 friction;
	Vec2 facingVector;
	float accelAmount;
	float facingDegrees;
	int Health;
	int Element;

	bool isAccelerating;
	bool player;

	GPU_Image* Image;

	Car()
	{
		facingDegrees = 0.0f;
		isAccelerating = false;
		Image = nullptr;
		accelAmount = 0.0f;
		player = false;
		Health = 0;
	}

	Car(GPU_Image* newImage, int _element)
	{
		facingDegrees = 0.0f;
		isAccelerating = false;
		Image = newImage;
		Element = _element;
		SetElement();
	}

	void Accelerate()
	{
		isAccelerating = true;
	}



	void Update(float dt)
	{
		

		float radiansPerDegree = (float)M_PI / 180.0f;
		facingVector.x = cos(radiansPerDegree * facingDegrees);
		facingVector.y = sin(radiansPerDegree * facingDegrees);
		//get new size after rotating
		position.w = fabs(50 * facingVector.x) + fabs(30 * facingVector.y);
		position.h = fabs(50* facingVector.y)+ fabs(30*facingVector.x);


		///update the velocity if the car is accelerating
		if (isAccelerating)
		{

			Vec2 acceleration = facingVector * accelAmount;
			velocity += acceleration * dt;



			isAccelerating = false;

		}

		Vec2 slidingDirection(-facingVector.y, facingVector.x);
		float slidingSpeed = velocity.Dot(slidingDirection);
		velocity -= slidingSpeed * slidingDirection;
		slidingSpeed *= 0.9f;
		velocity += slidingSpeed * slidingDirection;
			
		

		//update the position and such of the car
		if (player == false) position += velocity;

		//implement drag and friction
		//if (velocity.Magnitude() > 0.0001f)
		
			friction = velocity * 0.05f;
			velocity -= friction;
		

	}

	void SetElement()
	{
		if (Element == 0)
		{
			GPU_SetRGB(Image, 255, 255, 255);
		}
		else if (Element == 1)
		{
			GPU_SetRGB(Image, 255, 0, 0);
		}
		else if (Element == 2)
		{
			GPU_SetRGB(Image, 0, 255, 0);
		}
		else if (Element == 3)
		{
			GPU_SetRGB(Image, 0, 255, 255);
		}
		else if (Element == 4)
		{
			GPU_SetRGB(Image, 200, 0, 200);
		}
		else if (Element == 5)
		{
			GPU_SetRGB(Image, 255, 255, 0);
		}
	}

	virtual void Draw(GPU_Target* screen)
	{
		GPU_BlitRotate(Image, nullptr, screen, position.x, position.y, facingDegrees);

	}


};
