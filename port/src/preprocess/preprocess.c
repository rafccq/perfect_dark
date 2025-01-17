#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include <PR/libaudio.h>
#include "platform.h"
#include "data.h"
#include "bss.h"
#include "game/setuputils.h"
#include "game/texdecompress.h"
#include "preprocess.h"
#include "romdata.h"
#include "mod.h"
#include "system.h"
#include "common.h"

// HACK: to prevent double-swapping stuff, flag swapped offsets in a bitmap

static u8 swapmap[0x40000 >> 3];

static inline u32 alreadySwapped(const intptr_t addr) {
	const u32 mask = (1 << (addr & 7));
	const u32 old = swapmap[addr >> 3] & mask;
	if (!old) {
		swapmap[addr >> 3] |= mask;
	}
	return old;
}

static inline void preprocessALWaveTable(ALWaveTable *tbl, u8 *bankBase)
{
	if (alreadySwapped((u8 *)tbl - bankBase)) {
		return;
	}

	PD_SWAP_VAL(tbl->len);
	PD_SWAP_PTR(tbl->base);

	if (tbl->type == AL_ADPCM_WAVE) {
		if (tbl->waveInfo.adpcmWave.loop ) {
			PD_SWAP_PTR(tbl->waveInfo.adpcmWave.loop);
			ALADPCMloop *loop = PD_PTR_BASE(tbl->waveInfo.adpcmWave.loop, bankBase);
			PD_SWAP_VAL(loop->count);
			PD_SWAP_VAL(loop->start);
			PD_SWAP_VAL(loop->end);
			for (s32 i = 0; i < 16; ++i) {
				PD_SWAP_VAL(loop->state[i]);
			}
		}
		if (tbl->waveInfo.adpcmWave.book) {
			PD_SWAP_PTR(tbl->waveInfo.adpcmWave.book);
			ALADPCMBook *book = PD_PTR_BASE(tbl->waveInfo.adpcmWave.book, bankBase);
			PD_SWAP_VAL(book->npredictors);
			PD_SWAP_VAL(book->order);
			const s32 bookSize = book->order * book->npredictors * ADPCMVSIZE;
			for (s32 i = 0; i < bookSize && i < 128; ++i) {
				PD_SWAP_VAL(book->book[i]);
			}
		}
	} else if (tbl->type == AL_RAW16_WAVE) {
		if (tbl->waveInfo.rawWave.loop) {
			PD_SWAP_PTR(tbl->waveInfo.rawWave.loop);
			ALRawLoop *loop = PD_PTR_BASE(tbl->waveInfo.rawWave.loop, bankBase);
			PD_SWAP_VAL(loop->count);
			PD_SWAP_VAL(loop->start);
			PD_SWAP_VAL(loop->end);
		}
	}
}

static inline void preprocessALSound(ALSound *snd, u8 *bankBase)
{
	if (alreadySwapped((u8 *)snd - bankBase)) {
		return;
	}

	if (snd->envelope) {
		PD_SWAP_PTR(snd->envelope);
		if (!alreadySwapped((intptr_t)snd->envelope)) {
			ALEnvelope *env = PD_PTR_BASE(snd->envelope, bankBase);
			PD_SWAP_VAL(env->attackTime);
			PD_SWAP_VAL(env->releaseTime);
			PD_SWAP_VAL(env->decayTime);
		}
	}

	if (snd->keyMap) {
		PD_SWAP_PTR(snd->keyMap);
	}

	if (snd->wavetable) {
		PD_SWAP_PTR(snd->wavetable);
		preprocessALWaveTable(PD_PTR_BASE(snd->wavetable, bankBase), bankBase);
	}
}

static inline void preprocessALInstrument(ALInstrument *inst, u8 *bankBase)
{
	if (alreadySwapped((u8 *)inst - bankBase)) {
		return;
	}

	PD_SWAP_VAL(inst->bendRange);
	PD_SWAP_VAL(inst->soundCount);

	for (s16 i = 0; i < inst->soundCount; ++i) {
		PD_SWAP_PTR(inst->soundArray[i]);
		preprocessALSound(PD_PTR_BASE(inst->soundArray[i], bankBase), bankBase);
	}
}

static inline void preprocessALBank(ALBank *bank, u8 *bankBase)
{
	if (alreadySwapped((u8 *)bank - bankBase)) {
		return;
	}

	PD_SWAP_VAL(bank->sampleRate);
	PD_SWAP_VAL(bank->instCount);

	if (bank->percussion) {
		PD_SWAP_PTR(bank->percussion);
		preprocessALInstrument(PD_PTR_BASE(bank->percussion, bankBase), bankBase);
	}

	for (s16 i = 0; i < bank->instCount; ++i) {
		PD_SWAP_PTR(bank->instArray[i]);
		preprocessALInstrument(PD_PTR_BASE(bank->instArray[i], bankBase), bankBase);
	}
}

