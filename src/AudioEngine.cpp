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

void StarBangBang::AudioEngine::onNotify(Event e)
{
	if (e.id == EventId::PLAY_SOUND)
	{
		try
		{
			std::string s = std::any_cast<const char*>(e.context);
			std::cout << "Playing sound: " << s << std::endl;
			playSound(s);
		}
		catch (const std::exception&)
		{
			std::cout << "ERROR PLAYING SOUND" << std::endl;
			return;
		}

	}
	else if (e.id == EventId::PLAY_MUSIC)
	{
		try
		{
			std::string s = std::any_cast<const char*>(e.context);
			std::cout << "Playing sound: " << s << std::endl;
			playSound(s, true);
		}
		catch (const std::exception&)
		{
			std::cout << "ERROR PLAYING SOUND" << std::endl;
			return;
		}

	}

	if (e.id == EventId::STOP_SOUND)
	{
		StopMasterChannel();
	}

}

void StarBangBang::AudioEngine::AddSound(const std::string& name, FMOD::Sound* sound)
{
	soundList.push_back({name, sound});
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

void StarBangBang::AudioEngine::playSound(const std::string& name, bool loop)
{
	for (auto sound : soundList)
	{
		if (sound.name == name)
		{
			playSound(sound.sound, loop);
		}
	}
}

void StarBangBang::AudioEngine::ReleaseSound(FMOD::Sound* sound)
{
	sound->release();
}

void StarBangBang::AudioEngine::StopMasterChannel()
{
	FMOD::ChannelGroup* channelGroup;
	system->getMasterChannelGroup(&channelGroup);
	channelGroup->stop();
}

void StarBangBang::AudioEngine::Update()
{
	system->update();
}

void StarBangBang::AudioEngine::Exit()
{
	system->close();
}
