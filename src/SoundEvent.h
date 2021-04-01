#pragma once
#include <string>
#include "MessageBus.h"

namespace StarBangBang
{
	struct SoundEvent
	{
		const std::string name;
		float volume;

		SoundEvent(const std::string& name, float volume = 1.0f) : name{ name }, volume{ volume }
		{

		}

		void SendEvent()
		{
			Event e{ EventId::PLAY_SOUND, *this };
			MessageBus::Notify(e);
		};
	};
}