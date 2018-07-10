#include <audio/ogg.h>

static int _ov_header_fseek_wrap(FILE *f,ogg_int64_t off,int whence){
  if(f==NULL)return(-1);

#ifdef __MINGW32__
  return fseek(f,off,whence);
#elif defined (_WIN32)
  return _fseeki64(f,off,whence);
#else
  return fseek(f,off,whence);
#endif
}

static ov_callbacks OV_CALLBACKS_DEFAULT = {
  (size_t (*)(void *, size_t, size_t, void *))  fread,
  (int (*)(void *, ogg_int64_t, int))           _ov_header_fseek_wrap,
  (int (*)(void *))                             fclose,
  (long (*)(void *))                            ftell
};

void ogg::LoadAL()
{
	alGenSources(1, &source);
	alGenBuffers(16, buffers);

}

void ogg::DestroyAL()
{
	alDeleteSources(1, &source);
	alDeleteBuffers(16, buffers);
}

void ogg::Stream(ALint num, ALuint *stream_buffers)
{
	for (int i = 0; i < num; i++) {
		int pos = 0;

		while (pos < (long)sizeof(pcm)) {
			int ret = ov_read(&ogg_file, pcm + pos, sizeof(pcm) - pos, 0, 2, 1, &current_section);
			pos += ret;
			if (!ret) {
				eof = 1;
				break;
			}
		}
		ALenum format = (ogg_info->channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
		alBufferData(stream_buffers[i], format, pcm, pos, ogg_info->rate);
	}
}

void ogg::Load(const std::string &filepath)
{
	err = 0;
	fp = fopen(filepath.c_str(), "rb");

	if (!fp) {
		Debug_printf(__FILE__, __LINE__, "Could not open OGG file - %s\n", filepath.c_str());
		err = 1;
		return;
	}

	if (ov_open_callbacks(fp, &ogg_file, NULL, 0, OV_CALLBACKS_DEFAULT) < 0) {
		Debug_printf(__FILE__, __LINE__, "Invalid OGG file - %s\n", filepath.c_str());
		err = 1;
		return;
	}

	ogg_info = ov_info(&ogg_file, -1);

	Debug_printf(nullptr, 0, "Loaded OGG file - Sampling Rate %d - Channels %d\n", ogg_info->rate, ogg_info->channels);

	LoadAL();
	Stream(16, buffers);
	alSourceQueueBuffers(source, 16, buffers);
	alSourcePlay(source);
}

void ogg::Destroy()
{
	if (!err) {
		DestroyAL();
		ov_clear(&ogg_file);
		fclose(fp);
	}
}

void ogg::Play()
{
	if (!err) {
		ALenum state;
		ALuint released_buffers[16];
		ALint num_buffers;
		alGetSourcei(source, AL_SOURCE_STATE, &state);
		if (!eof) {
			alGetSourcei(source, AL_BUFFERS_PROCESSED, &num_buffers);
			alSourceUnqueueBuffers(source, num_buffers, released_buffers);

			Stream(num_buffers, released_buffers);

			alSourceQueueBuffers(source, num_buffers, released_buffers);
			Clock_Delay(5);
		} else {
			if (state == AL_STOPPED) {
				if (Looped) {
					ov_time_seek(&ogg_file, 0.0);
					alGetSourcei(source, AL_BUFFERS_PROCESSED, &num_buffers);
					alSourceUnqueueBuffers(source, num_buffers, released_buffers);
					alSourceQueueBuffers(source, 16, buffers);
					alSourcePlay(source);
					eof = 0;
				}
			}
		}
	}
}
