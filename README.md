# dynamic_surf_ows
-Add the unique surfing overworlds feature from pokeemerald to Fire Red (see https://github.com/Slawter666/pokeemerald/tree/surfable/src)

-credit to slawter for the original idea

NOTE: this feauture is currently missing a lot of necessary artwork. Any pokemon without art will default to the original surf blob. As art is added, either by the user or community, you can change this in src/surf_mons.h by changing the elements `.paletteTag` and `.images` of `const struct SpriteTemplate s[species]Overworld`

Adding New Species:

if you want to add new species that can learn surf, follow these steps. I will use Popplio as an example
1. make the sprite (I would recommend trying to use an in-game palette such as the default hero/surf blob palette)

2. add the indexed .png file to graphics/. Eg. `popplio.png`

3. add the following at the top of `surf_mons.h`
```
extern const u32 popplioTiles[];
extern const u16 popplioPal[];
extern const u16 popplioShinyPal[];
```

4. add `PAL_TAG_POPPLIO_SURF` to the list of palettes if you are using a custom palette

5. copy one of the overworld frame templates as so:
```
const struct SpriteFrameImage gSurfingOverworldPicTable_Popplio[] = {
    overworld_frame(&popplioTiles[0], 4, 4, 1),
    overworld_frame(&popplioTiles[0], 4, 4, 0),
    overworld_frame(&popplioTiles[0], 4, 4, 3),
    overworld_frame(&popplioTiles[0], 4, 4, 2),
    overworld_frame(&popplioTiles[0], 4, 4, 5),
    overworld_frame(&popplioTiles[0], 4, 4, 4),
    overworld_frame(&popplioTiles[0], 4, 4, 7),
    overworld_frame(&popplioTiles[0], 4, 4, 6),
};
```

6. If your sprite has any body parts you want covering the player (they should be part of the image, frames 6-12):
```
const struct SpriteFrameImage gSurfingOverlayPicTable_Popplio[] = {
    overworld_frame(&popplioTiles[0], 4, 4, 7),
    overworld_frame(&popplioTiles[0], 4, 4, 6),
    overworld_frame(&popplioTiles[0], 4, 4, 9),
    overworld_frame(&popplioTiles[0], 4, 4, 8),
    overworld_frame(&popplioTiles[0], 4, 4, 11),
    overworld_frame(&popplioTiles[0], 4, 4, 10),
};
```

7. Construct a sprite template for the main overworld sprite as so:
```const struct SpriteTemplate sPopplioOverworld = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_POPPLIO_SURF,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverworldPicTable_Popplio,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfBlobFieldEffect,
};
```

8. If you have overlay frames:
```
const struct SpriteTemplate sPopplioOverlay = {
	.tileTag = 0xFFFF,
	.paletteTag = PAL_TAG_POPPLIO_SURF,
	.oam = gEventObjectBaseOam_32x32,
	.anims = gSurfablePokemonAnimTable,
	.images = gSurfingOverlayPicTable_Popplio,
	.affineAnims = gDummySpriteAffineAnimTable,
	.callback = UpdateSurfMonOverlay,
};
```

9. Finally, add the following to the gSurfablePokemon structure at the bottom of the page. Note that I changed the structures from the pokeemerald source so you shouldn't have to worry about matching indices, since there is one main structure that defines the surfable pokemon
```
{
  .species = SPECIES_POPPLIO,
  .shinyPalTag = PAL_TAG_POPPLIO_SHINY,    // if it exists, 0 otherwise
  .overworldGfx = sLaprasOverword,
  .overlayGfx = sLaprasOverlay,
},
```

10. You will have to manually add the palette to the NPC palette table after compiling, which is one reason I recommend using existing palettes (and it saves space :D). The table has a format of [palette pointer] [palette tag] 00 00. The table must end in FF 11 00 00 00 00 00 00, but otherwise the tags do not need to be in order, as the game searches through each table entry for the palette tag.
