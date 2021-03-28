#include "GuardAnim.h"
#include "Physics.h"
#include "globals.h"
#include "ImageComponent.h"
#include "GuardMovement.h"

namespace StarBangBang
{
	enum class guard_direction { idle = 0, left, right, up, down };

	static Sprite guardForwardSprite1;
	static Sprite guardForwardSprite2;
	static Sprite guardForwardSprite3;

	static Sprite guardRightSprite1;
	static Sprite guardRightSprite2;
	static Sprite guardRightSprite3;

	static Sprite guardLeftSprite1;
	static Sprite guardLeftSprite2;
	static Sprite guardLeftSprite3;

	static Sprite guardBackSprite1;
	static Sprite guardBackSprite2;
	static Sprite guardBackSprite3;

	GuardAnim::GuardAnim(GameObject* gameObject) 
		: Script(gameObject)
		, rb(nullptr)
		, movement(nullptr)
		, dir{ guard_direction::idle } 
	{}

	void GuardAnim::Start()
	{
		rb = gameObject->GetComponent<RigidBody>();
		movement = gameObject->GetComponent<GuardMovement>();
	}

	void GuardAnim::Update()
	{
		if (movement->IsTurning())
		{
			gameObject->GetComponent<ImageComponent>()->SetSprite(guardForwardSprite1);
			return;
		}

		if (rb)
		{
			switch (dir)
			{
			case guard_direction::left:
				switch (animation_counter)
				{
					//animation swapping
				case 1:
					gameObject->GetComponent<ImageComponent>()->SetSprite(guardLeftSprite2);
					break;

				case 2:
					gameObject->GetComponent<ImageComponent>()->SetSprite(guardLeftSprite3);
					break;
				}
				break;
			case guard_direction::right:
				switch (animation_counter)
				{
					//animation swapping
				case 1:
					gameObject->GetComponent<ImageComponent>()->SetSprite(guardRightSprite2);
					break;

				case 2:
					gameObject->GetComponent<ImageComponent>()->SetSprite(guardRightSprite3);
					break;
				}
				break;
			case guard_direction::up:
				switch (animation_counter)
				{
					//animation swapping
				case 1:
					gameObject->GetComponent<ImageComponent>()->SetSprite(guardBackSprite2);
					break;

				case 2:
					gameObject->GetComponent<ImageComponent>()->SetSprite(guardBackSprite3);
					break;
				}
				break;
			case guard_direction::down:
				switch (animation_counter)
				{
					//animation swapping
				case 1:
					gameObject->GetComponent<ImageComponent>()->SetSprite(guardForwardSprite2);
					break;

				case 2:
					gameObject->GetComponent<ImageComponent>()->SetSprite(guardForwardSprite3);
					break;
				}
				break;
			}

			AEVec2 current_velocity = rb->velocity;
			if (current_velocity.x * current_velocity.x > current_velocity.y * current_velocity.y)
			{
				if (current_velocity.x > 0)
				{
					dir = guard_direction::right;
					app_time += g_dt;
				}
				else if (current_velocity.x < 0)
				{
					dir = guard_direction::left;
					app_time += g_dt;
				}

			}
			else
			{
				if (current_velocity.y > 0)
				{
					dir = guard_direction::up;
					app_time += g_dt;
				}
				else if (current_velocity.y < 0)
				{
					dir = guard_direction::down;
					app_time += g_dt;
				}

			}


			if (app_time >= 0.1f)
			{
				animation_counter++;
				app_time = 0.0f;
				if (animation_counter > 2) animation_counter = 0;
			}


			// Do animation stuff

		}
	}

	void GuardAnim::Load(GraphicsManager& gfxMgr)
	{
		guardForwardSprite1 = gfxMgr.CreateSprite(RESOURCES::SECURITYGUARD_F1_PATH);
		guardForwardSprite2 = gfxMgr.CreateSprite(RESOURCES::SECURITYGUARD_F2_PATH);
		guardForwardSprite3 = gfxMgr.CreateSprite(RESOURCES::SECURITYGUARD_F3_PATH);

		guardRightSprite1 = gfxMgr.CreateSprite(RESOURCES::SECURITYGUARD_R1_PATH);
		guardRightSprite2 = gfxMgr.CreateSprite(RESOURCES::SECURITYGUARD_R2_PATH);
		guardRightSprite3 = gfxMgr.CreateSprite(RESOURCES::SECURITYGUARD_R3_PATH);

		guardLeftSprite1 = gfxMgr.CreateSprite(RESOURCES::SECURITYGUARD_L1_PATH);
		guardLeftSprite2 = gfxMgr.CreateSprite(RESOURCES::SECURITYGUARD_L2_PATH);
		guardLeftSprite3 = gfxMgr.CreateSprite(RESOURCES::SECURITYGUARD_L3_PATH);

		guardBackSprite1 = gfxMgr.CreateSprite(RESOURCES::SECURITYGUARD_B1_PATH);
		guardBackSprite2 = gfxMgr.CreateSprite(RESOURCES::SECURITYGUARD_B2_PATH);
		guardBackSprite3 = gfxMgr.CreateSprite(RESOURCES::SECURITYGUARD_B3_PATH);
	}

}