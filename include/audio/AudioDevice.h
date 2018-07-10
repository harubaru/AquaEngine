#ifndef AQUAENGINE_AUDIODEVICE_H
#define AQUAENGINE_AUDIODEVICE_H

#include <string>
#include <stdio.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include <core/Debug.h>
#include <export.h>

/* for OpenAL context handling and audio playing in seperate thread */

class AudioDevice {
private:
public:
	AudioDevice();
	void Destroy();
};

#endif
