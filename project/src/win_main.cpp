// By Matthew Strumillo 2024-07-08
//
#include "baseTypes.hpp"
#include "debug.hpp"
#include "audio/audio.hpp"

s32 main (
	s32			argumentsCount,
	c8**		arguments
) {

	DEBUG LogInfo ("Hello World");
	DEBUG LogWarn ("Hello World");
	DEBUG LogErro ("Hello World");

	const c8* const AUDIO_WAV = "res/audio/" "wav/ChmpSlct_Tutorial.wav";
	
	ALCdevice* device = nullptr;
	ALCcontext* listener = nullptr;
	ALuint sound;
	ALuint source;

	{
		// LOADERS
		AUDIO::IO::WAV::Wav wavLoader {};

		// DEVICES
		AUDIO::DEVICE::Create 				(device);

		// LISTENERS
		AUDIO::LISTENER::Create 			(device, listener, AUDIO::ZERO, AUDIO::ZERO);

		// SOUNDS (Are attached to a listener eg. context)
		AUDIO::IO::WAV::MONO::Load 			(AUDIO_WAV, wavLoader);
		AUDIO::SOUND::MONO::Create 			(sound, wavLoader);
		AUDIO::IO::WAV::Destory 			(wavLoader);

		// SOURCES
		AUDIO::SOURCE::MONO::CreateGlobal	(source, sound, true, 1.0f, 1.0f);

		// STATES
		AUDIO::STATE::Play 					(source);

	}

	u32 isStop = 1;
	while (isStop != 0) {
		++isStop;
	}

	DEBUG LogInfo ("Freeing audio resources");

	{
		// STATES
		AUDIO::STATE::Stop 					(source);

		// SOURCES
		AUDIO::SOURCE::Destroy 				(source);

		// SOUNDS
		AUDIO::SOUND::Destroy				(sound);

		// LISTENERS
		AUDIO::LISTENER::Destory			(listener);

		// DEVICES
		AUDIO::DEVICE::Destory				(device);
	}

	return 0;
}
