#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "gbi.h"
#include "game/texdecompress.h"

#include "common.h"
#include "romdata.h"
#include "system.h"

enum contenttype {
	/* 0*/ CT_MODELDEF,
	/* 1*/ CT_NODE,
	/* 2*/ CT_TEXCONFIG,
	/* 3*/ CT_TEXDATA,
	/* 4*/ CT_PARTS,
	/* 5*/ CT_VTXCOL,
	/* 6*/ CT_GDL,
	/* 7*/ CT_RODATA_CHRINFO,
	/* 8*/ CT_RODATA_POSITION,
	/* 9*/ CT_RODATA_GUNDL,
	/*10*/ CT_RODATA_DISTANCE,
	/*11*/ CT_RODATA_REORDER,
	/*12*/ CT_RODATA_BBOX,
	/*13*/ CT_RODATA_CHRGUNFIRE,
	/*14*/ CT_RODATA_11,
	/*15*/ CT_RODATA_TOGGLE,
	/*16*/ CT_RODATA_POSITIONHELD,
	/*17*/ CT_RODATA_STARGUNFIRE,
	/*18*/ CT_RODATA_HEADSPOT,
	/*19*/ CT_RODATA_DL,
	/*20*/ CT_RODATA_19,
	/*21*/ CT_VTXCOL4,	// CT_VTXCOL but aligned to 4 bytes instead of 8
	/*22*/ CT_SKIP,	// to skip padding data
};

struct marker {
	u32 src_offset;
	u32 dst_offset;
	u32 parent_src_offset;
	enum contenttype type;
};

struct alignconfig {
	int before;
	int after;
};

struct alignconfig m_AlignConfigs[] = {
	/* 0*/ { 16, 4 },
	/* 1*/ { 4,  4 },
	/* 2*/ { 4,  4 },
	/* 3*/ { 8,  8 }, // CT_TEXDATA
	/* 4*/ { 4,  4 },
	/* 5*/ { 8,  4 }, // CT_VTXCOL
	/* 6*/ { 8,  8 }, // CT_GDL
	/* 7*/ { 4,  4 },
	/* 8*/ { 4,  4 },
	/* 9*/ { 8,  4 }, // CT_GUNDL
	/*10*/ { 4,  4 },
	/*11*/ { 4,  4 },
	/*12*/ { 4,  4 },
	/*13*/ { 4,  4 },
	/*14*/ { 4,  4 },
	/*15*/ { 4,  4 },
	/*16*/ { 4,  4 },
	/*17*/ { 8,  4 }, // CT_STARGUNFIRE
	/*18*/ { 4,  4 },
	/*19*/ { 8,  4 }, // CT_RODATA_DL
	/*20*/ { 4,  4 },
	/*21*/ { 4,  4 },
	/*22*/ { 4,  4 }
};

struct marker m_Markers[1024];
int m_NumMarkers;

struct src_modeldef {
	u32 ptr_rootnode;
	u32 ptr_skel;
	u32 ptr_parts;
	s16 numparts;
	s16 nummatrices;
	u32 scale;
	u16 rwdatalen;
	u16 numtexconfigs;
	u32 ptr_texconfigs;
};

struct dst_modeldef {
	uintptr_t ptr_rootnode;
	uintptr_t ptr_skel;
	uintptr_t ptr_parts;
	s16 numparts;
	s16 nummatrices;
	u32 scale;
	u16 rwdatalen;
	u16 numtexconfigs;
	uintptr_t ptr_texconfigs;
};

struct src_modelnode {
	u16 type;
	u32 ptr_rodata;
	u32 ptr_parent;
	u32 ptr_next;
	u32 ptr_prev;
	u32 ptr_child;
};

struct dst_modelnode {
	u16 type;
	uintptr_t ptr_rodata;
	uintptr_t ptr_parent;
	uintptr_t ptr_next;
	uintptr_t ptr_prev;
	uintptr_t ptr_child;
};

struct generic_rodata_chrinfo {
	u16 animpart;
	s16 mtxindex;
	u32 unk04;
	u16 rwdataindex;
};

struct generic_rodata_position {
	u32 pos[3];
	u16 part;
	s16 mtxindexes[3];
	u32 drawdist;
};

struct src_rodata_gundl {
	u32 ptr_opagdl;
	u32 ptr_xlugdl;
	u32 ptr_baseaddr;
	u32 ptr_vertices;
	s16 numvertices;
	s16 unk12;
};

struct dst_rodata_gundl {
	uintptr_t ptr_opagdl;
	uintptr_t ptr_xlugdl;
	uintptr_t ptr_baseaddr;
	uintptr_t ptr_vertices;
	s16 numvertices;
	s16 unk12;
};

struct src_rodata_distance {
	u32 near;
	u32 far;
	u32 ptr_target;
	u16 rwdataindex;
};

struct dst_rodata_distance {
	u32 near;
	u32 far;
	uintptr_t ptr_target;
	u16 rwdataindex;
};

struct src_rodata_reorder {
	u32 unk00;
	u32 unk04;
	u32 unk08;
	u32 unk0c[3];
	u32 ptr_node_unk18;
	u32 ptr_node_unk1c;
	s16 side;
	u16 rwdataindex;
};

struct dst_rodata_reorder {
	u32 unk00;
	u32 unk04;
	u32 unk08;
	u32 unk0c[3];
	uintptr_t ptr_node_unk18;
	uintptr_t ptr_node_unk1c;
	s16 side;
	u16 rwdataindex;
};

struct generic_rodata_bbox {
	s32 hitpart;
	u32 bbox[6];
};

