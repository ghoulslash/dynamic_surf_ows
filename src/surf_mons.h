#include "defines.h"
#include "../include/global.h"
#include "../include/field_effect.h"
#include "../include/species.h"
#include "../include/moves.h"
#include "../include/sprite.h"
#include "../include/gba/types.h"
#include "../include/fieldmap.h"

#define PAL_TAG_SURF_BLOB 0x1100
#define NO_OVERLAY {0, 0, NULL, NULL, NULL, NULL, NULL}

#define overworld_frame(ptr, width, height, frame) {.data = (u8 *)ptr + (width * height * frame * 64)/2, .size = (width * height * 64)/2}

extern s32 gFieldEffectArguments[8];
extern void UpdateSurfMonOverlay(struct Sprite *sprite);

const struct Coords16 sDirectionToVectors[] = {
    { 0,  0},
    { 0,  1},
    { 0, -1},
    {-1,  0},
    { 1,  0},
    {-1,  1},
    { 1,  1},
    {-1, -1},
    { 1, -1}
};


// Images
extern const u32 surfBlobTiles[];
extern const u16 surfBlobPal[];


extern const u32 squirtleTiles[];
extern const u16 squirtlePal[];
extern const u16 squirtleShinyPal[];

extern const u32 wartortleTiles[];
extern const u16 wartortlePal[];
extern const u16 wartortleShinyPal[];

extern const u32 blastoiseTiles[];
extern const u16 blastoisePal[];
extern const u16 blastoiseShinyPal[];

extern const u32 nidoqueenTiles[];
extern const u16 nidoqueenPal[];
extern const u16 nidoqueenShinyPal[];

extern const u32 nidokingTiles[];
extern const u16 nidokingPal[];
extern const u16 nidokingShinyPal[];

extern const u32 psyduckTiles[];
extern const u16 psyduckPal[];
extern const u16 psyduckShinyPal[];

extern const u32 golduckTiles[];
extern const u16 golduckPal[];
extern const u16 golduckShinyPal[];

extern const u32 poliwagTiles[];
extern const u16 poliwagPal[];
extern const u16 poliwagShinyPal[];

extern const u32 poliwhirlTiles[];
extern const u16 poliwhirlPal[];

extern const u32 poliwrathTiles[];
extern const u16 poliwrathPal[];

extern const u32 tentacoolTiles[];
extern const u16 tentacoolPal[];

extern const u32 tentacruelTiles[];
extern const u16 tentacruelPal[];

extern const u32 slowpokeTiles[];
extern const u16 slowpokePal[];

extern const u32 slowbroTiles[];
extern const u16 slowbroPal[];

extern const u32 seelTiles[];
extern const u16 seelPal[];

extern const u32 dewgongTiles[];
extern const u16 dewgongPal[];

extern const u32 Tiles[];
extern const u16 Pal[];

extern const u32 Tiles[];
extern const u16 Pal[];

extern const u32 Tiles[];
extern const u16 Pal[];

extern const u32 Tiles[];
extern const u16 Pal[];

extern const u32 Tiles[];
extern const u16 Pal[];

extern const u32 Tiles[];
extern const u16 Pal[];


extern const u32 laprasTiles[];
extern const u16 laprasPal[];




/*
Need to add pal pointer and tag to npc_pals (table pointer 5F4D8)
*/
enum
{
	PAL_TAG_SQUIRTLE_SURF = 0x3001,
	PAL_TAG_WARTORTLE_SURF,
	PAL_TAG_BLASTOISE_SURF,
	PAL_TAG_LAPRAS_SURF,
	//etc
};



/*================================================
	OVERWORLD FRAMES (by index)
================================================*/
//===== 00 SQUIRTLE
/*
const struct SpriteFrameImage gSurfingOverworldPicTable_Squirtle[] = {
    overworld_frame(&squirtleTiles[0], 4, 4, 1),
    overworld_frame(&squirtleTiles[0], 4, 4, 0),
    overworld_frame(&squirtleTiles[0], 4, 4, 3),
    overworld_frame(&squirtleTiles[0], 4, 4, 2),
    overworld_frame(&squirtleTiles[0], 4, 4, 5),
    overworld_frame(&squirtleTiles[0], 4, 4, 4),
    overworld_frame(&squirtleTiles[0], 4, 4, 7),
    overworld_frame(&squirtleTiles[0], 4, 4, 6),
};
const struct SpriteFrameImage gSurfingOverlayPicTable_Squirtle[] = {
    overworld_frame(&squirtleTiles[0], 4, 4, 7),
    overworld_frame(&squirtleTiles[0], 4, 4, 6),
    overworld_frame(&squirtleTiles[0], 4, 4, 9),
    overworld_frame(&squirtleTiles[0], 4, 4, 8),
    overworld_frame(&squirtleTiles[0], 4, 4, 11),
    overworld_frame(&squirtleTiles[0], 4, 4, 10),
};
*/

