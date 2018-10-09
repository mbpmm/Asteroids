#include "game_over.h"

#include <raylib.h>

#include "game.h"
#include "app.h"

using namespace app;
using namespace game;

namespace app
{
	namespace gameover
	{
		char text1[] = "Perdiste  :(";
		char text2[] = "Ganaste!!!";
		char text3[] = "JUGAR DE NUEVO";
		char text4[] = "MENU";
		int text1PositionX = 0;
		int text1PositionY = 0;
		int text2PositionX = 0;
		int text3PositionX = 0;
		int text3PositionY = 0;
		int text4PositionX = 0;
		int text4PositionY = 0;
		int winnerNumber = 0;
		int sizeText1 = 0;
		int sizeText2 = 0;

		Vector2 mousePoint;
		Rectangle rect1;
		Rectangle rect2;
		Color colorRect1;
		Color colorRect2;

		void InitGameover()
		{
			sizeText1 = (GetScreenWidth() * 50) / 800;
			sizeText2 = (GetScreenWidth() * 20) / 800;
			text1PositionX = GetScreenWidth() / 2 - MeasureText(text1, sizeText1) / 2;
			text1PositionY = GetScreenHeight() / 2 - GetScreenHeight() * 0.13333333;
			text2PositionX = GetScreenWidth() / 2 - MeasureText(text2, sizeText1) / 2;
			text3PositionX = GetScreenWidth()/2 - MeasureText(text3, sizeText2) / 2;
			text3PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.13333333;
			text4PositionX = GetScreenWidth() / 2 - MeasureText(text4, sizeText2) / 2;
			text4PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.23333333;

			colorRect1 = DARKPURPLE;
			colorRect2 = DARKPURPLE;

			rect1.x = GetScreenWidth() / 2 - MeasureText(text3, sizeText2)/1.9f;
			rect1.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.11;
			rect1.height = (GetScreenWidth() * 80) / 1600;
			rect1.width = (GetScreenWidth() * 385) / 1600;

			rect2.x = GetScreenWidth() / 2 - MeasureText(text3, sizeText2) / 1.9f;
			rect2.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.21;
			rect2.height = (GetScreenWidth() * 80) / 1600;
			rect2.width = (GetScreenWidth() * 385) / 1600;
		}

		void UpdateGameOver()
		{
			mousePoint = GetMousePosition();
			if (CheckCollisionPointRec(mousePoint, rect1))
			{
				colorRect1.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					currentScreen = Gameplay;
					ResetValues();
				}
			}
			else colorRect1.a = 255;

			if (CheckCollisionPointRec(mousePoint, rect2))
			{
				colorRect2.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					currentScreen = Menu;
					ResetValues();
				}
			}
			else colorRect2.a = 255;

			/*if (IsKeyPressed(KEY_SPACE))
			{
				currentScreen = Menu;
				ResetValues();
			}
			if (IsKeyPressed(KEY_ESCAPE))
			{
				exit = true;
			}*/
		}

		void DrawGameOver()
		{
			ClearBackground(BLACK);
			DrawRectangleRec(rect1, colorRect1);
			DrawRectangleRec(rect2, colorRect2);
			if (!victory)
			{
				DrawText(text1, text1PositionX, text1PositionY, sizeText1, GRAY);
			}
			else
			{
				DrawText(text2,text2PositionX, text1PositionY, sizeText1, GRAY);
			}
			DrawText(text3, text3PositionX, text3PositionY, sizeText2, GRAY);
			DrawText(text4, text4PositionX, text4PositionY, sizeText2, GRAY);
		}


	}
}