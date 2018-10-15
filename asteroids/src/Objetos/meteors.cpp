#include "meteors.h"

#include <raylib.h>
#include <cmath>

#include "spaceship.h"
#include "game.h"
#include "menu.h"
#include "app.h"

using namespace app;
using namespace menu;
using namespace game;
using namespace spaceship;

namespace app
{
	namespace meteors
	{
		static const int maxBigMeteors = 4;
		static const int maxMediumMeteors = 8;
		static const int maxSmallMeteors = 16;

		static Meteor bigMeteor[maxBigMeteors];
		static Meteor mediumMeteor[maxMediumMeteors];
		static Meteor smallMeteor[maxSmallMeteors];
		static int midMeteorsCount;
		static int	smallMeteorsCount;
		static int destroyedMeteorsCount;
		static float meteorSpeed;

		//Imagenes y texturas
		static Image meteorImage;
		static Texture2D meteorTexture;

		//Numeros magicos para escalar las textura
		static float bigMeteorScale;
		static Vector2 bigMeteorScalePos;
		static float mediumMeteorScale;
		static Vector2 mediumMeteorScalePos;
		static float smallMeteorScale;
		static Vector2 smallMeteorScalePos;

		//Sonidos 
		static Sound explosionSound;

		static bool init;

		void InitMeteors()
		{

			explosionSound = LoadSound("res/explosion.wav");
			meteorImage = LoadImage("res/asteroide.png");
	
			meteorTexture = LoadTextureFromImage(meteorImage);

			float posx, posy;
			float velx, vely;
			bool correctRange = false;
			init = false;

			destroyedMeteorsCount = 0;
			meteorSpeed = 1;

			for (int i = 0; i < maxBigMeteors; i++)
			{
				posx = GetRandomValue(0, GetScreenWidth());

				while (!correctRange)
				{
					if (posx > GetScreenWidth() / 2 && posx < GetScreenWidth() / 2) posx = GetRandomValue(0, GetScreenWidth());
					else correctRange = true;
				}

				correctRange = false;

				posy = GetRandomValue(0, GetScreenHeight());

				while (!correctRange)
				{
					if (posy > GetScreenHeight() / 2 && posy < GetScreenHeight() / 2)  posy = GetRandomValue(0, GetScreenHeight());
					else correctRange = true;
				}

				bigMeteor[i].position = { posx, posy };

				correctRange = false;
				velx = GetRandomValue(-meteorSpeed, meteorSpeed);
				vely = GetRandomValue(-meteorSpeed, meteorSpeed);

				while (!correctRange)
				{
					if (velx == 0 && vely == 0)
					{
						velx = GetRandomValue(-meteorSpeed, meteorSpeed);
						vely = GetRandomValue(-meteorSpeed, meteorSpeed);
					}
					else correctRange = true;
				}

				bigMeteor[i].speed = { velx, vely };
				bigMeteor[i].radius = (50 * GetScreenWidth()) / 1600;
				bigMeteor[i].active = true;
				bigMeteor[i].color = BLUE;
			}

			for (int i = 0; i < maxMediumMeteors; i++)
			{
				mediumMeteor[i].position = { -100, -100 };
				mediumMeteor[i].speed = { 0, 0 };
				mediumMeteor[i].radius = (30 * GetScreenWidth()) / 1600;
				mediumMeteor[i].active = false;
				mediumMeteor[i].color = BLUE;
			}

			for (int i = 0; i < maxSmallMeteors; i++)
			{
				smallMeteor[i].position = { -100, -100 };
				smallMeteor[i].speed = { 0, 0 };
				smallMeteor[i].radius = (15 * GetScreenWidth()) / 1600;
				smallMeteor[i].active = false;
				smallMeteor[i].color = BLUE;
			}

			midMeteorsCount = 0;
			smallMeteorsCount = 0;

			bigMeteorScale = (GetScreenWidth()* 0.25f) / 1600;
			mediumMeteorScale = (GetScreenWidth()* 0.15f) / 1600;
			smallMeteorScale = (GetScreenWidth()* 0.08f) / 1600;
			bigMeteorScalePos = { (bigMeteorScale*meteorImage.width) / 2 ,(bigMeteorScale*meteorImage.height) / 2 };
			mediumMeteorScalePos = { (mediumMeteorScale*meteorImage.width) / 2 ,(mediumMeteorScale*meteorImage.height) / 2 };
			smallMeteorScalePos = { (smallMeteorScale*meteorImage.width) / 2 ,(smallMeteorScale*meteorImage.height) / 2 };
		}