//===== 01 WARTORTLE
const struct SpriteFrameImage gSurfingOverworldPicTable_Wartortle[] = {
    overworld_frame(&wartortleTiles[0], 4, 4, 1),
    overworld_frame(&wartortleTiles[0], 4, 4, 0),
    overworld_frame(&wartortleTiles[0], 4, 4, 3),
    overworld_frame(&wartortleTiles[0], 4, 4, 2),
    overworld_frame(&wartortleTiles[0], 4, 4, 5),
    overworld_frame(&wartortleTiles[0], 4, 4, 4),
    overworld_frame(&wartortleTiles[0], 4, 4, 7),
    overworld_frame(&wartortleTiles[0], 4, 4, 6),
};
const struct SpriteFrameImage gSurfingOverlayPicTable_Wartortle[] = {
    overworld_frame(&wartortleTiles[0], 4, 4, 7),
    overworld_frame(&wartortleTiles[0], 4, 4, 6),
    overworld_frame(&wartortleTiles[0], 4, 4, 9),
    overworld_frame(&wartortleTiles[0], 4, 4, 8),
    overworld_frame(&wartortleTiles[0], 4, 4, 11),
    overworld_frame(&wartortleTiles[0], 4, 4, 10),
};

//===== 02 BLASTOISE

//===== 03 NIDOQUEEN

//===== 04 NIDOKING

//===== 05 PSYDUCK

//===== 06 GOLDUCK

//===== 07 POLIWAG

//===== 08 POLIWHIRL

//===== 09 POLIWRATH

//===== 10 TENTACOOL

//===== 11 TENTACRUEL

//===== 12 SLOWPOKE

//===== 13 SLOWBRO

//===== 14 SEEL

//===== 15 DEWGONG

//===== 16 

// LAPRAS
const struct SpriteFrameImage gSurfingOverworldPicTable_Lapras[] = {
    overworld_frame(&laprasTiles[0], 4, 4, 1),
    overworld_frame(&laprasTiles[0], 4, 4, 0),
    overworld_frame(&laprasTiles[0], 4, 4, 3),
    overworld_frame(&laprasTiles[0], 4, 4, 2),
    overworld_frame(&laprasTiles[0], 4, 4, 5),
    overworld_frame(&laprasTiles[0], 4, 4, 4),
    overworld_frame(&laprasTiles[0], 4, 4, 7),
    overworld_frame(&laprasTiles[0], 4, 4, 6),
};
const struct SpriteFrameImage gSurfingOverlayPicTable_Lapras[] = {
    overworld_frame(&laprasTiles[0], 4, 4, 7),
    overworld_frame(&laprasTiles[0], 4, 4, 6),
    overworld_frame(&laprasTiles[0], 4, 4, 9),
    overworld_frame(&laprasTiles[0], 4, 4, 8),
    overworld_frame(&laprasTiles[0], 4, 4, 11),
    overworld_frame(&laprasTiles[0], 4, 4, 10),
};


/*==================================================
	SPRITE TEMPLATES
==================================================*/
/*
//===== 00 SQUIRTLE
const struct SpriteTemplate sSquirtleOverworld = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_SQUIRTLE_SURF,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverworldPicTable_Squirtle,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfBlobFieldEffect,
};
const struct SpriteTemplate sSquirtleOverlay = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_WARTORTLE_SURF,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverlayPicTable_Wartortle,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfMonOverlay,
};
*/

//===== 01 WARTORTLE
const struct SpriteTemplate sWartortleOverworld = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_WARTORTLE_SURF,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverworldPicTable_Wartortle,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfBlobFieldEffect,
};
const struct SpriteTemplate sWartortleOverlay = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_WARTORTLE_SURF,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverlayPicTable_Wartortle,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfMonOverlay,
};
//===== 02 BLASTOISE

//===== 03 NIDOQUEEN


//===== LAPRAS
const struct SpriteTemplate sLaprasOverworld = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_LAPRAS_SURF,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverworldPicTable_Lapras,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfMonOverlay,
};
const struct SpriteTemplate sLaprasOverlay = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_LAPRAS_SURF,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverlayPicTable_Lapras,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfMonOverlay,
};


/*==================================================
	RIDEABLE POKEMON STRUCTURE
==================================================*/
struct RideableMons
{
	u16 species;
	u16 shinyPalTag;
	struct SpriteTemplate overworldGfx;
	struct SpriteTemplate overlayGfx;
};


const struct RideableMons gSurfablePokemon[] =
{
	{
		.species = SPECIES_WARTORTLE,
		.shinyPalTag = 0,
		.overworldGfx = sWartortleOverworld,
		.overlayGfx = sWartortleOverlay,
	},
	{
		.species = SPECIES_LAPRAS,
		.shinyPalTag = 0,
		.overworldGfx = sLaprasOverworld,
		.overlayGfx = sLaprasOverlay,
	},	
};


