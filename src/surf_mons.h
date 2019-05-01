#include "defines.h"
#include "config.h"
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
//extern const u16 laprasShinyPal[];

extern const u32 wailmerTiles[];
extern const u16 wailmerPal[];




/*
you only need one pal tag based on the way they are now loaded.
If you want more, uncomment out UNIQUE_TAGS in config.h and assign each to the species in gSurfablePokemon
*/
#define PAL_TAG_NEW_SURF_BLOB 0x3001

#ifdef UNIQUE_TAGS
enum {
	PAL_TAG_SQUIRTLE_SURF = 0x3001,
	PAL_TAG_WARTORTLE_SURF,
    PAL_TAG_BLASTOISE_SURF,
    PAL_TAG_NIDOQUEEN_SURF,
    PAL_TAG_NIDOKING_SURF,
    PAL_TAG_PSYDUCK_SURF,
    PAL_TAG_GOLDUCK_SURF,
    PAL_TAG_POLIWAG_SURF,
    PAL_TAG_POLIWHIRL_SURF,
    PAL_TAG_POLIWRATH_SURF,
    PAL_TAG_TENTACOOL_SURF,
    PAL_TAG_TENTACRUEL_SURF,
    PAL_TAG_SLOWPOKE_SURF,
    PAL_TAG_SLOWBRO_SURF,
    PAL_TAG_SEEL_SURF,
    PAL_TAG_DEWGONG_SURF,
    PAL_TAG_SHELLDER_SURF,
    PAL_TAG_CLOYSTER_SURF,
    PAL_TAG_KRABBY_SURF,
    PAL_TAG_KINGLER_SURF,
    PAL_TAG_LICKTUNG_SURF,
    PAL_TAG_RHYDON_SURF,
    PAL_TAG_KANGASKHAN_SURF,
    PAL_TAG_HORSEA_SURF,
    PAL_TAG_SEADRA_SURF,
    PAL_TAG_GOLDEEN_SURF,
    PAL_TAG_SEAKING_SURF,
    PAL_TAG_STARYU_SURF,
    PAL_TAG_STARMIE_SURF,
    PAL_TAG_TAUROS_SURF,
    PAL_TAG_GYARADOS_SURF,
    PAL_TAG_LAPRAS_SURF,
    PAL_TAG_VAPOREON_SURF,
    PAL_TAG_OMANYTE_SURF,
    PAL_TAG_OMASTAR_SURF,
    PAL_TAG_KABUTO_SURF,
    PAL_TAG_KABUTOPS_SURF,
    PAL_TAG_SNORLAX_SURF,
    PAL_TAG_DRATINI_SURF,
    PAL_TAG_DRAGONAIR_SURF,
    PAL_TAG_DRAGONITE_SURF,
    PAL_TAG_MEW_SURF,
// Gen II Pokemon
    PAL_TAG_TOTODILE_SURF,
    PAL_TAG_CROCONAW_SURF,
    PAL_TAG_FERALIGATR_SURF,
    PAL_TAG_SENTRET_SURF,
    PAL_TAG_FURRET_SURF,
    PAL_TAG_CHINCHOU_SURF,
    PAL_TAG_LANTURN_SURF,
    PAL_TAG_MARILL_SURF,
    PAL_TAG_AZUMARILL_SURF,
    PAL_TAG_POLITOED_SURF,
    PAL_TAG_WOOPER_SURF,
    PAL_TAG_QUAGSIRE_SURF,
    PAL_TAG_SLOWKING_SURF,
    PAL_TAG_QWILFISH_SURF,
    PAL_TAG_SNEASEL_SURF,
    PAL_TAG_CORSOLA_SURF,
    PAL_TAG_REMORAID_SURF,
    PAL_TAG_OCTILLERY_SURF,
    PAL_TAG_MANTINE_SURF,
    PAL_TAG_KINGDRA_SURF,
    PAL_TAG_MILTANK_SURF,
    PAL_TAG_SUICUNE_SURF,
    PAL_TAG_TYRANITAR_SURF,
    PAL_TAG_LUGIA_SURF,
// Gen III Pokemon
    PAL_TAG_MUDKIP_SURF,
    PAL_TAG_MARSHTOMP_SURF,
    PAL_TAG_SWAMPERT_SURF,
    PAL_TAG_ZIGZAGOON_SURF,
    PAL_TAG_LINOONE_SURF,
    PAL_TAG_LOTAD_SURF,
    PAL_TAG_LOMBRE_SURF,
    PAL_TAG_LUDICOLO_SURF,
    PAL_TAG_PELIPPER_SURF,
    PAL_TAG_EXPLOUD_SURF,
    PAL_TAG_MAKUHITA_SURF,
    PAL_TAG_HARIYAMA_SURF,
    PAL_TAG_AZURILL_SURF,
    PAL_TAG_AGGRON_SURF,
    PAL_TAG_CARVANHA_SURF,
    PAL_TAG_SHARPEDO_SURF,
    PAL_TAG_WAILMER_SURF,
    PAL_TAG_WAILORD_SURF,
    PAL_TAG_BARBOACH_SURF,
    PAL_TAG_WHISCASH_SURF,
    PAL_TAG_CORPHISH_SURF,
    PAL_TAG_CRAWDAUNT_SURF,
    PAL_TAG_FEEBAS_SURF,
    PAL_TAG_MILOTIC_SURF,
    PAL_TAG_SPHEAL_SURF,
    PAL_TAG_SEALEO_SURF,
    PAL_TAG_WALREIN_SURF,
    PAL_TAG_CLAMPERL_SURF,
    PAL_TAG_HUNTAIL_SURF,
    PAL_TAG_GOREBYSS_SURF,
    PAL_TAG_RELICANTH_SURF,
    PAL_TAG_LUVDISC_SURF,
    PAL_TAG_LATIAS_SURF,
    PAL_TAG_LATIOS_SURF,
    PAL_TAG_KYOGRE_SURF,
    PAL_TAG_RAYQUAZA_SURF,
};
#endif

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