		void UpdateMeteors()
		{
			if (!gameOver)
			{
				for (int a = 0; a < maxBigMeteors; a++)
				{
					if (CheckCollisionCircles({ ship.collider.x, ship.collider.y }, ship.collider.z, bigMeteor[a].position, bigMeteor[a].radius) && bigMeteor[a].active)
					{
						gameOver = true;
						victory = false;
						currentScreen = GameOver;
					}
				}

				for (int a = 0; a < maxMediumMeteors; a++)
				{
					if (CheckCollisionCircles({ ship.collider.x, ship.collider.y }, ship.collider.z, mediumMeteor[a].position, mediumMeteor[a].radius) && mediumMeteor[a].active)
					{
						gameOver = true;
						victory = false;
						currentScreen = GameOver;
					}
				}

				for (int a = 0; a < maxSmallMeteors; a++)
				{
					if (CheckCollisionCircles({ ship.collider.x, ship.collider.y }, ship.collider.z, smallMeteor[a].position, smallMeteor[a].radius) && smallMeteor[a].active)
					{
						gameOver = true;
						victory = false;
						currentScreen = GameOver;
					}
				}

				// Meteors logic: big meteors
				for (int i = 0; i < maxBigMeteors; i++)
				{
					if (bigMeteor[i].active)
					{
						// Movement
						bigMeteor[i].position.x += bigMeteor[i].speed.x*GetFrameTime() * 100;
						bigMeteor[i].position.y += bigMeteor[i].speed.y*GetFrameTime() * 100;

						// Collision logic: meteor vs wall
						if (bigMeteor[i].position.x > GetScreenWidth() + bigMeteor[i].radius) bigMeteor[i].position.x = -(bigMeteor[i].radius);
						else if (bigMeteor[i].position.x < 0 - bigMeteor[i].radius) bigMeteor[i].position.x = GetScreenWidth() + bigMeteor[i].radius;
						if (bigMeteor[i].position.y > GetScreenHeight() + bigMeteor[i].radius) bigMeteor[i].position.y = -(bigMeteor[i].radius);
						else if (bigMeteor[i].position.y < 0 - bigMeteor[i].radius) bigMeteor[i].position.y = GetScreenHeight() + bigMeteor[i].radius;
					}
				}

				// Meteors logic: medium meteors
				for (int i = 0; i < maxMediumMeteors; i++)
				{
					if (mediumMeteor[i].active)
					{
						// Movement
						mediumMeteor[i].position.x += mediumMeteor[i].speed.x*GetFrameTime() * 100;
						mediumMeteor[i].position.y += mediumMeteor[i].speed.y*GetFrameTime() * 100;

						// Collision logic: meteor vs wall
						if (mediumMeteor[i].position.x > GetScreenWidth() + mediumMeteor[i].radius) mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
						else if (mediumMeteor[i].position.x < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.x = GetScreenWidth() + mediumMeteor[i].radius;
						if (mediumMeteor[i].position.y > GetScreenHeight() + mediumMeteor[i].radius) mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
						else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.y = GetScreenHeight() + mediumMeteor[i].radius;
					}
				}

				// Meteors logic: small meteors
				for (int i = 0; i < maxSmallMeteors; i++)
				{
					if (smallMeteor[i].active)
					{
						// Movement
						smallMeteor[i].position.x += smallMeteor[i].speed.x*GetFrameTime() * 100;
						smallMeteor[i].position.y += smallMeteor[i].speed.y*GetFrameTime() * 100;

						// Collision logic: meteor vs wall
						if (smallMeteor[i].position.x > GetScreenWidth() + smallMeteor[i].radius) smallMeteor[i].position.x = -(smallMeteor[i].radius);
						else if (smallMeteor[i].position.x < 0 - smallMeteor[i].radius) smallMeteor[i].position.x = GetScreenWidth() + smallMeteor[i].radius;
						if (smallMeteor[i].position.y > GetScreenHeight() + smallMeteor[i].radius) smallMeteor[i].position.y = -(smallMeteor[i].radius);
						else if (smallMeteor[i].position.y < 0 - smallMeteor[i].radius) smallMeteor[i].position.y = GetScreenHeight() + smallMeteor[i].radius;
					}
				}

				// Collision logic: player-shoots vs meteors
				for (int i = 0; i < shipMaxShoots; i++)
				{
					if ((shoot[i].active))
					{
						for (int a = 0; a < maxBigMeteors; a++)
						{
							if (bigMeteor[a].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, bigMeteor[a].position, bigMeteor[a].radius))
							{
								PlaySound(explosionSound);
								shoot[i].active = false;
								bigMeteor[a].active = false;
								destroyedMeteorsCount++;

								for (int j = 0; j < 2; j++)
								{
									if (midMeteorsCount % 2 == 0)
									{
										mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x, bigMeteor[a].position.y };
										mediumMeteor[midMeteorsCount].speed = { cos(shoot[i].rotation*DEG2RAD)*meteorSpeed*-1, sin(shoot[i].rotation*DEG2RAD)*meteorSpeed*-1 };
									}
									else
									{
										mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x, bigMeteor[a].position.y };
										mediumMeteor[midMeteorsCount].speed = { cos(shoot[i].rotation*DEG2RAD)*meteorSpeed, sin(shoot[i].rotation*DEG2RAD)*meteorSpeed };
									}

									mediumMeteor[midMeteorsCount].active = true;
									midMeteorsCount++;
								}
								a = maxBigMeteors;
							}
						}

						for (int b = 0; b < maxMediumMeteors; b++)
						{
							if (mediumMeteor[b].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, mediumMeteor[b].position, mediumMeteor[b].radius))
							{
								PlaySound(explosionSound);
								shoot[i].active = false;
								mediumMeteor[b].active = false;
								destroyedMeteorsCount++;

								for (int j = 0; j < 2; j++)
								{
									if (smallMeteorsCount % 2 == 0)
									{
										smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
										smallMeteor[smallMeteorsCount].speed = { cos(shoot[i].rotation*DEG2RAD)*meteorSpeed*-1, sin(shoot[i].rotation*DEG2RAD)*meteorSpeed*-1 };
									}
									else
									{
										smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
										smallMeteor[smallMeteorsCount].speed = { cos(shoot[i].rotation*DEG2RAD)*meteorSpeed, sin(shoot[i].rotation*DEG2RAD)*meteorSpeed };
									}

									smallMeteor[smallMeteorsCount].active = true;
									smallMeteorsCount++;
								}
								b = maxMediumMeteors;
							}
						}

						for (int c = 0; c < maxSmallMeteors; c++)
						{
							if (smallMeteor[c].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, smallMeteor[c].position, smallMeteor[c].radius))
							{
								PlaySound(explosionSound);
								shoot[i].active = false;
								smallMeteor[c].active = false;
								destroyedMeteorsCount++;
								c = maxSmallMeteors;
							}
						}
					}
				}
			}

			if (destroyedMeteorsCount == maxBigMeteors + maxMediumMeteors + maxSmallMeteors)
			{
				victory = true;
				gameOver = true;
				currentScreen = GameOver;
			}
		}

		void DrawMeteors()
		{
			for (int i = 0; i < maxBigMeteors; i++)
			{
				if (bigMeteor[i].active)
				{
					DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, DARKGRAY);
					DrawTextureEx(meteorTexture, { bigMeteor[i].position.x - bigMeteorScalePos.x,bigMeteor[i].position.y - bigMeteorScalePos.y }, 0, bigMeteorScale, WHITE);
				}
				else DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, BLANK);
			}

			for (int i = 0; i < maxMediumMeteors; i++)
			{
				if (mediumMeteor[i].active)
				{
					DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, GRAY);
					DrawTextureEx(meteorTexture, { mediumMeteor[i].position.x - mediumMeteorScalePos.x,mediumMeteor[i].position.y - mediumMeteorScalePos.y }, 0, mediumMeteorScale, WHITE);
				}
				else DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, BLANK);
			}

			for (int i = 0; i < maxSmallMeteors; i++)
			{
				if (smallMeteor[i].active)
				{
					DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, GRAY);
					DrawTextureEx(meteorTexture, { smallMeteor[i].position.x - smallMeteorScalePos.x,smallMeteor[i].position.y - smallMeteorScalePos.y }, 0, smallMeteorScale, WHITE);
				}
				else DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, BLANK);
			}
		}
	}
}