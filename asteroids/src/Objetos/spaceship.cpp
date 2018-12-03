#include "spaceship.h"

#include <cmath>

#include "pause.h"
#include "game.h"
#include "app.h"

using namespace app;
using namespace game;
using namespace pause;

namespace app
{
	namespace spaceship
	{
		extern const int shipMaxShoots = 10;
		Spaceship ship;
		static float shipBaseSize = 20.0f;
		static float shipSpeed = 100.0f;
		static float shipAcc = 10.0f;
		static float shipHeight;
		static const float shipColliderZ = 24.0f;
		static const float speedBoost = 7.5f; //variable para que la velocidad se ajuste al GetFrameTime
		Shoot shoot[shipMaxShoots];
	
		static Vector2 v1;
		static Vector2 v2;
		static float prodVect;
		static float modv1;
		static float modv2;
		static Vector2 normAcel;

		//Imagenes y texturas
		static Image shipImage;
		static Image shootImage;
		static Texture2D backTexture;
		static Texture2D shootTexture;
		static Texture2D shipTexture;
		static Rectangle sourceRect;
		static Rectangle destRec;

		//Escala las texturas
		static float shipScale;
		static float shootScale;
		static Vector2 shootScalePos;

		//Sonidos 
		static Sound shootSound;
		bool pauseSoundShoot = false;

		static Vector2 mousePoint;

		static bool init;
		static int scaleAux = 1600;

		void InitSpaceship()
		{
			shootSound = LoadSound("res/shoot.wav");
			shootImage = LoadImage("res/shoot.png");
			shipImage = LoadImage("res/nave2.png");


			shipTexture = LoadTextureFromImage(shipImage);
			shootTexture = LoadTextureFromImage(shootImage);
			sourceRect.height = shipTexture.height;
			sourceRect.width = shipTexture.width;
			sourceRect.x = 0;
			sourceRect.y = 0;

			shipHeight = (shipBaseSize / 2) / tanf(20 * DEG2RAD);

			ship.position.x = GetScreenWidth() / 2;
			ship.position.y = GetScreenHeight() / 2 - shipHeight / 2;
			ship.acceleration = { 0, 0 };
			ship.rotation = 0;
			ship.collider = { ship.position.x + sin(ship.rotation*DEG2RAD)*(shipHeight / 2.5f), ship.position.y - cos(ship.rotation*DEG2RAD)*(shipHeight / 2.5f), shipColliderZ };
			ship.color = LIGHTGRAY;

			for (int i = 0; i < shipMaxShoots; i++)
			{
				shoot[i].position = { 0, 0 };
				shoot[i].speed = { 0, 0 };
				shoot[i].radius = 3;
				shoot[i].active = false;
				shoot[i].color = WHITE;
			}

			shipScale = (GetScreenWidth()* 0.08f) / scaleAux;
			shootScale = (GetScreenWidth()* 1.0f) / scaleAux;
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

		void Input()
		{
			RotationAngle();
			mousePoint = GetMousePosition();

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				if (!pauseSoundShoot)
				{
					PlaySound(shootSound);
				}
				else
				{
					PauseSound(shootSound);
				}
				init = true;
				for (int i = 0; i < shipMaxShoots; i++)
				{
					if (!shoot[i].active)
					{
						shoot[i].position = { ship.position.x + sin(ship.rotation*DEG2RAD)*(shipHeight), ship.position.y - cos(ship.rotation*DEG2RAD)*(shipHeight) };
						shoot[i].active = true;
						shoot[i].speed.x = speedBoost *sin(ship.rotation*DEG2RAD)*shipSpeed;
						shoot[i].speed.y = speedBoost *cos(ship.rotation*DEG2RAD)*shipSpeed;
						shoot[i].rotation = ship.rotation;
						break;
					}
				}
			}
			if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
			{
				normAcel.x = v2.x / modv2;
				normAcel.y = v2.y / modv2;
				ship.acceleration.x += normAcel.x*((shipAcc*GetFrameTime()*GetScreenWidth()) / scaleAux);
				ship.acceleration.y += normAcel.y*((shipAcc*GetFrameTime()*GetScreenWidth()) / scaleAux);
			}
		}



		void Update()
		{

			if (!gameOver)
			{
				// Player logic: movement
				ship.position.x += (ship.acceleration.x*GetFrameTime() * shipSpeed);
				ship.position.y += (ship.acceleration.y*GetFrameTime() * shipSpeed);
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

				ship.collider = { ship.position.x + sin(ship.rotation*DEG2RAD)*(shipHeight / 2.5f), ship.position.y - cos(ship.rotation*DEG2RAD)*(shipHeight / 2.5f), shipColliderZ };

			}
		}

		void UpdateSpaceship()
		{
			Input();
			Update();
		}

		void DrawSpaceship()
		{
			Vector2 v1 = { ship.position.x + sinf(ship.rotation*DEG2RAD)*(shipHeight), ship.position.y - cosf(ship.rotation*DEG2RAD)*(shipHeight) };
			Vector2 v2 = { ship.position.x - cosf(ship.rotation*DEG2RAD)*(shipBaseSize / 2), ship.position.y - sinf(ship.rotation*DEG2RAD)*(shipBaseSize / 2) };
			Vector2 v3 = { ship.position.x + cosf(ship.rotation*DEG2RAD)*(shipBaseSize / 2), ship.position.y + sinf(ship.rotation*DEG2RAD)*(shipBaseSize / 2) };
			DrawTexturePro(shipTexture, sourceRect, destRec, { (shipTexture.width / 2)*shipScale,(shipTexture.height / 2)*shipScale }, ship.rotation, WHITE);

			for (int i = 0; i < shipMaxShoots; i++)
			{
				if (shoot[i].active)
				{
					DrawCircleV(shoot[i].position, shoot[i].radius, WHITE);
					DrawTextureEx(shootTexture, { shoot[i].position.x - shootScalePos.x ,shoot[i].position.y - shootScalePos.y }, 0, shootScale, WHITE);
				}
			}
		}

		void UnloadSpaceship()
		{
			UnloadSound(shootSound);
			UnloadTexture(shipTexture);
			UnloadTexture(shootTexture);
			UnloadImage(shootImage);
			UnloadImage(shipImage);
		}
	}
}