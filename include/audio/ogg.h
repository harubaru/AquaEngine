#ifndef AQUAENGINE_AUDIO_AUDIODEVICE_H
#define AQUAENGINE_AUDIO_AUDIODEVICE_H

#ifndef OV_EXCLUDE_STATIC_CALLBACKS
#define OV_EXCLUDE_STATIC_CALLBACKS
#endif

#include <stdio.h>

#include <string>
#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include <core/Debug.h>
#include <util/Clock.h>
#include <export.h>

class API ogg {
private:
	FILE *fp;
	OggVorbis_File ogg_file;
	vorbis_info *ogg_info;
	ALuint source;
	ALuint buffers[16];

	void LoadAL();
	void DestroyAL();
	void Stream(ALint num, ALuint *stream_buffers);

	int current_section;
	int eof;
	int err;
	char pcm[16*1024];
public:
	ogg(const std::string &filepath) : Looped(false) { this->Load(filepath); }

	void Load(const std::string &filepath);
	void Destroy();
	void Play();

	bool Looped;
};

#endif
