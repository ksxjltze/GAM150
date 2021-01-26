#include "AudioEngine.h"

StarBangBang::AudioEngine::AudioEngine()
{
	if (FMOD::System_Create(&system) != FMOD_OK)
	{
		//Report some error
		return;
	}

	int driverCount = 0;
	system->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		//Report some error
		return;
	}

	system->init(36, FMOD_INIT_NORMAL, 0);

}

void StarBangBang::AudioEngine::CreateSound(FMOD::Sound** sound, const char* file)
{
	system->createSound(file, FMOD_DEFAULT, 0, sound);
}

void StarBangBang::AudioEngine::playSound(FMOD::Sound* sound, bool loop)
{
	if (!loop)
	{
		sound->setMode(FMOD_LOOP_OFF);
	}
	else
	{
		sound->setMode(FMOD_LOOP_NORMAL);
		sound->setLoopCount(-1);
	}
	FMOD::Channel* channel;
	FMOD::ChannelGroup* channelGroup;

	system->getMasterChannelGroup(&channelGroup);
	system->getChannel(0, &channel);
	system->playSound(sound, channelGroup, false, &channel);
}

void StarBangBang::AudioEngine::ReleaseSound(FMOD::Sound* sound)
{
	sound->release();
}

void StarBangBang::AudioEngine::Update()
{
	system->update();
}