struct src_rodata_chrgunfire {
	u32 pos[3];
	u32 dim[3];
	u32 ptr_texture;
	u32 unk1c;
	u16 rwdataindex;
	u32 ptr_baseaddr;
};

struct dst_rodata_chrgunfire {
	u32 pos[3];
	u32 dim[3];
	uintptr_t ptr_texture;
	u32 unk1c;
	u16 rwdataindex;
	uintptr_t ptr_baseaddr;
};

struct src_rodata_type11 {
	u32 unk00;
	u32 unk04;
	u32 unk08;
	u32 unk0c;
	u32 unk10;
	u32 ptr_unk14; // not used
	u32 extra1;
	u32 extra2;
};

struct dst_rodata_type11 {
	u32 unk00;
	u32 unk04;
	u32 unk08;
	u32 unk0c;
	u32 unk10;
	u32 unk14;
	u32 extra1;
	u32 extra2;
};

struct src_rodata_toggle {
	u32 ptr_target;
	u16 rwdataindex;
};

struct dst_rodata_toggle {
	uintptr_t ptr_target;
	u16 rwdataindex;
};

struct generic_rodata_positionheld {
	u32 pos[3];
	s16 mtxindex;
	u32 unk10;
};

struct src_rodata_stargunfire {
	u32 unk00;
	u32 ptr_vertices;
	u32 ptr_gdl;
	u32 ptr_baseaddr;
};

struct dst_rodata_stargunfire {
	u32 unk00;
	uintptr_t ptr_vertices;
	uintptr_t ptr_gdl;
	uintptr_t ptr_baseaddr;
};

struct generic_rodata_headspot {
	u16 rwdataindex;
};

struct src_rodata_dl {
	u32 ptr_opagdl;
	u32 ptr_xlugdl;
	u32 ptr_colours;
	u32 ptr_vertices; // colours follow this array
	s16 numvertices;
	s16 mcount;
	u16 rwdataindex;
	u16 numcolours;
};

struct dst_rodata_dl {
	uintptr_t ptr_opagdl;
	uintptr_t ptr_xlugdl;
	uintptr_t ptr_colours;
	uintptr_t ptr_vertices; // colours follow this array
	s16 numvertices;
	s16 mcount;
	u16 rwdataindex;
	u16 numcolours;
};

struct generic_rodata_type19 {
	u32 numvertices;
	u32 vertices[3];
};

struct src_texconfig {
	u32 ptr;
	u8 width;
	u8 height;
	u8 level;
	u8 format;
	u8 depth;
	u8 s;
	u8 t;
	u8 unk0b;
};

struct dst_texconfig {
	uintptr_t ptr;
	u8 width;
	u8 height;
	u8 level;
	u8 format;
	u8 depth;
	u8 s;
	u8 t;
	u8 unk0b;
};

static inline uintptr_t minPtr(uintptr_t a, uintptr_t b) {
	return (a && (a < b || !b)) ? a : b;
}

static inline uintptr_t minPtr3(uintptr_t a, uintptr_t b, uintptr_t c) {
	return minPtr(minPtr(a, b), c);
}

static struct marker *find_marker(u32 src_offset)
{
	for (int i = 0; i < m_NumMarkers; i++) {
		if (m_Markers[i].src_offset == src_offset) {
			return &m_Markers[i];
		}
	}

	return NULL;
}

static void set_marker(u32 src_offset, enum contenttype type, u32 parent_src_offset)
{
	if (src_offset == 0) {
		return;
	}

	src_offset &= 0x00ffffff;

	if (find_marker(src_offset)) {
		return;
	}

	if (m_NumMarkers >= ARRAYCOUNT(m_Markers)) {
		fprintf(stderr, "Marker limit exceeded\n");
		exit(EXIT_FAILURE);
	}

	m_Markers[m_NumMarkers].src_offset = src_offset;
	m_Markers[m_NumMarkers].type = type;
	m_Markers[m_NumMarkers].parent_src_offset = parent_src_offset;
	m_NumMarkers++;
}

enum contenttype m_NodeTypeToContentType[] = {
	/*0x00*/ -1,
	/*0x01*/ CT_RODATA_CHRINFO,
	/*0x02*/ CT_RODATA_POSITION,
	/*0x03*/ -1,
	/*0x04*/ CT_RODATA_GUNDL,
	/*0x05*/ -1,
	/*0x06*/ -1,
	/*0x07*/ -1,
	/*0x08*/ CT_RODATA_DISTANCE,
	/*0x09*/ CT_RODATA_REORDER,
	/*0x0a*/ CT_RODATA_BBOX,
	/*0x0b*/ -1,
	/*0x0c*/ CT_RODATA_CHRGUNFIRE,
	/*0x0d*/ -1,
	/*0x0e*/ -1,
	/*0x0f*/ -1,
	/*0x10*/ -1,
	/*0x11*/ CT_RODATA_11,
	/*0x12*/ CT_RODATA_TOGGLE,
	/*0x13*/ -1,
	/*0x14*/ -1,
	/*0x15*/ CT_RODATA_POSITIONHELD,
	/*0x16*/ CT_RODATA_STARGUNFIRE,
	/*0x17*/ CT_RODATA_HEADSPOT,
	/*0x18*/ CT_RODATA_DL,
	/*0x19*/ CT_RODATA_19,
};

