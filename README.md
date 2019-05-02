# dynamic_surf_ows

=====================================================

What Is This?

This is a feature, originally from pokeem, (see https://github.com/Slawter666/pokeemerald/tree/surfable/src), to have the surfing sprite dynamically change based on the first party pokemon or selected pokemon from the menu.

It has, in my opinion, a few improved features:

1. One master structure for all species data, so worrying about matching indexes is no longer an issue

2. The palette is directly loaded from an address rather than using a tag. A tag is still needed for tracking the palette, but there is no need to add the palette to the NPC palette table. This means you only need one tag for all surf sprites, since only one will exist at the same time.

=====================================================

Important Notes:

1. This includes the dynamic overworld palette hack, as it removes the need to worry about matching palettes, and is generally just awesome. See https://github.com/Navenatox/DynamicOverworldPalettes for more details. The original source code has been modified to call some of these functions, so removing the file if you've already added this feature will not do. There is ample free-space in FR so I suggest just leaving it be unless you know what you are doing.

2. This feauture is currently missing a lot of necessary artwork. Any pokemon without art will default to the original surf blob. As art is added, either by the user or community, you can change this in src/surf_mons.h by changing the elements `.paletteTag` and `.images` of `const struct SpriteTemplate s[species]Overworld`

3. Fire Red likes vertical images, and as such the sprites have to have all their frames lined up vertically, as opposed to the pokeem images that are layered horizontally. While annoying, changing the frame ordering isn't a big deal, and I hope this won't stand in the way of community art being shared.

=====================================================

How To Compile:

1. add `rom.gba` to the main directory

2. open `scripts/make.py` and modify `OFFSET_TO_PUT` to wherever you'd like to insert this code, as well as `SEARCH_FREE_SPACE` to `True` if you'd like to search for free space from said offset.

3a. download devkitPro. see this tutorial for more information: https://www.pokecommunity.com/showpost.php?p=8825585&postcount=96

3b. download python 3.7.2 (make sure `add to path` is checked), then type `python scripts/make.py` into the terminal to compile the code and images.

4. `test.gba` will be added to the folder, and the offsets will be located in `offsets.ini`



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
`const struct SpriteTemplate sPopplioOverworld = surf_template(PAL_TAG_SURF_NEW, gSurfingOverworldPicTable_Popplio, UpdateSurfBlobFieldEffect)`

8. If you have overlay frames:
`const struct SpriteTemplate sPopplioOverlay = surf_template(PAL_TAG_SURF_NEW, gSurfingOverworldPicTable_Popplio, UpdateSurfMonOverlay)`

If there are no overlay frames, you can simply set the `gSurfablePokemon.overlayGfx` element to 0 (see Step 9). The palette tag is included in the surf_template define to allow a user to allow each sprite a unique palette tag.

9. Finally, add the following to the gSurfablePokemon structure at the bottom of the page. Note that I changed the structures from the pokeemerald source so you shouldn't have to worry about matching indices, since there is one main structure that defines the surfable pokemon
```
{
  .species = SPECIES_POPPLIO,
  .palAddr = &popplioPal[0],
  .shinyPalAddr = &popplioShinyPal[0],	// or 0 if it doesn't exist
  .overworldGfx = &sPopplioOverword,
  .overlayGfx = &sPopplioOverlay,	// or 0 if it doesn't exist
},
```

