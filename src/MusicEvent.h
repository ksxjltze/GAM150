#pragma once
#include <string>
#include "MessageBus.h"

namespace StarBangBang
{
	struct MusicEvent
	{
		const std::string name;
		float volume;
		bool loop;

		MusicEvent(const std::string& name, float volume = 1.0f, bool loop = true) : name{ name }, volume{ volume }, loop{ loop }
		{

		}

		void SendEvent()
		{
			Event e{ EventId::PLAY_MUSIC, *this };
			MessageBus::Notify(e);
		};
	};
}