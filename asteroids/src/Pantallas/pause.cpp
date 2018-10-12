#include "pause.h"

#include <raylib.h>

#include "game.h"
#include "app.h"

using namespace app;
using namespace game;

namespace app
{
	namespace pause
	{
		char text1[] = "PAUSA";
		char text2[] = "SEGUIR";
		char text3[] = "MENU";
		char text4[] = "SALIR";
		int sizeText1 = 0;
		int sizeText2 = 0;
		int sizeText3 = 0;
		int textPositionX = 0;
		int textPositionY = 0;
		int text2PositionX = 0;
		int text2PositionY = 0;
		int text3PositionX = 0;
		int text3PositionY = 0;
		int text4PositionX = 0;
		int text4PositionY = 0;
		int text5PositionX = 0;
		int text5PositionY = 0;
		Vector2 mousePoint;
		Rectangle rect1;
		Rectangle rect2;
		Rectangle rect3;
		Color colorRect1;
		Color colorRect2;
		Color colorRect3;
		Color backGround;

		void InitPause()
		{
			sizeText1 = (GetScreenWidth() * 80) / 800;
			sizeText2 = (GetScreenWidth() * 20) / 800;
			sizeText3 = (GetScreenWidth() * 15) / 800;
			textPositionX = GetScreenWidth() / 2 - MeasureText(text1, sizeText1) / 2;
			textPositionY = GetScreenHeight() * 0.1333333;
			text2PositionX = GetScreenWidth() / 2 - MeasureText(text2, sizeText2) / 2;
			text2PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.1333333;
			text3PositionX = GetScreenWidth() / 2 - MeasureText(text3, sizeText2) / 2;
			text3PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.2333333;
			text4PositionX = GetScreenWidth() / 2 - MeasureText(text4, sizeText2) / 2;
			text4PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.3333333;

			colorRect1 = PURPLE;
			colorRect2 = PURPLE;
			colorRect3 = PURPLE;
			backGround = BLANK;

			rect1.x = GetScreenWidth() / 2 - MeasureText(text4, sizeText2);
			rect1.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.11;
			rect1.height = (GetScreenWidth() * 80) / 1600;
			rect1.width = (GetScreenWidth() * 255) / 1600;

			rect2.x = GetScreenWidth() / 2 - MeasureText(text4, sizeText2);
			rect2.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.21;
			rect2.height = (GetScreenWidth() * 80) / 1600;
			rect2.width = (GetScreenWidth() * 255) / 1600;

			rect3.x = GetScreenWidth() / 2 - MeasureText(text4, sizeText2);
			rect3.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.31;
			rect3.height = (GetScreenWidth() * 80) / 1600;
			rect3.width = (GetScreenWidth() * 255) / 1600;
		}

		void UpdatePause()
		{
			mousePoint = GetMousePosition();

			if (CheckCollisionPointRec(mousePoint, rect1))
			{
				colorRect1.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = Gameplay;
			}
			else colorRect1.a = 255;

			/*if (IsKeyPressed(KEY_ENTER))
			{
			currentScreen = Gameplay;
			}*/

			if (CheckCollisionPointRec(mousePoint, rect3))
			{
				colorRect3.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) exit = true;
			}
			else colorRect3.a = 255;

			/*if (IsKeyPressed(KEY_ESCAPE))
			{
			exit = true;
			}*/

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

			/*if (IsKeyPressed(KEY_C))
			{
			currentScreen = Credits;
			}*/
		}

		void DrawPause()
		{
			ClearBackground(backGround);
			DrawRectangleRec(rect1, colorRect1);
			DrawRectangleRec(rect2, colorRect2);
			DrawRectangleRec(rect3, colorRect3);
			DrawText(text1, textPositionX, textPositionY, sizeText1, RAYWHITE);
			DrawText(text2, text2PositionX, text2PositionY, sizeText2, BLACK);
			DrawText(text3, text3PositionX, text3PositionY, sizeText2, BLACK);
			DrawText(text4, text4PositionX, text4PositionY, sizeText2, BLACK);
		}
	}
}