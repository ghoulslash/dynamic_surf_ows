#include "defines.h"
#include "config.h"
#include "pal_tags.h"
#include "../include/global.h"
#include "../include/field_effect.h"
#include "../include/species.h"
#include "../include/moves.h"
#include "../include/sprite.h"
#include "../include/gba/types.h"
#include "../include/fieldmap.h"


#define PAL_TAG_SURF_BLOB 0x1100
#define PAL_TAG_SURF_NEW 0x3001

#define NO_OVERLAY {0, 0, NULL, NULL, NULL, NULL, NULL}

#define overworld_frame(ptr, width, height, frame) {.data = (u8 *)ptr + (width * height * frame * 64)/2, .size = (width * height * 64)/2}
#define surf_template(tag, image, cb) {.tileTag = 0xFFFF, .paletteTag = tag, .oam = gEventObjectBaseOam_32x32, .anims = gSurfablePokemonAnimTable, .images = image, .affineAnims = gDummySpriteAffineAnimTable, .callback = cb}

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

extern const u32 tentacoolTiles[];
extern const u16 tentacoolPal[];
extern const u16 tentacoolShinyPal[];

extern const u32 tentacruelTiles[];
extern const u16 tentacruelPal[];
extern const u16 tentacruelShinyPal[];

extern const u32 seelTiles[];
extern const u16 seelPal[];
extern const u16 seelShinyPal[];

extern const u32 dewgongTiles[];
extern const u16 dewgongPal[];
extern const u16 dewgongShinyPal[];

extern const u32 laprasTiles[];
extern const u16 laprasPal[];
extern const u16 laprasShinyPal[];

extern const u32 vaporeonTiles[];
extern const u16 vaporeonPal[];
extern const u16 vaporeonShinyPal[];

extern const u32 wailmerTiles[];
extern const u16 wailmerPal[];
extern const u16 wailmerShinyPal[];

/*================================================
	OVERWORLD FRAMES (by index)
================================================*/
//===== SQUIRTLE
const struct SpriteFrameImage gSurfingOverworldPicTable_Squirtle[] = {
    overworld_frame(&squirtleTiles[0], 4, 4, 1),
    overworld_frame(&squirtleTiles[0], 4, 4, 0),
    overworld_frame(&squirtleTiles[0], 4, 4, 3),
    overworld_frame(&squirtleTiles[0], 4, 4, 2),
    overworld_frame(&squirtleTiles[0], 4, 4, 5),
    overworld_frame(&squirtleTiles[0], 4, 4, 4),
};
const struct SpriteFrameImage gSurfingOverlayPicTable_Squirtle[] = {
    overworld_frame(&squirtleTiles[0], 4, 4, 7),
    overworld_frame(&squirtleTiles[0], 4, 4, 6),
    overworld_frame(&squirtleTiles[0], 4, 4, 9),
    overworld_frame(&squirtleTiles[0], 4, 4, 8),
    overworld_frame(&squirtleTiles[0], 4, 4, 11),
    overworld_frame(&squirtleTiles[0], 4, 4, 10),
};

