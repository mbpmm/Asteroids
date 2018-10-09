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
		void RotationAngle();

		extern bool victory;
	}
}
#endif // !GAME_H