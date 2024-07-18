#pragma once
#include "audio.hpp"

namespace AUDIO::MANAGER {

	void Create (
		ALCdevice*& device,
		ALCcontext*& listener,
		ALuint& sound,
		ALuint& source
	) {
		// LOADERS
		AUDIO::IO::WAV::Wav wavLoader {};

		// DEVICES
		AUDIO::DEVICE::Create 				(device);

		// LISTENERS
		AUDIO::LISTENER::Create 			(device, listener, AUDIO::ZERO, AUDIO::ZERO);

		// SOUNDS (Are attached to a listener eg. context)
		AUDIO::IO::WAV::MONO::Load 			(ASSET::MANAGER::AUDIO_WAV_SAMPLE, wavLoader);
		AUDIO::SOUND::MONO::Create 			(sound, wavLoader);
		AUDIO::IO::WAV::Destory 			(wavLoader);

		// SOURCES
		AUDIO::SOURCE::MONO::CreateGlobal	(source, sound, true, 1.0f, 1.0f);

		// STATES
		AUDIO::STATE::Play 					(source);
	}


	void Destroy (
		ALCdevice*& device,
		ALCcontext*& listener,
		ALuint& sound,
		ALuint& source
	) {
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

}