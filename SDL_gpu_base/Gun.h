#pragma once
#include "SDL_gpu.h"
#include <cmath>
#include "Car.h"
#include <NFont_gpu.h>
class Gun
{
public:
	//Physical state
	Vec2 position;
	float facingDegrees;
	float initialSpeedOfProjectile;
	int damage;
	float firerate;
	float firerateTimer;
	int Ammo;
	NFont::Color AmmoFontColor;
	//element(1,2,3,4,5)==(fire, naturem, water, dark, light) == (3>1>2>3, 4<>5)
	int Element;

	//renderering
	GPU_Image* Image;
	GPU_Image* projectilesImage;

	Gun(GPU_Image* image,  GPU_Image* _projectilesImage, float sp, int _damage, float _firerate)
	{
		facingDegrees = 0.0f;
		Image = image;
		initialSpeedOfProjectile = sp;
		projectilesImage = _projectilesImage;
		damage = _damage;
		firerateTimer = 0.0f;
		firerate = _firerate;
		Ammo = 200;
		AmmoFontColor = NFont::Color(255, 0, 0);
		GPU_SetRGB(image, 255, 0, 0);
		Element = 1;//default fire
	}

	void refilAmmo(int amount)
	{
		Ammo += amount;
	}

	void Update(Car* car, float dt)
	{
		position = car->position;
		firerateTimer += dt;
		
		if (Element == 0)
		{
			GPU_SetRGB(Image, 255, 255, 255);
			GPU_SetRGB(projectilesImage, 255, 255, 255);
			AmmoFontColor = NFont::Color(255, 255, 255);
		}
		else if (Element == 1)
		{
			GPU_SetRGB(Image, 255, 0, 0);
			GPU_SetRGB(projectilesImage, 255, 0, 0);
			AmmoFontColor = NFont::Color(255, 0, 0);
		}
		else if (Element == 2)
		{
			GPU_SetRGB(Image, 0, 255, 0);
			GPU_SetRGB(projectilesImage, 0, 255, 0);
			AmmoFontColor = NFont::Color(0, 255, 0);
		}
		else if (Element == 3)
		{
			GPU_SetRGB(Image, 0, 255, 255);
			GPU_SetRGB(projectilesImage, 0, 255, 255);
			AmmoFontColor = NFont::Color(0, 255, 255);
		}
		else if (Element == 4)
		{
			GPU_SetRGB(Image, 200, 0, 200);
			GPU_SetRGB(projectilesImage, 200, 0, 200);
			AmmoFontColor = NFont::Color(200, 0, 200);
		}
		else if (Element == 5)
		{
			GPU_SetRGB(Image, 255, 255, 0);
			GPU_SetRGB(projectilesImage, 255, 255, 0);
			AmmoFontColor = NFont::Color(255, 255, 0);
		}
	}

	void Draw(GPU_Target* screen)
	{
		GPU_BlitRotate(Image, nullptr, screen, position.x , position.y, facingDegrees);

	}

	void Fire(Vector<Projectile*>& projectiles); //just a declaration
};