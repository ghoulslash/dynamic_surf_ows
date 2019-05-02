#include "surf_mons.h"


extern u8 FindOrLoadNPCPalette(u16 PalTag);
extern u8 FindPalRef(u8 Type, u16 PalTag);
extern u8 PalRefIncreaseCount(u8 PalSlot);
extern u8 AddPalRef(u8 Type, u16 PalTag);
extern void MaskPaletteIfFadingIn(u8 PalSlot);

void UpdateSurfMonOverlay(struct Sprite *sprite);



bool8 IsShinyOtIdPersonality(u32 otId, u32 personality)
{
    bool8 retVal = FALSE;
    u32 shinyValue = HIHALF(otId) ^ LOHALF(otId) ^ HIHALF(personality) ^ LOHALF(personality);
    if (shinyValue < 8)
        retVal = TRUE;
    return retVal;
}

bool8 IsMonShiny(struct Pokemon *mon) {
    u32 otId = GetMonData(mon, MON_DATA_OT_ID, 0);
    u32 personality = GetMonData(mon, MON_DATA_PERSONALITY, 0);
    return IsShinyOtIdPersonality(otId, personality);
};

void LoadSurfPalette(u16 index, u8 palSlot) {
	u16 offset = ((palSlot << 0x14) + 0x1000000) >> 0x10;
	if (IsMonShiny(&gPlayerParty[Var8000]) && gSurfablePokemon[index].shinyPalAddr != 0)
		LoadPalette(gSurfablePokemon[index].shinyPalAddr, offset, 0x20);
	else
		LoadPalette(gSurfablePokemon[index].palAddr, offset, 0x20);
	TintPalette_Switch(palSlot);
};

u8 FindOrLoadSurfPalette(u16 surfIndex, u16 PalTag) {
	u8 PalSlot;
	PalSlot = FindPalRef(PalTypeNPC, PalTag);
	if (PalSlot != 0xFF)
		return PalRefIncreaseCount(PalSlot);
	PalSlot = AddPalRef(PalTypeNPC, PalTag);
	if (PalSlot == 0xFF)
		return PalRefIncreaseCount(0);	
	//LoadNPCPalette(PalTag, PalSlot);
	LoadSurfPalette(surfIndex, PalSlot);
	MaskPaletteIfFadingIn(PalSlot);
	return PalRefIncreaseCount(PalSlot);
};


u16 GetSurfMonSpecies(void) {
    u8 i;
    for (i = 0; i < 6; ++i)
    {
        if (MonHasMove(&gPlayerParty[i], MOVE_SURF))
        {
            u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL);
			Var8000 = i;	// position in party
            return species;
        }
    }
    return 0xFFFF;
};

u16 GetSurfablePokemonSprite(void) {
    u8 i;
	u16 mon;
	
	mon = GetSurfMonSpecies();	//find first party mon with surf
	
	// find species in table
    for (i = 0; i < ARRAY_COUNT(gSurfablePokemon); ++i)
    {
		if (mon == gSurfablePokemon[i].species)
            return i;
    }
    return 0xFFFF;
};


u8 LoadSurfOverworldPalette(u16 index) {
	if (index == 0xFFFF || gSurfablePokemon[index].palAddr == 0)
		return FindOrLoadNPCPalette(0x1100);	//surf blob pal tag
	else
		return FindOrLoadSurfPalette(index, gSurfablePokemon[index].overworldGfx->paletteTag);
		// assuming pal tags are unique, the shiny tag is the same as the regular
};



void CreateOverlaySprite(u16 index) {
    u8 overlaySprite;
    struct Sprite *sprite;

    overlaySprite = CreateSpriteAtEnd(gSurfablePokemon[index].overlayGfx, gFieldEffectArguments[0], gFieldEffectArguments[1], 0x96);

    if (overlaySprite != MAX_SPRITES)
    {
        sprite = &gSprites[overlaySprite];
        sprite->coordOffsetEnabled = TRUE;
		
		u8 palSlot = LoadSurfOverworldPalette(index);	// same hook loc for SetPalSurf
		sprite->oam.paletteNum |= palSlot;			
		
        sprite->data[2] = gFieldEffectArguments[2];
        sprite->data[3] = 0;
        sprite->data[6] = -1;
        sprite->data[7] = -1;
        sprite->oam.priority = 1;
    }
    BindObj(overlaySprite, 1);
};


