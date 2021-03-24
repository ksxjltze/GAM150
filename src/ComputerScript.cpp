#include "ComputerScript.h"
#include "Utils.h"
#include "MessageBus.h"
#include "CollisionEvent.h"

namespace StarBangBang
{
	ComputerScript::ComputerScript(GameObject* gameObject) : Script(gameObject), enabled{ false }
	{

	}

	void ComputerScript::Start()
	{
	}

	void ComputerScript::onNotify(Event e)
	{
		if (e.id == EventId::COLLISION)
		{
			CollisionEvent data = std::any_cast<CollisionEvent>(e.context);
			BoxCollider* collider = gameObject->GetComponent<BoxCollider>();

			if (data.first->gameObject->name == "Player" || data.first->gameObject->name == "Client")
			{
				if (data.first == collider || data.second == collider)
					enabled = true;

			}
		}
	}

	void ComputerScript::Update()
	{
		if (enabled)
		{
			if (AEInputCheckTriggered(AEVK_LBUTTON))
			{
				Transform& transform = gameObject->transform;
				if (PointRectTest(GetMouseWorldPos(), transform.position, transform.scale.x * GRAPHICS::MESH_WIDTH, transform.scale.y * GRAPHICS::MESH_HEIGHT))
				{
					gameObject->active = false;
					Event e;
					e.id = EventId::COMPUTER_CLICK;
					MessageBus::Notify(e);
				}
			}
		}
		enabled = false;
	}
}