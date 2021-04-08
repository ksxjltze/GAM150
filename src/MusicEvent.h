#pragma once
#include <string>
#include "MessageBus.h"

namespace StarBangBang
{
	struct MusicEvent
	{
		const std::string name;
		float volume;

		MusicEvent(const std::string& name, float volume = 1.0f) : name{ name }, volume{ volume }
		{

		}

		void SendEvent()
		{
			Event e{ EventId::PLAY_MUSIC, *this };
			MessageBus::Notify(e);
		};
	};
}