#include "credits.h"

#include <raylib.h>

#include "game.h"
#include "app.h"

using namespace app;
using namespace game;

namespace app
{
	namespace credits
	{
		char text1[] = "Usando libreria raylib";
		char text2[] = "Musica realizada con Bosca Ceoil";
		char text3[] = "Creado por Mariano Martinez";
		char text4[] = "MENU";
		char text5[] = "ASTEROIDS V 0.7";
		char text6[] = "Sonidos realizados con Bfxr";
		int sizeText = 0;
		int sizeText2 = 0;
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
		int text6PositionX = 0;
		int text6PositionY = 0;

		Vector2 mousePoint;
		Rectangle rect1;
		Color colorRect1;

		void InitCredits()
		{
			sizeText = (GetScreenWidth() * 30) / 800;
			sizeText2 = (GetScreenWidth() * 15) / 800;
			textPositionX = GetScreenWidth() / 2 - MeasureText(text1, sizeText) / 2;
			textPositionY = GetScreenHeight() * 0.2452;
			text2PositionX = GetScreenWidth() / 2 - MeasureText(text2, sizeText) / 2;
			text2PositionY = GetScreenHeight() * 0.388571;
			text6PositionX = GetScreenWidth() / 2 - MeasureText(text6, sizeText) / 2;
			text6PositionY = GetScreenHeight() * 0.528571;
			text3PositionX = GetScreenWidth() / 2 - MeasureText(text3, sizeText) / 2;
			text3PositionY = GetScreenHeight() * 0.661428;
			text4PositionX = GetScreenWidth() / 2 - MeasureText(text4, sizeText2) / 2;
			text4PositionY = GetScreenHeight() * 0.80;
			text5PositionX = GetScreenWidth() / 2 - MeasureText(text5, sizeText) / 2;
			text5PositionY = GetScreenHeight() * 0.102857;

			colorRect1 = DARKPURPLE;

			rect1.x = GetScreenWidth() / 2 - MeasureText(text4, sizeText2);
			rect1.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.275;
			rect1.height = (GetScreenWidth() * 80) / 1600;
			rect1.width = (GetScreenWidth() * 170) / 1600;
		}

		void UpdateCredits()
		{
			mousePoint = GetMousePosition();
			if (CheckCollisionPointRec(mousePoint, rect1))
			{
				colorRect1.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					currentScreen = Menu;
					ResetValues();
				}
			}
			else colorRect1.a = 255;
			/*if (IsKeyPressed(KEY_SPACE))
			{
				currentScreen = Menu;
				ResetValues();
			}*/
		}

		void DrawCredits()
		{
			ClearBackground(BLACK);
			DrawRectangleRec(rect1, colorRect1);
			DrawText(text1, textPositionX, textPositionY, sizeText, GRAY);
			DrawText(text2, text2PositionX, text2PositionY, sizeText, GRAY);
			DrawText(text3, text3PositionX, text3PositionY, sizeText, GRAY);
			DrawText(text4, text4PositionX, text4PositionY, sizeText2, GRAY);
			DrawText(text5, text5PositionX, text5PositionY, sizeText, GRAY);
			DrawText(text6, text6PositionX, text6PositionY, sizeText, GRAY);
		}
	}
}