//===== WARTORTLE
const struct SpriteFrameImage gSurfingOverworldPicTable_Wartortle[] = {
    overworld_frame(&wartortleTiles[0], 4, 4, 1),
    overworld_frame(&wartortleTiles[0], 4, 4, 0),
    overworld_frame(&wartortleTiles[0], 4, 4, 3),
    overworld_frame(&wartortleTiles[0], 4, 4, 2),
    overworld_frame(&wartortleTiles[0], 4, 4, 5),
    overworld_frame(&wartortleTiles[0], 4, 4, 4),
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
const struct SpriteFrameImage gSurfingOverworldPicTable_Blastoise[] = {
    overworld_frame(&blastoiseTiles[0], 4, 4, 1),
    overworld_frame(&blastoiseTiles[0], 4, 4, 0),
    overworld_frame(&blastoiseTiles[0], 4, 4, 3),
    overworld_frame(&blastoiseTiles[0], 4, 4, 2),
    overworld_frame(&blastoiseTiles[0], 4, 4, 5),
    overworld_frame(&blastoiseTiles[0], 4, 4, 4),
};
const struct SpriteFrameImage gSurfingOverlayPicTable_Blastoise[] = {
    overworld_frame(&blastoiseTiles[0], 4, 4, 7),
    overworld_frame(&blastoiseTiles[0], 4, 4, 6),
    overworld_frame(&blastoiseTiles[0], 4, 4, 9),
    overworld_frame(&blastoiseTiles[0], 4, 4, 8),
    overworld_frame(&blastoiseTiles[0], 4, 4, 11),
    overworld_frame(&blastoiseTiles[0], 4, 4, 10),
};
	
//===== NIDOQUEEN
//===== NIDOKING
//===== PSYDUCK
//===== GOLDUCK
//===== POLIWAG
//===== POLIWHIRL
//===== POLIWRATH
//===== TENTACOOL
const struct SpriteFrameImage gSurfingOverworldPicTable_Tentacool[] = {
    overworld_frame(&tentacoolTiles[0], 4, 4, 1),
    overworld_frame(&tentacoolTiles[0], 4, 4, 0),
    overworld_frame(&tentacoolTiles[0], 4, 4, 3),
    overworld_frame(&tentacoolTiles[0], 4, 4, 2),
    overworld_frame(&tentacoolTiles[0], 4, 4, 5),
    overworld_frame(&tentacoolTiles[0], 4, 4, 4),
};
const struct SpriteFrameImage gSurfingOverlayPicTable_Tentacool[] = {
    overworld_frame(&tentacoolTiles[0], 4, 4, 7),
    overworld_frame(&tentacoolTiles[0], 4, 4, 6),
    overworld_frame(&tentacoolTiles[0], 4, 4, 9),
    overworld_frame(&tentacoolTiles[0], 4, 4, 8),
    overworld_frame(&tentacoolTiles[0], 4, 4, 11),
    overworld_frame(&tentacoolTiles[0], 4, 4, 10),
};

//===== TENTACRUEL
const struct SpriteFrameImage gSurfingOverworldPicTable_Tentacruel[] = {
    overworld_frame(&tentacruelTiles[0], 4, 4, 1),
    overworld_frame(&tentacruelTiles[0], 4, 4, 0),
    overworld_frame(&tentacruelTiles[0], 4, 4, 3),
    overworld_frame(&tentacruelTiles[0], 4, 4, 2),
    overworld_frame(&tentacruelTiles[0], 4, 4, 4),
    overworld_frame(&tentacruelTiles[0], 4, 4, 5),
};
const struct SpriteFrameImage gSurfingOverlayPicTable_Tentacruel[] = {
    overworld_frame(&tentacruelTiles[0], 4, 4, 7),
    overworld_frame(&tentacruelTiles[0], 4, 4, 6),
    overworld_frame(&tentacruelTiles[0], 4, 4, 9),
    overworld_frame(&tentacruelTiles[0], 4, 4, 8),
    overworld_frame(&tentacruelTiles[0], 4, 4, 11),
    overworld_frame(&tentacruelTiles[0], 4, 4, 10),
};

//===== SLOWPOKE
//===== SLOWBRO
//===== SEEL
const struct SpriteFrameImage gSurfingOverworldPicTable_Seel[] = {
    overworld_frame(&seelTiles[0], 4, 4, 1),
    overworld_frame(&seelTiles[0], 4, 4, 0),
    overworld_frame(&seelTiles[0], 4, 4, 3),
    overworld_frame(&seelTiles[0], 4, 4, 2),
    overworld_frame(&seelTiles[0], 4, 4, 5),
    overworld_frame(&seelTiles[0], 4, 4, 4),
};
const struct SpriteFrameImage gSurfingOverlayPicTable_Seel[] = {
    overworld_frame(&seelTiles[0], 4, 4, 7),
    overworld_frame(&seelTiles[0], 4, 4, 6),
    overworld_frame(&seelTiles[0], 4, 4, 9),
    overworld_frame(&seelTiles[0], 4, 4, 8),
    overworld_frame(&seelTiles[0], 4, 4, 11),
    overworld_frame(&seelTiles[0], 4, 4, 10),
};

//===== DEWGONG
const struct SpriteFrameImage gSurfingOverworldPicTable_Dewgong[] = {
    overworld_frame(&dewgongTiles[0], 4, 4, 1),
    overworld_frame(&dewgongTiles[0], 4, 4, 0),
    overworld_frame(&dewgongTiles[0], 4, 4, 3),
    overworld_frame(&dewgongTiles[0], 4, 4, 2),
    overworld_frame(&dewgongTiles[0], 4, 4, 5),
    overworld_frame(&dewgongTiles[0], 4, 4, 4),
};
const struct SpriteFrameImage gSurfingOverlayPicTable_Dewgong[] = {
    overworld_frame(&dewgongTiles[0], 4, 4, 7),
    overworld_frame(&dewgongTiles[0], 4, 4, 6),
    overworld_frame(&dewgongTiles[0], 4, 4, 9),
    overworld_frame(&dewgongTiles[0], 4, 4, 8),
    overworld_frame(&dewgongTiles[0], 4, 4, 11),
    overworld_frame(&dewgongTiles[0], 4, 4, 10),
};

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
const struct SpriteFrameImage gSurfingOverworldPicTable_Vaporeon[] = {
    overworld_frame(&vaporeonTiles[0], 4, 4, 1),
    overworld_frame(&vaporeonTiles[0], 4, 4, 0),
    overworld_frame(&vaporeonTiles[0], 4, 4, 3),
    overworld_frame(&vaporeonTiles[0], 4, 4, 2),
    overworld_frame(&vaporeonTiles[0], 4, 4, 5),
    overworld_frame(&vaporeonTiles[0], 4, 4, 4),
};
const struct SpriteFrameImage gSurfingOverlayPicTable_Vaporeon[] = {
    overworld_frame(&vaporeonTiles[0], 4, 4, 7),
    overworld_frame(&vaporeonTiles[0], 4, 4, 6),
    overworld_frame(&vaporeonTiles[0], 4, 4, 9),
    overworld_frame(&vaporeonTiles[0], 4, 4, 8),
    overworld_frame(&vaporeonTiles[0], 4, 4, 11),
    overworld_frame(&vaporeonTiles[0], 4, 4, 10),
};

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
//===== SQUIRTLE
const struct SpriteTemplate sSquirtleOverworld = surf_template(PAL_TAG_SURF_NEW, gSurfingOverworldPicTable_Squirtle, UpdateSurfBlobFieldEffect);
const struct SpriteTemplate sSquirtleOverlay = surf_template(PAL_TAG_SURF_NEW, gSurfingOverlayPicTable_Squirtle, UpdateSurfMonOverlay);

//===== WARTORTLE
const struct SpriteTemplate sWartortleOverworld = surf_template(PAL_TAG_SURF_NEW, gSurfingOverworldPicTable_Wartortle, UpdateSurfBlobFieldEffect);
const struct SpriteTemplate sWartortleOverlay = surf_template(PAL_TAG_SURF_NEW, gSurfingOverlayPicTable_Wartortle, UpdateSurfMonOverlay);

//===== BLASTOISE
const struct SpriteTemplate sBlastoiseOverworld = surf_template(PAL_TAG_SURF_NEW, gSurfingOverworldPicTable_Blastoise, UpdateSurfBlobFieldEffect);
const struct SpriteTemplate sBlastoiseOverlay = surf_template(PAL_TAG_SURF_NEW, gSurfingOverlayPicTable_Blastoise, UpdateSurfMonOverlay);

//===== NIDOQUEEN
//===== NIDOKING
//===== PSYDUCK
//===== GOLDUCK
//===== POLIWAG
//===== POLIWHIRL
//===== POLIWRATH
//===== TENTACOOL
const struct SpriteTemplate sTentacoolOverworld = surf_template(PAL_TAG_SURF_NEW, gSurfingOverworldPicTable_Tentacool, UpdateSurfBlobFieldEffect);
const struct SpriteTemplate sTentacoolOverlay = surf_template(PAL_TAG_SURF_NEW, gSurfingOverlayPicTable_Tentacool, UpdateSurfMonOverlay);

//===== TENTACRUEL
const struct SpriteTemplate sTentacruelOverworld = surf_template(PAL_TAG_SURF_NEW, gSurfingOverworldPicTable_Tentacruel, UpdateSurfBlobFieldEffect);
const struct SpriteTemplate sTentacruelOverlay = surf_template(PAL_TAG_SURF_NEW, gSurfingOverlayPicTable_Tentacruel, UpdateSurfMonOverlay);

//===== SLOWPOKE
//===== SLOWBRO

//===== SEEL
const struct SpriteTemplate sSeelOverworld = surf_template(PAL_TAG_SURF_NEW, gSurfingOverworldPicTable_Seel, UpdateSurfBlobFieldEffect);
const struct SpriteTemplate sSeelOverlay = surf_template(PAL_TAG_SURF_NEW, gSurfingOverlayPicTable_Seel, UpdateSurfMonOverlay);

//===== DEWGONG
const struct SpriteTemplate sDewgongOverworld = surf_template(PAL_TAG_SURF_NEW, gSurfingOverworldPicTable_Dewgong, UpdateSurfBlobFieldEffect);
const struct SpriteTemplate sDewgongOverlay = surf_template(PAL_TAG_SURF_NEW, gSurfingOverlayPicTable_Dewgong, UpdateSurfMonOverlay);

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
const struct SpriteTemplate sLaprasOverworld = surf_template(PAL_TAG_SURF_NEW, gSurfingOverworldPicTable_Lapras, UpdateSurfBlobFieldEffect);
const struct SpriteTemplate sLaprasOverlay = surf_template(PAL_TAG_SURF_NEW, gSurfingOverlayPicTable_Lapras, UpdateSurfMonOverlay);

//===== VAPOREON
const struct SpriteTemplate sVaporeonOverworld = surf_template(PAL_TAG_SURF_NEW, gSurfingOverworldPicTable_Vaporeon, UpdateSurfBlobFieldEffect);
const struct SpriteTemplate sVaporeonOverlay = surf_template(PAL_TAG_SURF_NEW, gSurfingOverlayPicTable_Vaporeon, UpdateSurfMonOverlay);

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
const struct SpriteTemplate sWailmerOverworld = surf_template(PAL_TAG_SURF_NEW, gSurfingOverworldPicTable_Wailmer, UpdateSurfBlobFieldEffect);
const struct SpriteTemplate sWailmerOverlay = surf_template(PAL_TAG_SURF_NEW, gSurfingOverlayPicTable_Wailmer, UpdateSurfMonOverlay);

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
		.palAddr = &squirtlePal[0],
		.shinyPalAddr = &squirtleShinyPal[0],
		.overworldGfx = &sSquirtleOverworld,
		.overlayGfx = &sSquirtleOverlay,
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
		.palAddr = &blastoisePal[0],
		.shinyPalAddr = 0,
		.overworldGfx = &sBlastoiseOverworld,
		.overlayGfx = &sBlastoiseOverlay,
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
		.palAddr = &tentacoolPal[0],
		.shinyPalAddr = &tentacoolShinyPal[0],
		.overworldGfx = &sTentacoolOverworld,
		.overlayGfx = &sTentacoolOverlay,
	},
	{
		.species = SPECIES_TENTACRUEL,
		.palAddr = &tentacruelPal[0],
		.shinyPalAddr = &tentacruelShinyPal[0],
		.overworldGfx = &sTentacruelOverworld,
		.overlayGfx = &sTentacruelOverlay,
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
		.palAddr = &seelPal[0],
		.shinyPalAddr = &seelShinyPal[0],
		.overworldGfx = &sSeelOverworld,
		.overlayGfx = &sSeelOverlay,
	},
	{
		.species = SPECIES_DEWGONG,
		.palAddr = &dewgongPal[0],
		.shinyPalAddr = 0,
		.overworldGfx = &sDewgongOverworld,
		.overlayGfx = &sDewgongOverlay,
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
		.shinyPalAddr = &laprasShinyPal[0],
		.overworldGfx = &sLaprasOverworld,
		.overlayGfx = &sLaprasOverlay,
	},
	{
		.species = SPECIES_VAPOREON,
		.palAddr = &vaporeonPal[0],
		.shinyPalAddr = &vaporeonShinyPal[0],
		.overworldGfx = &sVaporeonOverworld,
		.overlayGfx = &sVaporeonOverlay,
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
		.palAddr = &wailmerPal[0],
		.shinyPalAddr = &wailmerShinyPal[0],
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
