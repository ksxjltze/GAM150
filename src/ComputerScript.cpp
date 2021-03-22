#include "ComputerScript.h"
#include "Utils.h"
#include "MessageBus.h"
#include "Collider.h"

namespace StarBangBang
{
	ComputerScript::ComputerScript(GameObject* gameObject) : Script(gameObject), enabled{ false }
	{
		MessageBus::RegisterListener(this);
	}

	void ComputerScript::Start()
	{
	}

	void ComputerScript::onNotify(Event e)
	{
		if (e.id == EventId::COLLISION)
		{
			using colPair = std::pair<Collider*, Collider*>;
			colPair colliderPair = std::any_cast<colPair>(e.context);

			BoxCollider* collider = gameObject->GetComponent<BoxCollider>();

			if (colliderPair.first->gameObject->name == "Player" || colliderPair.second->gameObject->name == "Player")
			{
				if (colliderPair.first == collider || colliderPair.second == collider)
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
					e.context = std::string("\nTESTING DETECTION LISTENER\n");
					MessageBus::Notify(e);
				}
			}
		}
		enabled = false;
	}
}