//===== WARTORTLE
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

//===== BLASTOISE
//===== NIDOQUEEN
//===== NIDOKING
//===== PSYDUCK
//===== GOLDUCK
//===== POLIWAG
//===== POLIWHIRL
//===== POLIWRATH
//===== TENTACOOL
//===== TENTACRUEL
//===== SLOWPOKE
//===== SLOWBRO
//===== SEEL
//===== DEWGONG
//===== SHELLDER
//===== CLOYSTER
//===== KRABBY
//===== KINGLER
//===== LICKTUNG
//===== RHYDON
//===== KANGASKHAN
//===== HORSEA
//===== SEADRA
//===== GOLDEEN
//===== SEAKING
//===== STARYU
//===== STARMIE
//===== TAUROS
//===== GYARADOS
//===== LAPRAS
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

//===== VAPOREON
//===== OMANYTE
//===== OMASTAR
//===== KABUTO
//===== KABUTOPS
//===== SNORLAX
//===== DRATINI
//===== DRAGONAIR
//===== DRAGONITE
//===== MEW
//===== 
//===== TOTODILE
//===== CROCONAW
//===== FERALIGATR
//===== SENTRET
//===== FURRET
//===== CHINCHOU
//===== LANTURN
//===== MARILL
//===== AZUMARILL
//===== POLITOED
//===== WOOPER
//===== QUAGSIRE
//===== SLOWKING
//===== QWILFISH
//===== SNEASEL
//===== CORSOLA
//===== REMORAID
//===== OCTILLERY
//===== MANTINE
//===== KINGDRA
//===== MILTANK
//===== SUICUNE
//===== TYRANITAR
//===== LUGIA
//===== 
//===== MUDKIP
//===== MARSHTOMP
//===== SWAMPERT
//===== ZIGZAGOON
//===== LINOONE
//===== LOTAD
//===== LOMBRE
//===== LUDICOLO
//===== PELIPPER
//===== EXPLOUD
//===== MAKUHITA
//===== HARIYAMA
//===== AZURILL
//===== AGGRON
//===== CARVANHA
//===== SHARPEDO
//===== WAILMER
const struct SpriteFrameImage gSurfingOverworldPicTable_Wailmer[] = {
    overworld_frame(&wailmerTiles[0], 4, 4, 1),
    overworld_frame(&wailmerTiles[0], 4, 4, 0),
    overworld_frame(&wailmerTiles[0], 4, 4, 3),
    overworld_frame(&wailmerTiles[0], 4, 4, 2),
    overworld_frame(&wailmerTiles[0], 4, 4, 5),
    overworld_frame(&wailmerTiles[0], 4, 4, 4),
    overworld_frame(&wailmerTiles[0], 4, 4, 7),
    overworld_frame(&wailmerTiles[0], 4, 4, 6),
};
const struct SpriteFrameImage gSurfingOverlayPicTable_Wailmer[] = {
    overworld_frame(&wailmerTiles[0], 4, 4, 7),
    overworld_frame(&wailmerTiles[0], 4, 4, 6),
    overworld_frame(&wailmerTiles[0], 4, 4, 9),
    overworld_frame(&wailmerTiles[0], 4, 4, 8),
    overworld_frame(&wailmerTiles[0], 4, 4, 11),
    overworld_frame(&wailmerTiles[0], 4, 4, 10),
};

//===== WAILORD
//===== BARBOACH
//===== WHISCASH
//===== CORPHISH
//===== CRAWDAUNT
//===== FEEBAS
//===== MILOTIC
//===== SPHEAL
//===== SEALEO
//===== WALREIN
//===== CLAMPERL
//===== HUNTAIL
//===== GOREBYSS
//===== RELICANTH
//===== LUVDISC
//===== LATIAS
//===== LATIOS
//===== KYOGRE
//===== RAYQUAZA



