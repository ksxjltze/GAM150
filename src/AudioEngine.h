#pragma once
#pragma warning(push)
#pragma warning(disable : 26812)
#include "fmod.hpp"
#pragma warning(pop)

#include <vector>
#include <string>

namespace StarBangBang
{
	struct Sound
	{
		std::string name;
		FMOD::Sound* sound;
	};

	class AudioEngine
	{
	public:
		AudioEngine();
		void CreateSound(FMOD::Sound** sound, const char* file);
		void AddSound(const std::string& name, FMOD::Sound* sound);
		void playSound(FMOD::Sound* sound, bool loop = false);
		void playSound(const std::string& name, bool loop = false);
		void ReleaseSound(FMOD::Sound* sound);
		void Update();
		void Exit();
	private:
		FMOD::System* system;
		std::vector<Sound> soundList;
	};
}