void MoveCoords(u8 direction, s16 *x, s16 *y) {
    *x += sDirectionToVectors[direction].x;
    *y += sDirectionToVectors[direction].y;
};


void SyncSurfSprite(struct EventObject *eventObject, struct Sprite *sprite)
{
    u8 i;
    s16 x = eventObject->currentCoords.x;
    s16 y = eventObject->currentCoords.y;
    s32 spriteY = sprite->pos2.y;

    if (spriteY == 0 && (x != sprite->data[6] || y != sprite->data[7]))
    {
        sprite->data[5] = spriteY;
        sprite->data[6] = x;
        sprite->data[7] = y;
        for (i = DIR_SOUTH; i <= DIR_EAST; ++i, x = sprite->data[6], y = sprite->data[7])
        {
            MoveCoords(i, &x, &y);
            if (MapGridGetZCoordAt(x, y) == 3)
            {
                sprite->data[5] ++;
                break;
            }
        }
    }
};



/*
// sub_80DC4E0 in fire red
sub_8155640 in pokeem
*/
u8 SpriteDataCheck(struct Sprite *sprite) {
    return (sprite->data[0] & 0xF0) >> 4;
};


u8 surfBlobDirectionAnims[] = {
	[DIR_NONE] = 0,
	[DIR_SOUTH] = 0,
	[DIR_NORTH] = 1,
	[DIR_WEST] = 2,
	[DIR_EAST] = 3,
	[DIR_SOUTHWEST] = 0,
	[DIR_SOUTHEAST] = 0,
	[DIR_NORTHWEST] = 1,
	[DIR_NORTHEAST] = 1,
};

void SyncDirection(struct EventObject *eventObject, struct Sprite *sprite) {
    if (SpriteDataCheck(sprite) == 0)
        StartSpriteAnimIfDifferent(sprite, surfBlobDirectionAnims[eventObject->movementDirection]);
};



void UpdateSurfMonOverlay(struct Sprite *sprite)
{
    struct EventObject *eventObject;
    struct Sprite *linkedSprite;

    eventObject = &gEventObjects[gPlayerAvatar->eventObjectId];
    linkedSprite = &gSprites[eventObject->spriteId];

    SyncDirection(eventObject, sprite);	//SynchroniseSurfAnim
    SyncSurfSprite(eventObject, sprite);

    if (linkedSprite->animNum < 20)
    {
        sprite->pos1.x = linkedSprite->pos1.x;
        sprite->pos1.y = linkedSprite->pos1.y + 8;
        sprite->pos2.y = linkedSprite->pos2.y;
    }
    if (!(gPlayerAvatar->flags & PLAYER_AVATAR_FLAG_SURFING))
        DestroySprite(sprite);
};



// main func - 080dc3d0
u32 CreateSurfablePokemonSprite(void) {
    u8 spriteId;
    struct Sprite *sprite;

    LogCoordsCameraRelative(&gFieldEffectArguments[0], &gFieldEffectArguments[1], 8, 8);
    u16 sSurfSpeciesIdx = GetSurfablePokemonSprite();
	
    if (sSurfSpeciesIdx != 0xFFFF)
    {
        spriteId = CreateSpriteAtEnd(gSurfablePokemon[sSurfSpeciesIdx].overworldGfx, gFieldEffectArguments[0], gFieldEffectArguments[1], 0x96);
        
		if (gSurfablePokemon[sSurfSpeciesIdx].overlayGfx != 0)
            CreateOverlaySprite(sSurfSpeciesIdx);
    }
    else	// Create surf blob
        spriteId = CreateSpriteAtEnd(gFieldEffectObjectTemplatePointers[7], gFieldEffectArguments[0], gFieldEffectArguments[1], 0x96);

    if (spriteId != MAX_SPRITES)
    {
        sprite = &gSprites[spriteId];
        sprite->coordOffsetEnabled = TRUE;
		
		u8 palSlot = LoadSurfOverworldPalette(sSurfSpeciesIdx);	// same hook loc for SetPalSurf
		sprite->oam.paletteNum |= palSlot;
		
        sprite->data[2] = gFieldEffectArguments[2];
        sprite->data[3] = 0;
        sprite->data[6] = -1;
        sprite->data[7] = -1;
    }
    FieldEffectActiveListRemove(FLDEFF_SURF_BLOB);
    return spriteId;
};



