#include "app.h"

#include <raylib.h>

#include "game.h"
#include "menu.h"
#include "game_over.h"
#include "credits.h"
#include "pause.h"

using namespace app;
using namespace game;
using namespace menu;
using namespace gameover;
using namespace credits;
using namespace pause;

namespace app
{
	int screenWidth = 1280;
	int screenHeight = 768;
	bool exit = false;
	Screens currentScreen = Menu;
	Music menuSong;
	bool pauseMusic = false;

	static void InitGame()
	{
		SetExitKey(0);
		InitWindow(screenWidth, screenHeight, "ASTEROIDS");
		//HideCursor();
		InitAudioDevice();
		InitValues();
		InitMenu();
		InitCredits();
		InitGameover();
		InitPause();
		menuSong = LoadMusicStream("res/menusong2.ogg");
		PlayMusicStream(menuSong);

	}

	static void UpdateGame()
	{
		UpdateMusicStream(menuSong);
		if (IsKeyPressed(KEY_P))
		{
				pauseMusic = !pauseMusic;

				if (pauseMusic) StopMusicStream(menuSong);
				else PlayMusicStream(menuSong);
		}
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
		case Pause:
			UpdatePause();
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
			break;
		case Pause:
			DrawPause();
			break;
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
		while (!WindowShouldClose()&&!exit)
		{
			UpdateGame();
			DrawGame();
		}
		CloseGame();
	}
}