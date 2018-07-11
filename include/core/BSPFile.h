/*
 * source-engine-map-renderer - A toy project for rendering source engine maps
 * Copyright (C) 2018 nyxxxie
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.	If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @file
 * @brief Contains definitions for constructs that exist in a BSP file.
 *
 */

#ifndef AQUAENGINE_CORE_BSPFILE_H
#define AQUAENGINE_CORE_BSPFILE_H

#include <export.h>

#define BSP_FILE_IDENTIFIER	(('P' << 24) + ( 'S' << 16) + ('B' << 8) + 'V')
#define BSP_TOTAL_LUMPS 64

#define LUMP_ENTITIES 0
#define LUMP_PLANES 1
#define LUMP_TEXDATA 2
#define LUMP_VERTEXES 3
#define LUMP_VISIBILITY 4
#define LUMP_NODES 5
#define LUMP_TEXINFO 6
#define LUMP_FACES 7
#define LUMP_LIGHTING 8
#define LUMP_OCCLUSION 9
#define LUMP_LEAFS 10
#define LUMP_FACEIDS 11
#define LUMP_EDGES 12
#define LUMP_SURFEDGES 13
#define LUMP_MODELS 14
#define LUMP_WORLDLIGHTS 15
#define LUMP_LEAFFACES 16
#define LUMP_LEAFBRUSHES 17
#define LUMP_BRUSHES 18
#define LUMP_BRUSHSIDES 19
#define LUMP_AREAS 20
#define LUMP_AREAPORTALS 21
#define LUMP_PORTALS 22
#define LUMP_UNUSED0 22
#define LUMP_PROPCOLLISION 22
#define LUMP_CLUSTERS 23
#define LUMP_UNUSED1 23
#define LUMP_PROPHULLS 23
#define LUMP_PORTALVERTS 24
#define LUMP_UNUSED2 24
#define LUMP_PROPHULLVERTS 24
#define LUMP_CLUSTERPORTALS 25
#define LUMP_UNUSED3 25
#define LUMP_PROPTRIS 25
#define LUMP_DISPINFO 26
#define LUMP_ORIGINALFACES 27
#define LUMP_PHYSDISP 28
#define LUMP_PHYSCOLLIDE 29
#define LUMP_VERTNORMALS 30
#define LUMP_VERTNORMALINDICES 31
#define LUMP_DISP_LIGHTMAP_ALPHAS 32
#define LUMP_DISP_VERTS 33
#define LUMP_DISP_LIGHTMAP_SAMPLE_POSITIONS 34
#define LUMP_GAME_LUMP 35
#define LUMP_LEAFWATERDATA 36
#define LUMP_PRIMITIVES 37
#define LUMP_PRIMVERTS 38
#define LUMP_PRIMINDICES 39
#define LUMP_PAKFILE 40
#define LUMP_CLIPPORTALVERTS 41
#define LUMP_CUBEMAPS 42
#define LUMP_TEXDATA_STRING_DATA 43
#define LUMP_TEXDATA_STRING_TABLE 44
#define LUMP_OVERLAYS 45
#define LUMP_LEAFMINDISTTOWATER 46
#define LUMP_FACE_MACRO_TEXTURE_INFO 47
#define LUMP_DISP_TRIS 48
#define LUMP_PHYSCOLLIDESURFACE 49
#define LUMP_PROP_BLOB 49
#define LUMP_WATEROVERLAYS 50
#define LUMP_LIGHTMAPPAGES 51
#define LUMP_LEAF_AMBIENT_INDEX_HDR 52
#define LUMP_LIGHTMAPPAGEINFOS 53
#define LUMP_LEAF_AMBIENT_INDEX 54
#define LUMP_LIGHTING_HDR 55
#define LUMP_WORLDLIGHTS_HDR 56
#define LUMP_LEAF_AMBIENT_LIGHTING_HDR 57
#define LUMP_LEAF_AMBIENT_LIGHTING 58
#define LUMP_XZIPPAKFILE 59
#define LUMP_FACES_HDR 60
#define LUMP_MAP_FLAGS 61
#define LUMP_OVERLAY_FADES 62
#define LUMP_DISP_MULTIBLEND 63


struct API bsp_lump_t {
	unsigned int file_offset;	// Where this lump's data is located
	unsigned int size;	// How much space this lump takes up
	unsigned int version;	// Version of this lump
	unsigned int identifier;	// Lump identifier code
} __attribute__((packed));

struct API bsp_header_t {
	unsigned int file_identifier;	// Should be equal to BSP_FILE_IDENTIFIER
	unsigned int version;	// Version of the BSP file format we're using
	bsp_lump_t lumps[BSP_TOTAL_LUMPS];	// The meat of the bsp file
	unsigned int map_revision;	// version number of the map
} __attribute__((packed));

struct API bsp_vertex_t {
	float x;
	float y;
	float z;
} __attribute__((packed));

struct API bsp_dplane_t
{
	float normal[3];
	float dist;
	int type;
};

struct API bsp_texinfo_t {
	float textureVecs[2][4];
	float lightmapVecs[2][4];
	int flags;
	int texdata;
} __attribute__((packed));

struct API bsp_edge_t {
	short unsigned int v[2];
} __attribute__((packed));

typedef int bsp_surfedge_t;

struct API bsp_face_t {
	short unsigned int plane_index;
	unsigned char side;
	unsigned char on_node;	//
	unsigned int first_edge;
	short unsigned int num_edges;
	short unsigned int tex_info;
	short unsigned int disp_info;
	short unsigned int surface_fog_volume_id;
	unsigned char styles[4];
	unsigned int light_offset;
	float area;
	unsigned int lightmap_mins[2];
	unsigned int lightmap_size[2];
	unsigned int orig_face;
	short unsigned int num_primitives;
	short unsigned int first_primitive;
	unsigned int smoothing_groups;
} __attribute__((packed));

#endif // AQUAENGINE_CORE_BSPFILE_H
