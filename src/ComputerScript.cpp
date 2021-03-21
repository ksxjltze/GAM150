#include "ComputerScript.h"
#include "Utils.h"
#include "MessageBus.h"


namespace StarBangBang
{
	ComputerScript::ComputerScript(GameObject* gameObject) : Script(gameObject)
	{
		
	}

	void ComputerScript::Start()
	{
		
	}
	void ComputerScript::Update()
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
}