/*!*********************************************************************
\title	  Captain Stealth
\file     PlayerAnimation.cpp
\author   Sim Chin Hin
\par      DP email: s.chinhin\@digipen.edu
\date     11/04/2021

\brief
		  This file contains script class for players animation

Copyright (C) 2021 DigiPen Institute of Technology Singapore. All
rights reserved.
***********************************************************************/
#include "PlayerAnimation.h"
#include "constants.h"
#include "GraphicsManager.h"
#include "ImageComponent.h"

namespace StarBangBang
{
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
	void PlayerAnimator::PlayerAnimation(direction dir, current_char character, GameObject* player, GameObject* player2, const AnimationSprites& sprites, const int& animation_counter)
	{
		//update animation for prisoner and client
		switch (character)
		{
		case current_char::fei_ge:

			switch (dir)
			{//fei ge's animation

			case direction::right:

				switch (animation_counter)
				{
				case 1:
					player->GetComponent<ImageComponent>()->SetSprite(sprites.playerImageR2);
					break;
				case 2:
					player->GetComponent<ImageComponent>()->SetSprite(sprites.playerImageR3);
					break;

				case 3:
					player->GetComponent<ImageComponent>()->SetSprite(sprites.playerImageR1);
					break;
				}

				break;

			case direction::left:

				switch (animation_counter)
				{
				case 1:
					player->GetComponent<ImageComponent>()->SetSprite(sprites.playerImageL2);
					break;
				case 2:
					player->GetComponent<ImageComponent>()->SetSprite(sprites.playerImageL3);
					break;
				case 3:
					player->GetComponent<ImageComponent>()->SetSprite(sprites.playerImageL1);
					break;
				}

				break;
			}

			break;

		case current_char::prisoner:
			switch (dir)
			{
				//prisoner's animation

			case direction::right:

				switch (animation_counter)
				{
				case 1:
					player2->GetComponent<ImageComponent>()->SetSprite(sprites.playerImage2R2);
					break;
				case 2:
					player2->GetComponent<ImageComponent>()->SetSprite(sprites.playerImage2R3);
					break;
				case 3:
					player2->GetComponent<ImageComponent>()->SetSprite(sprites.playerImage2R1);
					break;
				}

				break;

			case direction::left:

				switch (animation_counter)
				{
				case 1:
					player2->GetComponent<ImageComponent>()->SetSprite(sprites.playerImage2L2);
					break;
				case 2:
					player2->GetComponent<ImageComponent>()->SetSprite(sprites.playerImage2L3);
					break;

				case 3:
					player2->GetComponent<ImageComponent>()->SetSprite(sprites.playerImage2L1);
					break;
				}

				break;

			}
			break;

		}

		//ANIMATION ~~~
	}
	/*!*********************************************************************
	\brief
		Loads sprite for players animation
	***********************************************************************/
	void AnimationSprites::Load(GraphicsManager& graphicsManager)
	{
		//right animation player 1
		playerImageR1 = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_R1_PATH);
		playerImageR2 = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_R2_PATH);
		playerImageR3 = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_R3_PATH);

		//left animation for player 1 
		playerImageL1 = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_L1_PATH);
		playerImageL2 = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_L2_PATH);
		playerImageL3 = graphicsManager.CreateSprite(RESOURCES::CAPTAINSTEALTH_L3_PATH);

		//right animation player 2
		playerImage2R1 = graphicsManager.CreateSprite(RESOURCES::PRISONER_R1_PATH);
		playerImage2R2 = graphicsManager.CreateSprite(RESOURCES::PRISONER_R2_PATH);
		playerImage2R3 = graphicsManager.CreateSprite(RESOURCES::PRISONER_R3_PATH);

		//left animation for player 2 
		playerImage2L1 = graphicsManager.CreateSprite(RESOURCES::PRISONER_L1_PATH);
		playerImage2L2 = graphicsManager.CreateSprite(RESOURCES::PRISONER_L2_PATH);
		playerImage2L3 = graphicsManager.CreateSprite(RESOURCES::PRISONER_L3_PATH);
	}
}