static void populateMarkers(u8 *src)
{
	m_NumMarkers = 0;

	set_marker(0x05000000, CT_MODELDEF, 0);

	for (int i = 0; i < m_NumMarkers; i++) {
		struct marker *marker = &m_Markers[i];
		void *src_thing = &src[marker->src_offset];
		int numvtx = 0;
		u32 colstart = 0;

		switch (marker->type) {
		case CT_MODELDEF:
			struct src_modeldef *src_modeldef = src_thing;
			int num_texconfigs = srctoh16(src_modeldef->numtexconfigs);
			u32 texconfigpos = srctoh32(src_modeldef->ptr_texconfigs);
			set_marker(srctoh32(src_modeldef->ptr_rootnode), CT_NODE, marker->src_offset);
			set_marker(srctoh32(src_modeldef->ptr_parts), CT_PARTS, marker->src_offset);

			for (int i = 0; i < num_texconfigs; i++) {
				set_marker(texconfigpos + sizeof(struct src_texconfig) * i, CT_TEXCONFIG, marker->src_offset);
			}
			break;
		case CT_NODE:
			struct src_modelnode *src_node = src_thing;
			u32 node_type = srctoh16(src_node->type) & 0xff;
			set_marker(srctoh32(src_node->ptr_rodata), m_NodeTypeToContentType[node_type], marker->src_offset);
			set_marker(srctoh32(src_node->ptr_parent), CT_NODE, marker->src_offset);
			set_marker(srctoh32(src_node->ptr_next), CT_NODE, marker->src_offset);
			set_marker(srctoh32(src_node->ptr_prev), CT_NODE, marker->src_offset);
			set_marker(srctoh32(src_node->ptr_child), CT_NODE, marker->src_offset);
			break;
		case CT_TEXCONFIG:
			struct src_texconfig *src_texconfig = src_thing;
			if ((srctoh32(src_texconfig->ptr) & 0xff000000) == 0x05000000) {
				set_marker(srctoh32(src_texconfig->ptr), CT_TEXDATA, marker->src_offset);
			}
			break;
		case CT_PARTS:
			struct src_modeldef *src_modeldef2 = (struct src_modeldef *) src;
			u32 *src_parts = (u32 *) src_thing;
			int num_parts = srctoh16(src_modeldef2->numparts);

			for (int i = 0; i < num_parts; i++) {
				set_marker(srctoh32(src_parts[i]), CT_NODE, marker->src_offset);
			}
			break;
		case CT_RODATA_CHRINFO:
			break;
		case CT_RODATA_POSITION:
			break;
		case CT_RODATA_GUNDL:
			struct src_rodata_gundl *src_gundl = src_thing;
			set_marker(srctoh32(src_gundl->ptr_opagdl), CT_GDL, marker->src_offset);
			set_marker(srctoh32(src_gundl->ptr_xlugdl), CT_GDL, marker->src_offset);
			set_marker(srctoh32(src_gundl->ptr_vertices), CT_VTXCOL, marker->src_offset);
			break;
		case CT_RODATA_DISTANCE:
			struct src_rodata_distance *src_dist = src_thing;
			set_marker(srctoh32(src_dist->ptr_target), CT_NODE, marker->src_offset);
			break;
		case CT_RODATA_REORDER:
			struct src_rodata_reorder *src_reorder = src_thing;
			set_marker(srctoh32(src_reorder->ptr_node_unk18), CT_NODE, marker->src_offset);
			set_marker(srctoh32(src_reorder->ptr_node_unk1c), CT_NODE, marker->src_offset);
			break;
		case CT_RODATA_CHRGUNFIRE:
			struct src_rodata_chrgunfire *src_chrgunfire = src_thing;
			set_marker(srctoh32(src_chrgunfire->ptr_texture), CT_TEXCONFIG, marker->src_offset);
			break;
		case CT_RODATA_TOGGLE:
			struct src_rodata_toggle *src_toggle = src_thing;
			set_marker(srctoh32(src_toggle->ptr_target), CT_NODE, marker->src_offset);
			break;
		case CT_RODATA_STARGUNFIRE:
			struct src_rodata_stargunfire *src_stargunfire = src_thing;
			colstart = srctoh32(src_stargunfire->unk00)*4*(sizeof(s16) * 6);
			u32 vtxstart = srctoh32(src_stargunfire->ptr_vertices);
			u32 vtxend = vtxstart + colstart;
			colstart = ALIGN8(vtxstart + colstart);
			set_marker(vtxstart, CT_VTXCOL4, marker->src_offset);
			if (vtxend != colstart) { 
				set_marker(vtxend, CT_SKIP, marker->src_offset);
			}
			set_marker(colstart, CT_VTXCOL, marker->src_offset);
			set_marker(srctoh32(src_stargunfire->ptr_gdl), CT_GDL, marker->src_offset);
			break;
		case CT_RODATA_DL:
			struct src_rodata_dl *src_dl = src_thing;
			set_marker(srctoh32(src_dl->ptr_opagdl), CT_GDL, marker->src_offset);
			set_marker(srctoh32(src_dl->ptr_xlugdl), CT_GDL, marker->src_offset);
			set_marker(srctoh32(src_dl->ptr_colours), CT_VTXCOL, marker->src_offset);
			set_marker(srctoh32(src_dl->ptr_vertices), CT_VTXCOL, marker->src_offset);
			break;
		case CT_TEXDATA:
		case CT_VTXCOL:
		case CT_GDL:
		case CT_RODATA_BBOX:
		case CT_RODATA_11:
		case CT_RODATA_POSITIONHELD:
		case CT_RODATA_HEADSPOT:
		case CT_RODATA_19:
			break;
		}
	}
}

