#include "menu.h"

#include <raylib.h>

#include "app.h"

using namespace app;

namespace app
{
	namespace menu
	{
		static char text2[] = "JUGAR";
		static char text3[] = "CREDITOS";
		static char text4[] = "SALIR";
		static char text5[] = "V 0.9";
		static int sizeText2 = 0;
		static int sizeText3 = 0;
		static int text2PositionX = 0;
		static int text2PositionY = 0;
		static int text3PositionX = 0;
		static int text3PositionY = 0;
		static int text4PositionX = 0;
		static int text4PositionY = 0;
		static int text5PositionX = 0;
		static int text5PositionY = 0;
		static Vector2 mousePoint;
		static Rectangle rect1;
		static Rectangle rect2;
		static Rectangle rect3;
		static Color colorRect1;
		static Color colorRect2;
		static Color colorRect3;

		static const int scaleAux1 = 800;
		static const int scaleAux2 = 1600;
		static const int scaleAux3 = 1280;

		static Image menuImage;
		static Texture2D menuImageTexture;
		static float scaleBackground;
		
		void InitMenu()
		{
			menuImage = LoadImage("res/menuBack.png");
			menuImageTexture = LoadTextureFromImage(menuImage);

			sizeText2 = (GetScreenWidth() * 20) / scaleAux1;
			sizeText3 = (GetScreenWidth() * 15) / scaleAux1;
			text2PositionX = GetScreenWidth() / 2 - MeasureText(text2, sizeText2) / 2;
			text2PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.1333333;
			text3PositionX = GetScreenWidth() / 2 - MeasureText(text3, sizeText2) / 2;
			text3PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.2333333;
			text4PositionX = GetScreenWidth() / 2 - MeasureText(text4, sizeText2) / 2;
			text4PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.3333333;
			text5PositionX = GetScreenWidth() * 0.05;
			text5PositionY = GetScreenHeight() * 0.95;

			colorRect1 = PURPLE;
			colorRect2 = PURPLE;
			colorRect3 = PURPLE;

			rect1.height = (GetScreenWidth() * 80) / scaleAux2;
			rect1.width = (GetScreenWidth() * 255) / scaleAux2;
			rect1.x= GetScreenWidth() / 2 - rect1.width / 2;
			rect1.y= GetScreenHeight() / 2 + GetScreenHeight() * 0.11;

			rect2.height = (GetScreenWidth() * 80) / scaleAux2;
			rect2.width = (GetScreenWidth() * 255) / scaleAux2;
			rect2.x = GetScreenWidth() / 2 - rect1.width / 2;
			rect2.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.21;

			rect3.height = (GetScreenWidth() * 80) / scaleAux2;
			rect3.width = (GetScreenWidth() * 255) / scaleAux2;
			rect3.x = GetScreenWidth() / 2 - rect1.width / 2;
			rect3.y = GetScreenHeight() / 2 + GetScreenHeight() * 0.31;

			scaleBackground= (GetScreenWidth() * 1.0f) / scaleAux3;
		}

		void UpdateMenu()
		{
			mousePoint = GetMousePosition();
			
			if (CheckCollisionPointRec(mousePoint, rect1))
			{
				colorRect1.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = Gameplay;
			}
			else colorRect1.a = 255;

			if (CheckCollisionPointRec(mousePoint, rect3))
			{
				colorRect3.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) exit = true;
			}
			else colorRect3.a = 255;

			if (CheckCollisionPointRec(mousePoint, rect2))
			{
				colorRect2.a = 120;

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentScreen = Credits;
			}
			else colorRect2.a = 255;
		}

		void DrawMenu()
		{
			ClearBackground(WHITE);
			DrawTextureEx(menuImageTexture, { 0,0 }, 0, scaleBackground, WHITE);
			DrawRectangleRec(rect1, colorRect1);
			DrawRectangleRec(rect2, colorRect2);
			DrawRectangleRec(rect3, colorRect3);
			DrawText(text2, text2PositionX, text2PositionY, sizeText2, BLACK);
			DrawText(text3, text3PositionX, text3PositionY, sizeText2, BLACK);
			DrawText(text4, text4PositionX, text4PositionY, sizeText2, BLACK);
			DrawText(text5, text5PositionX, text5PositionY, sizeText2, WHITE);
		}
	}
}