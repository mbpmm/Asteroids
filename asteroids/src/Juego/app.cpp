#include "app.h"

#include <raylib.h>

#include "game.h"
#include "menu.h"
#include "game_over.h"
#include "credits.h"

using namespace app;
using namespace game;
using namespace menu;
using namespace gameover;
using namespace credits;

namespace app
{
	int screenWidth = 1600;
	int screenHeight = 900;
	bool exit = false;
	Screens currentScreen = Menu;

	static void InitGame()
	{
		SetExitKey(0);
		InitWindow(screenWidth, screenHeight, "PONG");
		HideCursor();
		InitAudioDevice();
		InitValues();
		InitMenu();
		InitCredits();
		InitGameover();

	}

	static void UpdateGame()
	{
		switch (currentScreen)
		{
		case Menu:
			UpdateMenu();
			break;
		case Credits:
			UpdateCredits();
			break;
		case Gameplay:
			UpdateFrame();
			break;
		case GameOver:
			UpdateGameOver();
			break;
		default:
			break;
		}
	}

	static void DrawGame()
	{
		BeginDrawing();
		switch (currentScreen)
		{
		case Menu:
			DrawMenu();
			break;
		case Credits:
			DrawCredits();
			break;
		case Gameplay:
			Draw();
			break;
		case GameOver:
			DrawGameOver();
		default:
			break;
		}
		EndDrawing();
	}

	static void CloseGame()
	{
		CloseAudioDevice();
		CloseWindow();
	}

	void ExecuteGame()
	{
		InitGame();
		// Main game loop
		while (!exit)
		{
			UpdateGame();
			DrawGame();
		}
		CloseGame();
	}
}