static void sortMarkers(void)
{
	for (int i = 0; i < m_NumMarkers - 1; i++) {
		u32 min_offset = 0xffffffff;
		int min_index = -1;

		for (int j = i + 1; j < m_NumMarkers; j++) {
			if (m_Markers[j].src_offset < min_offset) {
				min_offset = m_Markers[j].src_offset;
				min_index = j;
			}
		}

		if (min_index >= 0 && m_Markers[min_index].src_offset < m_Markers[i].src_offset) {
			struct marker tmp = m_Markers[i];
			m_Markers[i] = m_Markers[min_index];
			m_Markers[min_index] = tmp;
		}
	}
}

static u32 convertContent(u8 *dst, u8 *src, u32 src_file_len)
{
	u32 dstpos = 0;

	for (int i = 0; i < m_NumMarkers; i++) {
		struct marker *marker = &m_Markers[i];
		void *src_thing = &src[marker->src_offset];
		u32 src_end = i < m_NumMarkers - 1 ? m_Markers[i + 1].src_offset : src_file_len;
		u32 src_len = src_end - marker->src_offset;

		dstpos = ALIGN(dstpos, m_AlignConfigs[marker->type].before);

		marker->dst_offset = dstpos;
		void *dst_thing = &dst[dstpos];

		switch (marker->type) {
		case CT_MODELDEF:
			struct src_modeldef *src_modeldef = src_thing;
			struct dst_modeldef *dst_modeldef = dst_thing;
			dst_modeldef->ptr_skel = srctodst32(src_modeldef->ptr_skel);
			dst_modeldef->numparts = srctodst16(src_modeldef->numparts);
			dst_modeldef->nummatrices = srctodst16(src_modeldef->nummatrices);
			dst_modeldef->scale = srctodst32(src_modeldef->scale);
			dst_modeldef->rwdatalen = srctodst16(src_modeldef->rwdatalen);
			dst_modeldef->numtexconfigs = srctodst16(src_modeldef->numtexconfigs);
			dstpos += sizeof(*dst_modeldef);
			break;
		case CT_NODE:
			struct src_modelnode *src_node = src_thing;
			struct dst_modelnode *dst_node = dst_thing;
			dst_node->type = srctodst16(src_node->type);
			dstpos += sizeof(*dst_node);
			break;
		case CT_TEXCONFIG:
			struct src_texconfig *src_texconfig = src_thing;
			struct dst_texconfig *dst_texconfig = dst_thing;

			while (src_len >= sizeof(*src_texconfig)) {
				if ((srctoh32(src_texconfig->ptr) & 0xff000000) != 0x05000000) {
					dst_texconfig->ptr = srctodst32(src_texconfig->ptr);
				}

				dst_texconfig->width = src_texconfig->width;
				dst_texconfig->height = src_texconfig->height;
				dst_texconfig->level = src_texconfig->level;
				dst_texconfig->format = src_texconfig->format;
				dst_texconfig->depth = src_texconfig->depth;
				dst_texconfig->s = src_texconfig->s;
				dst_texconfig->t = src_texconfig->t;
				dst_texconfig->unk0b = src_texconfig->unk0b;

				dstpos += sizeof(*dst_texconfig);
				src_len -= sizeof(*src_texconfig);
				src_texconfig++;
				dst_texconfig++;
			}
			break;
		case CT_TEXDATA:
			memcpy(dst_thing, src_thing, src_len);
			dstpos += src_len;
			break;
		case CT_PARTS:
			struct src_modeldef *src_modeldef2 = (struct src_modeldef *) src;
			u32 *src_parts = (u32 *) src_thing;
			uintptr_t *dst_parts = (uintptr_t *) dst_thing;
			int num_parts = srctoh16(src_modeldef2->numparts);
			u16 *src_nums = (u16 *) &src_parts[num_parts];
			u16 *dst_nums = (u16 *) &dst_parts[num_parts];

			for (int i = 0; i < num_parts; i++) {
				dst_nums[i] = srctodst16(src_nums[i]);
			}
			dstpos += num_parts * sizeof(uintptr_t) + num_parts * sizeof(u16);
			if (num_parts) {
				dstpos = ALIGN8(dstpos);
			}
			break;
		case CT_VTXCOL:
		case CT_VTXCOL4:
			memcpy(dst_thing, src_thing, src_len);
			dstpos += src_len;
			break;
		case CT_GDL:
			struct marker *parent = find_marker(marker->parent_src_offset);
			u32 src_vtx;
			u32 dst_vtx;

			if (parent->type == CT_RODATA_GUNDL) {
				struct src_rodata_gundl *src_rodata = (struct src_rodata_gundl *) &src[parent->src_offset];
				struct dst_rodata_gundl *dst_rodata = (struct dst_rodata_gundl *) &dst[parent->dst_offset];
				src_vtx = srctoh32(src_rodata->ptr_vertices) & 0x00ffffff;
				dst_vtx = dsttoh32(dst_rodata->ptr_vertices) & 0x00ffffff;
			} else if (parent->type == CT_RODATA_STARGUNFIRE) {
				struct src_rodata_stargunfire *src_rodata = (struct src_rodata_stargunfire *) &src[parent->src_offset];
				struct dst_rodata_stargunfire *dst_rodata = (struct dst_rodata_stargunfire *) &dst[parent->dst_offset];
				src_vtx = srctoh32(src_rodata->ptr_vertices) & 0x00ffffff;
				dst_vtx = dsttoh32(dst_rodata->ptr_vertices) & 0x00ffffff;
			} else if (parent->type == CT_RODATA_DL) {
				struct src_rodata_dl *src_rodata = (struct src_rodata_dl *) &src[parent->src_offset];
				struct dst_rodata_dl *dst_rodata = (struct dst_rodata_dl *) &dst[parent->dst_offset];
				src_vtx = srctoh32(src_rodata->ptr_vertices) & 0x00ffffff;
				dst_vtx = dsttoh32(dst_rodata->ptr_vertices) & 0x00ffffff;
			}

			dstpos = gbiConvertGdl(dst, dstpos, src, marker->src_offset, 0);
			break;
		case CT_RODATA_CHRINFO:
			struct generic_rodata_chrinfo *src_chrinfo = src_thing;
			struct generic_rodata_chrinfo *dst_chrinfo = dst_thing;
			dst_chrinfo->animpart = srctodst16(src_chrinfo->animpart);
			dst_chrinfo->mtxindex = srctodst16(src_chrinfo->mtxindex);
			dst_chrinfo->unk04 = srctodst32(src_chrinfo->unk04);
			dst_chrinfo->rwdataindex = srctodst16(src_chrinfo->rwdataindex);
			dstpos += sizeof(*dst_chrinfo);
			break;
		case CT_RODATA_POSITION:
			struct generic_rodata_position *src_position = src_thing;
			struct generic_rodata_position *dst_position = dst_thing;
			dst_position->pos[0] = srctodst32(src_position->pos[0]);
			dst_position->pos[1] = srctodst32(src_position->pos[1]);
			dst_position->pos[2] = srctodst32(src_position->pos[2]);
			dst_position->part = srctodst16(src_position->part);
			dst_position->mtxindexes[0] = srctodst16(src_position->mtxindexes[0]);
			dst_position->mtxindexes[1] = srctodst16(src_position->mtxindexes[1]);
			dst_position->mtxindexes[2] = srctodst16(src_position->mtxindexes[2]);
			dst_position->drawdist = srctodst32(src_position->drawdist);
			dstpos += sizeof(*dst_position);
			break;
		case CT_RODATA_GUNDL:
			struct src_rodata_gundl *src_gundl = src_thing;
			struct dst_rodata_gundl *dst_gundl = dst_thing;
			dst_gundl->ptr_vertices = 0;
			dst_gundl->numvertices = srctodst16(src_gundl->numvertices);
			dst_gundl->unk12 = srctodst16(src_gundl->unk12);
			dstpos += sizeof(*dst_gundl);
			break;
		case CT_RODATA_DISTANCE:
			struct src_rodata_distance *src_dist = src_thing;
			struct dst_rodata_distance *dst_dist = dst_thing;
			dst_dist->near = srctodst32(src_dist->near);
			dst_dist->far = srctodst32(src_dist->far);
			dst_dist->rwdataindex = srctodst16(src_dist->rwdataindex);
			dstpos += sizeof(*dst_dist);
			break;
		case CT_RODATA_REORDER:
			struct src_rodata_reorder *src_reorder = src_thing;
			struct dst_rodata_reorder *dst_reorder = dst_thing;
			dst_reorder->unk00 = srctodst32(src_reorder->unk00);
			dst_reorder->unk04 = srctodst32(src_reorder->unk04);
			dst_reorder->unk08 = srctodst32(src_reorder->unk08);
			dst_reorder->unk0c[0] = srctodst32(src_reorder->unk0c[0]);
			dst_reorder->unk0c[1] = srctodst32(src_reorder->unk0c[1]);
			dst_reorder->unk0c[2] = srctodst32(src_reorder->unk0c[2]);
			dst_reorder->side = srctodst16(src_reorder->side);
			dst_reorder->rwdataindex = srctodst16(src_reorder->rwdataindex);
			dstpos += sizeof(*dst_reorder);
			break;
		case CT_RODATA_BBOX:
			struct generic_rodata_bbox *src_bbox = src_thing;
			struct generic_rodata_bbox *dst_bbox = dst_thing;
			dst_bbox->hitpart = srctodst32(src_bbox->hitpart);
			dst_bbox->bbox[0] = srctodst32(src_bbox->bbox[0]);
			dst_bbox->bbox[1] = srctodst32(src_bbox->bbox[1]);
			dst_bbox->bbox[2] = srctodst32(src_bbox->bbox[2]);
			dst_bbox->bbox[3] = srctodst32(src_bbox->bbox[3]);
			dst_bbox->bbox[4] = srctodst32(src_bbox->bbox[4]);
			dst_bbox->bbox[5] = srctodst32(src_bbox->bbox[5]);
			dstpos += sizeof(*dst_bbox);
			break;
		case CT_RODATA_CHRGUNFIRE:
			struct src_rodata_chrgunfire *src_chrgunfire = src_thing;
			struct dst_rodata_chrgunfire *dst_chrgunfire = dst_thing;
			dst_chrgunfire->pos[0] = srctodst32(src_chrgunfire->pos[0]);
			dst_chrgunfire->pos[1] = srctodst32(src_chrgunfire->pos[1]);
			dst_chrgunfire->pos[2] = srctodst32(src_chrgunfire->pos[2]);
			dst_chrgunfire->dim[0] = srctodst32(src_chrgunfire->dim[0]);
			dst_chrgunfire->dim[1] = srctodst32(src_chrgunfire->dim[1]);
			dst_chrgunfire->dim[2] = srctodst32(src_chrgunfire->dim[2]);
			dst_chrgunfire->unk1c = srctodst32(src_chrgunfire->unk1c);
			dst_chrgunfire->rwdataindex = srctodst16(src_chrgunfire->rwdataindex);
			dst_chrgunfire->ptr_baseaddr = 0;
			dstpos += sizeof(*dst_chrgunfire);
			break;
		case CT_RODATA_11:
			struct src_rodata_type11 *src_type11 = src_thing;
			struct dst_rodata_type11 *dst_type11 = dst_thing;
			dst_type11->unk00 = srctodst32(src_type11->unk00);
			dst_type11->unk04 = srctodst32(src_type11->unk04);
			dst_type11->unk08 = srctodst32(src_type11->unk08);
			dst_type11->unk0c = srctodst32(src_type11->unk0c);
			dst_type11->unk10 = srctodst32(src_type11->unk10);
			dst_type11->extra1 = srctodst32(src_type11->extra1);
			dst_type11->extra2 = srctodst32(src_type11->extra2);
			dstpos += sizeof(*dst_type11);
			break;
		case CT_RODATA_TOGGLE:
			struct src_rodata_toggle *src_toggle = src_thing;
			struct dst_rodata_toggle *dst_toggle = dst_thing;
			dst_toggle->rwdataindex = srctodst16(src_toggle->rwdataindex);
			dstpos += sizeof(*dst_toggle);
			break;
		case CT_RODATA_POSITIONHELD:
			struct generic_rodata_positionheld *src_posheld = src_thing;
			struct generic_rodata_positionheld *dst_posheld = dst_thing;
			dst_posheld->pos[0] = srctodst32(src_posheld->pos[0]);
			dst_posheld->pos[1] = srctodst32(src_posheld->pos[1]);
			dst_posheld->pos[2] = srctodst32(src_posheld->pos[2]);
			dst_posheld->mtxindex = srctodst16(src_posheld->mtxindex);
			dst_posheld->unk10 = srctodst32(src_posheld->unk10);
			dstpos += sizeof(*dst_posheld);
			break;
		case CT_RODATA_STARGUNFIRE:
			struct src_rodata_stargunfire *src_stargunfire = src_thing;
			struct dst_rodata_stargunfire *dst_stargunfire = dst_thing;
			dst_stargunfire->unk00 = srctodst32(src_stargunfire->unk00);
			dstpos += sizeof(*dst_stargunfire);
			break;
		case CT_RODATA_HEADSPOT:
			struct generic_rodata_headspot *src_headspot = src_thing;
			struct generic_rodata_headspot *dst_headspot = dst_thing;
			dst_headspot->rwdataindex = srctodst16(src_headspot->rwdataindex);
			dstpos += sizeof(*dst_headspot);
			break;
		case CT_RODATA_DL:
			struct src_rodata_dl *src_dl = src_thing;
			struct dst_rodata_dl *dst_dl = dst_thing;
			dst_dl->numvertices = srctodst16(src_dl->numvertices);
			dst_dl->mcount = srctodst16(src_dl->mcount);
			dst_dl->rwdataindex = srctodst16(src_dl->rwdataindex);
			dst_dl->numcolours = srctodst16(src_dl->numcolours);
			dstpos += sizeof(*dst_dl);
			break;
		case CT_RODATA_19:
			struct generic_rodata_type19 *src_type19 = src_thing;
			struct generic_rodata_type19 *dst_type19 = dst_thing;
			u32 *src_vertices = src_thing + sizeof(u32);
			u32 *dst_vertices = dst_thing + sizeof(u32);
			int num_vertices = srctoh32(src_type19->numvertices);

			dst_type19->numvertices = htodst32(num_vertices);
			dstpos += sizeof(u32);

			for (int i = 0; i < num_vertices; i++) {
				dst_vertices[i * 3 + 0] = srctodst32(src_vertices[i * 3 + 0]);
				dst_vertices[i * 3 + 1] = srctodst32(src_vertices[i * 3 + 1]);
				dst_vertices[i * 3 + 2] = srctodst32(src_vertices[i * 3 + 2]);
				dstpos += sizeof(u32) * 3;
			}
			break;
		case CT_SKIP: 
			break;
		}

		dstpos = ALIGN(dstpos, m_AlignConfigs[marker->type].after);
	}

	return dstpos;
}

