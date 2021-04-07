#pragma once
#include "GameObject.h"
#include "Sprite.h"

namespace StarBangBang
{
	enum class direction;
	enum class current_char;
	class ImageComponent;
	class GraphicsManager;

	struct AnimationSprites
	{
		Sprite playerImageR1;
		Sprite playerImageR2;
		Sprite playerImageR3;
		Sprite playerImageL1;
		Sprite playerImageL2;
		Sprite playerImageL3;
		Sprite playerImage2R1;
		Sprite playerImage2R2;
		Sprite playerImage2R3;
		Sprite playerImage2L1;
		Sprite playerImage2L2;
		Sprite playerImage2L3;

		void Load(GraphicsManager& graphicsManager);
	};

	class PlayerAnimator
	{
	public:
		static void PlayerAnimation(direction dir, current_char character, GameObject* player, GameObject* player2, const AnimationSprites& sprites, const int& animation_counter);
	};
}
