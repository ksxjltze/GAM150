#include "GuardAnim.h"
#include "Physics.h"

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
			AEVec2 velocity = rb->velocity;
			// Do animation stuff

		}
	}
}