static u32 resolvePointer(u32 src_offset)
{
	if (src_offset == 0) {
		return 0;
	}

	struct marker *marker = find_marker(src_offset & 0x00ffffff);
	return marker ? (0x05000000 | marker->dst_offset) : 0;
}

static u8 *relinkPointers(u8 *dst, u8 *src)
{
	uintptr_t textures_end = 0;

	for (int i = 0; i < m_NumMarkers; i++) {
		struct marker *marker = &m_Markers[i];
		void *src_thing = &src[marker->src_offset];
		void *dst_thing = &dst[marker->dst_offset];
		
		uintptr_t lowestptr = 0;

		switch (marker->type) {
		case CT_MODELDEF:
			struct src_modeldef *src_modeldef = src_thing;
			struct dst_modeldef *dst_modeldef = dst_thing;
			dst_modeldef->ptr_rootnode = htodst32(resolvePointer(srctoh32(src_modeldef->ptr_rootnode)));
			dst_modeldef->ptr_parts = htodst32(resolvePointer(srctoh32(src_modeldef->ptr_parts)));
			dst_modeldef->ptr_texconfigs = htodst32(resolvePointer(srctoh32(src_modeldef->ptr_texconfigs)));
			break;
		case CT_NODE:
			struct src_modelnode *src_node = src_thing;
			struct dst_modelnode *dst_node = dst_thing;
			dst_node->ptr_rodata = htodst32(resolvePointer(srctoh32(src_node->ptr_rodata)));
			dst_node->ptr_parent = htodst32(resolvePointer(srctoh32(src_node->ptr_parent)));
			dst_node->ptr_next = htodst32(resolvePointer(srctoh32(src_node->ptr_next)));
			dst_node->ptr_prev = htodst32(resolvePointer(srctoh32(src_node->ptr_prev)));
			dst_node->ptr_child = htodst32(resolvePointer(srctoh32(src_node->ptr_child)));

			lowestptr = dst_node->ptr_rodata;
			break;
		case CT_TEXCONFIG:
			struct src_texconfig *src_texconfig = src_thing;
			struct dst_texconfig *dst_texconfig = dst_thing;
			if ((srctoh32(src_texconfig->ptr) & 0xff000000) == 0x05000000) {
				dst_texconfig->ptr = htodst32(resolvePointer(srctoh32(src_texconfig->ptr)));
				gbiAddTexAddr(srctoh32(src_texconfig->ptr), dst_texconfig->ptr);
			}
			break;
		case CT_PARTS:
			struct src_modeldef *src_modeldef2 = (struct src_modeldef *) src;
			u32 *src_parts = (u32 *) src_thing;
			uintptr_t *dst_parts = (uintptr_t *) dst_thing;
			int num_parts = srctoh16(src_modeldef2->numparts);

			for (int i = 0; i < num_parts; i++) {
				dst_parts[i] = htodst32(resolvePointer(srctoh32(src_parts[i])));
			}
			break;
		case CT_RODATA_CHRINFO:
			break;
		case CT_RODATA_POSITION:
			break;
		case CT_RODATA_GUNDL:
			struct src_rodata_gundl *src_gundl = src_thing;
			struct dst_rodata_gundl *dst_gundl = dst_thing;
			dst_gundl->ptr_opagdl = htodst32(resolvePointer(srctoh32(src_gundl->ptr_opagdl)));
			dst_gundl->ptr_xlugdl = htodst32(resolvePointer(srctoh32(src_gundl->ptr_xlugdl)));
			dst_gundl->ptr_vertices = htodst32(resolvePointer(srctoh32(src_gundl->ptr_vertices)));
			
			gbiConvertVtx(dst, dst_gundl->ptr_vertices & 0x00ffffff, dst_gundl->numvertices);

			gbiSetVtx(srctoh32(src_gundl->ptr_vertices), dst_gundl->ptr_vertices);
			gbiSetSegment(0x04, dst_gundl->ptr_vertices);

			gbiGdlRewriteAddrs(dst, dst_gundl->ptr_opagdl);
			gbiGdlRewriteAddrs(dst, dst_gundl->ptr_xlugdl);

			if (dst_gundl->ptr_opagdl) dst_gundl->ptr_opagdl |= 1;
			if (dst_gundl->ptr_xlugdl) dst_gundl->ptr_xlugdl |= 1;

			lowestptr = minPtr3(dst_gundl->ptr_opagdl, dst_gundl->ptr_xlugdl, dst_gundl->ptr_vertices);
			break;
		case CT_RODATA_DISTANCE:
			struct src_rodata_distance *src_dist = src_thing;
			struct dst_rodata_distance *dst_dist = dst_thing;
			dst_dist->ptr_target = htodst32(resolvePointer(srctoh32(src_dist->ptr_target)));
			break;
		case CT_RODATA_REORDER:
			struct src_rodata_reorder *src_reorder = src_thing;
			struct dst_rodata_reorder *dst_reorder = dst_thing;
			dst_reorder->ptr_node_unk18 = htodst32(resolvePointer(srctoh32(src_reorder->ptr_node_unk18)));
			dst_reorder->ptr_node_unk1c = htodst32(resolvePointer(srctoh32(src_reorder->ptr_node_unk1c)));
			break;
		case CT_RODATA_CHRGUNFIRE:
			struct src_rodata_chrgunfire *src_chrgunfire = src_thing;
			struct dst_rodata_chrgunfire *dst_chrgunfire = dst_thing;
			dst_chrgunfire->ptr_texture = htodst32(resolvePointer(srctoh32(src_chrgunfire->ptr_texture)));
			if ((srctoh32(dst_chrgunfire->ptr_texture) & 0xff000000) == 0x05000000) {
				gbiAddTexAddr(srctoh32(dst_chrgunfire->ptr_texture), dst_chrgunfire->ptr_texture);
			}
			break;
		case CT_RODATA_TOGGLE:
			struct src_rodata_toggle *src_toggle = src_thing;
			struct dst_rodata_toggle *dst_toggle = dst_thing;
			dst_toggle->ptr_target = htodst32(resolvePointer(srctoh32(src_toggle->ptr_target)));
			break;
		case CT_RODATA_STARGUNFIRE:
			struct src_rodata_stargunfire *src_stargunfire = src_thing;
			struct dst_rodata_stargunfire *dst_stargunfire = dst_thing;
			dst_stargunfire->ptr_vertices = htodst32(resolvePointer(srctoh32(src_stargunfire->ptr_vertices)));
			dst_stargunfire->ptr_gdl = htodst32(resolvePointer(srctoh32(src_stargunfire->ptr_gdl)));

			gbiConvertVtx(dst, dst_stargunfire->ptr_vertices & 0x00ffffff, dst_stargunfire->unk00*4);

			gbiSetVtx(srctoh32(src_stargunfire->ptr_vertices), dst_stargunfire->ptr_vertices);
			gbiSetSegment(0x04, dst_stargunfire->ptr_vertices);
			gbiGdlRewriteAddrs(dst, dst_stargunfire->ptr_gdl);
			if (dst_stargunfire->ptr_gdl) dst_stargunfire->ptr_gdl |= 1;

			lowestptr = minPtr(dst_stargunfire->ptr_gdl, dst_stargunfire->ptr_vertices);
			break;
		case CT_RODATA_DL:
			struct src_rodata_dl *src_dl = src_thing;
			struct dst_rodata_dl *dst_dl = dst_thing;
			dst_dl->ptr_opagdl = htodst32(resolvePointer(srctoh32(src_dl->ptr_opagdl)));
			dst_dl->ptr_xlugdl = htodst32(resolvePointer(srctoh32(src_dl->ptr_xlugdl)));
			dst_dl->ptr_colours = htodst32(resolvePointer(srctoh32(src_dl->ptr_colours)));
			dst_dl->ptr_vertices = htodst32(resolvePointer(srctoh32(src_dl->ptr_vertices)));
			
			gbiConvertVtx(dst, dst_dl->ptr_vertices & 0x00ffffff, dst_dl->numvertices);

			gbiSetVtx(srctoh32(src_dl->ptr_vertices), dst_dl->ptr_vertices);
			gbiSetSegment(0x04, dst_dl->ptr_vertices);
			gbiGdlRewriteAddrs(dst, dst_dl->ptr_opagdl);
			gbiGdlRewriteAddrs(dst, dst_dl->ptr_xlugdl);
			
			if (dst_dl->ptr_opagdl) dst_dl->ptr_opagdl |= 1;
			if (dst_dl->ptr_xlugdl) dst_dl->ptr_xlugdl |= 1;

			lowestptr = minPtr3(dst_dl->ptr_opagdl, dst_dl->ptr_xlugdl, dst_dl->ptr_colours);
			lowestptr = minPtr(lowestptr, dst_dl->ptr_vertices);
			break;
		case CT_TEXDATA:
		case CT_VTXCOL:
		case CT_VTXCOL4:
		case CT_GDL:
		case CT_RODATA_BBOX:
		case CT_RODATA_11:
		case CT_RODATA_POSITIONHELD:
		case CT_RODATA_HEADSPOT:
		case CT_RODATA_19:
			break;
		}

		textures_end = minPtr(textures_end, lowestptr);
	}

	return (u8*)textures_end;
}