u8* preprocessAnimations(u8* data, u32 size, u32* outSize)
{
	// set the anim table pointers as well
	extern u8 *_animationsTableRomStart;
	extern u8 *_animationsTableRomEnd;

	// the animation table is at the end of the segment
	u32 *animtbl = (void *)(data + size - 0x38a0);
	_animationsTableRomStart = (u8 *)animtbl;
	_animationsTableRomEnd = data + size;

	PD_SWAP_VAL(*animtbl);
	const u32 count = *animtbl++;

	struct animtableentry *anim = (struct animtableentry *)animtbl;
	for (u32 i = 0; i < count; ++i, ++anim) {
		PD_SWAP_VAL(anim->numframes);
		PD_SWAP_VAL(anim->bytesperframe);
		PD_SWAP_VAL(anim->headerlen);
		PD_SWAP_VAL(anim->data);
		// if an external replacement exists, replace the table entry and mark the offset
		if (modAnimationLoadDescriptor(i, anim) > 0) {
			anim->data = 0xffffffff;
		}
	}
	return 0;
}

u8* preprocessMpConfigs(u8* data, u32 size, u32* outSize)
{
	const u32 count = size / sizeof(struct mpconfig);
	struct mpconfig *cfg = (struct mpconfig *)data;
	for (u32 i = 0; i < count; ++i, ++cfg) {
		PD_SWAP_VAL(cfg->setup.options);
		PD_SWAP_VAL(cfg->setup.teamscorelimit);
		PD_SWAP_VAL(cfg->setup.chrslots);
		// TODO: are these required or are they always 0?
		PD_SWAP_VAL(cfg->setup.fileguid.deviceserial);
		PD_SWAP_VAL(cfg->setup.fileguid.fileid);
		// convert MPWEAPON_ to take classic weapons and JPN weapons into account
		for (s32 j = 0; j < ARRAYCOUNT(cfg->setup.weapons); ++j) {
#if VERSION == VERSION_JPN_FINAL /* TODO: replace with runtime check */
			if (cfg->setup.weapons[j] >= 0x24) {
				// weapons after and including the shield need to be shifted
				cfg->setup.weapons[j] += (MPWEAPON_SHIELD - MPWEAPON_PP9I);
			}
			if (cfg->setup.weapons[j] >= 0x19) {
				// weapons after the combat knife also need to be shifted up in JPN
				cfg->setup.weapons[j]++;
			}
#else
			// in other versions we only care about the shield and above
			if (cfg->setup.weapons[j] >= 0x25) {
				cfg->setup.weapons[j] += (MPWEAPON_SHIELD - MPWEAPON_PP9I);
			}
#endif
		}
	}
	return 0;
}

u8* preprocessJpnFont(u8* data, u32 size, u32* outSize)
{
	// ???
	return 0;
}

// to be removed eventually #TODO
u8* preprocessALBankFile_x86(u8* data, u32 size, u32* outSize)
{
	memset(swapmap, 0, sizeof(swapmap));

	ALBankFile *bankf = (ALBankFile *)data;
	PD_SWAP_VAL(bankf->revision);
	PD_SWAP_VAL(bankf->bankCount);

	for (s16 i = 0; i < bankf->bankCount; ++i) {
		PD_SWAP_PTR(bankf->bankArray[i]);
		preprocessALBank(PD_PTR_BASE(bankf->bankArray[i], data), data);
	}
	return 0;
}

void preprocessALCMidiHdr(u8 *data, u32 size)
{
	ALCMidiHdr *hdr = (ALCMidiHdr *)data;
	PD_SWAP_VAL(hdr->division);
	for (s32 i = 0; i < ARRAYCOUNT(hdr->trackOffset); ++i) {
		PD_SWAP_VAL(hdr->trackOffset[i]);
	}
}

u8* preprocessSequences(u8* data, u32 size, u32* outSize)
{
	struct seqtable *seq = (struct seqtable *)data;
	PD_SWAP_VAL(seq->count);

	for (s16 i = 0; i < seq->count; ++i) {
		PD_SWAP_VAL(seq->entries[i].binlen);
		PD_SWAP_VAL(seq->entries[i].ziplen);
		PD_SWAP_VAL(seq->entries[i].romaddr);
	}
	return 0;
}

u8* preprocessTexturesList(u8* data, u32 size, u32* outSize)
{
	struct texture *tex = (struct texture *)data;
	const u32 count = size / sizeof(*tex);
	for (u32 i = 0; i < count; ++i, ++tex) {
		// TODO: it sure looks like none of the fields except soundsurfacetype, surfacetype and dataoffset are set
		// just swap the last 3 bytes of the first word...
		const u32 dofs = (u32)tex->dataoffset << 8;
		tex->dataoffset = PD_BE32(dofs);
		// ...and the surface types in the first byte
		const u8 tmp = tex->soundsurfacetype;
		tex->soundsurfacetype = tex->surfacetype;
		tex->surfacetype = tmp;
	}
	return 0;
}
