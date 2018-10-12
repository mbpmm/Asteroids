#include "game.h"

#include <raylib.h>
#include <cmath>

#include "menu.h"
#include "app.h"

using namespace app;
using namespace menu;

namespace app
{
	namespace game
	{
		struct Spaceship
		{
			Vector2 position;
			Vector2 acceleration;
			float rotation;
			Vector3 collider;
			Color color;
		};

		struct Shoot
		{
			Vector2 position;
			Vector2 speed;
			float radius;
			float rotation;
			bool active;
			Color color;
		};

		struct Meteor
		{
			Vector2 position;
			Vector2 speed;
			float radius;
			bool active;
			Color color;
		};

		extern bool victory=false;
		bool gameOver;
		const int maxBigMeteors = 4;
		const int maxMediumMeteors = 8;
		const int maxSmallMeteors = 16;
		const int shipMaxShoots = 10;
		Spaceship ship;
		float shipBaseSize = 20.0f;
		float shipSpeed = 100.0f;
		float shipHeight;
		Shoot shoot[shipMaxShoots];
		Meteor bigMeteor[maxBigMeteors];
		Meteor mediumMeteor[maxMediumMeteors];
		Meteor smallMeteor[maxSmallMeteors];
		int midMeteorsCount;
		int	smallMeteorsCount;
		int destroyedMeteorsCount;
		float meteorSpeed;
		Vector2 v1;
		Vector2 v2;
		float prodVect;
		float modv1;
		float modv2;
		Vector2 normAcel;
		char text[] = "CLICK DER: Acelerar, CLICK IZQ: Disparar, P: Pausar musica.";
		int sizeText;
		float textPositionX;
		float textPositionY;

		//Imagenes y texturas

		Image shipImage;
		Image asteroidImage;
		Image shootImage;
		Image backImage;
		Texture2D backTexture;
		Texture2D shootTexture;
		Texture2D shipTexture;
		Texture2D asteroidTexture;
		Rectangle sourceRect;
		Rectangle destRec;

		//Numeros magicos para escalar las texturas

		float shipScale;
		float shootScale;
		Vector2 shootScalePos;
		float bigMeteorScale;
		Vector2 bigMeteorScalePos;
		float mediumMeteorScale;
		Vector2 mediumMeteorScalePos;
		float smallMeteorScale;
		Vector2 smallMeteorScalePos;

		//Sonidos 
		Sound shootSound;
		Sound explosionSound;

		//Boton pausa

		Rectangle botonPausa1;
		Rectangle botonPausa2;
		Color colorRect;
		Vector2 mousePoint;

		bool init;

