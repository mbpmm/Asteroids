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
		int text1PositionX = 0;
		int text1PositionY = 0;
		int text2PositionX = 0;
		int text3PositionX = 0;
		int text3PositionY = 0;
		int winnerNumber = 0;
		int sizeText1 = 0;
		int sizeText2 = 0;

		void InitGameover()
		{
			sizeText1 = (GetScreenWidth() * 50) / 800;
			sizeText2 = (GetScreenWidth() * 20) / 800;
			text1PositionX = GetScreenWidth() / 2 - MeasureText(text1, sizeText1) / 2;
			text1PositionY = GetScreenHeight() / 2 - GetScreenHeight() * 0.13333333;
			text2PositionX = GetScreenWidth() / 2 - MeasureText(text2, sizeText1) / 2;
			text3PositionX = GetScreenWidth() * 0.1875;
			text3PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.13333333;
		}

		void UpdateGameOver()
		{
			if (IsKeyPressed(KEY_SPACE))
			{
				currentScreen = Menu;
				ResetValues();
			}
			if (IsKeyPressed(KEY_ESCAPE))
			{
				exit = true;
			}
		}

		void DrawGameOver()
		{
			ClearBackground(BLACK);
			if (!victory)
			{
				DrawText(text1, text1PositionX, text1PositionY, sizeText1, GRAY);
			}
			else
			{
				DrawText(text2,text2PositionX, text1PositionY, sizeText1, GRAY);
			}
			DrawText("Apreta ESPACIO para volver al menu, ESC para salir", text3PositionX, text3PositionY, sizeText2, GRAY);
		}


	}
}