/*!*********************************************************************
\title	  Captain Stealth
\file     PlayerAnimation.h
\author   Sim Chin Hin
\par      DP email: s.chinhin\@digipen.edu
\date     11/04/2021

\brief
		  This file contains script class for players animation

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
***********************************************************************/
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
		/*!*********************************************************************
		\brief
			Loads sprite for players animation
		***********************************************************************/
		void Load(GraphicsManager& graphicsManager);
	};

	class PlayerAnimator
	{
	public:
		/*!*********************************************************************
		\brief
			Updates player animation
		\dir
			current direction of player
		\character
			current character (prisoner or captain stealth)
		\player
			captain stealth object
		\player 2 
			prisoner object
		\sprites
			struct of sprites used for animation
		\animation counter
			used to determine which sprite should be drawn
		***********************************************************************/
		static void PlayerAnimation(direction dir, current_char character, GameObject* player, GameObject* player2, const AnimationSprites& sprites, const int& animation_counter);
	};
}