static void preprocessTextureRGBA32Embedded(u32* dest, u32 size_bytes)
{
	for (uint32_t i = 0; i < size_bytes; i += 4, ++dest) {
		*dest = PD_BE32(*dest);
	}
}

static void preprocessModelTextures(u8 *base, u8 *textures_end)
{
	struct modeldef* mdl = (struct modeldef*)base;
	if (!mdl->texconfigs) return;

	u32 ofs = 0x5000000;
	struct textureconfig* texconfigs = PD_PTR_BASEOFS(mdl->texconfigs, base, ofs);
	for (s16 i = 0; i < mdl->numtexconfigs; ++i) {
		if ((texconfigs[i].texturenum & 0xf000000) == 0x5000000) {
			// embedded texture; we need to unswizzle this
			u8* texdata = PD_PTR_BASEOFS(texconfigs[i].textureptr, base, ofs);
			// figure out the max possible size the texture can have, because sometimes the texconfig is wrong
			const u32 maxSize = (textures_end > texconfigs[i].textureptr) ? (textures_end - texconfigs[i].textureptr) : 0;
			// figure out the format and unswizzle
			const s32 format = texConfigToFormat(&texconfigs[i]);
			texSwizzleInternal(texdata, texconfigs[i].width, texconfigs[i].height, format, maxSize);

			if (format == TEXFORMAT_RGBA32) {
				// for some reason, RGBA32 embedded textures don't need to be byte-swapped,
				// so we byte-swap them here, which will be undone when the renderer imports it
				u32 size_bytes = texconfigs[i].width * texconfigs[i].height * 4;
				preprocessTextureRGBA32Embedded((u32*)texdata, size_bytes);
			}
		}
	}
}

