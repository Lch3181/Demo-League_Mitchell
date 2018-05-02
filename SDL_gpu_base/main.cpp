#pragma once
#include <iostream>
#include "SDL_gpu.h"
#include "Vector.h"
#include"PlayerController.h"
#include "Car.h"
#include <random>
#include <cmath>
#include <NFont_gpu.h>
#include"Loot.h"
#include "ReadWriteFile.h"
using namespace std;

//functions
bool isColliding(Car* rec1, PlayerController rec2);//(enemry, player)
bool isColliding(Car* rec1, Car* rec2);//(enemy, enemry)
bool InRange(Car* rec1);//(enemy, screen)
bool isColliding(Car* rec1, Loot* rec2);//player car, loot
bool isCounter(int player, int enemy);//counter element(player projectile, enemy)

int main(int argc, char* argv[])
{
	GPU_Target* screen = GPU_Init(800, 600, GPU_DEFAULT_INIT_FLAGS);
	if (screen == nullptr)
		return 1;

	SDL_SetWindowTitle(SDL_GetWindowFromID(screen->context->windowID), "Demolition League");

	//set up controllers for the players
	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

	SDL_GameController* player1Controller = nullptr;

	//loop through all of the joysticks to find the player's controller
	int numJoysticks = SDL_NumJoysticks();
	for (int i = 0; i < numJoysticks; ++i)
	{
		if (SDL_IsGameController(i))
		{
			//store the controller somewhere
			player1Controller = SDL_GameControllerOpen(i);
			cout << "We got a game controller!" << endl;

			break;
		}
	}

	//load Images
	GPU_Image* carImage = GPU_LoadImage("car.png");
	if (carImage == nullptr)
		return 2;

	GPU_Image* enemyCarImage = GPU_LoadImage("car.png");

	GPU_Image* gun1Image = GPU_LoadImage("gun1.png");
	if (gun1Image == nullptr)
		return 2;
	GPU_Image* enemyGunImage = GPU_LoadImage("gun1.png");

	GPU_Image* backgroundImage = GPU_LoadImage("background.png");
	if (backgroundImage == nullptr)
		return 2;

	GPU_Image* Projectile1Image = GPU_LoadImage("Projectiles1.png");
	GPU_SetRGB(Projectile1Image, 255, 0, 0);
	if (Projectile1Image == nullptr) return 2;

	GPU_Image* enemyProjectileImage = GPU_LoadImage("Projectiles1.png");

	NFont font;
	font.load("FreeSans.ttf", 14);//load the font at size 14

	int counter = 0;

	//add player info
	PlayerController player;
	player.CreateCar(carImage, 0);
	player.controller = player1Controller;
	player.car->accelAmount = 25.0f;
	player.car->position.w = 50.0f;
	player.car->position.h = 30.0f;
	player.CreateGun(gun1Image, Projectile1Image, 10.0f, 50, 0.05f);
	player.gun->position.w = 30.0f;
	player.car->player = true;
	player.car->Health = 1000;
	bool DarkMode = false;//switich gun's element between dark and light
	//GPU_SetRGB(carImage, 255, 0, 0);//change color of the image
	int Score = 0;
	float ScoreScale = 1.0f;//scale up when time past
	int temp = 2;
	int EnemyElement = 0;

	//local score leaderboard
	LocalScoreLeaderboard* localScoreLeaderboard= new LocalScoreLeaderboard();
	bool WriteScoreOnce = false;
	//set camera
	Vec2 camera(player.car->position.x, player.car->position.y);
	camera.w = 5000;
	camera.h = 5000;

	//add enemy
	Vector<Car*> enemies;
	Vector<Gun*> enemiesGun;
	unsigned int EnemiesNumbers = 15;

	//Pause game for upgrade and check stat
	bool Pause = false;

	//add lootBox
	Vector<Loot*> loot;

	//add enemy projectile
	Vector<Projectile*> enemyprojectiles;

	//add projectiles
	Vector<Projectile*> projectiles;

	//get random number
	random_device seed;
	mt19937 mt;
	mt.seed(seed());

	//add mouse stats
	Uint32 mousestats = SDL_GetMouseState(NULL, NULL);

	// Array of boolean values: Is a key held down or not?
	const Uint8* keystates = SDL_GetKeyboardState(nullptr);

	float dt = 0.01f;
	float accumulator = 0.0f;

	//set player's car position
	player.car->position.x = 400;
	player.car->position.y = 300;
	player.car->facingDegrees = 0;

	//get player's gun position
	player.gun->position = player.car->position;

	SDL_Event event;
	bool done = false;
	while (!done)
	{
		Uint32 frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				done = true;
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					done = true;
				if (event.key.keysym.sym == SDLK_p)
					Pause = !Pause;
				if (event.key.keysym.sym == SDLK_r)
				{
					if (player.gun->Ammo >= 100)
					{
						projectiles.clear();
						enemyprojectiles.clear();
						player.gun->Ammo -= 100;
					}
				}
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					DarkMode = !DarkMode;
					if (DarkMode)
					{
						player.gun->Element = 4;
					}
					else
					{
						player.gun->Element = 5;
					}
				}
			}
		}


		//clean old frame
		GPU_Clear(screen);

		//draw background
		GPU_Blit(backgroundImage, nullptr, screen, camera.x, camera.y);
		if (player.car->Health > 0)//keep updating objects if player is still alive
		{


			//spawn enemies
			for (unsigned int i = enemies.size(); i < EnemiesNumbers; i++)
			{
				Car* car = new Car(enemyCarImage, EnemyElement);
				int gunDamage = 1 * (int)ScoreScale;
				Gun* gun = new Gun(enemyGunImage, enemyProjectileImage, 3.0f, gunDamage, 1.0f);
				gun->Element = 0;
				car->accelAmount = 10.0f;
				car->position.w = 20.0f;
				car->position.h = 30.0f;
				car->Health = 100 * (int)ScoreScale;
				gun->Ammo = 2000;
				uniform_real<float> rand(0, 360);//degree
				car->position.x = player.car->position.x + (800 * (float)cos(rand(mt)));
				car->position.y = player.car->position.y + (800 * (float)sin(rand(mt)));
				enemies.push_back(car);
				enemiesGun.push_back(gun);

			}

			//colider
			for (unsigned int i = 0; i < enemies.size(); ++i)
			{

				//isColliding(enemies, player)
				if (isColliding(enemies[i], player))
				{

					Vec2 speration = enemies[i]->position - player.car->position;
					speration.Normalize();

					player.car->velocity = -enemies[i]->velocity.Magnitude() * speration * 1.2f;
					enemies[i]->velocity = player.car->velocity.Magnitude() * speration  * 1.2f;

					player.car->Health -= 20;
					enemies[i]->Health -= 100;
					if (enemies[i]->Health <= 0)
					{
						Score += enemies[i]->Health;
						//loot drop
						Loot* _loot = new Loot();
						//drop ammobox(energy)
						if (_loot->Drop())
						{
							_loot->Position = enemies[i]->position;
							_loot->Position.w = 25.0f;
							loot.push_back(_loot);
						}


						delete enemies[i];
						enemies.remove_at(i);
						delete enemiesGun[i];
						enemiesGun.remove_at(i);
						break;
					}
					break;
				}

				//isCOlliding(enemies, enemies)
				for (unsigned int j = 0; j < enemies.size(); ++j)
				{
					if (i == j)
						continue;
					if (isColliding(enemies[i], enemies[j]))
					{

						Vec2 speration = enemies[j]->position - enemies[i]->position;
						speration.Normalize();

						enemies[j]->velocity = enemies[j]->velocity.Magnitude() * speration * 1.3f;
						enemies[i]->velocity = -enemies[i]->velocity.Magnitude() * speration  * 1.3f;

						enemies[j]->isAccelerating = false;
					}
				}

				//isColliding(enemies, projectiles)
				for (unsigned int j = 0; j < projectiles.size(); ++j)
				{
					if (projectiles[j]->Projectile::IsColliding(enemies[i]))
					{


						//-hitpoint or smth
						if (isCounter(player.gun->Element, EnemyElement))
						{
							cout << 1 << endl;
							enemies[i]->Health -= projectiles[j]->damage * 2;
							Score += projectiles[j]->damage * 2;
							if (enemies[i]->Health <= 0)
							{
								Score += enemies[i]->Health * 2;

							}
						}
						else
						{
							enemies[i]->Health -= projectiles[j]->damage;
							Score += projectiles[j]->damage;
							if (enemies[i]->Health <= 0)
							{
								Score += enemies[i]->Health;
							}
						}

						if (enemies[i]->Health <= 0)
						{

							//loot drop
							Loot* _loot = new Loot();
							//drop ammobox(energy)
							if (_loot->Drop())
							{
								_loot->Position = enemies[i]->position;
								_loot->Position.w = 25.0f;
								loot.push_back(_loot);
							}

							delete enemies[i];
							enemies.remove_at(i);
							delete enemiesGun[i];
							enemiesGun.remove_at(i);
							i++;
							break;
						}
						delete projectiles[j];
						projectiles.remove_at(j);
						--j;
						break;
					}
				}

				//isColliding(player, enemyprojectiles)
				for (unsigned int j = 0; j < enemyprojectiles.size(); ++j)
				{
					if (enemyprojectiles[j]->Projectile::IsColliding(player.car))
					{
						player.car->Health -= enemyprojectiles[j]->damage;
						delete enemyprojectiles[j];
						enemyprojectiles.remove_at(j);
						j++;
						break;
					}
				}

				//isCollising(player, loot)
				for (unsigned int j = 0; j < loot.size(); ++j)
				{
					if (isColliding(player.car, loot[j]))
					{
						if (loot[j]->type == 1) player.gun->Ammo += 50;
						else if (loot[j]->type == 2)player.gun->damage += 5;

						if (loot[j]->type == 3 && player.car->Health + 100 <= 1000)player.car->Health += 100;
						else if (loot[j]->type == 3 && player.car->Health + 100 > 1000)player.car->Health = 1000;

						delete loot[j];
						loot.remove_at(j);
						j++;
						break;
					}
				}

			}

			//player control
			player.HandleInputState(keystates, event, projectiles);

			//camera (need to move to a new header file)
			if (camera.x >= camera.w / 2)
				camera.x = 1500;
			if (camera.x <= 1000)
				camera.x = camera.w / 2;
			if (camera.y >= camera.h / 2)
				camera.y = 1500;
			if (camera.y <= 1000)
				camera.y = camera.h / 2;

			// Update world objects
			while (accumulator > dt)
			{
				//player
				player.car->Update(dt);
				player.gun->Update(player.car, dt);
				for (unsigned int i = 0; i < projectiles.size(); ++i)
				{
					projectiles[i]->Update(dt);
					//remove projectile after amount of time
					if (projectiles[i]->removetimer >= 0.5)
					{
						delete projectiles[i];
						projectiles.remove_at(i);
						--i;
					}
				}

				//enemy
				for (unsigned int i = 0; i < enemies.size(); ++i)
				{
					//get degree between player and enemies
					float EnemyFacingPlayerDegree = atan2(player.car->position.y - enemies[i]->position.y, player.car->position.x - enemies[i]->position.x);

					enemiesGun[i]->Update(enemies[i], dt);
					enemiesGun[i]->facingDegrees = enemies[i]->facingDegrees;
					if (InRange(enemies[i]))
						enemiesGun[i]->Fire(enemyprojectiles);

					enemies[i]->facingDegrees = EnemyFacingPlayerDegree * 180 / (float)M_PI;
					enemies[i]->position -= player.car->velocity;
					enemies[i]->Update(dt);
					enemies[i]->isAccelerating = true;
					enemiesGun[i]->firerateTimer += dt;


				}

				for (unsigned int i = 0; i < enemyprojectiles.size(); ++i)
				{
					enemyprojectiles[i]->position -= player.car->velocity;
					enemyprojectiles[i]->Update(dt);

					//remove projectile after amount of time
					if (enemyprojectiles[i]->removetimer >= 5.0)
					{
						delete enemyprojectiles[i];
						enemyprojectiles.remove_at(i);
						--i;
					}
				}

				//when enemy level increase
				if (ScoreScale >= temp)
				{
					uniform_int<int> random(1, 5);
					EnemyElement = random(mt);
					temp++;
				}

				//loot
				for (unsigned int i = 0; i < loot.size(); ++i)
				{
					loot[i]->Position -= player.car->velocity;
				}


				//update camera
				camera -= player.car->velocity;

				accumulator -= dt;
			}



			//increase score when time past

			ScoreScale += dt * 0.1f;
			Score += (int)ScoreScale;


			//drawing

			player.car->Draw(screen);
			player.gun->Draw(screen);



		}//end of player.health>0

		//drawing
		for (unsigned int i = 0; i < enemies.size(); ++i)
		{
			enemies[i]->Draw(screen);
			enemiesGun[i]->Draw(screen);
		}
		for (unsigned int i = 0; i < projectiles.size(); ++i)
		{
			projectiles[i]->Draw(screen);
		}
		for (unsigned int i = 0; i < enemyprojectiles.size(); ++i)
		{
			enemyprojectiles[i]->Draw(screen);
		}
		for (unsigned int i = 0; i < loot.size(); ++i)
		{
			loot[i]->Draw(screen);
		}



		//font
		if (player.car->Health > 0)
		{
			font.draw(screen, 350, 20, NFont::Color(255, 255, 255), "Score: %d", Score);//Score
			font.draw(screen, 20, 20, NFont::Color(255 * abs(((1000.0f - (float)player.car->Health) / 1000.0f)), 255 * abs(1 - ((1000.0f - (float)player.car->Health) / 1000.0f)), 0), "Health: %d", player.car->Health);//player's Health amount
			font.draw(screen, 20, 40, player.gun->AmmoFontColor, "Energy: %d", player.gun->Ammo);//gun1's ammo amount
			font.draw(screen, 20, 60, player.gun->AmmoFontColor, "Damage: %d", player.gun->damage);//gun1's ammo amount
			if (Score < 1000) font.draw(screen, 350, 250, NFont::Color(150, 150, 150), "Try your best!!!!!");//title screen when game start


		}
		else
		{
			font.draw(screen, 20, 20, NFont::Color(255, 0, 0), "Health: %d", player.car->Health);//player ran out of Health amount
			//Score leaderboard
			if (!WriteScoreOnce)
			{
				localScoreLeaderboard->ReadFile("Demo League");
				localScoreLeaderboard->AddScore(Score);
				localScoreLeaderboard->GetLeaderboard();
				localScoreLeaderboard->SortLearderboard();
				localScoreLeaderboard->WriteFile("Demo League");
				WriteScoreOnce = true;
			}
			localScoreLeaderboard->Draw(screen);
			font.draw(screen, 350, 100, NFont::Color(255, 255, 255), "Final Score: %d", Score);//Final Score

		}
		font.draw(screen, 350, 5, NFont::Color(255, 255, 255), "Level : %d", (int)ScoreScale);

		//Draw stuff
		GPU_Flip(screen);

		Uint32 frameEnd = SDL_GetTicks();

		//how much more time do we need to delay
		Sint32 delay = 1000 / 60 - (frameEnd - frameStart);

		//cd
		if (delay > 0)
			SDL_Delay(delay);

		frameEnd = SDL_GetTicks();

		//find out how much time passed (in second)
		accumulator += (frameEnd - frameStart) / 1000.0f;

		//test
	}

	//free stuff and close resources
	GPU_FreeImage(carImage);
	GPU_FreeImage(gun1Image);
	GPU_FreeImage(backgroundImage);
	SDL_GameControllerClose(player1Controller);


	GPU_Quit();

	return 0;
}