#include "menu.h"

#include <raylib.h>

#include "app.h"

using namespace app;

namespace app
{
	namespace menu
	{
		bool pause = false;
		char text1[] = "ASTEROIDS";
		char text2[] = "Presiona ENTER para jugar";
		char text3[] = "C para ver los creditos";
		char text4[] = "ESC para salir";
		char text5[] = "V 0.1";
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
		/*Music menuSong;*/

		void InitMenu()
		{
			/*menuSong = LoadMusicStream("res/sounds/menusong.ogg");
			PlayMusicStream(menuSong);*/
			sizeText1 = (GetScreenWidth() * 110) / 800;
			sizeText2 = (GetScreenWidth() * 20) / 800;
			sizeText3 = (GetScreenWidth() * 15) / 800;
			textPositionX = GetScreenWidth() / 2 - MeasureText(text1, sizeText1) / 2;
			textPositionY = GetScreenHeight() * 0.2333333;
			text2PositionX = GetScreenWidth() / 2 - MeasureText(text2, sizeText2) / 2;
			text2PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.1333333;
			text3PositionX = GetScreenWidth() / 2 - MeasureText(text3, sizeText2) / 2;
			text3PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.2333333;
			text4PositionX = GetScreenWidth() / 2 - MeasureText(text4, sizeText2) / 2;
			text4PositionY = GetScreenHeight() / 2 + GetScreenHeight() * 0.3333333;
			text5PositionX = GetScreenWidth() * 0.05;
			text5PositionY = GetScreenHeight() * 0.95;
		}

		void UpdateMenu()
		{
			/*UpdateMusicStream(menuSong);*/
			if (IsKeyPressed(KEY_ENTER))
			{
				currentScreen = Gameplay;
			}

			if (IsKeyPressed(KEY_ESCAPE))
			{
				exit = true;
			}

			if (IsKeyPressed(KEY_P))
			{
				/*pause = !pause;

				if (pause) StopMusicStream(menuSong);
				else PlayMusicStream(menuSong);*/
			}

			if (IsKeyPressed(KEY_C))
			{
				currentScreen = Credits;
			}
		}

		void DrawMenu()
		{
			ClearBackground(WHITE);
			DrawText(text1, textPositionX, textPositionY, sizeText1, BLACK);
			DrawText(text2, text2PositionX, text2PositionY, sizeText2, BLACK);
			DrawText(text3, text3PositionX, text3PositionY, sizeText2, BLACK);
			DrawText(text4, text4PositionX, text4PositionY, sizeText2, BLACK);
			DrawText(text5, text5PositionX, text5PositionY, sizeText2, BLACK);
		}
	}
}