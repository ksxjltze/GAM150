#pragma once
#pragma warning(push)
#pragma warning(disable : 26812)
#include "fmod.hpp"
#pragma warning(pop)

#include "Listener.h"
#include <vector>
#include <string>

namespace StarBangBang
{
	struct Sound
	{
		std::string name;
		FMOD::Sound* sound;
	};

	class AudioEngine : public Listener
	{
	public:
		AudioEngine();
		void CreateSound(FMOD::Sound** sound, const char* file);
		void onNotify(Event e);
		void AddSound(const std::string& name, FMOD::Sound* sound);
		void playSound(FMOD::Sound* sound, bool loop = false);
		void playSound(const std::string& name, bool loop = false);
		void ReleaseSound(FMOD::Sound* sound);
		void StopMasterChannel();
		void Update();
		void Exit();
	private:
		FMOD::System* system;
		std::vector<Sound> soundList;
	};
}