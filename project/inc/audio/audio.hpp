// By Matthew Strumillo 2024-07-08
//
#pragma once

#include "baseTypes.hpp"
#include "debug.hpp"
#include "io.hpp"

#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <AL/al.h>
#include <AL/alc.h>
#pragma GCC diagnostic pop


#define ErrorSilentOpenAL(...) { \
	ErrorSilent ("OPENAL", __VA_ARGS__); \
}


namespace AUDIO {

	using float3 = ALfloat[3];
	float3 ZERO { 0 }; 

	const float MAX_GAIN = 10.0f;

	void CheckError ( const char* message ) {
		const ALenum errorCode = alGetError ();
		switch (errorCode) {
			case AL_NO_ERROR: 																	return;
			case AL_INVALID_NAME:		ErrorSilentOpenAL ("AL_INVALID_NAME", message);			return;
			case AL_INVALID_ENUM:		ErrorSilentOpenAL ("AL_INVALID_ENUM", message);			return;
			case AL_INVALID_VALUE:		ErrorSilentOpenAL ("AL_INVALID_ENUM", message);			return;
			case AL_INVALID_OPERATION:	ErrorSilentOpenAL ("AL_INVALID_OPERATION", message);	return;
			case AL_OUT_OF_MEMORY:		ErrorSilentOpenAL ("AL_OUT_OF_MEMORY", message);		return;
			default:					ErrorSilentOpenAL ("UNKNOWN", message);					return;
		}
	}

}


namespace AUDIO::DEVICE {

	void Create (ALCdevice*& audioDevice) {
		const ALCchar* defaultDeviceString	= alcGetString (nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);	// nullptr means get default.
		audioDevice	= alcOpenDevice (defaultDeviceString);

		if (audioDevice == nullptr) Error ("OPENAL: Failed to get the default device.");		// release build check

		DEBUG LogInfo ("OpenAL Device: {0}", alcGetString (audioDevice, ALC_DEVICE_SPECIFIER));
	}

	void Destory (ALCdevice*& device) { alcCloseDevice (device); }

}


namespace AUDIO::LISTENER {

    auto Create (
        /* IN  */ ALCdevice*& audioDevice, 
        /* OUT */ ALCcontext*& audioContext,
        /* IN  */ const float3& position,
		/* IN  */ const float3& velocity
    ) {
		audioContext = alcCreateContext (audioDevice, /*attributelist*/ nullptr);

        // Activate the context and release check.
		if (!alcMakeContextCurrent (audioContext)) Error ("OPENAL: Failed to make the context active.");	

		const ALfloat forwardAndUpVectors[] {
			/* forward */   1.0f, 0.0f, 0.0f,
			/* up */        0.0f, 1.0f, 0.0f
		};

		alListener3f (AL_POSITION, position[0], position[1], position[2]);
		DEBUG CheckError ("Listener: SET: POSITION");

		alListener3f (AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
		DEBUG CheckError ("Listener: SET: VELOCITY");

		alListenerfv (AL_ORIENTATION, forwardAndUpVectors);
		DEBUG CheckError ("Listener: SET: ORIENTATION");
	}

    void Destory (ALCcontext*& audioContext) { 
		alcMakeContextCurrent (nullptr);				// Unreference context
		alcDestroyContext (audioContext);				// Free it's memory
	}

}


namespace AUDIO::SOUND::MONO {

	void Create ( 
		ALuint& sound,
		IO::WAV::Wav& wav
	) {
		alGenBuffers(1, &sound);
		DEBUG CheckError ("Sound: CREATE: BUFFORS");

		const auto depth = wav.channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
		const ALsizei size = wav.pcmCount * sizeof (s16);
		alBufferData (sound, depth, wav.pcm, size, wav.sampleRate );
		DEBUG CheckError ("Sound: SET: BUFFORS");
	}

}


namespace AUDIO::SOUND {

    void Destroy (ALuint& sound) {
		alDeleteBuffers (1, &sound);
		DEBUG CheckError ("Sound: DESTROY");
	}

}


namespace AUDIO::SOURCE::MONO {

	// ! MONO SOURCES ONLY WORK WITH MONO SOUNDS !

	void Create (
		/* OUT */ ALuint& source,						// REF
		/* IN  */ const ALuint& sound, 					// REF
		/* IN  */ const float3& position,				// REF
		/* IN  */ const float3& velocity,				// REF
		/* IN  */ const ALboolean& islooped = false, 	// REF
		/* IN  */ const ALfloat& pitch = 1.0f, 			// REF
		/* IN  */ const ALfloat& gain = 1.0f			// REF
	) {
		alGenSources (1, &source);
		DEBUG CheckError ("Source: CREATE: BUFFORS");

		alSource3f (source, AL_POSITION, position[0], position[1], position[2]);
		DEBUG CheckError ("Source: SET: POSITION");

		alSource3f (source, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
		DEBUG CheckError ("Source: SET: VELOCITY");

		alSourcef (source, AL_MAX_GAIN, MAX_GAIN);
		DEBUG CheckError ("Source: SET: MAX_GAIN");

		alSourcef (source, AL_PITCH, pitch);
		DEBUG CheckError ("Source: SET: PITCH");

		alSourcef (source, AL_GAIN, gain);
		DEBUG CheckError ("Source: SET: GAIN");

		alSourcei(source, AL_LOOPING, islooped);
		DEBUG CheckError ("Source: SET: LOOP");

		alSourcei(source, AL_BUFFER, sound);
		DEBUG CheckError ("Source: SET: SOUND");
	}

	void CreateGlobal (
		/* OUT */ ALuint& source,						// REF
		/* IN  */ const ALuint& sound, 					// REF
		/* IN  */ const ALboolean& islooped = false, 	// REF
		/* IN  */ const ALfloat& pitch = 1.0f, 			// REF
		/* IN  */ const ALfloat& gain = 1.0f			// REF
	) { Create (source, sound, ZERO, ZERO, islooped, pitch, gain); }

}


namespace AUDIO::SOURCE {

    void Destroy (ALuint& source) {
		alDeleteSources (1, &source);
		DEBUG CheckError ("Source: DESTROY");
	}

}


namespace AUDIO::STATE {

	void Play (const ALuint& source) {
		alSourcePlay (source);
        DEBUG CheckError ("State: PLAY: Source could not start playing");
	}

	void Stop (const ALuint& source) {
		alSourceStop (source);
		DEBUG CheckError ("State: STOP: Source could not stop playing");
	}

}