static int convertModel(u8* dst, u8* src, u32 srclen)
{
	u32 dstpos;

	populateMarkers(src);
	sortMarkers();

	dstpos = convertContent(dst, src, srclen);
	u8* tex_end = relinkPointers(dst, src);
	preprocessModelTextures(dst, tex_end);

	return dstpos;
}

u8 *preprocessModelFile(u8 *data, u32 size, u32 *outSize)
{
	gbiReset();

	u32 newSizeEstimated = romdataFileGetEstimatedSize(size, FT_MODEL);
	u8 *dst = sysMemZeroAlloc(newSizeEstimated);

	u32 newSize = convertModel(dst, data, size);

	if (newSize > newSizeEstimated) {
		sysLogPrintf(LOG_ERROR, "overflow when trying to preprocess model, size %d newsize %d", size, newSize);
		exit(EXIT_FAILURE);
	}
	
	memcpy(data, dst, newSize);
	sysMemFree(dst);

	*outSize = newSize;

	return 0;
}

u8 *preprocessGunFile(u8 *data, u32 size, u32 *outSize)
{
	gbiReset();

	u32 newSizeEstimated = romdataFileGetEstimatedSize(size, FT_MODEL);
	u8 *dst = sysMemZeroAlloc(newSizeEstimated+128);

	u32 newSize = convertModel(dst, data, size);

	if (newSize > newSizeEstimated) {
		sysLogPrintf(LOG_ERROR, "overflow when trying to preprocess model, size %d newsize %d", size, newSize);
		exit(EXIT_FAILURE);
	}

	memcpy(data, dst, newSize);
	sysMemFree(dst);

	*outSize = newSize;

	return 0;
}
