#include "surf_mons.h"

extern u8 FindOrLoadNPCPalette(u16 PalTag);
extern void UpdateSurfMonOverlay(struct Sprite *sprite);

/*
void DoLoadSpritePalette(const u16 *src, u16 paletteOffset)
{
    LoadPalette(src, paletteOffset + 0x100, 32);
}

u8 LoadSpritePalette(const struct SpritePalette *palette)
{
    u8 index = IndexOfSpritePaletteTag(palette->tag);

    if (index != 0xFF)
        return index;

    index = IndexOfSpritePaletteTag(0xFFFF);

    if (index == 0xFF)
    {
        return 0xFF;
    }
    else
    {
        sSpritePaletteTags[index] = palette->tag;
        DoLoadSpritePalette(palette->data, index * 16);
        return index;
    }
}
*/


u16 GetSurfMonSpecies(void) {
    u8 i;
    for (i = 0; i < 6; ++i)
    {
        if (MonHasMove(&gPlayerParty[i], MOVE_SURF))
        {
            u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL);
            return species;
        }
    }
    return 0xFFFF;
};

u16 GetSurfablePokemonSprite(void) {
    u8 i;
	u16 mon;
	
	if (gBrmData->selectedPoke != 7)
		mon = GetMonData(&gPlayerParty[gBrmData->selectedPoke], MON_DATA_SPECIES, NULL);	// selected from party menu
	else
		mon = GetSurfMonSpecies();	//find first party mon with surf
	
	// find species in table
    for (i = 0; i < ARRAY_COUNT(gSurfablePokemon); ++i)
    {
		if (mon == gSurfablePokemon[i].species)
            return i;
    }
    return 0xFFFF;
};

/*
bool8 IsMonShiny(struct Pokemon *mon) {
    u32 otId = GetMonData(mon, MON_DATA_OT_ID, 0);
    u32 personality = GetMonData(mon, MON_DATA_PERSONALITY, 0);
    return IsShinyOtIdPersonality(otId, personality);
};
*/

u8 LoadSurfOverworldPalette(u16 index) {
	if (index == 0xFFFF)
		return FindOrLoadNPCPalette(0x1100);	//surf blob pal tag
	else
	/*{
		if (IsMonShiny)
			return FindOrLoadNPCPalette(gSurfablePokemon[index].shinyPalTag);
		else
			return FindOrLoadNPCPalette(gSurfablePokemon[index].palTag);
		
	}*/
		return FindOrLoadNPCPalette(gSurfablePokemon[index].overworldGfx->paletteTag);
};



void CreateOverlaySprite(u16 index) {
    u8 overlaySprite;
    struct Sprite *sprite;

    overlaySprite = CreateSpriteAtEnd(gSurfablePokemon[index].overlayGfx, gFieldEffectArguments[0], gFieldEffectArguments[1], 0x96);

    if (overlaySprite != MAX_SPRITES)
    {
        sprite = &gSprites[overlaySprite];
        sprite->coordOffsetEnabled = TRUE;
        sprite->data[2] = gFieldEffectArguments[2];
		
		u8 palSlot = LoadSurfOverworldPalette(index);	// same hook loc for SetPalSurf
		sprite->oam.paletteNum |= palSlot;		
		
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



