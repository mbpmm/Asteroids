#ifndef GAME_H
#define GAME_H

namespace app
{
	namespace game
	{
		void InitValues();
		void UpdateFrame();
		void Draw();
		void ResetValues();

		extern bool victory;
		extern int pointsP1;
	}
}
#endif // !GAME_H