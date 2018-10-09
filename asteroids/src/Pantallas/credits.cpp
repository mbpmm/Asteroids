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
		char text4[] = "Aprete SPACE para volver al menu";
		char text5[] = "ASTEROIDS V 0.3";
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

		void InitCredits()
		{
			sizeText = (GetScreenWidth() * 30) / 800;
			sizeText2 = (GetScreenWidth() * 15) / 800;
			textPositionX = GetScreenWidth() / 2 - MeasureText(text1, sizeText) / 2;
			textPositionY = GetScreenHeight() * 0.2852;
			text2PositionX = GetScreenWidth() / 2 - MeasureText(text2, sizeText) / 2;
			text2PositionY = GetScreenHeight() * 0.428571;
			text3PositionX = GetScreenWidth() / 2 - MeasureText(text3, sizeText) / 2;
			text3PositionY = GetScreenHeight() * 0.571428;
			text4PositionX = GetScreenWidth() / 2 - MeasureText(text4, sizeText2) / 2;
			text4PositionY = GetScreenHeight() * 0.714285;
			text5PositionX = GetScreenWidth() / 2 - MeasureText(text5, sizeText) / 2;
			text5PositionY = GetScreenHeight() * 0.142857;
		}

		void UpdateCredits()
		{
			if (IsKeyPressed(KEY_SPACE))
			{
				currentScreen = Menu;
				ResetValues();
			}
		}

		void DrawCredits()
		{
			ClearBackground(BLACK);
			DrawText(text1, textPositionX, textPositionY, sizeText, GRAY);
			DrawText(text2, text2PositionX, text2PositionY, sizeText, GRAY);
			DrawText(text3, text3PositionX, text3PositionY, sizeText, GRAY);
			DrawText(text4, text4PositionX, text4PositionY, sizeText2, GRAY);
			DrawText(text5, text5PositionX, text5PositionY, sizeText, GRAY);
		}


	}
}