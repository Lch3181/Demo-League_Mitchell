#pragma once
#include <SDL_gpu.h>

class HealthBar
{
public:
	int health;

	HealthBar()
	{
		health = 0;
	}

	void Draw(GPU_Target* screen)
	{
		GPU_Rect back = { 20,20,100,20 };
		SDL_Rect fore = { 20,20,100,20 };
		SDL_Color red = { 255,0,0 };
		GPU_RectangleFilled2(screen, back, red);
	}
};