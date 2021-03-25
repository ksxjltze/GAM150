#include "GuardAnim.h"
#include "Physics.h"
#include "globals.h"
#include "ImageComponent.h"

static float app_time = 0.0f;
static int animation_counter = 0;

enum class direction { idle = 0, left, right, up, down };
direction dir;

namespace StarBangBang
{
	GuardAnim::GuardAnim(GameObject* gameObject) : Script(gameObject) {}

	void GuardAnim::Start()
	{

	}

	void GuardAnim::Update()
	{
		RigidBody* rb = gameObject->GetComponent<RigidBody>();
		if (rb)
		{

			switch (dir)
			{
			case direction::left:
				switch (animation_counter)
				{
					//animation swapping
				case 1:
					break;

				case 2:
					break;
				}
				break;
			case direction::right:
				switch (animation_counter)
				{
					//animation swapping
				case 1:
					break;

				case 2:
					break;
				}
				break;
			case direction::up:
				switch (animation_counter)
				{
					//animation swapping
				case 1:
					break;

				case 2:
					break;
				}
				break;
			case direction::down:
				switch (animation_counter)
				{
					//animation swapping
				case 1:
					gameObject->GetComponent<ImageComponent>()->SetSprite(playerImageR2);
					break;

				case 2:
					break;
				}
				break;
			}

			AEVec2 current_velocity = rb->velocity;
			if (current_velocity.x > 0)
			{
				dir = direction::right;
				app_time += g_dt;
			}
			else if (current_velocity.x < 0)
			{
				dir = direction::left;
				app_time += g_dt;
			}
			else if (current_velocity.y > 0)
			{
				dir = direction::up;
				app_time += g_dt;
			}
			else if (current_velocity.y < 0)
			{
				dir = direction::down;
				app_time += g_dt;
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
}