		void InitValues()
		{
			sizeText = (GetScreenWidth() * 20) / 1600;
			textPositionX = GetScreenWidth()*0.01f;
			textPositionY = GetScreenHeight() * 0.97f;

			shootSound = LoadSound("res/shoot.wav");
			explosionSound = LoadSound("res/explosion.wav");
			shootImage = LoadImage("res/shoot.png");
			shipImage = LoadImage("res/nave2.png");
			asteroidImage= LoadImage("res/asteroide.png");
			backImage = LoadImage("res/fondo.png");

			//init boton pausa
			botonPausa1.x = GetScreenWidth()*0.96f;
			botonPausa1.y = GetScreenHeight()*0.02f;
			botonPausa1.height = (GetScreenWidth() * 40)/1600;
			botonPausa1.width = (GetScreenWidth() * 15) / 1600;
			botonPausa2.x = GetScreenWidth()*0.975f;
			botonPausa2.y = GetScreenHeight()*0.02f;
			botonPausa2.height = (GetScreenWidth() * 40) / 1600;
			botonPausa2.width = (GetScreenWidth() * 15) / 1600;
			colorRect = GRAY;


			shipTexture = LoadTextureFromImage(shipImage);
			asteroidTexture = LoadTextureFromImage(asteroidImage);
			shootTexture = LoadTextureFromImage(shootImage);
			backTexture = LoadTextureFromImage(backImage);
			sourceRect.height = shipTexture.height;
			sourceRect.width = shipTexture.width;
			sourceRect.x = 0;
			sourceRect.y = 0;

			float posx, posy;
			float velx, vely;
			bool correctRange = false;
			init = false;

			shipHeight = (shipBaseSize / 2) / tanf(20 * DEG2RAD);

			ship.position.x = GetScreenWidth() / 2;
			ship.position.y = GetScreenHeight() / 2 - shipHeight / 2;
			ship.acceleration = { 0, 0 };
			ship.rotation = 0;
			ship.collider = { ship.position.x + sin(ship.rotation*DEG2RAD)*(shipHeight / 2.5f), ship.position.y - cos(ship.rotation*DEG2RAD)*(shipHeight / 2.5f), 24 };
			ship.color = LIGHTGRAY;

			for (int i = 0; i < shipMaxShoots; i++)
			{
				shoot[i].position = { 0, 0 };
				shoot[i].speed = { 0, 0 };
				shoot[i].radius = 3;
				shoot[i].active = false;
				shoot[i].color = WHITE;
			}

			destroyedMeteorsCount = 0;
			meteorSpeed = 1;

			for (int i = 0; i < maxBigMeteors; i++)
			{
				posx = GetRandomValue(0, GetScreenWidth());

				while (!correctRange)
				{
					if (posx > GetScreenWidth() / 2  && posx < GetScreenWidth() / 2 ) posx = GetRandomValue(0, GetScreenWidth());
					else correctRange = true;
				}

				correctRange = false;

				posy = GetRandomValue(0, GetScreenHeight());

				while (!correctRange)
				{
					if (posy > GetScreenHeight() / 2  && posy < GetScreenHeight() / 2 )  posy = GetRandomValue(0, GetScreenHeight());
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
				bigMeteor[i].radius = (50*GetScreenWidth())/1600;
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

			shipScale = (GetScreenWidth()* 0.08f) / 1600;
			shootScale= (GetScreenWidth()* 1.0f) / 1600;
			bigMeteorScale = (GetScreenWidth()* 0.25f) / 1600;
			mediumMeteorScale = (GetScreenWidth()* 0.15f) / 1600;
			smallMeteorScale = (GetScreenWidth()* 0.08f) / 1600;
			bigMeteorScalePos = { (bigMeteorScale*asteroidImage.width) / 2 ,(bigMeteorScale*asteroidImage.height) / 2 };
			mediumMeteorScalePos = { (mediumMeteorScale*asteroidImage.width) / 2 ,(mediumMeteorScale*asteroidImage.height) / 2 };
			smallMeteorScalePos = { (smallMeteorScale*asteroidImage.width) / 2 ,(smallMeteorScale*asteroidImage.height) / 2 };
			shootScalePos = { (shootScale*shootImage.width) / 2 ,(shootScale*shootImage.height) / 2 };

			destRec.width = shipTexture.width*shipScale;
			destRec.height = shipTexture.height*shipScale;

		}

		static void RotationAngle()
		{
			v1.x = 0;
			v1.y = 0.0f - ship.position.y;

			v2.x = GetMouseX() - ship.position.x;
			v2.y = GetMouseY() - ship.position.y;

			prodVect = v1.x*v2.x + v1.y*v2.y;
			modv1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
			modv2 = sqrt(pow(v2.x, 2) + pow(v2.y, 2));

			ship.rotation = acos(prodVect / (modv1*modv2));
			ship.rotation *= RAD2DEG;

			if (GetMouseX() < ship.position.x)
			{
				ship.rotation = 360 - ship.rotation;
			}
		}

		static void Input()
		{
			RotationAngle();
			mousePoint = GetMousePosition();
			//if (IsKeyDown(KEY_LEFT)) ship.rotation -= 350 * GetFrameTime();
			//if (IsKeyDown(KEY_RIGHT)) ship.rotation += 350 * GetFrameTime();

			if (CheckCollisionPointRec(mousePoint, botonPausa1))
			{
				colorRect.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = Pause;
			}
			else colorRect.a = 255;

			if (CheckCollisionPointRec(mousePoint, botonPausa2))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = Pause;
			}

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(shootSound);
				init = true;
				for (int i = 0; i < shipMaxShoots; i++)
				{
					if (!shoot[i].active)
					{
						shoot[i].position = { ship.position.x + sin(ship.rotation*DEG2RAD)*(shipHeight), ship.position.y - cos(ship.rotation*DEG2RAD)*(shipHeight) };
						shoot[i].active = true;
						shoot[i].speed.x = 7.5*sin(ship.rotation*DEG2RAD)*shipSpeed;
						shoot[i].speed.y = 7.5*cos(ship.rotation*DEG2RAD)*shipSpeed;
						shoot[i].rotation = ship.rotation;
						break;
					}
				}
			}

			// Player acceleration
			if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
			{
				normAcel.x = v2.x / modv2;
				normAcel.y = v2.y / modv2;
				ship.acceleration.x += normAcel.x*((10.0f*GetFrameTime()*GetScreenWidth()) / 1600);
				ship.acceleration.y += normAcel.y*((10.0f*GetFrameTime()*GetScreenWidth()) / 1600);
				
				/*if (ship.acceleration > 0) ship.acceleration -= (200.0f*GetFrameTime()*GetScreenWidth()) / 1600;
				else if (ship.acceleration < 0) ship.acceleration = 0;*/

			}
			
			
			
			
			

			/*if (IsKeyPressed(KEY_ESCAPE))
			{
				currentScreen = Menu;
				ResetValues();
			}*/
		}

		

