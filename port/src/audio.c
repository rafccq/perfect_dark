#include <PR/ultratypes.h>
#include <SDL3/SDL.h>
#include "platform.h"
#include "config.h"
#include "audio.h"
#include "system.h"

static SDL_AudioStream *stream;
static const s16 *nextBuf;
static u32 nextSize = 0;

static s32 bufferSize = 512;
static s32 queueLimit = 8192;

s32 audioInit(void)
{
	if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
		sysLogPrintf(LOG_ERROR, "SDL audio init error: %s", SDL_GetError());
		return -1;
	}

	SDL_AudioSpec want;
	SDL_zero(want);
	want.freq = 22020; // TODO: this might cause trouble for some platforms
	want.format = SDL_AUDIO_S16;
	want.channels = 2;

	nextBuf = NULL;

	stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &want, NULL, NULL);
	if (stream == 0) {
		sysLogPrintf(LOG_ERROR, "SDL_OpenAudio error: %s", SDL_GetError());
		return -1;
	}

	SDL_ResumeAudioDevice(SDL_GetAudioStreamDevice(stream));

	return 0;
}

s32 audioGetBytesBuffered(void)
{
	SDL_AudioSpec src_spec, dst_spec;
	int src_size, dst_size;
	s32 available;

	if (!SDL_GetAudioStreamFormat(stream, &src_spec, &dst_spec)) {
		return 0;
	}

	available = SDL_GetAudioStreamAvailable(stream);
	if (available < 0) {
		return 0;
	}

	src_size = src_spec.channels * src_spec.freq * (s32) SDL_AUDIO_BYTESIZE(src_spec.format);
	dst_size = dst_spec.channels * dst_spec.freq * (s32) SDL_AUDIO_BYTESIZE(dst_spec.format);

	return available * src_size / dst_size;
}

s32 audioGetSamplesBuffered(void)
{
	return audioGetBytesBuffered() / 4;
}

void audioSetNextBuffer(const s16 *buf, u32 len)
{
	nextBuf = buf;
	nextSize = len;
}

void audioEndFrame(void)
{
	if (nextBuf && nextSize) {
		if (audioGetSamplesBuffered() < queueLimit) {
			SDL_PutAudioStreamData(stream, nextBuf, nextSize);
		}
		nextBuf = NULL;
		nextSize = 0;
	}
}

PD_CONSTRUCTOR static void audioConfigInit(void)
{
	configRegisterInt("Audio.BufferSize", &bufferSize, 0, 1 * 1024 * 1024);
	configRegisterInt("Audio.QueueLimit", &queueLimit, 0, 1 * 1024 * 1024);
}