/*==================================================
	SPRITE TEMPLATES
==================================================*/
/*
//===== SQUIRTLE
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

//===== WARTORTLE
const struct SpriteTemplate sWartortleOverworld = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_NEW_SURF_BLOB,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverworldPicTable_Wartortle,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfBlobFieldEffect,
};
const struct SpriteTemplate sWartortleOverlay = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_NEW_SURF_BLOB,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverlayPicTable_Wartortle,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfMonOverlay,
};
//===== BLASTOISE
//===== NIDOQUEEN
//===== NIDOKING


//===== LAPRAS
const struct SpriteTemplate sLaprasOverworld = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_NEW_SURF_BLOB,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverworldPicTable_Lapras,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfBlobFieldEffect,
};
const struct SpriteTemplate sLaprasOverlay = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_NEW_SURF_BLOB,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverlayPicTable_Lapras,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfMonOverlay,
};

//===== WAILMER
const struct SpriteTemplate sWailmerOverworld = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_NEW_SURF_BLOB,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverworldPicTable_Wailmer,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfBlobFieldEffect,
};
const struct SpriteTemplate sWailmerOverlay = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_NEW_SURF_BLOB,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverlayPicTable_Wailmer,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfMonOverlay,
};

/*==================================================
	RIDEABLE POKEMON STRUCTURE
==================================================*/

struct RideableMons
{
	u16 species;
	u16 filler;
	const u16* palAddr;
	const u16* shinyPalAddr;
	const struct SpriteTemplate* overworldGfx;
	const struct SpriteTemplate* overlayGfx;
};

const struct RideableMons gSurfablePokemon[] =
{
	{
		.species = SPECIES_SQUIRTLE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_WARTORTLE,
		.palAddr = &wartortlePal[0],
		.shinyPalAddr = &wartortleShinyPal[0],
		.overworldGfx = &sWartortleOverworld,
		.overlayGfx = &sWartortleOverlay,
	},
	{
		.species = SPECIES_BLASTOISE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_NIDOQUEEN,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_NIDOKING,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_PSYDUCK,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_GOLDUCK,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_POLIWAG,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_POLIWHIRL,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_POLIWRATH,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_TENTACOOL,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_TENTACRUEL,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SLOWPOKE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SLOWBRO,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SEEL,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_DEWGONG,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SHELLDER,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_CLOYSTER,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_KRABBY,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_KINGLER,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_LICKITUNG,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_RHYDON,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_KANGASKHAN,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_HORSEA,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SEADRA,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_GOLDEEN,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SEAKING,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_STARYU,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_STARMIE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_TAUROS,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_GYARADOS,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_LAPRAS,
		.palAddr = &laprasPal[0],
		.shinyPalAddr = 0,
		.overworldGfx = &sLaprasOverworld,
		.overlayGfx = &sLaprasOverlay,
	},
	{
		.species = SPECIES_VAPOREON,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_OMANYTE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_OMASTAR,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_KABUTO,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_KABUTOPS,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SNORLAX,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_DRATINI,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_DRAGONAIR,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_DRAGONITE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_MEW,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_TOTODILE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_CROCONAW,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_FERALIGATR,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SENTRET,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_FURRET,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_CHINCHOU,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_LANTURN,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_MARILL,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_AZUMARILL,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_POLITOED,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_WOOPER,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_QUAGSIRE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SLOWKING,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_QWILFISH,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SNEASEL,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_CORSOLA,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_REMORAID,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_OCTILLERY,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_MANTINE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_KINGDRA,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_MILTANK,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SUICUNE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_TYRANITAR,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_LUGIA,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_MUDKIP,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_MARSHTOMP,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SWAMPERT,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_ZIGZAGOON,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_LINOONE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_LOTAD,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_LOMBRE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_LUDICOLO,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_PELIPPER,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_EXPLOUD,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_MAKUHITA,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_HARIYAMA,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_AZURILL,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_AGGRON,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_CARVANHA,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SHARPEDO,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_WAILMER,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = &sWailmerOverworld,
		.overlayGfx = &sWailmerOverlay,
	},
	{
		.species = SPECIES_WAILORD,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_BARBOACH,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_WHISCASH,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_CORPHISH,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_CRAWDAUNT,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_FEEBAS,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_MILOTIC,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SPHEAL,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_SEALEO,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_WALREIN,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_CLAMPERL,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_HUNTAIL,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_GOREBYSS,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_RELICANTH,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_LUVDISC,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_LATIAS,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_LATIOS,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_KYOGRE,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
	{
		.species = SPECIES_RAYQUAZA,
		.palAddr = 0,
		.shinyPalAddr = 0,
		.overworldGfx = sDefaultSurfBlob,
		.overlayGfx = 0,
	},
};
