#pragma once
#include "fmod.hpp"

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