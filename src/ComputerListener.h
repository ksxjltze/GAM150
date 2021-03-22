#pragma once
#include "ListenerComponent.h"

namespace StarBangBang
{
	/// <summary>
	/// Simple Listener Component that reacts to detection events.
	/// Can be added to any gameObject that should react to detection.
	/// E.g. guard detects player, game over.
	/// Can be further inherited to specialize behaviour.
	/// WIP, currently only prints to console.
	/// ListenerComponent inherits from the Listener abstract class, extending its interface.
	/// </summary>
	class ComputerListener : public ListenerComponent
	{
	public:
		ComputerListener(GameObject* gameObject);
		virtual void onNotify(Event e);
	private:
		int counter;
	};
}