		static void Update()
		{

			if (!gameOver)
			{
				// Player logic: speed
				//ship.speed.x = (sin(ship.rotation*DEG2RAD)*shipSpeed*GetFrameTime() * 150*GetScreenWidth())/1600;
				//ship.speed.y = (cos(ship.rotation*DEG2RAD)*shipSpeed*GetFrameTime() * 150 * GetScreenWidth()) / 1600;

				// Player logic: movement
				ship.position.x += (ship.acceleration.x*GetFrameTime()*100);
				ship.position.y += (ship.acceleration.y*GetFrameTime()*100);
				destRec.x = ship.position.x;
				destRec.y = ship.position.y;


				// Collision logic: player vs walls
				if (ship.position.x > GetScreenWidth() + shipHeight) ship.position.x = -(shipHeight);
				else if (ship.position.x < -(shipHeight)) ship.position.x = GetScreenWidth() + shipHeight;
				if (ship.position.y > (GetScreenHeight() + shipHeight)) ship.position.y = -(shipHeight);
				else if (ship.position.y < -(shipHeight)) ship.position.y = GetScreenHeight() + shipHeight;

				// Shot logic
				for (int i = 0; i < shipMaxShoots; i++)
				{
					if (shoot[i].active)
					{
						// Movement
						shoot[i].position.x += shoot[i].speed.x*GetFrameTime();
						shoot[i].position.y -= shoot[i].speed.y*GetFrameTime();

						// Collision logic: shoot vs walls
						if (shoot[i].position.x > GetScreenWidth() + shoot[i].radius)
						{
							shoot[i].active = false;
						}
						else if (shoot[i].position.x < 0 - shoot[i].radius)
						{
							shoot[i].active = false;
						}
						if (shoot[i].position.y > GetScreenHeight() + shoot[i].radius)
						{
							shoot[i].active = false;
						}
						else if (shoot[i].position.y < 0 - shoot[i].radius)
						{
							shoot[i].active = false;
						}
					}
				}

				ship.collider = { ship.position.x + sin(ship.rotation*DEG2RAD)*(shipHeight / 2.5f), ship.position.y - cos(ship.rotation*DEG2RAD)*(shipHeight / 2.5f), 24 };

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
						bigMeteor[i].position.x += bigMeteor[i].speed.x*GetFrameTime()*100;
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

		void UpdateFrame()
		{
			Input();
			Update();
		}

		void Draw()
		{
			ClearBackground(BLANK);
			DrawTexture(backTexture,0,0,WHITE);
			Vector2 v1 = { ship.position.x + sinf(ship.rotation*DEG2RAD)*(shipHeight), ship.position.y - cosf(ship.rotation*DEG2RAD)*(shipHeight) };
			Vector2 v2 = { ship.position.x - cosf(ship.rotation*DEG2RAD)*(shipBaseSize / 2), ship.position.y - sinf(ship.rotation*DEG2RAD)*(shipBaseSize / 2) };
			Vector2 v3 = { ship.position.x + cosf(ship.rotation*DEG2RAD)*(shipBaseSize / 2), ship.position.y + sinf(ship.rotation*DEG2RAD)*(shipBaseSize / 2) };
			//DrawTriangle(v1, v2, v3, DARKGREEN);
			DrawTexturePro(shipTexture, sourceRect, destRec, { (shipTexture.width/2)*shipScale,(shipTexture.height/2)*shipScale }, ship.rotation, WHITE);
			
			for (int i = 0; i < maxBigMeteors; i++)
			{
				if (bigMeteor[i].active)
				{
					DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, DARKGRAY);
					DrawTextureEx(asteroidTexture, { bigMeteor[i].position.x - bigMeteorScalePos.x,bigMeteor[i].position.y - bigMeteorScalePos.y }, 0, bigMeteorScale, WHITE);
				}
				else DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, BLANK);
			}

			for (int i = 0; i < maxMediumMeteors; i++)
			{
				if (mediumMeteor[i].active)
				{
					DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, GRAY);
					DrawTextureEx(asteroidTexture, { mediumMeteor[i].position.x - mediumMeteorScalePos.x,mediumMeteor[i].position.y - mediumMeteorScalePos.y }, 0, mediumMeteorScale, WHITE);
				}
				else DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, BLANK);
			}

			for (int i = 0; i < maxSmallMeteors; i++)
			{
				if (smallMeteor[i].active)
				{
					DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, GRAY);
					DrawTextureEx(asteroidTexture, { smallMeteor[i].position.x - smallMeteorScalePos.x,smallMeteor[i].position.y - smallMeteorScalePos.y }, 0, smallMeteorScale, WHITE);
				}
				else DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, BLANK);
			}
			for (int i = 0; i < shipMaxShoots; i++)
			{
				if (shoot[i].active)
				{
					DrawCircleV(shoot[i].position, shoot[i].radius, WHITE);
					DrawTextureEx(shootTexture, { shoot[i].position.x-shootScalePos.x ,shoot[i].position.y-shootScalePos.y  }, 0, shootScale, WHITE);
				}
			}

			DrawRectangleRec(botonPausa1, colorRect);
			DrawRectangleRec(botonPausa2, colorRect);
			DrawText(text, textPositionX, textPositionY, sizeText, PURPLE);
		}

		void ResetValues()
		{
			InitValues();
			gameOver = false;
		}
	}
}