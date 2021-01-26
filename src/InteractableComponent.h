#pragma once
#include "Component.h"

namespace StarBangBang
{
	class InteractableComponent : public Component
	{
	public:
		enum class INTERACTABLE_TYPE
		{
			TYPE_NONE = 0,
			TYPE_PRINTER,
			TYPE_VENDING_MACHINE,
			TYPE_TOTAL,
		};

		const static int id = Constants::ComponentType::INTERACTABLE;
		InteractableComponent(GameObject* gameObject);
		Component* Clone(GameObject* gameObject, Component* component);

		void OnUse();
		inline void SetType(INTERACTABLE_TYPE _type) { type = _type; }
		inline INTERACTABLE_TYPE GetType() { return type; }
	private:
		bool enabled;
		INTERACTABLE_TYPE type;
	};
}