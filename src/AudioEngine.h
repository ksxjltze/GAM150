#pragma once
#pragma warning(push)
#pragma warning(disable : 26812)
#include "fmod.hpp"
#pragma warning(pop)

namespace StarBangBang
{
	class AudioEngine
	{
	public:
		AudioEngine();
		void CreateSound(FMOD::Sound** sound, const char* file);
		void playSound(FMOD::Sound* sound, bool loop = false);
		void ReleaseSound(FMOD::Sound* sound);
		void Update();
		void Exit();
	private:
		FMOD::System* system;
	};
}