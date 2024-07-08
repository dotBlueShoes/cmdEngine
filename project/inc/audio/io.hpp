// By Matthew Strumillo 2024-07-08
//
#pragma once

#include "baseTypes.hpp"
#include "debug.hpp"
#include "dr_wav.h"

namespace AUDIO::IO::WAV {

	struct Wav {
		drwav_uint64    totalPCMFrameCount;
		u32             sampleRate;
		u32             channels;
		u64             pcmCount;
		s16*            pcm;
	};

	void GetTotalSamples (const Wav& wav, drwav_uint64& totalSamples) {
		totalSamples = wav.totalPCMFrameCount * wav.channels;
	}

	void Destory (Wav& wav) { 
		drwav_free (wav.pcm, nullptr);
	}

}

namespace AUDIO::IO::WAV::MONO {

	void Load (const char* const filepath, Wav& wav) {

		wav.pcm = drwav_open_file_and_read_pcm_frames_s16 (
			filepath, &wav.channels, &wav.sampleRate, 
			&wav.totalPCMFrameCount, nullptr
		);

		if (wav.pcm == nullptr) {
			drwav_free (wav.pcm, nullptr);
			Error ("{0}: Could not load the file. Check it's filepath.", "AUDIO::IO");
		}

		GetTotalSamples (wav, wav.pcmCount);
	
		if (wav.pcmCount > (drwav_uint64)(std::numeric_limits<size_t>::max())) {
			drwav_free (wav.pcm, nullptr);
			Error ("{0}: File is to large for 32bit addressing! Use a smaller file!", "AUDIO::IO");
		}
		
		//wav.pcm = new s16[wav.pcmCount];							// Allocation
		//memcpy (wav.pcm, data, wav.pcmCount * sizeof (s16));		// CPY
		//drwav_free (data, nullptr);								// FREE

	}

}
